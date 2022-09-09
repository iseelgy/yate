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

#define MSG_YATE			"engine.yate"
#define MSG_YATESHOP_CMD	"Yateshop.cmd"


//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
//  JNI 回调命令

#define CB_YATE_CMD									1
#define CB_VTOKON_CMD								10		// 
#define CB_ANDOID_SYS_INFO							20		// 
#define CB_VOIP_AUDIO								30		// 
#define CB_IDCARD_HANDLE							40		// 

#define ZMQ_SKF										60		// 
#define ZMQ_SKF_CALLBACK							70		// 
#define ZMQ_SKF_NOTIFY								80		// 
#define ZMQ_SKF_VTOKEN								90		// Skf 
#define ZMQ_WORKSHOP								99


#define ZMQ_GOAL									100
#define CB_LOG_FILE_WRITE							0x80000000  // 


#ifdef CB_YATE_CMD
	const static int ARG1_YATE_ENGINE_START = 1;   // 
	const static int ARG1_YATE_SKF_DEVICE_INSTALL = 10;   //
	const static int ARG1_YATE_SKF_DEVICE_REMOVE = 20;   //
#endif


#define ZMQ_SKF										60		// Skf 
#define ZMQ_SKF_CALLBACK							70		// Skf服务回调客户端
#define ZMQ_SKF_NOTIFY								80		// Skf服务通知
#define ZMQ_SKF_VTOKEN								90		// Skf 
#define ZMQ_WORKSHOP								99


#ifdef ZMQ_WORKSHOP

	#define SKF_CLEINT_TYPE_UNKNOW					0	//   
	#define SKF_CLEINT_TYPE_SKF						1	// CSP    
	#define SKF_CLEINT_TYPE_TOOL					2   // 管理工具
	#define SKF_CLEINT_TYPE_DEBUG					3   // 调试工具

	const static int ARG1_ZMQ_REGISTER = 10;	// 注册
	const static int ARG1_ZMQ_UNREGISTER = 20;	// 注消

#endif


#define CMD_OP_TEST					1		
#define CMD_OP_REMOVE_CLIENT		100  // 移除客户端
#define CMD_OP_CLIENT_TIMER			101
#define CMD_OP_CALLBACK_ERROR		200
#define CMD_OP_DEVICE_CHANGE		300
#define CMD_OP_DEVICE_CHANGE_TIMEOUT	301
#define CMD_OP_CHECK_DEVICE			400


const static int ARG1_SKF_NOTIFY_STOP = 10;	// 服务关闭
const static int ARG1_SKF_NOTIFY_DEVICE_CHANGE = 20;	// 设备变化

const static int ARG1_SKF_NOTIFY_DELETE_APP = 30;	// 删除应用

const static int ARG1_SKF_NOTIFY_CREATE_CONT = 40;	// 生成容器
const static int ARG1_SKF_NOTIFY_DELETE_CONT = 50;	// 删除容器

const static int ARG1_SKF_NOTIFY_CREATE_KEYPARE = 60;	// 生成密钥对
const static int ARG1_SKF_NOTIFY_IMPORT_CERT = 70;	// 导入证书


//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
// ΢
// 微盾 命令范围
#ifdef CB_VTOKON_CMD

	const static int ARG1_VTOKEN_HAS_DETECT = 6000;   
	const static int ARG1_VTOKEN_ENUM_DEVICE = 6001;  
	const static int ARG1_VTOKEN_OPEN_DEVICE = 6002;
	const static int ARG1_VTOKEN_CLOSE_DEVICE = 6003;
	const static int ARG1_VTOKEN_GET_SN = 6004;
	const static int ARG1_VTOKEN_LOG_IN = 6005;
	const static int ARG1_VTOKEN_LOG_OUT = 6006;
	const static int ARG1_VTOKEN_CREATE_CONT = 6006;
	const static int ARG1_VTOKEN_DELETE_CONT = 6007;
	const static int ARG1_VTOKEN_WRITE_CONT = 6008;
	const static int ARG1_VTOKEN_READ_CONT = 6009;
	const static int ARG1_VTOKEN_IMPORT_CERT = 6010;
	const static int ARG1_VTOKEN_EXPORT_CERT = 6011;
	const static int ARG1_VTOKEN_CLEAR_CERT = 6012;
	const static int ARG1_VTOKEN_CLOSE_SM4 = 6013;
	const static int ARG1_VTOKEN_OPEN_SM4 = 6014;
	const static int ARG1_VTOKEN_DELETE_SM4 = 6015;
	const static int ARG1_VTOKEN_CREATE_SM4 = 6016;
	const static int ARG1_VTOKEN_IMPORT_SM4 = 6017;
	const static int ARG1_VTOKEN_EXPORT_SM4 = 6018;
	const static int ARG1_VTOKEN_GET_FIRMWARE = 6019;
	const static int ARG1_VTOKEN_LIST_SM4 = 6020;


	const static int ARG1_VTOKEN_DEVICE_REMOVE = 7000;
	const static int ARG1_VTOKEN_SCAN_START = 7001;
	const static int ARG1_VTOKEN_SCAN_END = 7002;
	const static int ARG1_VTOKEN_DEVICE_GET = 7003;

	const static int ARG1_VTOKEN_START_STEP = 8000; 
	const static int ARG1_VTOKEN_START_SHOW = 8001;


#endif

//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
#ifdef CB_ANDOID_SYS_INFO

	const static int ARG1_ASYS_INFO_GET_SIM			= 10;	// 
	const static int ARG1_ASYS_INFO_GET_DEVICEID	= 11;	
	const static int ARG1_ASYS_APP_REGISTER			= 20;

#endif

//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
// 
#ifdef CB_VOIP_AUDIO

	const static int ARG1_AUDIO_OBJECT_NEW 			= 5000;   //
	const static int ARG1_AUDIO_OBJECT_DELETE 		= 5001;   //
	const static int ARG1_AUDIO_OBJECT_SET 			= 5002;   //
	const static int ARG1_AUDIO_OBJECT_START 		= 5003;   //
	const static int ARG1_AUDIO_OBJECT_STOP 		= 5004;   //
	const static int ARG1_AUDIO_OBJECT_READ 		= 5005;   //
	const static int ARG1_AUDIO_OBJECT_WRITE 		= 5006;   //

#endif

//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
// CB_IDCARD_HANDLE

// 

#ifdef CB_IDCARD_HANDLE

	const static int ARG1_IDCARD_QUERY_RESULT		= 1000;   // 



#endif



//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================


#ifdef ZMQ_GOAL
	const static int ARG1_GOAL_LOAD_CERT			= 1;
	const static int ARG1_GOAL_PRIVATE_OP			= 2;
	const static int ARG1_GOAL_SM1					= 3;
#endif



//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
// JNI 
#define ID_ZDTOKEN_GET_INFO 							1	// 
#define ID_ZDTOKEN_SET_INFO 							2	// 
#define ID_DEVLOPMENT_TEST								3	// 


#define CMD_YATE_MESSAGE								10000	// 
#define CMD_VTOKEN_HANDLE								10020	// 
#define CMD_SUNELAN										10030	// 
#define CMD_VOIP										10040	// 

const static int ARG1_ID_INFO_VERSION 					= 10;  	// 
const static int ARG1_ID_INFO_IDCARD_SERVER				= 20;	// 
const static int ARG1_ID_INFO_PSAM_SERVER				= 30;	// 
const static int ARG1_ID_INFO_CARD_ID					= 40;
const static int ARG1_ID_INFO_DEVICE_INFO				= 41;	// 
const static int ARG1_ID_INFO_CARD_PUBKEY				= 50;
const static int ARG1_ID_INFO_CARD_SIGN					= 51;
const static int ARG1_ID_INFO_DEVICE_ID					= 60;


#ifdef CMD_YATE_MESSAGE

	const static int ARG1_YATE_MESSAGE_LOG_BROADCAST	= 1;   // 
	const static int ARG1_YATE_MESSAGE_SIM_STATE_CHANGE = 100;   // 
	const static int ARG1_YATE_MESSAGE_LOCATION_CHANGE =  200;   // 

#endif


#ifdef ID_DEVLOPMENT_TEST
	const static int ARG1_ID_DEV_TEST_YATE 				= 10;  
	const static int ARG1_ID_DEV_TEST_ZMQ 				= 20;
	const static int ARG1_ID_DEV_TEST_JNI 				= 30;
	const static int ARG1_ID_DEV_TEST_VTOKEN			= 40;
#endif

#ifdef CMD_VTOKEN_HANDLE

	const static int ARG1_CMD_VTOKEN_INFO				= 100;
	const static int ARG1_CMD_VTOKEN_OPEN				= 1000;
	const static int ARG1_CMD_VTOKEN_CLOSE				= 1020;
	const static int ARG1_CMD_VTOKEN_SN					= 1030;
	const static int ARG1_CMD_VTOKEN_CERT				= 1040;
	const static int ARG1_CMD_VTOKEN_SIGN				= 1050;

	const static int ARG1_CMD_VTOKEN_SCAN_START			= 10014;

	const static int ARG1_CMD_VTOKEN_NOTIFY_ADD			= 20000;
	const static int ARG1_CMD_VTOKEN_NOTIFY_REMOVE		= 20001;

	const static int ARG1_CMD_VTOKEN_INSE_INSTALL		= 30000;
	const static int ARG1_CMD_VTOKEN_TEE_AUTH			= 40000;


#endif


#ifdef CMD_SUNELAN
	const static int ARG1_CMD_SUNELAN_OPEN				= 0;
	const static int ARG1_CMD_SUNELAN_CLOSE				= 1;
	const static int ARG1_CMD_SUNELAN_STATE				= 2;
	const static int ARG1_CMD_SUNELAN_POWER_OFF			= 3;
	const static int ARG1_CMD_SUNELAN_WAKEUP			= 4;
	const static int ARG1_CMD_SUNELAN_OPEN_115200		= 10;

	const static int ARG1_CMD_SUNELAN_COS_VERSION		= 20;
	const static int ARG1_CMD_SUNELAN_DOWNLOAD_COS		= 21;
	const static int ARG1_CMD_SUNELAN_SET_COS_MODE		= 22;
	const static int ARG1_CMD_SUNELAN_WAKEUP_STATE		= 23;

	const static int ARG1_CMD_SUNELAN_  = 0;
	const static int ARG1_CMD_SUNELAN_SKF_VERSION		= 201;
	const static int ARG1_CMD_SUNELAN_CARD_INFO			= 202;
	const static int ARG1_CMD_SUNELAN_USER_NAME			= 203;
	const static int ARG1_CMD_SUNELAN_CARD_ID			= 204;
	const static int ARG1_CMD_SUNELAN_PIN_CHECK			= 205;
	const static int ARG1_CMD_SUNELAN_PIN_CHANGE		= 206;
	const static int ARG1_CMD_SUNELAN_ROOT_SIGN  		= 207;
	const static int ARG1_CMD_SUNELAN_ROOT_VERIFY  		= 208;
	const static int ARG1_CMD_SUNELAN_ROOT_PUBLIC  		= 209;
	const static int ARG1_CMD_SUNELAN_GET_RAND  		= 210;

	const static int ARG1_CMD_SUNELAN_MANU		  		= 220;
	const static int ARG1_CMD_SUNELAN_VOIP_SETKEY  		= 230;
	const static int ARG1_CMD_SUNELAN_VOIP_CLEARKEY 	= 240;
	const static int ARG1_CMD_SUNELAN_VOIP_KEYSTREAM	= 250;

#endif


#ifdef CMD_VOIP


#endif 



//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
// ΢
#ifdef ZMQ_SKF

	const static int ZMQ_SKF_ARG1_0000 = 0;

	const static int ARG1_SKF_WaitForDevEvent		= 10 ;
	const static int ARG1_SKF_CancelWaitForDevEvent	= 20 ;
	const static int ARG1_SKF_EnumDev				= 30 ;
	const static int ARG1_SKF_ConnectDev			= 40 ;
	const static int ARG1_SKF_DisConnectDev			= 50 ;
	const static int ARG1_SKF_GetDevState			= 60 ;
	const static int ARG1_SKF_SetLabel				= 70 ;
	const static int ARG1_SKF_GetDevInfo			= 80 ;
	const static int ARG1_SKF_LockDev				= 90 ;
	const static int ARG1_SKF_UnlockDev				= 100 ;
	const static int ARG1_SKF_Transmit				= 110 ;

	const static int ARG1_SKF_ChangeDevAuthKey		= 120 ;
	const static int ARG1_SKF_DevAuth				= 130 ;
	const static int ARG1_SKF_ChangePIN				= 140 ;
	const static int ARG1_SKF_GetPINInfo			= 150 ;
	const static int ARG1_SKF_VerifyPIN				= 160 ;
	const static int ARG1_SKF_UnblockPIN			= 170 ;
	const static int ARG1_SKF_ClearSecureState		= 180 ;

	const static int ARG1_SKF_CreateApplication		= 190 ;
	const static int ARG1_SKF_EnumApplication		= 200 ;
	const static int ARG1_SKF_DeleteApplication		= 210 ;
	const static int ARG1_SKF_OpenApplication		= 220 ;
	const static int ARG1_SKF_CloseApplication		= 230 ;

	const static int ARG1_SKF_CreateFile			= 240 ;
	const static int ARG1_SKF_DeleteFile			= 250 ;
	const static int ARG1_SKF_EnumFiles				= 260 ;
	const static int ARG1_SKF_GetFileInfo			= 270 ;
	const static int ARG1_SKF_ReadFile				= 280 ;
	const static int ARG1_SKF_WriteFile				= 290 ;

	const static int ARG1_SKF_CreateContainer		= 300 ;
	const static int ARG1_SKF_DeleteContainer		= 310 ;
	const static int ARG1_SKF_OpenContainer			= 320 ;
	const static int ARG1_SKF_CloseContainer		= 330 ;
	const static int ARG1_SKF_EnumContainer			= 340 ;
	const static int ARG1_SKF_GetContainerType		= 350 ;
	const static int ARG1_SKF_ImportCertificate		= 360 ;
	const static int ARG1_SKF_ExportCertificate		= 370 ;
	const static int ARG1_SKF_DeleteCertificate		= 380 ;
	const static int ARG1_SKF_GetKeyType			= 390 ;
	const static int ARG1_SKF_GenRandom				= 400 ;
	const static int ARG1_SKF_GenExtRSAKey			= 410 ;
	const static int ARG1_SKF_GenRSAKeyPair			= 420 ;
	const static int ARG1_SKF_GenExchRSAKeyPair		= 430 ;
	const static int ARG1_SKF_ImportRSAKeyPair		= 440 ;
	const static int ARG1_SKF_RSASignData			= 450 ;
	const static int ARG1_SKF_RSAVerify				= 460 ;
	const static int ARG1_SKF_RSAExportSessionKey	= 470 ;
	const static int ARG1_SKF_RSAExportSessionKeyEx	= 471 ;
	const static int ARG1_SKF_ExtRSAPubKeyOperation = 480 ;
	const static int ARG1_SKF_ExtRSAPriKeyOperation = 490 ;
	const static int ARG1_SKF_GenECCKeyPair			= 500 ;
	const static int ARG1_SKF_ImportECCKeyPair		= 510 ;
	const static int ARG1_SKF_ECCSignData			= 520 ;
	const static int ARG1_SKF_ECCVerify				= 530 ;
	const static int ARG1_SKF_ECCExportSessionKey	= 540 ;
	const static int ARG1_SKF_ECCExportSessionKeyEx	= 541 ;
	const static int ARG1_SKF_ExtECCEncrypt			= 550 ;
	const static int ARG1_SKF_ExtECCDecrypt			= 560 ;
	const static int ARG1_SKF_ExtECCSign			= 570 ;
	const static int ARG1_SKF_ExtECCVerify			= 580 ;
	const static int ARG1_SKF_GenerateAgreementDataWithECC = 590 ;
	const static int ARG1_SKF_GenerateAgreementDataAndKeyWithECC=600;
	const static int ARG1_SKF_GenerateKeyWithECC	=610;
	const static int ARG1_SKF_ExportPublicKey		= 620 ;
	const static int ARG1_SKF_ImportRSAKeyPairVen	= 630 ;
	const static int ARG1_SKF_RSAExchSignData		= 640 ;
	const static int ARG1_SKF_ImportSessionKey		= 650 ;
	const static int ARG1_SKF_SetSymmKey			= 660 ;
	const static int ARG1_SKF_EncryptInit			= 700 ;
	const static int ARG1_SKF_Encrypt				= 710 ;
	const static int ARG1_SKF_EncryptUpdate			= 720 ;
	const static int ARG1_SKF_EncryptFinal			= 730 ;
	const static int ARG1_SKF_DecryptInit			= 740 ;
	const static int ARG1_SKF_Decrypt				= 750 ;
	const static int ARG1_SKF_DecryptUpdate			= 760 ;
	const static int ARG1_SKF_DecryptFinal			= 770 ;
	const static int ARG1_SKF_DigestInit			= 780 ;
	const static int ARG1_SKF_Digest				= 790 ;
	const static int ARG1_SKF_DigestUpdate			= 800 ;
	const static int ARG1_SKF_DigestFinal			= 810 ;
	const static int ARG1_SKF_MacInit				= 820 ;
	const static int ARG1_SKF_Mac					= 830 ;
	const static int ARG1_SKF_MacUpdate				= 840 ;
	const static int ARG1_SKF_MacFinal				= 850 ;
	const static int ARG1_SKF_CloseHandle			= 860 ;
	const static int ARG1_SKF_Manu					= 870 ;

#endif



//=====================================================================================================================
//=====================================================================================================================
//=====================================================================================================================
//  int IDcard( int cmd, String&result, String& info, String& server, String& idcard )
//  IDcard 

const static int IDCARD_CMD_DN_QUERY_BASE	= 1;	// 
const static int IDCARD_CMD_DN_QUERY_ALL	= 2;  // ͨ
const static int IDCARD_CMD_DN_QUERY_PSAM	= 3;  // ͨ
const static int IDCARD_CMD_REPORT			= 1002;  // 

#endif

