/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

/******************************************************************

 iLBC Speech Coder ANSI-C Source Code

 WebRtcIlbcfix_Encode.h

******************************************************************/

#ifndef WEBRTC_MODULES_AUDIO_CODING_CODECS_ILBC_MAIN_SOURCE_ENCODE_H_
#define WEBRTC_MODULES_AUDIO_CODING_CODECS_ILBC_MAIN_SOURCE_ENCODE_H_

#include "defines.h"

/*----------------------------------------------------------------*
 *  main encoder function
 *---------------------------------------------------------------*/

void WebRtcIlbcfix_EncodeImpl(
    WebRtc_UWord16 *bytes,     /* (o) encoded data bits iLBC */
    WebRtc_Word16 *block,     /* (i) speech vector to encode */
    iLBC_Enc_Inst_t *iLBCenc_inst /* (i/o) the general encoder
                                           state */
                          );

#endif
