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


#include "Aux_type.h"
//#include "Aux_cmd_define.h"

#include <yatecbase.h>
#include <yatephone.h>


#define ShowLevel TelEngine::DebugNote

#define TE TelEngine

void YATE_API show_data(unsigned char * data, int size);
void YATE_API show_data_x(unsigned char * data, int size);

bool YATE_API b64_decode(const char * in, TelEngine::DataBlock& dest);
bool YATE_API b64_decode(void * in, int size, TelEngine::DataBlock& dest);

void YATE_API logStartup();

void YATE_API logShutdown();

void YATE_API logShowDemo();

void YATE_API yateLog(const char * file, const char * function, int line, const char * Category, int level, const char * fmt ...);

//#define log(category, level, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, level, fmt, ## args)
#define logFail(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugFail, fmt, ## args)
#define logTest(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugTest, fmt, ## args)
#define logGoOn(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugGoOn, fmt, ## args)
#define logConf(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugConf, fmt, ## args)
#define logStub(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugStub, fmt, ## args)
#define logWarn(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugWarn, fmt, ## args)
#define logMild(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugMild, fmt, ## args)
#define logCall(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugCall, fmt, ## args)
#define logNote(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugNote, fmt, ## args)
#define logInfo(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugInfo, fmt, ## args)
#define logDebug(category, fmt, args) yateLog(__FILE__, __FUNCTION__, __LINE__, category, TelEngine::DebugAll, fmt, ## args)


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




#endif