#include "Aux_yate_hal.h"


namespace {	 // 使用匿名空间

using namespace TelEngine;

//===============================
// 类定义

class MyPlugin : public Module
{
public:

	enum Relay {
		Start = Private << 1,
	};

	MyPlugin() : Module("demo")	{
		// Output("Loaded module demomodule");
		m_init = false;
	}


	~MyPlugin() {

	}

	virtual void initialize(void);
	virtual bool received(Message& msg, int id);

	void onEngineStart();
	bool unload();

private:

	bool m_init;

protected:

};

INIT_PLUGIN(MyPlugin);

//class 
class MyHandler : public MessageHandler
{
public:
	MyHandler(unsigned int prio = 100);
	virtual bool received(Message& msg);
};


//===============================
// 变量定义
static Configuration s_cfg;


//===============================
// 功能实现



void MyPlugin::initialize()
{
	Debug(this, DebugInfo, "Initializing module demo");

	s_cfg = Engine::configFile("demo");

	if (!m_init) {

		m_init = true;

		installRelay(Halt);
		installRelay(Stop);
		installRelay(Status);
		installRelay(Start, "engine.start");
	}

}


void MyPlugin::onEngineStart()
{
}


bool MyPlugin::received(Message& msg, int id)
{
	if (id == Halt) {
		Debug(this, DebugInfo, "MyPlugin::received - Halt");
	}
	else if (Start == id) {
		onEngineStart();
		return false;
	}
	else if (Status == id) {
		Debug(this, DebugInfo, "MyPlugin::received - Status");
	}
	else if (Stop == id) {
		Debug(this, DebugInfo, "MyPlugin::received - Stop");
	}
	return Module::received(msg, id);
}

bool MyPlugin::unload()
{
	return true;
}


}

/*
 *
 *	支持模块动态卸载接口
 *
*/
UNLOAD_PLUGIN(unloadNow)
{
	if (unloadNow) {
		// 动态卸载模块
		if (!__plugin.unload()) {
			return false;
		}
		return true;
	}
	else {
		// 检测是否能够动态卸载
		return true;
	}
}

