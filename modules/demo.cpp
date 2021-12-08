#include "Aux_yate_hal.h"


namespace {	 // ʹ�������ռ�

using namespace TelEngine;

//===============================
// �ඨ��

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
// ��������
static Configuration s_cfg;


//===============================
// ����ʵ��



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
 *	֧��ģ�鶯̬ж�ؽӿ�
 *
*/
UNLOAD_PLUGIN(unloadNow)
{
	if (unloadNow) {
		// ��̬ж��ģ��
		if (!__plugin.unload()) {
			return false;
		}
		return true;
	}
	else {
		// ����Ƿ��ܹ���̬ж��
		return true;
	}
}

