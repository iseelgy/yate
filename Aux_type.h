#ifndef _AUX_TYPE_H_
#define _AUX_TYPE_H_

#include <limits.h>
#include <sys/types.h>
#include <stddef.h>
#include <errno.h>
#include <stdarg.h>

#include <sys/types.h>

#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <memory>
#include <stdint.h>


#ifndef BOOL
typedef int                 BOOL;
#endif

#ifndef U8
#define U8 unsigned char
#endif

#ifndef S8
#define S8 char
#endif


#ifndef U16
#define U16 unsigned short
#endif

#ifndef S16
#define S16 short
#endif


#ifndef U32
#define U32 unsigned int
#endif

#ifndef S32
#define S32 int
#endif


#ifndef S64
#define S64 long long
#endif

#ifndef U64
#define U64 unsigned long long
#endif


#ifndef u8
#define u8 unsigned char 
#endif

#ifndef s8
#define s8 char
#endif

#ifndef u16
#define u16 unsigned short
#endif

#ifndef s16
#define s16 short
#endif

#ifndef u32
#define u32 unsigned int
#endif

#ifndef s32
#define s32 int
#endif

#ifndef s64
#define s64 long long
#endif

#ifndef u64
#define u64 unsigned long long
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
#endif


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef BIT
#define BIT(n) (1L<<(n))
#endif


#define _DEFINE_SHARED_PTR(x) \
    typedef x* x##_np;     \
    typedef std::shared_ptr<x> x##_sp;     \
    typedef std::list<x##_np> x##_npl;    \
    typedef std::vector<x##_np> x##_npv;    \
    typedef std::list<x##_np>::iterator x##_npli;    \
    typedef std::vector<x##_np>::iterator x##_npvi;    \
    typedef std::list<x##_sp> x##_spl;    \
    typedef std::vector<x##_sp> x##_spv;    \
    typedef std::list<x##_sp>::iterator x##_spli;    \
    typedef std::vector<x##_sp>::iterator x##_spvi;    \



_DEFINE_SHARED_PTR(U8)
_DEFINE_SHARED_PTR(S8)


#endif 