/**

	https://www.cnblogs.com/lisuyun/p/5744548.html


在使用MFC库开发程序时，我非常喜欢MFC框架中的内存泄漏诊断机制，它的确能很好地帮助我们查找出内存泄漏。
可是链接了MFC库也使得生成的可执行文件大了许多，这个没什么负面影响。
最可怕的是如果仅为了使用内存诊断机制，而带来了链接库冲突的麻烦。我也是在遇到这个问题时，才写出了一个简易的内存诊断机制。
一般大家都误以为这些内存泄漏的检测功能是由MFC提供的，其实不然。MFC只是封装和利用了MS C-Runtime Library的Debug Function。
非MFC程序也可以利用MS C-Runtime Library的Debug Function加入内存泄漏的检测功能。MS C-Runtime Library在实现malloc/free，strdup等函数时已经内建了内存泄漏的检测功能。

*/


#pragma once


#include <crtdbg.h>
#include <malloc.h>

#ifdef _DEBUG_MSVC_NEW_
	#define THIS_FILE __FILE__
	//添加宏定义,使用malloc分配内存也能检测到内存泄漏
	#define   malloc(s)   _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)

	//设置使用new分配内存能检测到内存泄漏
	void* _cdecl operator new(size_t nSize, int nType, const char* lpszFileName, int nLine);

	//覆盖operator new 和 delete 运算符,
	void* _cdecl operator new(size_t nSize, const char* lpszFileName, int nLine);
	void* __cdecl operator new[](size_t nSize, const char* lpszFileName, int nLine);
	void __cdecl operator delete(void* p);
	void __cdecl operator delete[](void* p);

	#define DEBUG_NEW new(THIS_FILE, __LINE__)
#else
	#define DEBUG_NEW new
#endif  //_DEBUG


//mfc的afx.h头文件中关于new覆盖的定义
// Memory tracking allocation

//void* AFX_CDECL operator new(size_t nSize, LPCSTR lpszFileName, int nLine);
//#define DEBUG_NEW new(THIS_FILE, __LINE__)
//void AFX_CDECL operator delete(void* p, LPCSTR lpszFileName, int nLine);
//
//void * __cdecl operator new[](size_t);
//void* __cdecl operator new[](size_t nSize, LPCSTR lpszFileName, int nLine);
//void __cdecl operator delete[](void* p, LPCSTR lpszFileName, int nLine);
//void __cdecl operator delete[](void *);

