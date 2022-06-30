#include "Aux_yate_hal.h"


bool b64_decode(const char * in, TelEngine::DataBlock& dest)
{
	TelEngine::Base64 b64Decode((U8 *)in, strlen(in));
	return b64Decode.decode(dest);
}

void show_data(void * data, int size)
{
	int i;
	std::string info;
	char show[64];
	u8* buf = (u8*)data;
	for (i = 0; i < size; i++) {
		if ((i % 16) == 0) {
			info += "\r\n""        ";
		}
		::sprintf(show, "%02X ", buf[i]);
		info += show;
	}
	info += "\r\n";
	TE::Output( "%s", info.c_str() );
}

void show_data_x(void * data, int size)
{
	int i;
	std::string info;
	char show[64];
	u8 * buf = (u8*)data;
	for (i = 0; i < size; i++) {
		if ((i % 16) == 0) {
			info += "\r\n""        ";
		}
		::sprintf(show, "0x%02X, ", buf[i]);
		info += show;
	}
	info += "\r\n";
	TE::Output("%s", info.c_str());
}


#define strtok_r( _s, _sep, _lasts ) (*(_lasts) = strtok( (_s),(_sep)))

Aux_cmd_line::Aux_cmd_line(void)
{
	m_argc = 0;
	m_argv = 0;
}


Aux_cmd_line::~Aux_cmd_line(void)
{
	clear();
}


void Aux_cmd_line::clear()
{
	int i;
	for (i = 0; i < m_argc; i++) {
		delete m_argv[i];
	}
	delete m_argv;
	m_argc = 0;
	m_argv = 0;
}


int Aux_cmd_line::set(int argc, char ** argv)
{
	int i, len;

	clear();
	m_argv = new char *[argc];
	for (i = 0; i < argc; i++) {
		len = strlen(argv[i]) + 2;
		m_argv[i] = new char[len];
		strcpy(m_argv[i], argv[i]);
	}
	m_argc = argc;
	return 0;
}


int Aux_cmd_line::format(const char * cmd)
{
	#define MAX_ARGV_NUM 1024
	#define COMMAND_LINE_LENGTH 64*1024

	int argc;           /* My argc value */
	char *argv[MAX_ARGV_NUM+6];     /* Collected argv[] array */
	char * buf;      /* Command buffer */

	char *svptr;        /* strtok_r() updates this */
	char *s;            /* Returned strtok_r() pointer */
	//int x;              /* Work index */  
	const char delim[] = " \t\n"; /* Delimiters */
	int cmdLen = strlen(cmd); //ÃüÁîÐÐ³¤¶È  
	if (cmdLen > COMMAND_LINE_LENGTH - 1) return -1;

	buf = new char[cmdLen + 8];

	memcpy(buf, cmd, cmdLen);  /* Fake a command */
	*(buf + cmdLen) = 0;
	s = strtok_r(buf, delim, &svptr); /* First call */
	argc = 0;                    /* Start on my_argv[0] */
	while (s != 0){
		if (argc >= MAX_ARGV_NUM) {
			delete buf;
			return -1;
		}
		argv[argc++] = s;     /* Save argv[] value */
		s = strtok_r(NULL, delim, &svptr); /* Parse next tkn */
	}
	argv[argc] = 0;
	set(argc, argv);
	delete buf;

	return 0;
}


void logStartup()
{

	//logFail("111", "%s", "Hi");

}

void logShutdown()
{


}

void logShowDemo()
{


}

void yateLog(const char * file, const char * function, int line, const char * category, int level, const char * fmt ...)
{
	if (level > TE::debugLevel()) {
		return;
	}

#ifdef WIN32 


#else


#endif

	// TelEngine::Debug(TelEngine::DebugFail, "%s, %s, %d", file, function, line);


}

