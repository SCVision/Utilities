// VideoGrabber.HPP
//
// Video frame grabber for video devices, C++ version.
// V2: Surport access by multiple process.
// by Jingyu Lin, linjy02@hotmail.com, 2019.1
//
// VideoGrabber：用于管理视频设备和获取视频帧。
// 【注】VideoGrabber对象分为设备管理对象和视频帧获取对象。一个视频设备可以关联多个VideoGrabber对象，这些对象可以属于不同的进程，
// 其中可以有多个视频帧获取对象，但只有且必须有一个设备管理对象。一个视频设备如果没有关联设备管理对象则不能启动，无法获取视频帧；
// 如果关联多个设备管理对象则只有一个起作用。所有视频帧获取对象可以同时读取视频帧。
//
// 使用方法如下：
// 1. 首先用静态函数SearchVideoDevices()搜索系统安装的视频设备。
// 2. 创建设备管理对象或视频帧获取对象。
//    2.1 如果需要管理视频设备，则应该为每一个视频设备创建一个设备管理对象，保证每个设备都可以获取视频帧。
//        设备管理对象使用方法如下：
//        2.1.1 创建一个VideoGrabber对象。用Open()关联被管理的视频设备。
//        2.1.2 用Start()启动关联的视频设备的视频流。用Stop()停止关联的视频设备的视频流。用GetRunningState()查看视频流状态。
//        2.1.3 用“设备管理”函数设置关联的视频设备的属性、视频格式，获取视频信息。对于视频采集卡用GetCapturerInfo()查看可用输入端口。
//        2.1.4 用GetActivatedDeviceNo()、GetActivatedDeviceName()查看关联的视频设备编号和名称。
//        2.1.5 不再使用设备时，调用Close()或删除对象将关闭关联的视频设备。
//    2.2 如果需要获取视频帧，则应该创建一个视频帧获取对象。一个视频设备允许关联多个视频帧获取对象，使用方法如下：
//        2.2.1 创建一个VideoGrabber对象。用SelectSourceDevice()选择关联的视频源设备。
//        2.2.2 定时用ReadFrame()获取视频帧及其信息。注意设备管理对象用Start()启动设备后，视频帧获取对象才能用ReadFrame()获得视频帧。
//        2.2.3 用GetSourceDeviceNo()、GetSourceDeviceName()查看关联的视频源设备编号和名称。
// 3. 注意通过此模块获得的名称、信息和图像等指针由对象管理，用户不要主动释放指针。
//

#ifndef VideoGrabber_HPP
#define VideoGrabber_HPP

class __declspec(dllexport) VideoGrabber 
{
public:
	/************************ 设备查询 ************************/

	// 功能：搜索系统安装的所有视频设备。拔插设备后需要调用此函数更新设备列表。
	// 返回值：视频设备总数，0表示搜索失败或无视频设备。
	static int SearchVideoDevices();

	// 功能：取得视频设备总数。调用SearchVideoDevices()后有效。
	// 返回值：视频设备总数。-1表示未调用SearchVideoDevices()。0表示无视频设备。
	static int GetDeviceTotal();

	// 功能：取得视频设备名称。调用SearchVideoDevices()后有效。
	// 输入：DevNo - 设备序号（从0开始）。
	// 返回值：设备名称字符串指针。NULL表示DevNo大于设备总数。
	static char* GetDeviceName(int devNo);

	/************************ 构造函数 ************************/

	VideoGrabber();
	~VideoGrabber();

	/************************ 设备管理 ************************/

	// 功能：设备管理对象关联指定编号的视频设备。之前关联的视频设备被停止视频流并断开。
	// 输入：DevNo - 选中的设备序号（从0开始）。
	//       VideoPinType - 选择视频采集卡的输入端口类型。缺省值为PhysConn_Video_Composite(2)。
	//                      参阅PhysicalConnectorType（头文件末尾说明）。如果指定的设备非视频采集卡，则忽略此参数。
	// 返回值：返回1表示成功，0表示失败。
	// 说明：关联设备后才能启动设备和设置视频格式和属性。
	int Open(int DevNo, int VideoPinType = -1);

	// 功能：停止视频流，断开关联的视频设备和关联的视频源设备。
	// 说明：VideoGrabber对象结束时自动调用此函数。
	void Close();

	// 功能：获得关联的视频设备编号（从0开始）。返回-1表示未关联视频设备。
	int GetActivatedDeviceNo();

	// 功能：获得关联的视频设备名称。返回NULL表示未关联视频设备。
	char* GetActivatedDeviceName();

	// 功能：查询关联的视频设备的视频流状态。
	// 返回值：返回0表示停止，1表示暂停，2表示正常运行，-1表示未关联视频设备，-2表示状态获取失败。
	int GetRunningState();

	// 功能：启动关联的视频设备的视频流。
	// 说明：启动的视频设备不能被其它设备管理对象管理。
	int Start();

	// 功能：停止关联的视频设备的视频流。
	int Stop();

	// 功能：暂停关联的视频设备的视频流。
	int Pause();

	// 功能：打开视频设备属性对话框并设置属性。
	void SetVideoDeviceDlg();

	// 功能：如果当前关联的设备是视频采集卡，则获得其所有输入端口的信息。
	// 返回值：视频采集卡的输入端口信息字符串指针。NULL表示未关联设备或非视频采集卡。
	char* GetCapturerInfo();

	// 功能：读取视频设备所支持的视频格式数量。
	// 返回值：支持的视频格式数量
	int GetVideoFormatTotal();

	// 功能：读取指定编号的自定义视频格式名称。格式名称由格式编号（从1开始）和格式缩写组成。
	// 输入：FormatNo - 视频设备所支持的视频格式编号（从0开始）
	// 输出：无。
	// 返回值：视频格式名称字符串指针。NULL表示失败。
	char* GetVideoFormatName(int FormatNo);

	// 功能：读取指定编号的视频格式的尺寸和信息字符串。
	// 输入：FormatNo - 视频设备所支持的视频格式编号（从0开始）。
	// 输出：Channel -  颜色通道数。Width - 视频宽度。Height - 视频高度。secPerFrame - 每帧秒数。
	// 返回值：视频格式信息字符串指针。NULL表示失败。
	char* GetVideoFormat(int FormatNo, int& Channel, int& Width, int& Height, double& secPerFrame);

	// 功能：读取当前视频格式的尺寸和信息字符串。
	// 输入：无。
	// 输出：Channel -  颜色通道数。Width - 视频宽度。Height - 视频高度。secPerFrame - 每帧秒数。
	// 返回值：视频格式信息字符串指针。NULL表示失败。
	char* GetCurrentVideoFormat(int& Channel, int& Width, int& Height, double& secPerFrame);

	// 功能：设置视频格式为指定编号的视频格式，并获得设置后的视频格式的尺寸。
	// 输入：FormatNo - 视频设备所支持的视频格式编号（从0开始）。
	// 输出：Channel - 颜色通道数。Width - 视频宽度。Height - 视频高度。secPerFrame - 每帧秒数。
	// 返回值：返回1表示成功，0表示失败。
	// 说明：即使格式设置失败可可以得到当前视频格式的尺寸。
	int SetVideoFormat(int FormatNo, int& Channel, int& Width, int& Height, double& secPerFrame);

	/************************ 图像获取 ************************/

	// 功能：视频帧获取对象关联指定的视频设备为视频源。该设备启动后就可以获取图像。可以用Close()取消关联。
	// 输入：DevNo - 选中的设备序号（从0开始）。
	// 返回值：返回1表示成功，0表示失败。
	// 说明：选中的视频源设备必须已经在本进程或其它进程关联一个设备管理对象（调用Open()），否则本函数调用失败。
	int SelectSourceDevice(int DevNo);

	// 功能：获得视频帧来源的设备编号（从0开始）。返回-1表示未选择。
	int GetSourceDeviceNo();

	// 功能：获得视频帧来源的设备名称。返回NULL表示未选择视频源设备。
	char* GetSourceDeviceName();

	// 功能：从关联的视频源读取一个视频帧。
	// 输入：Dib[szDib] - 帧缓冲区。
	// 输出：Dib[] - 视频帧点阵。szFrame - 视频帧帧字节数。secStamp - 帧的时戳（秒）。
	//       Channel - 颜色通道数。Width - 视频宽度。Height - 视频高度。secPerFrame - 每帧秒数。
	// 返回值：返回1表示成功，0表示失败。
	// 说明：1）关联的视频源必须存在一个调用Start()启动该设备的设备管理对象，ReadFrame()才能获得实时的图像帧。
	//       2）如果帧缓冲区空间不足（szDib<szFrame），则不获取视频帧，但仍然可以得到视频信息，包括所需字节数szFrame。
	//       3）Channel是视频设备输出的颜色通道数，而Dib中获取的视频帧的颜色通道数总是3（24bit）。
	int ReadFrame(BYTE* Dib, int szDib, int& szFrame, double& secStamp, int& Channel, int& Width, int& Height, double& secPerFrame);

private:
	BYTE privatedata[96]; 
};

#endif // #ifndef VideoGrabber_HPP

//typedef enum tagPhysicalConnectorType
//{
//	PhysConn_Video_Tuner = 1,
//	PhysConn_Video_Composite = (PhysConn_Video_Tuner + 1),
//	PhysConn_Video_SVideo = (PhysConn_Video_Composite + 1),
//	PhysConn_Video_RGB = (PhysConn_Video_SVideo + 1),
//	PhysConn_Video_YRYBY = (PhysConn_Video_RGB + 1),
//	PhysConn_Video_SerialDigital = (PhysConn_Video_YRYBY + 1),
//	PhysConn_Video_ParallelDigital = (PhysConn_Video_SerialDigital + 1),
//	PhysConn_Video_SCSI = (PhysConn_Video_ParallelDigital + 1),
//	PhysConn_Video_AUX = (PhysConn_Video_SCSI + 1),
//	PhysConn_Video_1394 = (PhysConn_Video_AUX + 1),
//	PhysConn_Video_USB = (PhysConn_Video_1394 + 1),
//	PhysConn_Video_VideoDecoder = (PhysConn_Video_USB + 1),
//	PhysConn_Video_VideoEncoder = (PhysConn_Video_VideoDecoder + 1),
//	PhysConn_Video_SCART = (PhysConn_Video_VideoEncoder + 1),
//	PhysConn_Video_Black = (PhysConn_Video_SCART + 1), // 15
//	PhysConn_Audio_Tuner = 0x1000,
//	PhysConn_Audio_Line = (PhysConn_Audio_Tuner + 1),
//	PhysConn_Audio_Mic = (PhysConn_Audio_Line + 1),
//	PhysConn_Audio_AESDigital = (PhysConn_Audio_Mic + 1),
//	PhysConn_Audio_SPDIFDigital = (PhysConn_Audio_AESDigital + 1),
//	PhysConn_Audio_SCSI = (PhysConn_Audio_SPDIFDigital + 1),
//	PhysConn_Audio_AUX = (PhysConn_Audio_SCSI + 1),
//	PhysConn_Audio_1394 = (PhysConn_Audio_AUX + 1),
//	PhysConn_Audio_USB = (PhysConn_Audio_1394 + 1),
//	PhysConn_Audio_AudioDecoder = (PhysConn_Audio_USB + 1) // 0x1009
//} 	PhysicalConnectorType;
