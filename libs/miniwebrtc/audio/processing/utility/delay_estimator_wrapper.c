/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "delay_estimator_wrapper.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "delay_estimator.h"

typedef union {
  float float_;
  int32_t int32_;
} SpectrumType;

typedef struct {
  // Pointers to mean values of spectrum.
  SpectrumType* mean_far_spectrum;
  SpectrumType* mean_near_spectrum;
  // |mean_*_spectrum| initialization indicator.
  int far_spectrum_initialized;
  int near_spectrum_initialized;

  int spectrum_size;

  // Binary spectrum based delay estimator
  BinaryDelayEstimator* binary_handle;
} DelayEstimator;

// Only bit |kBandFirst| through bit |kBandLast| are processed and
// |kBandFirst| - |kBandLast| must be < 32.
static const int kBandFirst = 12;
static const int kBandLast = 43;

static __inline uint32_t SetBit(uint32_t in, int pos) {
  uint32_t mask = (1 << pos);
  uint32_t out = (in | mask);

  return out;
}

// Calculates the mean recursively. Same version as WebRtc_MeanEstimatorFix(),
// but for float.
//
// Inputs:
//    - new_value             : New additional value.
//    - scale                 : Scale for smoothing (should be less than 1.0).
//
// Input/Output:
//    - mean_value            : Pointer to the mean value for updating.
//
static void MeanEstimatorFloat(float new_value,
                               float scale,
                               float* mean_value) {
  assert(scale < 1.0f);
  *mean_value += (new_value - *mean_value) * scale;
}

// Computes the binary spectrum by comparing the input |spectrum| with a
// |threshold_spectrum|. Float and fixed point versions.
//
// Inputs:
//      - spectrum            : Spectrum of which the binary spectrum should be
//                              calculated.
//      - threshold_spectrum  : Threshold spectrum with which the input
//                              spectrum is compared.
// Return:
//      - out                 : Binary spectrum.
//
static uint32_t BinarySpectrumFix(uint16_t* spectrum,
                                  SpectrumType* threshold_spectrum,
                                  int q_domain,
                                  int* threshold_initialized) {
  int i = kBandFirst;
  uint32_t out = 0;

  assert(q_domain < 16);

  if (!(*threshold_initialized)) {
    // Set the |threshold_spectrum| to half the input |spectrum| as starting
    // value. This speeds up the convergence.
    for (i = kBandFirst; i <= kBandLast; i++) {
      if (spectrum[i] > 0) {
        // Convert input spectrum from Q(|q_domain|) to Q15.
        int32_t spectrum_q15 = ((int32_t) spectrum[i]) << (15 - q_domain);
        threshold_spectrum[i].int32_ = (spectrum_q15 >> 1);
        *threshold_initialized = 1;
      }
    }
  }
  for (i = kBandFirst; i <= kBandLast; i++) {
    // Convert input spectrum from Q(|q_domain|) to Q15.
    int32_t spectrum_q15 = ((int32_t) spectrum[i]) << (15 - q_domain);
    // Update the |threshold_spectrum|.
    WebRtc_MeanEstimatorFix(spectrum_q15, 6, &(threshold_spectrum[i].int32_));
    // Convert |spectrum| at current frequency bin to a binary value.
    if (spectrum_q15 > threshold_spectrum[i].int32_) {
      out = SetBit(out, i - kBandFirst);
    }
  }

  return out;
}

static uint32_t BinarySpectrumFloat(float* spectrum,
                                    SpectrumType* threshold_spectrum,
                                    int* threshold_initialized) {
  int i = kBandFirst;
  uint32_t out = 0;
  const float kScale = 1 / 64.0;

  if (!(*threshold_initialized)) {
    // Set the |threshold_spectrum| to half the input |spectrum| as starting
    // value. This speeds up the convergence.
    for (i = kBandFirst; i <= kBandLast; i++) {
      if (spectrum[i] > 0.0f) {
        threshold_spectrum[i].float_ = (spectrum[i] / 2);
        *threshold_initialized = 1;
      }
    }
  }

  for (i = kBandFirst; i <= kBandLast; i++) {
    // Update the |threshold_spectrum|.
    MeanEstimatorFloat(spectrum[i], kScale, &(threshold_spectrum[i].float_));
    // Convert |spectrum| at current frequency bin to a binary value.
    if (spectrum[i] > threshold_spectrum[i].float_) {
      out = SetBit(out, i - kBandFirst);
    }
  }

  return out;
}

int WebRtc_FreeDelayEstimator(void* handle) {
  DelayEstimator* self = (DelayEstimator*) handle;

  if (self == NULL) {
    return -1;
  }

  if (self->mean_far_spectrum != NULL) {
    free(self->mean_far_spectrum);
    self->mean_far_spectrum = NULL;
  }
  if (self->mean_near_spectrum != NULL) {
    free(self->mean_near_spectrum);
    self->mean_near_spectrum = NULL;
  }

  WebRtc_FreeBinaryDelayEstimator(self->binary_handle);

  free(self);

  return 0;
}

int WebRtc_CreateDelayEstimator(void** handle,
                                int spectrum_size,
                                int max_delay,
                                int lookahead) {
  DelayEstimator* self = NULL;

  // Check if the sub band used in the delay estimation is small enough to fit
  // the binary spectra in a uint32_t.
  assert(kBandLast - kBandFirst < 32);

  if (handle == NULL) {
    return -1;
  }
  if (spectrum_size < kBandLast) {
    return -1;
  }

  self = malloc(sizeof(DelayEstimator));
  *handle = self;
  if (self == NULL) {
    return -1;
  }

  self->mean_far_spectrum = NULL;
  self->mean_near_spectrum = NULL;

  // Create binary delay estimator.
  if (WebRtc_CreateBinaryDelayEstimator(&self->binary_handle,
                                        max_delay,
                                        lookahead) != 0) {
    WebRtc_FreeDelayEstimator(self);
    self = NULL;
    return -1;
  }
  // Allocate memory for spectrum buffers.
  self->mean_far_spectrum = malloc(spectrum_size * sizeof(SpectrumType));
  if (self->mean_far_spectrum == NULL) {
    WebRtc_FreeDelayEstimator(self);
    self = NULL;
    return -1;
  }
  self->mean_near_spectrum = malloc(spectrum_size * sizeof(SpectrumType));
  if (self->mean_near_spectrum == NULL) {
    WebRtc_FreeDelayEstimator(self);
    self = NULL;
    return -1;
  }

  self->spectrum_size = spectrum_size;

  return 0;
}

int WebRtc_InitDelayEstimator(void* handle) {
  DelayEstimator* self = (DelayEstimator*) handle;

  if (self == NULL) {
    return -1;
  }

  // Initialize binary delay estimator.
  if (WebRtc_InitBinaryDelayEstimator(self->binary_handle) != 0) {
    return -1;
  }
  // Set averaged far and near end spectra to zero.
  memset(self->mean_far_spectrum, 0,
         sizeof(SpectrumType) * self->spectrum_size);
  memset(self->mean_near_spectrum, 0,
         sizeof(SpectrumType) * self->spectrum_size);
  // Reset initialization indicators.
  self->far_spectrum_initialized = 0;
  self->near_spectrum_initialized = 0;

  return 0;
}

int WebRtc_DelayEstimatorProcessFix(void* handle,
                                    uint16_t* far_spectrum,
                                    uint16_t* near_spectrum,
                                    int spectrum_size,
                                    int far_q,
                                    int near_q) {
  DelayEstimator* self = (DelayEstimator*) handle;
  uint32_t binary_far_spectrum = 0;
  uint32_t binary_near_spectrum = 0;

  if (self == NULL) {
    return -1;
  }
  if (far_spectrum == NULL) {
    // Empty far end spectrum.
    return -1;
  }
  if (near_spectrum == NULL) {
    // Empty near end spectrum.
    return -1;
  }
  if (spectrum_size != self->spectrum_size) {
    // Data sizes don't match.
    return -1;
  }
  if (far_q > 15) {
    // If |far_q| is larger than 15 we cannot guarantee no wrap around.
    return -1;
  }
  if (near_q > 15) {
    // If |near_q| is larger than 15 we cannot guarantee no wrap around.
    return -1;
  }

  // Get binary spectra.
  binary_far_spectrum = BinarySpectrumFix(far_spectrum,
                                          self->mean_far_spectrum,
                                          far_q,
                                          &(self->far_spectrum_initialized));
  binary_near_spectrum = BinarySpectrumFix(near_spectrum,
                                           self->mean_near_spectrum,
                                           near_q,
                                           &(self->near_spectrum_initialized));

  return WebRtc_ProcessBinarySpectrum(self->binary_handle,
                                      binary_far_spectrum,
                                      binary_near_spectrum);
}

int WebRtc_DelayEstimatorProcessFloat(void* handle,
                                      float* far_spectrum,
                                      float* near_spectrum,
                                      int spectrum_size) {
  DelayEstimator* self = (DelayEstimator*) handle;
  uint32_t binary_far_spectrum = 0;
  uint32_t binary_near_spectrum = 0;

  if (self == NULL) {
    return -1;
  }
  if (far_spectrum == NULL) {
    // Empty far end spectrum.
    return -1;
  }
  if (near_spectrum == NULL) {
    // Empty near end spectrum.
    return -1;
  }
  if (spectrum_size != self->spectrum_size) {
    // Data sizes don't match.
    return -1;
  }

  // Get binary spectra.
  binary_far_spectrum = BinarySpectrumFloat(far_spectrum,
                                            self->mean_far_spectrum,
                                            &(self->far_spectrum_initialized));
  binary_near_spectrum = BinarySpectrumFloat(near_spectrum,
                                             self->mean_near_spectrum,
                                             &(self->near_spectrum_initialized));

  return WebRtc_ProcessBinarySpectrum(self->binary_handle,
                                      binary_far_spectrum,
                                      binary_near_spectrum);
}

int WebRtc_last_delay(void* handle) {
  DelayEstimator* self = (DelayEstimator*) handle;

  if (self == NULL) {
    return -1;
  }

  return WebRtc_binary_last_delay(self->binary_handle);
}
