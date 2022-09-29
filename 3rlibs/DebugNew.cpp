//实现文件
//#include "StdAfx.h"
#include <malloc.h>
#include "DebugNew.h"


namespace
{
    class AutoDetectMemory
    {
    public:
        AutoDetectMemory()
        {
#ifdef _DEBUG_MSVC_NEW_
            _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
        }
    };

    static AutoDetectMemory gs_am;

}


void* _cdecl operator new(size_t nSize, const char* lpszFileName, int nLine)
{
    return ::operator new(nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}

void* __cdecl operator new[](size_t nSize, const char* lpszFileName, int nLine)
{
    return ::operator new(nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}

void __cdecl operator delete(void* p)
{
#ifdef _DEBUG_MSVC_NEW_
    _free_dbg(p, _NORMAL_BLOCK);
#else
    free(p);
#endif
}

void __cdecl operator delete[](void* p)
{
    ::operator delete(p);
}

void* __cdecl operator new(size_t nSize, int nType, const char* lpszFileName, int nLine)
{
#ifdef _DEBUG_MSVC_NEW_
    return _malloc_dbg(nSize, nType, lpszFileName, nLine);
#else
    //UNREFERENCED_PARAMETER(nType);
    //UNREFERENCED_PARAMETER(lpszFileName);
    //UNREFERENCED_PARAMETER(nLine);
    return ::operator new(nSize);
#endif
}