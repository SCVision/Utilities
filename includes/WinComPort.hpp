// WinComPort.hpp
//
// Functions for serial ports on Windows, C++ version
// by Lin, Jingyu, linjy02@hotmail.com, 2017.9
//
// 可以通过输出函数访问（#include "WinComPort.h"），也可以通过WinComPort对象访问（#include "WinComPort.hpp"）。
// WinComPort对象使用方法：
// 1. 如果需要，用静态函数SearchPorts()查询系统安装的串口，然后用GetPortName()查看串口名称和编号。
// 2. 创建WinComPort对象。
// 3. 用Open()打开指定串口。用Close()关闭串口。WinComPort对象结束时自动关闭串口。
// 4. 设置串口：用ConfigDlg()打开设置对话框；或用SetState()/GetState()读取和设置串口。
// 5. 收发数据：用Write()通过串口发送数据，用Read()读取串口接收到的数据。
//

#ifndef WINCOMPORT_HPP
#define WINCOMPORT_HPP

class __declspec(dllexport) WinComPort
{
public:
	WinComPort();
	~WinComPort();

	/************************ 串口查询 ************************/

	// 功能：查询设备管理器中的串口。查询后可用GetPortName()读取串口的名称和端口号。
	// 返回值：系统中串口的数量。
	static int __stdcall SearchPorts();

	// 功能：读取设备管理器中串口的名称和端口号。必须先调用SearchPorts()。
	// 输入：idx - 串口序号。
	// 输出：ComNo - 串口端口号（即COMx中的x）。无效串口的端口号为-1。
	// 返回值：串口名称字符串指针。NULL表示序号超过串口数量。
	static char* __stdcall GetPortName(int idx, int& ComNo);

	// 功能：获得系统中串口总数。如果未调用过SearchPorts()则返回-1。无串口则返回0。
	static int __stdcall GetPortTotal();


	/************************ 串口打开和关闭 ************************/

	// 功能：打开串口。
	// 输入：ComNo是串口端口号，szInBuf和szOutBuf是输入输出缓冲区大小，默认为4096字节。
	// 返回值：返回1表示成功，0表示失败。
	int __stdcall Open(int ComNo, int szInBuf = 4096, int szOutBuf = 4096);

	// 功能：关闭串口。
	void __stdcall Close();


	/************************ 串口配置 ************************/

	// 功能：用串口配置对话框设置串口参数。
	// 输入：hCom是用ComOpen获得的串口句柄，pTitle必须是所设置的串口名称（COMx）。
	// 输出：串口参数被修改。
	// 返回值：1表示成功，0表示失败。
	int __stdcall ConfigDlg();

	// 功能：直接设置串口参数。
	// 输入：BaudRate是波特率，ByteSize是每个字节bit数，Parity是奇偶校验位: 0(无)，1(奇)，2(偶)，
	//       StopBits是停止位: 0(1 bit), 1(1.5 bits), 2(2 bits)。参数值-1表示不改变。
	// 输出：无。
	// 返回值：1表示成功，0表示失败。
	int __stdcall SetState(int BaudRate = -1, int ByteSize = -1, int Parity = -1, int StopBits = -1);

	// 功能：读取串口参数。
	// 输入：无。
	// 输出：BaudRate是波特率，ByteSize是每个字节bit数，Parity是奇偶校验位: 0(无)，1(奇)，2(偶)，
	//       StopBits是停止位: 0(1 bit), 1(1.5 bits), 2(2 bits)。
	// 返回值：1表示成功，0表示失败。
	int __stdcall GetState(int& BaudRate, int& ByteSize, int& Parity, int& StopBits);


	/************************ 串口读写 ************************/

	// 功能：向串口写入数据。
	// 输入：Data[nData]是要写入串口的数据。nData是数据字节数。
	// 输出：数据写入串口。
	// 返回值：实际写入串口的数据字节数。
	// 说明：采用同步操作，即函数返回后没有挂起的后台操作。
	int __stdcall Write(char* Data, int nData);

	// 功能：从串口读取数据。
	// 输入：Data[nData]是存放从串口读取的数据的缓冲区。nData是最多可读取的字节数。
	// 输出：从串口读取的数据保存在Data[nData]中。
	// 返回值：实际从串口读取的数据字节数。
	// 说明：采用同步操作，即函数返回后没有挂起的后台操作。
	int __stdcall Read(char* Data, int nData);

	// 功能：清除串口读写缓冲区。
	void __stdcall Purge();

	/************************ 端口信息 ************************/

	// 功能：判断串口是否打开。返回1表示串口已打开，0表示已关闭。
	int __stdcall IsOpened();

	// 功能：获得打开的串口端口号。返回-1表示串口未打开。
	int __stdcall GetActiveComNo();

	// 功能：获得打开的串口句柄。返回NULL表示串口未打开。
	HANDLE __stdcall GetComHandle();

private:
	HANDLE hWinCom;      // handle of opened port
	INT32 ActiveComNo;   // Com No of opened port
};

#endif // #ifndef WINCOMPORT_HPP
