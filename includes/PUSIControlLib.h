#ifndef __PUSICONTROL_LIB_H
#define __PUSICONTROL_LIB_H

/**************************************宏定义**************************************/


/**************************************类型定义**************************************/
typedef enum
{
	RET_SUCCESS = 0,  //操作成功
	RET_GENERAL_ERR,//通用错误
	RET_LOG_CREATE_FAIL,  //创建LOG文件失败
	RET_COMM_OPEN_FAIL, //打开串口失败
	RET_COMM_NOT_OPEN,  //串口未打开
	RET_COMM_WRITE_TIMEOUT,  //写命令超时
	RET_COMM_READ_TIMEOUT,  //读命令超时
	RET_CMDHEAD_ERROR,   //命令头错误
	RET_RESP_ADDR_ERROR,   //响应地址错误
	RET_CMD_NOTSUPPORT,   //命令不支持
	RET_UPDATEFILE_OPEN_FAIL, //升级文件打开失败
	RET_UPDATE_CRC_ERROR, //升级出现CRC error
	RET_UPDATE_NOT_RESPONSE, //升级过程无响应
}PUSIResult;

typedef enum
{
	PMC006B4 = 0,  //PMC006B4平台
	PMC006B3 = 1,  //PMC006B3平台
	PIO002B2 = 2,   //PIO002B2平台
	PCS0801 = 3,  //PCS0801平台
	PMC006A4 = 4,  //PMC006A4平台
}PLATFORM_TYPE;

#ifdef __cplusplus
extern "C" {
#endif

/**************************************类型定义**************************************/
typedef void (__stdcall *TraceCallback)(TCHAR* strTrace); //跟踪回调函数定义
typedef void (__stdcall *UpdateCallback)(DWORD dwPercent); //升级回调函数定义

/**************************************导出函数声明**************************************/
void __stdcall SetTraceCallback(TraceCallback callback); //设置跟踪回调
void __stdcall SetPlatformType(PLATFORM_TYPE platformType); //设置平台类型
PUSIResult __stdcall SetLogPath(TCHAR* strLogPath); //初始化LOG
PUSIResult __stdcall OpenPort(UINT portnr, DWORD baud); //初始化通信端口
PUSIResult __stdcall SetPortHandle(HANDLE handle); //设置通信端口句柄
PUSIResult __stdcall ClosePort(void); //关闭通信端口
//system control
PUSIResult __stdcall GetFirmwareVersion(DWORD dwAddress,DWORD* pVersion); //获取固件版本
PUSIResult __stdcall SetAddress(DWORD dwAddress,DWORD dwNewAddr); //设置控制器地址
PUSIResult __stdcall EnterBootloader(DWORD dwAddress); //进入bootloader模式
PUSIResult __stdcall SaveAllPara(DWORD dwAddress); //保存所有参数
//GPIO
PUSIResult __stdcall SetIOValue(DWORD dwAddress,DWORD dwIOValue); //设置IO端口的值
PUSIResult __stdcall GetIOValue(DWORD dwAddress,DWORD *pIOValue); //获取IO端口的值
//offline cmd
PUSIResult __stdcall RunOfflineCmd(DWORD dwAddress,DWORD dwPointer); //运行当前用户指令
PUSIResult __stdcall SetCurrentOfflineCmd(DWORD dwAddress,DWORD dwCmd); //设置控制器命令buffer的当前指令
PUSIResult __stdcall GetCurrentOfflineCmd(DWORD dwAddress,DWORD *pCmd); //获取控制器命令buffer的当前指令
PUSIResult __stdcall SetCmdBuffPointer(DWORD dwAddress,DWORD dwPointer); //设置当前命令buffer指针
PUSIResult __stdcall GetCmdBuffPointer(DWORD dwAddress,DWORD *pPointer); //获取当前命令buffer指针
PUSIResult __stdcall SetCmdBuffCmdCount(DWORD dwAddress,DWORD dwCmdCount); //设置命令buffer总数
PUSIResult __stdcall GetCmdBuffCmdCount(DWORD dwAddress,DWORD *pCmdCount); //获取命令buffer总数
PUSIResult __stdcall SetOfflineAutoRun(DWORD dwAddress,BOOL bRun); //设置离线自动运行
PUSIResult __stdcall SaveCmdBuffer(DWORD dwAddress); //保存命令buffer所有指令
//update
void __stdcall SetUpdateCallback(UpdateCallback callback); //设置升级过程回调,用于显示百分比
PUSIResult __stdcall UpdateApplication(DWORD dwAddress,TCHAR *strAppPath); //升级应用

PUSIResult __stdcall GetDebugData(DWORD dwAddress,DWORD *pDebugData);

#ifdef __cplusplus
}
#endif

#endif