// URG04Kit.HPP
//
// Tool kit for URG04 laser range finder, C++ version.
// by Lin, Jingyu, linjy02@hotmail.com, 2019.9
//
// 使用方法：
// 1. 创建URG04Device对象。
// 2. 用StartScan()选择设备所在串口并启动激光测距仪。串口可以直接指定，或用SearchURG04Device()查询。
//    用Close()关闭启动的激光测距仪。URG04Device对象结束时自动关闭启动的激光测距仪。
// 3. 用ReadScanAngle()读取测距数据对应的扫描角数组。该数组不会
// 4. 定时（周期100ms）调用ReadRange()读取测距数据及其时戳。测距数据未去除错误和噪声。
// 5. 进行测距数据处理：如果距离值太小（<20mm）说明超出测距范围或面对镜面。
// 6. 如果需要可以用RangeToMap()将测距数据转换为二维地图以便显示。
//

// 修改记录
// 20190907：合并串口功能，不再需要WinComPort.dll。
//

#ifndef URG04Kit_HPP
#define URG04Kit_HPP

class __declspec(dllexport) URG04Device
{
public:
	URG04Device();
	~URG04Device();

	/************************ 查询设备 ************************/

	// 功能：查询连接的激光测距仪。
	// 返回值：系统中激光测距仪的数量。
	// 说明：拔插设备后需要再次调用此函数。有可能误将其它USB设备识别为激光测距仪。
	static int SearchURG04Device();

	// 功能：读取激光测距仪的名称和串口号。调用SearchURG04Device()后有效。
	// 输入：idx - 激光测距仪的序号。
	// 输出：ComNo - 串口端口号（即COMx中的x）。无效串口的端口号为-1。
	// 返回值：名称字符串指针。NULL表示序号超过设备总数。
	static char* GetURG04Port(int idx, int& ComNo);

	// 功能：获得系统中激光测距仪的总数。如果未调用过SearchURG04Device()则返回-1。无激光测距仪则返回0。
	static int GetURG04Total();


	/************************ 开关设备 ************************/

	// 功能：启动指定串口上的URG激光测距仪。成功后持续采集测距数据，每组数据采集时间为100ms。
	//       用ReadRange()可以随时读取测距数据。
	// 输入：ComNo - 激光测距仪的串口号。
	// 输出：无。
	// 返回值：1表示成功启动激光测距仪。0表示非激光测距仪。
	int StartScan(int ComNo);

	// 功能：关闭URG激光测距仪，停止采集测距数据。
	// 说明：URG04Device对象结束时自动调用此函数。
	void Close();

	/************************ 读取数据 ************************/

	// 功能：读取测距数据对应的扫描角（rad）及其数量szTheta。如果theta为NULL则仅返回扫描角的数量szTheta。
	// 输入：theta[] - 扫描角缓冲区，大小为szTheta。
	// 输出：theta[] - 扫描角数组。
	// 返回值：扫描角的数量szTheta（即测距数据的数量），等效于扫描的范围。
	// 说明：测距仪将一周（360°）分为1024步，因此扫描角的单位为360°/1024=0.3516°。
	//       测距仪左右对称扫描。定义测距仪正前方的扫描角为0，逆时针方向为正向。
	//       因此szTheta=0是最右边，szTheta/2-1是正前方，szTheta-1是最左边。
	int ReadScanAngle(double* theta);

	// 功能：读取测距数据（m）及其时戳和数量szRange。如果缓冲区为NULL则不返回相应数据。
	// 输入：range[], range0[] - 测距数据缓冲区，大小为szRange。
	//       timeStamp, timeStamp0 - 用于获取时戳。
	// 输出：range[], range0[] - 最新与上次的测距数据，每个扫描角对应一个距离值。
	//       *timeStamp, *timeStamp0 - 测距数据的时戳。
	// 返回值：测距数据的数量szRange，等于扫描角的数量。
	// 说明：测距仪将一周（360°）分为1024步，因此扫描角的单位为360°/1024=0.3516°。
	//       测距仪左右对称扫描。定义正前方的扫描角为0，逆时针方向为正向。
	//       因此szRange=0是最右边，szRange/2是正前方，szRange-1是最左边。
	int ReadRange(double* range, int* timeStamp, double* range0 = NULL, int* timeStamp0 = NULL);

	/************************ 设备信息 ************************/

	// 功能：判断设备是否启动。
	// 返回值：返回1表示已启动，0表示已关闭。
	int IsActive();

	// 功能：获得启动的设备的串口端口号。返回-1表示未启动。
	int GetActiveURGComNo();

	// 功能：访问数据记录状态。log文件为urgRange.txt。
	void SetDataLog(int bLog);
	int GetDataLog();

	/************************ 辅助功能 ************************/

	// 功能：将测距数据转换为二维地图。
	// 输入：map[mapRow][mapCol] - 二维地图缓冲区。r_front - 地图中心到地图顶部正中的物理距离（m），用于尺度变换。
	//       steering - 转向角（弧度），地图正上方为0（北），逆时针为正，顺时针为负。
	//       range[szRange] - 用ReadRange()读取的测距数据或经过处理的测距数据（m）。szRange=-1表示用系统缺省值。
	//       stepAngle - 扫描角步长（弧度）。stepAngle=-1表示用系统缺省值。
	// 输出：map - 二维地图，像素逐行排列，每个像素取值0表示阻塞，0xFF表示无遮挡。
	// 说明：测距仪位于地图中心，r_front对应半个地图（mapRow/2）的距离。
	//       调用ReadScanAngle()可以获得szRange值，并且相邻的扫描角之差就是stepAngle。
	static void RangeToMap(unsigned char *map, int mapRow, int mapCol, double r_front, double steering,
		double* range, int szRange = -1, double stepAngle = -1);

private:
	char privatedata[24]; // 24 bytes for x64, 12 bytes for Win32
};
#endif // #ifndef URG04Kit_HPP
