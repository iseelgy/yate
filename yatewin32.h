#ifndef _YATEWIN32_H_
#define _YATEWIN32_H_

#ifdef _WINDOWS

#include <windows.h>
#include <io.h>
#include <direct.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


/**
 * Windows definitions for commonly used types
 */


#ifndef strcasecmp
#define strcasecmp _stricmp
#endif

#ifndef strncasecmp
#define strncasecmp _strnicmp
#endif

#ifndef vsnprintf
#define vsnprintf _vsnprintf
#endif 

#ifndef snprintf
#define snprintf _snprintf
#endif

#define strdup _strdup
#define strtoll _strtoi64
#define strtoull _strtoui64
#define open _open
#define dup2 _dup2
#define read _read
#define write _write
#define close _close
#define getpid _getpid
#define chdir _chdir
#define mkdir(p,m) _mkdir(p)
#define unlink _unlink
#define llabs _abs64

#define O_RDWR   _O_RDWR
#define O_RDONLY _O_RDONLY
#define O_WRONLY _O_WRONLY
#define O_APPEND _O_APPEND
#define O_BINARY _O_BINARY
#define O_EXCL   _O_EXCL
#define O_CREAT  _O_CREAT
#define O_TRUNC  _O_TRUNC
#define O_NOCTTY 0

#define S_IRUSR _S_IREAD
#define S_IWUSR _S_IWRITE
#define S_IXUSR 0
#define S_IRWXU (_S_IREAD|_S_IWRITE)

#endif


#endif


