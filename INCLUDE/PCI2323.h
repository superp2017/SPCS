#ifndef _PCI2323_DEVICE_
#define _PCI2323_DEVICE_

//***********************************************************
// �жϺ���PCI2323_InitDeviceInt�е�INTSelectʹ�õ��ж�ѡ��ѡ��
const long PCI2323_INTSRC_COSINT		= 0x00;	// ʹ��COS�ж�(ʹ�ܸ��жϺ󣬻���ʹ�����������룬ʹ����������������ͨ��������ʹ�ܵ�����������ͨ��״̬�ı�ʱ�������ж�)
const long PCI2323_INTSRC_DI0INT		= 0x01;	// ʹ��DI0�ж�(����������ͨ��0�����ز����ж�), =TRUEʹ��, =FALSE��ֹ
const long PCI2323_INTSRC_DI1INT		= 0x02;	// ʹ��DI1�ж�(����������ͨ��1�����ز����ж�), =TRUEʹ��, =FALSE��ֹ
const long PCI2323_INTSRC_DI01INT		= 0x03;	// ʹ��DI0��DI1�ж�(����������ͨ��0��1�����ز����ж�), =TRUEʹ��, =FALSE��ֹ

// �ж�״̬����
typedef struct _PCI2323_STATUS_INT	// �ж���Ϣ���Ʋ���
{
	LONG bCOSINT;						// COS�����ж�(16·����������״̬�ı�����ж�)
	LONG bDI0INT;						// DI0�����ش����ж�
	LONG bDI1INT;						// DI1�����ش����ж�
} PCI2323_STATUS_INT, *PPCI2323_STATUS_INT;
//######################## �������� #################################
// CreateFileObject���õ��ļ�������ʽ������(��ͨ����ָ��ʵ�ֶ��ַ�ʽ������)
#define PCI2323_modeRead          0x0000			// ֻ���ļ���ʽ
#define PCI2323_modeWrite         0x0001			// ֻд�ļ���ʽ
#define	PCI2323_modeReadWrite     0x0002			// �ȶ���д�ļ���ʽ
#define PCI2323_modeCreate        0x1000			// ����ļ�������Դ������ļ���������ڣ����ؽ����ļ�������0
#define PCI2323_typeText          0x4000			// ���ı���ʽ�����ļ�

//***********************************************************
// ����DA�ĸ�λ��ʽ��������PCI2323_InitDevProDA������ResetMode������
#define PCI2323_RESET_MODE_NEGATIVE        0x0000	// �����ȣ�-5V��-10V...��
#define PCI2323_RESET_MODE_ZERO			   0x0001	// ���(0V)

//***********************************************************
// �û������ӿ�
#ifndef _PCI2323_DRIVER_
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	//######################## ����ͨ�ú��� #################################
	// �����ڱ��豸�����������
	HANDLE DEVAPI FAR PASCAL PCI2323_CreateDevice(int DeviceID = 0);		// �����豸����
	int DEVAPI FAR PASCAL PCI2323_GetDeviceCount(HANDLE hDevice);			// ȡ���豸��̨��
	BOOL DEVAPI FAR PASCAL PCI2323_GetDeviceCurrentID(HANDLE hDevice, PLONG DeviceLgcID, PLONG DevicePhysID);
	BOOL DEVAPI FAR PASCAL PCI2323_ListDeviceDlg(HANDLE hDevice);			// �б�ϵͳ���е����еĸ�PCI�豸
    BOOL DEVAPI FAR PASCAL PCI2323_ReleaseDevice(HANDLE hDevice);			// �ر��豸,��ֹ����,���ͷ���Դ

	//####################### ����I/O����������� #################################
	// �û�����ʹ��WriteRegisterULong��ReadRegisterULong�Ⱥ���ֱ�ӿ��ƼĴ�������I/O
	// �����������ʹ����������������ʡ�£�������Ҫ�����ļĴ��������λ�����ȣ���ֻ
	// ����VB�����Ե����Բ�����ô�򵥵�ʵ�ָ�������ͨ���Ŀ��ơ�
	BOOL DEVAPI FAR PASCAL PCI2323_SetDeviceDO(             // �������������״̬     
										HANDLE hDevice,     // �豸���								        
										BYTE bDOSts[16]);	// ��λ�븴λ״̬״̬(0Ϊ��λ״̬��1Ϊ��λ״̬)

	BOOL DEVAPI FAR PASCAL PCI2323_GetDeviceDI(             // ȡ������������״̬     
										HANDLE hDevice,     // �豸���								        
										BYTE bDISts[16]);	// ����״̬	

	//####################### �жϺ��� #################################
	// ����Ӳ���źŵ�״̬�仯����CPU�����ж��¼�hEventInt��
	BOOL DEVAPI FAR PASCAL PCI2323_InitDeviceInt(			// ��ʼ���ж�
										HANDLE hDevice,     // �豸���	
										HANDLE hEventInt,	// �ж��¼����,����CreateSystemEvent����
										LONG INTSrc);		// �ж�Դѡ��
	BOOL DEVAPI FAR PASCAL PCI2323_SetCOSINTCH(				// ���ж�Դѡ��ΪCOSINTʱ���ò���COS�жϵ�ͨ��
										HANDLE hDevice,		// �豸���	
										BYTE bDIInt[16]);	// 16·DIͨ���ж�ʹ��, =1ʹ��, =0��ֹ
	LONG DEVAPI FAR PASCAL PCI2323_GetDeviceIntCount(HANDLE hDevice);  // ���жϳ�ʼ��������ȡ���жϷ����������Ĵ���
	BOOL DEVAPI FAR PASCAL PCI2323_GetDeviceIntSrc(HANDLE hDevice, PPCI2323_STATUS_INT pINTSts);  // ���жϳ�ʼ��������ȡ���ж�Դ
	BOOL DEVAPI FAR PASCAL PCI2323_ReleaseDeviceInt(HANDLE hDevice); // �ͷ��ж���Դ

	//################# �ڴ�ӳ��Ĵ���ֱ�Ӳ�������д���� ########################
	// �������û��Ա��豸��ֱ�ӡ������⡢���Ͳ㡢�����ӵĿ��ơ�������������
	// ���ƶ�����Ҫ����Ŀ������̺Ϳ���Ч��ʱ�����û�����ʹ����Щ�ӿ�����ʵ�֡�
	BOOL DEVAPI FAR PASCAL PCI2323_GetDeviceAddr(			// ȡ��ָ����ָ���豸�Ĵ���������Ի���ַ�������ַ
									HANDLE hDevice,			// �豸������,����CreateDevice��������
									PULONG LinearAddr,		// ����ָ���Ĵ���������Ե�ַ
									PULONG PhysAddr,		// ����ָ���Ĵ�����������ַ
									int RegisterID = 0);	// �豸�Ĵ������ID�ţ�0-5��

	BOOL DEVAPI FAR PASCAL PCI2323_GetDeviceBar(			// ȡ��ָ����ָ���豸�Ĵ�����BAR��ַ
									HANDLE hDevice,			// �豸������,����CreateDevice��������
									ULONG  pulPCIBar[6]);	// ����PCI BAR���е�ַ,����PCI BAR���ж��ٿ��õ�ַ�뿴Ӳ��˵����

	BOOL DEVAPI FAR PASCAL PCI2323_GetDevVersion(			// ��ȡ�豸�̼�������汾
									HANDLE hDevice,			// �豸������,����CreateDevice��������
									PULONG pulFmwVersion,	// �̼��汾
									PULONG pulDriverVersion);// �����汾

    BOOL DEVAPI FAR PASCAL PCI2323_WriteRegisterByte(		// ��ָ���Ĵ����ռ�λ��д�뵥��������
									HANDLE hDevice,			// �豸������,����CreateDevice��������
									ULONG LinearAddr,		// ָ���Ĵ��������Ի���ַ,������GetDeviceAddr�е�LinearAddr��������ֵ
									ULONG OffsetBytes,		// ��������Ի���ַ����ַ��ƫ��λ��(�ֽ�)
									BYTE Value);			// ��ָ����ַд�뵥�ֽ����ݣ����ַ�����Ի���ַ��ƫ��λ�þ�����

	BOOL DEVAPI FAR PASCAL PCI2323_WriteRegisterWord(		// д˫�ֽ����ݣ�����ͬ�ϣ�
									HANDLE hDevice, 
									ULONG LinearAddr, 
									ULONG OffsetBytes,  
									WORD Value);

	BOOL DEVAPI FAR PASCAL PCI2323_WriteRegisterULong(		// д�Ľ������ݣ�����ͬ�ϣ�
									HANDLE hDevice, 
									ULONG LinearAddr, 
									ULONG OffsetBytes,  
									ULONG Value);

	BYTE DEVAPI FAR PASCAL PCI2323_ReadRegisterByte(		// ���뵥�ֽ����ݣ�����ͬ�ϣ�
									HANDLE hDevice, 
									ULONG LinearAddr, 
									ULONG OffsetBytes);

	WORD DEVAPI FAR PASCAL PCI2323_ReadRegisterWord(		// ����˫�ֽ����ݣ�����ͬ�ϣ�
									HANDLE hDevice, 
									ULONG LinearAddr, 
									ULONG OffsetBytes);

	ULONG DEVAPI FAR PASCAL PCI2323_ReadRegisterULong(		// �������ֽ����ݣ�����ͬ�ϣ�
									HANDLE hDevice, 
									ULONG LinearAddr, 
									ULONG OffsetBytes);

	//################# I/O�˿�ֱ�Ӳ�������д���� ########################
	// �������û��Ա��豸��ֱ�ӡ������⡢���Ͳ㡢�����ӵĿ��ơ�������������
	// ���ƶ�����Ҫ����Ŀ������̺Ϳ���Ч��ʱ�����û�����ʹ����Щ�ӿ�����ʵ�֡�
	// ����Щ������Ҫ�����ڴ�ͳ�豸����ISA���ߡ����ڡ����ڵ��豸���������ڱ�PCI�豸
    BOOL DEVAPI FAR PASCAL PCI2323_WritePortByte(HANDLE hDevice, UINT nPort, BYTE Value);
    BOOL DEVAPI FAR PASCAL PCI2323_WritePortWord(HANDLE hDevice, UINT nPort, WORD Value);
    BOOL DEVAPI FAR PASCAL PCI2323_WritePortULong(HANDLE hDevice, UINT nPort, ULONG Value);

    BYTE DEVAPI FAR PASCAL PCI2323_ReadPortByte(HANDLE hDevice, UINT nPort);
    WORD DEVAPI FAR PASCAL PCI2323_ReadPortWord(HANDLE hDevice, UINT nPort);
    ULONG DEVAPI FAR PASCAL PCI2323_ReadPortULong(HANDLE hDevice, UINT nPort);


   	//######################### �ļ��������� ##############################
    HANDLE DEVAPI FAR PASCAL PCI2323_CreateFileObject(			// ��ʼ�ļ�ϵͳ
										  HANDLE hDevice,		// �豸����
										  LPCTSTR NewFileName,	// ���ļ���
										  int Mode);			// �ļ�������ʽ    
    BOOL DEVAPI FAR PASCAL PCI2323_WriteFile(					// �����û��ռ�������
										HANDLE hFileObject,		// �豸����
										PVOID pDataBuffer,		// �û����ݿռ��ַ
										ULONG nWriteSizeBytes); // ��������С(�ֽ�)

    BOOL DEVAPI FAR PASCAL PCI2323_ReadFile(					// ������
										  HANDLE hFileObject,	// �豸����
										  PVOID pDataBuffer,	// �����ļ����ݵ��û��ڴ滺����
										  ULONG OffsetBytes,	// ���ļ�ǰ�˿�ʼ��ƫ��λ��
										  ULONG nReadSizeBytes); // ��ƫ��λ�ÿ�ʼ�����ֽ���

	BOOL DEVAPI FAR PASCAL PCI2323_SetFileOffset(				// �����ļ�ƫ��ָ��
										  HANDLE hFileObject,   // �ļ�����
										  ULONG nOffsetBytes);  // �ļ�ƫ��λ�ã�����Ϊ��λ��  

	ULONG DEVAPI FAR PASCAL PCI2323_GetFileLength(HANDLE hFileObject); // ȡ��ָ���ļ����ȣ��ֽڣ�

    BOOL DEVAPI FAR PASCAL PCI2323_ReleaseFile(HANDLE hFileObject);
    ULONGLONG DEVAPI FAR PASCAL PCI2323_GetDiskFreeBytes(		// ���ָ���̷��Ĵ��̿ռ�(ע��ʹ��64λ����)
								      LPCTSTR DiskName);		// �̷���,��C��Ϊ"C:\\", D��Ϊ"D:\\"

	//########################### �̲߳������� ######################################
	HANDLE DEVAPI FAR PASCAL PCI2323_CreateSystemEvent(void);			// �����ں��¼����󣬹�InitDeviceInt��VB���̵߳Ⱥ���ʹ��
	BOOL DEVAPI FAR PASCAL PCI2323_ReleaseSystemEvent(HANDLE hEvent);	// �ͷ��ں��¼�����
	
 	BOOL DEVAPI FAR PASCAL PCI2323_CreateVBThread(HANDLE *hThread, LPTHREAD_START_ROUTINE StartThread);
    BOOL DEVAPI FAR PASCAL PCI2323_TerminateVBThread(HANDLE hThreadHandle);

	//############################### �������� ###################################
	BOOL DEVAPI FAR PASCAL PCI2323_SaveParaInt(HANDLE hDevice, LPCTSTR strParaName, int nValue); // ���������ݱ��浽ע�����(Device-x\Others)
	UINT DEVAPI FAR PASCAL PCI2323_LoadParaInt(HANDLE hDevice, LPCTSTR strParaName, int nDefaultVal); // ���������ݴ�ע����лض�����(Device-x\Others)
	BOOL DEVAPI FAR PASCAL PCI2323_SaveParaString(HANDLE hDevice, LPCTSTR strParaName, LPCTSTR strParaVal); // ���ַ������ݱ��浽ע�����(Device-x\Others)
	BOOL DEVAPI FAR PASCAL PCI2323_LoadParaString(HANDLE hDevice, LPCTSTR strParaName, LPCTSTR strParaVal, LPCTSTR strDefaultVal); // ���ַ������ݴ�ע����лض�����(Device-x\Others)

 	DWORD DEVAPI FAR PASCAL PCI2323_GetLastErrorEx(			// �Ӵ�����Ϣ���л��ָ�����������һ�δ�����Ϣ
									LPCTSTR strFuncName,	// ����ĺ�������ע���Сд
									LPTSTR strErrorMsg);    // ���صĴ�����Ϣ

	BOOL DEVAPI FAR PASCAL PCI2323_RemoveLastErrorEx(		// �Ӵ�����Ϣ�����Ƴ�ָ�����������һ�δ�����Ϣ
									LPCTSTR strFuncName);	// ����ĺ�������ע���Сд
	BOOL DEVAPI FAR PASCAL PCI2323_DelayTimeUs(HANDLE hDevice, LONG nTimeUs); // ΢�뼶��ʱ���������������߳���ʱ�䣩

#ifdef __cplusplus
}
#endif

// �Զ������������������
#ifndef _PCI2323_DRIVER_
	#pragma comment(lib, "PCI2323.lib")
	#pragma message("======== Welcome to use our art company's products!")
	#pragma message("======== Automatically linking with PCI2323.dll...")
	#pragma message("======== Successfully linked with PCI2323.dll")
#endif

#endif // _PCI2323_DEVICE_
