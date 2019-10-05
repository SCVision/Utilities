// WinComPort.h
//
// Functions for serial ports on Windows, C version
// by Lin, Jingyu, linjy02@hotmail.com, 2016.3
//
// 可以通过输出函数访问（#include "WinComPort.h"），也可以通过WinComPort对象访问（#include "WinComPort.hpp"）。
// 输出函数使用方法：
// 1. 用ComPortListName()查询串口名称和编号。
// 2. 用ComOpen()打开串口。用ComClose()关闭串口。
// 3. 设置串口：用ComDlgConfig()打开设置对话框；或用ComSetState()/ComGetState()读取和设置串口。
// 4. 收发数据：用ComWrite()通过串口发送数据，用ComRead()读取串口接收到的数据。
//

#ifndef WINCOMPORT_H
#define WINCOMPORT_H

#define WinComPortExport extern "C" __declspec(dllexport)

/************************ 串口查询和开关 ************************/

// 功能：查询设备管理器中串口的名称和编号。
// 输入：ComName[lenComName]是保存串口名称字符串的缓冲区，PortNo[nPortN0]是保存串口编号的数组。
// 输出：串口名称按顺序保存在ComName[lenComName]，多个串口的名称字符串之间用0间隔。
//       串口编号（即COMx中的x）按顺序保存在数组PortNo[nPortNo]中，无效串口的编号为-1。
// 返回值：系统中串口的数量。
// 说明：如果ComName[lenComName]或PortNo[nPortNo]空间不足则获得的相应信息不完整，但是仍然返回正确的串口数量。
WinComPortExport int __stdcall ComPortListName(char* PortName, int lenPortName, int* PortNo, int nPortNo);

// 功能：查询注册表中串口字符串“COMx”，字符串之间用0间隔。
// 输入：PortName[lenPortName]是保存COMx字符串的缓冲区。
// 输出：COMx字符串保存在PortName[lenPortName]，多个串口的字符串之间用0间隔。
// 返回值：系统中串口的数量。
// 说明：如果PortName[lenPortName]空间不足则获得的相应信息不完整，但是仍然返回正确的串口数量。
WinComPortExport int __stdcall ComPortQueryNumber(char* PortName, int lenPortName);

// 功能：打开串口。
// 输入：nPort是串口号，szInBuf和szOutBuf是输入输出缓冲区大小。
// 输出：无。
// 返回值：串口句柄。
// 说明：需要保存串口以供后续调用。
WinComPortExport HANDLE __stdcall ComOpen(int nPort, int szInBuf = 4096, int szOutBuf = 4096);

// 功能：关闭串口。
// 输入：hCom是用ComOpen获得的串口句柄。
// 输出：无。
WinComPortExport void __stdcall ComClose(HANDLE hCom);


/************************ 串口配置 ************************/

// 功能：用串口配置对话框设置串口参数。
// 输入：hCom是用ComOpen获得的串口句柄，pTitle必须是所设置的串口名称（COMx）。
// 输出：串口参数被修改。
WinComPortExport void __stdcall ComDlgConfig(HANDLE hCom, char* pTitle);

// 功能：直接设置串口参数。
// 输入：hCom是用ComOpen获得的串口句柄，其余为参数值（-1表示用默认值）：BaudRate是波特率，ByteSize是每个字节bit数，
//       Parity是奇偶校验位: 0(无)，1(奇)，2(偶)，StopBits是停止位: 0(1 bit), 1(1.5 bits), 2(2 bits)。
// 输出：无。
WinComPortExport void __stdcall ComSetState(HANDLE hCom, int BaudRate = -1, int ByteSize = -1, int Parity = -1, int StopBits = -1);

// 功能：读取串口参数。
// 输入：hCom是用ComOpen获得的串口句柄。
// 输出：BaudRate是波特率，ByteSize是每个字节bit数，Parity是奇偶校验位: 0(无)，1(奇)，2(偶)，
//       StopBits是停止位: 0(1 bit), 1(1.5 bits), 2(2 bits)。
WinComPortExport void __stdcall ComGetState(HANDLE hCom, int& BaudRate, int& ByteSize, int& Parity, int& StopBits);


/************************ 串口读写 ************************/

// 功能：向串口写入数据。
// 输入：hCom是用ComOpen获得的串口句柄，Data[nData]是要写入串口的数据，nData是数据字节数。
// 输出：数据写入串口。
// 返回值：实际写入串口的数据字节数。
// 说明：采用同步操作，即函数返回后没有挂起的后台操作。
WinComPortExport int __stdcall ComWrite(HANDLE hCom, char* Data, int nData);

// 功能：从串口读取数据。
// 输入：hCom是用ComOpen获得的串口句柄，Data[nData]是存放从串口读取的数据的缓冲区，nData是最多可读取的字节数。
// 输出：从串口读取的数据保存在Data[nData]中。
// 返回值：实际从串口读取的数据字节数。
// 说明：采用同步操作，即函数返回后没有挂起的后台操作。
WinComPortExport int __stdcall ComRead(HANDLE hCom, char* Data, int nData);


#endif // #ifndef WINCOMPORT_H
