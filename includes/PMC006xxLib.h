#ifndef __PMC006XX_LIB_H
#define __PMC006XX_LIB_H

#include "PUSIControlLib.h"

/**************************************宏定义**************************************/
//外部停止
#ifndef EXTSTOP1
#define EXTSTOP1	0x1
#endif

#ifndef EXTSTOP2
#define EXTSTOP2	0x2
#endif

#ifdef __cplusplus
extern "C" {
#endif
/**************************************类型定义**************************************/


/**************************************导出函数声明**************************************/
PUSIResult __stdcall SetVelocityMode(DWORD dwAddress,BOOL bVelocityMode); //设置速度模式
PUSIResult __stdcall StartStep(DWORD dwAddress,DWORD dwStepNum); //启动步进
PUSIResult __stdcall AbortStep(DWORD dwAddress); //当前步进命令中止	
PUSIResult __stdcall SetMicroStep(DWORD dwAddress,DWORD dwMicroStep); //设置细分数
PUSIResult __stdcall GetMicroStep(DWORD dwAddress,DWORD* pMicroStep); //获取细分数
PUSIResult __stdcall SetMotorPosition(DWORD dwAddress,int nMotorPos); //设置马达位置
PUSIResult __stdcall GetMotorPosition(DWORD dwAddress,int* pMotorPos); //获取马达位置
PUSIResult __stdcall SetDirection(DWORD dwAddress,BOOL bReverse); //设置转动方向
PUSIResult __stdcall SetVelocity(DWORD dwAddress,DWORD dwVelocity); //设置转动速度
PUSIResult __stdcall GetVelocity(DWORD dwAddress,DWORD *pVelocity); //获取转动速度
PUSIResult __stdcall SetVelocityCompFactor(DWORD dwAddress,DWORD dwVelocityComp); //设置速度补偿因子
PUSIResult __stdcall GetVelocityCompFactor(DWORD dwAddress,DWORD *pVelocityComp); //获取速度补偿因子
PUSIResult __stdcall SetStartVelocity(DWORD dwAddress,DWORD dwStartVelocity); //设置启动速度
PUSIResult __stdcall GetStartVelocity(DWORD dwAddress,DWORD *pStartVelocity); //获取启动速度
PUSIResult __stdcall SetStopVelocity(DWORD dwAddress,DWORD dwStopVelocity); //设置停止速度
PUSIResult __stdcall GetStopVelocity(DWORD dwAddress,DWORD *pStopVelocity); //获取停止速度
PUSIResult __stdcall SetAccCoff(DWORD dwAddress,DWORD dwCoff); //设置加速系数
PUSIResult __stdcall GetAccCoff(DWORD dwAddress,DWORD *pCoff);//获取加速系数
PUSIResult __stdcall SetDecCoff(DWORD dwAddress,DWORD dwCoff); //设置减速系数
PUSIResult __stdcall GetDecCoff(DWORD dwAddress,DWORD *pCoff); //获取减速系数
PUSIResult __stdcall SetMaxCurrent(DWORD dwAddress,DWORD dwMaxCurrent); //设置最大电流
PUSIResult __stdcall GetMaxCurrent(DWORD dwAddress,DWORD *pMaxCurrent); //获取最大电流
PUSIResult __stdcall SetCurrCompFactor(DWORD dwAddress,DWORD dwCompFactor); //设置电流补偿因子
PUSIResult __stdcall GetCurrCompFactor(DWORD dwAddress,DWORD *pCompFactor); //获取电流补偿因子
PUSIResult __stdcall SetExtStopEnable(DWORD dwAddress,DWORD dwStopEnable); //设置外部紧急停止使能
PUSIResult __stdcall SetExtStopTrigerMode(DWORD dwAddress,DWORD dwTrigerMode); //设置外部紧急停止触发方式
PUSIResult __stdcall GetExtStopTrigerMode(DWORD dwAddress,DWORD *pTrigerMode); //获取外部紧急停止触发方式
PUSIResult __stdcall ClearExtStop(DWORD dwAddress,DWORD dwExtStop); //清除外部停止
PUSIResult __stdcall SetCurrentAutoDecay(DWORD dwAddress,BOOL bEnable); //设置电流衰减使能
PUSIResult __stdcall SetCurrentDecayFactor(DWORD dwAddress,DWORD dwDecayFactor); //设置电流衰减因子
PUSIResult __stdcall GetCurrentDecayFactor(DWORD dwAddress,DWORD *pDecayFactor); //获取电流衰减因子
PUSIResult __stdcall SetOfflineEnable(DWORD dwAddress,BOOL bEnable); //设置离线使能
PUSIResult __stdcall GetControllerStatus1(DWORD dwAddress,DWORD *pStatus); //获取控制器状态1
PUSIResult __stdcall GetControllerStatus2(DWORD dwAddress,DWORD *pStatus); //获取控制器状态2

PUSIResult __stdcall GetStallConfig(DWORD dwAddress,DWORD *pStallConfig); //获取堵转配置
PUSIResult __stdcall SetStallConfig(DWORD dwAddress,DWORD dwStallConfig); //设置堵转配置
PUSIResult __stdcall GetStallTriger(DWORD dwAddress,DWORD *pTriger); //获取堵转触发值
PUSIResult __stdcall SetStallTriger(DWORD dwAddress,DWORD dwTriger); //设置堵转触发值
PUSIResult __stdcall GetStallTrigerLength(DWORD dwAddress,DWORD *pTrigerLen); //获取堵转触发长度
PUSIResult __stdcall SetStallTrigerLength(DWORD dwAddress,DWORD dwTrigerLen); //设置堵转触发长度
PUSIResult __stdcall ClearStallFlag(DWORD dwAddress); //清除堵转标志位

PUSIResult __stdcall GetADCValue(DWORD dwAddress,DWORD *pADCValue); //获取模拟量

////PMC006A4新增加
//PUSIResult __stdcall SetCoil(DWORD dwAddress,DWORD dwDutyCycle); //设置线圈


#ifdef __cplusplus
}
#endif

#endif
