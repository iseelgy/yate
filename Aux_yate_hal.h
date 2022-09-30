#ifndef _AUX_YATE_HAL_H_
#define _AUX_YATE_HAL_H_


#include <time.h>
#include <cstdlib>
#include <cstring>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <sstream>
#include <memory>


#ifdef _MSC_VER
#include <WinSock2.h>
#include <ws2ipdef.h>
#include <WS2tcpip.h>
#endif


#include "Aux_type.h"
#include "Aux_yate_log.h"

#include <yateclass.h>
#include <yatecbase.h>
#include <yatephone.h>



#define ShowLevel TelEngine::DebugNote

#define TE TelEngine

void YATE_API show_data(void * data, int size);
void YATE_API show_data_x(void * data, int size);

bool YATE_API b64_decode(const char * in, TelEngine::DataBlock& dest);
bool YATE_API b64_decode(void * in, int size, TelEngine::DataBlock& dest);

void YATE_API logStartup();

class YATE_API Aux_cmd_line
{
public:
	Aux_cmd_line(void);
	~Aux_cmd_line(void);

public:

	int m_argc;
	char ** m_argv;

	void clear();

	int set(int argc, char ** argv);

	int format(const char * cmd);

protected:



};


namespace TelEngine {

	
	_DEFINE_SHARED_PTR(File)

	_DEFINE_SHARED_PTR(Stream)

	_DEFINE_SHARED_PTR(String)

	_DEFINE_SHARED_PTR(Socket)

	_DEFINE_SHARED_PTR(NamedList)		

	_DEFINE_SHARED_PTR(Semaphore)
		
	_DEFINE_SHARED_PTR(Mutex)

	_DEFINE_SHARED_PTR(DataBlock)



} // END of namespace TelEngine



#endif