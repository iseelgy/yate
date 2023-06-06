#ifndef _AUX_CMD_DEFINE_H_
#define _AUX_CMD_DEFINE_H_

#ifndef J_RESULT
#define J_RESULT "result"
#endif

#ifndef J_RESULT_ZERO
#define J_RESULT_ZERO "{\"result\":0}"
#endif

#ifndef J_ERROR
#define J_ERROR "error"
#endif

#ifndef J_CODE
#define J_CODE "code"
#endif

#ifndef J_INFO
#define J_INFO "info"
#endif

#ifndef SAR_OK
#define SAR_OK							0x00000000
#endif

#ifndef HRESULT
typedef long HRESULT;
#endif

#ifndef S_OK
#define S_OK                                   ((HRESULT)0L)
#endif


#define JSON_KEY_RPC  "jsonrpc"
#define JSON_KEY_ID  "id"
#define JSON_KEY_CODE  "code"
#define JSON_KEY_METHOD  "method"
#define JSON_KEY_ERROR  "error"
#define JSON_KEY_RESULT  "result"
#define JSON_KEY_MESSAGE  "message"
#define JSON_KEY_ONLINE  "online"
#define JSON_KEY_DATA  "data"
#define JSON_KEY_NOTIFY  "notify"
#define JSON_KEY_PARAMS  "params"

#define JSON_VALUE_VERSION  "2.0"


#define JKEY_DEVICE_TIME "time"
#define JKEY_DEVICE_MODE "mode"
#define JKEY_DEVICE_NAME "name"
#define JKEY_DEVICE_UUID "uuid"
#define JKEY_DEVICE_TYPE "deviceType"
#define JKEY_DEVICE_SN "SN"
#define JKEY_SKF_APPLICATION "Application"


#define MSG_SKF_JSON		"Skf.Json"
#define MSG_SKF_TEST		"Skf.Test"
#define MSG_SKF_CMD			"Skf.Cmd"


#define MSG_ENGINE_START	"engine.start"
#define MSG_ENGINE_STOP		"engine.stop"

#define MSG_YATE			"Yateshop.cmd"
#define MSG_YATESHOP_CMD	"Yateshop.cmd"


//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
//


#endif

