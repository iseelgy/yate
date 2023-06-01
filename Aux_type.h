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

typedef char S8;
typedef unsigned char U8;

typedef short S16;
typedef unsigned short U16;

typedef int S32;
typedef unsigned int U32;

typedef long long S64 ;
typedef unsigned long long U64 ;

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
    typedef std::list<x##_np> x##_npl;    \
    typedef std::vector<x##_np> x##_npv;    \
    typedef std::list<x##_np>::iterator x##_npli;    \
    typedef std::vector<x##_np>::iterator x##_npvi;    \
    typedef std::shared_ptr<x> x##_sp;     \
    typedef std::list<x##_sp> x##_spl;    \
    typedef std::vector<x##_sp> x##_spv;    \
    typedef std::list<x##_sp>::iterator x##_spli;    \
    typedef std::vector<x##_sp>::iterator x##_spvi;    \
    typedef std::unique_ptr<x> x##_up; \
    typedef std::list<x##_up> x##_upl;    \
    typedef std::vector<x##_up> x##_upv;    \
    typedef std::list<x##_up>::iterator x##_upli;    \
    typedef std::vector<x##_up>::iterator x##_upvi;    \



_DEFINE_SHARED_PTR(U8)
_DEFINE_SHARED_PTR(S8)


#endif 