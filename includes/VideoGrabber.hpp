// VideoGrabber.HPP
//
// Video frame grabber for video devices, C++ version.
// V2: Surport access by multiple process.
// writen by Jingyu Lin, linjy02@hotmail.com, 2019.1
// revised by Jingyu Lin, linjy02@hotmail.com, 2021.9
//
/**********************************************************************************************************

VideoGrabber�����ڹ�����Ƶ�豸�ͻ�ȡ��Ƶ֡��
��ע��VideoGrabber�����Ϊ���豸������󡱺͡���Ƶ֡��ȡ���󡱡�ǰ�߿���������ֹͣ�豸����Ƶ����������Ƶ��ʽ��
����ֻ��ֻ�ܻ����Ƶ�豸��Ϣ����Ƶ���ݡ�һ����Ƶ�豸���Թ������VideoGrabber������Щ����������ڲ�ͬ�Ľ��̣�
����ֻ���ұ�����һ���豸�������������Ϊ��Ƶ֡��ȡ����һ����Ƶ�豸���û�й����豸����������޷��������޷�
��ȡ��Ƶ֡�������������豸���������ֻ��һ�������á�������Ƶ֡��ȡ�������ͬʱ��ȡ��Ƶ֡��

ʹ�÷������£�
1. �����þ�̬����SearchVideoDevices()����ϵͳ��װ����Ƶ�豸��
2. �����豸����������Ƶ֡��ȡ����VideoGrabber���󣩡�
   2.1 �����Ҫ������Ƶ�豸����Ӧ��Ϊÿһ����Ƶ�豸����һ���豸������󣬱�֤ÿ���豸�����Ի�ȡ��Ƶ֡��
       �豸�������ʹ�÷������£�
       2.1.1 ����һ��VideoGrabber������Open()�������������Ƶ�豸��
       2.1.2 ��Start()������������Ƶ�豸����Ƶ������Stop()ֹͣ��������Ƶ�豸����Ƶ������GetRunningState()�鿴��Ƶ��״̬��
       2.1.3 �á��豸�����������ù�������Ƶ�豸�����ԡ���Ƶ��ʽ����ȡ��Ƶ��Ϣ��������Ƶ�ɼ�����GetCapturerInfo()�鿴��������˿ڡ�
       2.1.4 ��GetActivatedDeviceNo()��GetActivatedDeviceName()�鿴��������Ƶ�豸��ź����ơ�
       2.1.5 ����ʹ���豸ʱ������Close()��ɾ�����󽫹رչ�������Ƶ�豸��
   2.2 �����Ҫ��ȡ��Ƶ֡����Ӧ�ô���һ����Ƶ֡��ȡ����һ����Ƶ�豸������������Ƶ֡��ȡ����ʹ�÷������£�
       2.2.1 ����һ��VideoGrabber������SelectSourceDevice()ѡ���������ƵԴ�豸��
       2.2.2 ��ʱ��ReadFrame()��ȡ��Ƶ֡������Ϣ��ע���豸���������Start()�����豸����Ƶ֡��ȡ���������ReadFrame()�����Ƶ֡��
       2.2.3 ��GetSourceDeviceNo()��GetSourceDeviceName()�鿴��������ƵԴ�豸��ź����ơ�
3. ע��ͨ����ģ���õ����ơ���Ϣ��ͼ���ָ���ɶ�������û���Ҫ�����ͷ�ָ�롣

**********************************************************************************************************/

#ifndef VideoGrabber_HPP
#define VideoGrabber_HPP

class __declspec(dllexport) VideoGrabber 
{
public:
	/************************ �豸��ѯ ************************/

	// ���ܣ�����ϵͳ��װ��������Ƶ�豸���β��豸����Ҫ���ô˺��������豸�б�
	// ����ֵ����Ƶ�豸������0��ʾ����ʧ�ܻ�����Ƶ�豸��
	static int SearchVideoDevices();

	// ���ܣ�ȡ����Ƶ�豸����������SearchVideoDevices()����Ч��
	// ����ֵ����Ƶ�豸������-1��ʾδ����SearchVideoDevices()��0��ʾ����Ƶ�豸��
	static int GetDeviceTotal();

	// ���ܣ�ȡ����Ƶ�豸���ơ�����SearchVideoDevices()����Ч��
	// ���룺DevNo - �豸��ţ���0��ʼ����
	// ����ֵ���豸�����ַ���ָ�롣NULL��ʾDevNo�����豸������
	static char* GetDeviceName(int devNo);

	/************************ ���캯�� ************************/

	VideoGrabber();
	~VideoGrabber();

	/************************ �豸���� ************************/

	// ���ܣ��豸����������ָ����ŵ���Ƶ�豸��ѡ����Ƶ��ʽ��֮ǰ��������Ƶ�豸��ֹͣ��Ƶ�����Ͽ���
	// ���룺DevNo - ѡ�е��豸��ţ���0��ʼ����FormatNo - ��Ƶ�豸��֧�ֵ���Ƶ��ʽ��ţ���0��ʼ����
	//       VideoPinType - ѡ����Ƶ�ɼ���������˿����͡�ȱʡֵΪPhysConn_Video_Composite(2)��
	//                      ����PhysicalConnectorType��ͷ�ļ�ĩβ˵���������ָ�����豸����Ƶ�ɼ���������Դ˲�����
	// ����ֵ������1��ʾ�ɹ���0��ʾʧ�ܡ�
	// ˵���������豸����������豸���������ԡ���GetCurrentVideoFormat()���Եõ�ʵ����Ƶ��ʽ��Ϣ��
	int Open(int DevNo, int FormatNo = 0, int VideoPinType = -1);

	// ���ܣ�ֹͣ��Ƶ�����Ͽ���������Ƶ�豸�͹�������ƵԴ�豸��
	// ˵����VideoGrabber�������ʱ�Զ����ô˺�����
	void Close();

	// ���ܣ���ù�������Ƶ�豸��ţ���0��ʼ��������-1��ʾδ������Ƶ�豸��
	int GetActivatedDeviceNo();

	// ���ܣ���ù�������Ƶ�豸���ơ�����NULL��ʾδ������Ƶ�豸��
	char* GetActivatedDeviceName();

	// ���ܣ���ѯ��������Ƶ�豸����Ƶ��״̬��
	// ����ֵ������0��ʾֹͣ��1��ʾ��ͣ��2��ʾ�������У�-1��ʾδ������Ƶ�豸��-2��ʾ״̬��ȡʧ�ܡ�
	int GetRunningState();

	// ���ܣ�������������Ƶ�豸����Ƶ����
	// ˵������������Ƶ�豸���ܱ������豸����������
	int Start();

	// ���ܣ�ֹͣ��������Ƶ�豸����Ƶ����
	int Stop();

	// ���ܣ���ͣ��������Ƶ�豸����Ƶ����
	int Pause();

	// ���ܣ�����Ƶ�豸���ԶԻ����������ԡ�
	void SetVideoDeviceDlg();

	// ���ܣ������ǰ�������豸����Ƶ�ɼ�������������������˿ڵ���Ϣ��
	// ����ֵ����Ƶ�ɼ���������˿���Ϣ�ַ���ָ�롣NULL��ʾδ�����豸�����Ƶ�ɼ�����
	char* GetCapturerInfo();

	// ���ܣ���ȡ��Ƶ�豸��֧�ֵ���Ƶ��ʽ������
	// ����ֵ��֧�ֵ���Ƶ��ʽ����
	int GetVideoFormatTotal();

	// ���ܣ���ȡָ����ŵ��Զ�����Ƶ��ʽ���ơ���ʽ�����ɸ�ʽ��ţ���1��ʼ���͸�ʽ��д��ɡ�
	// ���룺FormatNo - ��Ƶ�豸��֧�ֵ���Ƶ��ʽ��ţ���0��ʼ��
	// ������ޡ�
	// ����ֵ����Ƶ��ʽ�����ַ���ָ�롣NULL��ʾʧ�ܡ�
	char* GetVideoFormatName(int FormatNo);

	// ���ܣ���ȡָ����ŵ���Ƶ��ʽ�ĳߴ����Ϣ�ַ�����
	// ���룺FormatNo - ��Ƶ�豸��֧�ֵ���Ƶ��ʽ��ţ���0��ʼ����
	// �����Channel -  ��ɫͨ������Width - ��Ƶ��ȡ�Height - ��Ƶ�߶ȡ�secPerFrame - ÿ֡������
	// ����ֵ����Ƶ��ʽ��Ϣ�ַ���ָ�롣NULL��ʾʧ�ܡ�
	char* GetVideoFormat(int FormatNo, int& Channel, int& Width, int& Height, double& secPerFrame);

	// ���ܣ���ȡ��ǰ��Ƶ��ʽ�ĳߴ����Ϣ�ַ�����
	// ���룺�ޡ�
	// �����Channel -  ��ɫͨ������Width - ��Ƶ��ȡ�Height - ��Ƶ�߶ȡ�secPerFrame - ÿ֡������
	// ����ֵ����Ƶ��ʽ��Ϣ�ַ���ָ�롣NULL��ʾʧ�ܡ�
	char* GetCurrentVideoFormat(int& Channel, int& Width, int& Height, double& secPerFrame);

	//// �ı���Ƶ��ʽ��Ҫ���½���Graph�����Ǿɰ汾��
	//// ���ܣ�������Ƶ��ʽΪָ����ŵ���Ƶ��ʽ����������ú����Ƶ��ʽ�ĳߴ硣
	//// ���룺FormatNo - ��Ƶ�豸��֧�ֵ���Ƶ��ʽ��ţ���0��ʼ����
	//// �����Channel - ��ɫͨ������Width - ��Ƶ��ȡ�Height - ��Ƶ�߶ȡ�secPerFrame - ÿ֡������
	//// ����ֵ������1��ʾ�ɹ���0��ʾʧ�ܡ�
	//// ˵������ʹ��ʽ����ʧ�ܿɿ��Եõ���ǰ��Ƶ��ʽ�ĳߴ硣
	//int SetVideoFormat(int FormatNo, int& Channel, int& Width, int& Height, double& secPerFrame);

	/************************ ͼ���ȡ ************************/

	// ���ܣ���Ƶ֡��ȡ�������ָ������Ƶ�豸Ϊ��ƵԴ�����豸������Ϳ��Ի�ȡͼ�񡣿�����Close()ȡ��������
	// ���룺DevNo - ѡ�е��豸��ţ���0��ʼ����
	// ����ֵ������1��ʾ�ɹ���0��ʾʧ�ܡ�
	// ˵����ѡ�е���ƵԴ�豸�����Ѿ��ڱ����̻��������̹���һ���豸������󣨵���Open()�������򱾺�������ʧ�ܡ�
	int SelectSourceDevice(int DevNo);

	// ���ܣ������Ƶ֡��Դ���豸��ţ���0��ʼ��������-1��ʾδѡ��
	int GetSourceDeviceNo();

	// ���ܣ������Ƶ֡��Դ���豸���ơ�����NULL��ʾδѡ����ƵԴ�豸��
	char* GetSourceDeviceName();

	// ���ܣ��ӹ�������ƵԴ��ȡһ����Ƶ֡��
	// ���룺Dib[szDib] - ֡��������
	// �����Dib[] - ��Ƶ֡����szFrame - ��Ƶ֡֡�ֽ�����secStamp - ֡��ʱ�����룩��
	//       Channel - ��ɫͨ������Width - ��Ƶ��ȡ�Height - ��Ƶ�߶ȡ�secPerFrame - ÿ֡������
	// ����ֵ������1��ʾ�ɹ���0��ʾʧ�ܡ�
	// ˵����1����������ƵԴ�������һ������Start()�������豸���豸�������ReadFrame()���ܻ��ʵʱ��ͼ��֡��
	//       2�����֡�������ռ䲻�㣨szDib<szFrame�����򲻻�ȡ��Ƶ֡������Ȼ���Եõ���Ƶ��Ϣ�����������ֽ���szFrame��
	//       3��Channel����Ƶ�豸�������ɫͨ��������Dib�л�ȡ����Ƶ֡����ɫͨ��������3��24bit����
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
