//***********************************************************
typedef struct _PCI2361_PARA_COUNTER_CTRL      // ������������(CONTROL)
{
	BYTE OperateType;  // ��������(D5D4)
	BYTE CountMode;    // ������ʽ(D3-D1) 
	BYTE BCD;          // ��������(D0)
} PCI2361_PARA_COUNTER_CTRL,*PPCI2361_PARA_COUNTER_CTRL;

//***********************************************************
// 8253Ӳ������PCI2361_PARA_COUNTER_CTRL�е�OperateType��Ա��ʹ��ѡ��
// ��������
#define PCI2361_OperateType_0	  0x00  // �������������
#define PCI2361_OperateType_1	  0x01  // ֻ��/д���ֽ�
#define PCI2361_OperateType_2     0x02  // ֻ��/д���ֽ�
#define PCI2361_OperateType_3     0x03  // �ȶ�/д���ֽڣ����/д���ֽ�
//***********************************************************
// 8253Ӳ������PCI2361_PARA_COUNTER_CTRL�е�CountMode��Ա��ʹ��ѡ��
// ������ʽ
#define PCI2361_CountMode_0		  0x00  // ������ʽ0�������������жϷ�ʽ
#define PCI2361_CountMode_1		  0x01  // ������ʽ1���ɱ�̵������巽ʽ
#define PCI2361_CountMode_2		  0x02  // ������ʽ2��Ƶ�ʷ�������ʽ
#define PCI2361_CountMode_3		  0x03  // ������ʽ3������Ƶ�ʷ�������ʽ
#define PCI2361_CountMode_4		  0x04  // ������ʽ4���������ѡͨ��ʽ
#define PCI2361_CountMode_5		  0x05  // ������ʽ5��Ӳ������ѡͨ��ʽ
//***********************************************************
// 8253Ӳ������PCI2361_PARA_COUNTER_CTRL�е�BCD��Ա��ʹ��ѡ��
// ��������
#define PCI2361_BCD_0			  0x00  // ��������0�������Ƽ���
#define PCI2361_BCD_1			  0x01  // ��������1��BCD�����

//***********************************************************
// ���ڿ������Ĳ����ṹ
#ifndef _PCI2361_PARA_DO
typedef struct _PCI2361_PARA_DO      // �������������
{
	BYTE DO0;       // 0ͨ��
	BYTE DO1;       // 1ͨ��
	BYTE DO2;       // 2ͨ��
	BYTE DO3;       // 3ͨ��
	BYTE DO4;       // 4ͨ��
	BYTE DO5;       // 5ͨ��
	BYTE DO6;       // 6ͨ��
	BYTE DO7;       // 7ͨ��
	BYTE DO8;       // 8ͨ��
	BYTE DO9;       // 9ͨ��
	BYTE DO10;       // 10ͨ��
	BYTE DO11;       // 11ͨ��
	BYTE DO12;       // 12ͨ��
	BYTE DO13;       // 13ͨ��
	BYTE DO14;       // 14ͨ��
	BYTE DO15;       // 15ͨ��
} PCI2361_PARA_DO,*PPCI2361_PARA_DO;
#endif

#ifndef _PCI2361_PARA_DI
typedef struct _PCI2361_PARA_DI      // �������������
{
	BYTE DI0;       // 0ͨ��
	BYTE DI1;       // 1ͨ��
	BYTE DI2;       // 2ͨ��
	BYTE DI3;       // 3ͨ��
	BYTE DI4;       // 4ͨ��
	BYTE DI5;       // 5ͨ��
	BYTE DI6;       // 6ͨ��
	BYTE DI7;       // 7ͨ��
	BYTE DI8;       // 8ͨ��
	BYTE DI9;       // 9ͨ��
	BYTE DI10;       // 10ͨ��
	BYTE DI11;       // 11ͨ��
	BYTE DI12;       // 12ͨ��
	BYTE DI13;       // 13ͨ��
	BYTE DI14;       // 14ͨ��
	BYTE DI15;       // 15ͨ��
} PCI2361_PARA_DI,*PPCI2361_PARA_DI;
#endif


//***********************************************************
// InitDeviceFile���õ��ļ�������ʽ������(��ͨ����ָ��ʵ�ֶ��ַ�ʽ������)
#define PCI2361_modeRead          0x0000   // ֻ���ļ���ʽ
#define PCI2361_modeWrite         0x0001   // ֻд�ļ���ʽ
#define	PCI2361_modeReadWrite     0x0002   // �ȶ���д�ļ���ʽ
#define PCI2361_modeCreate        0x1000   // ����ļ�������Դ������ļ���������ڣ����ؽ����ļ�������0

//***********************************************************
#ifndef DEFINING
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	//################### ����ͨ�ú���(�ϲ�ײ��û��ӿ�)####################
	// �����ڱ��豸�����������
	DEVAPI HANDLE FAR PASCAL PCI2361_CreateDevice(int DeviceID);  // �����豸����
	DEVAPI int FAR PASCAL PCI2361_GetDeviceCount(HANDLE hDevice); // ȡ���豸��̨��
	DEVAPI BOOL PCI2361_ListDeviceDlg(HANDLE hDevice); // �б�ϵͳ���е����еĸ�PCI�豸
	DEVAPI BOOL PCI2361_ListDeviceDlgEx(HANDLE hDevice); // �б�ϵͳ���е����еĸ�PCI�豸
    DEVAPI BOOL FAR PASCAL PCI2361_ReleaseDevice(HANDLE hDevice); // �ر��豸,��ֹ����,���ͷ���Դ

   	//########################## �������������� ##################################
    DEVAPI BOOL FAR PASCAL PCI2361_InitDevCounter( // ��ʼ����·������
										HANDLE hDevice,     // �豸���
										PPCI2361_PARA_COUNTER_CTRL pCtrlPara, // ������������
										LONG CntrValue,      // ��������16λֵ
										int nCntrChannel);   // ������ͨ���ţ�0-8��

	DEVAPI BOOL FAR PASCAL PCI2361_GetDevCounter(			// ȡ�ü�����ֵ
										HANDLE hDevice,			// �豸���
										PLONG pCntrValue,	    // ȡ��16λ������ֵ
										int nCntrChannel);    // ������ͨ���ţ�0-8��

	DEVAPI double FAR PASCAL PCI2361_MeasureFreq(			 // ȡ�ü���������Ƶ��(����)
									  HANDLE hDevice,		 // �豸���
									  LONG nTimeMs,          // ��ʱʱ��(����),��СֵΪ10���룬���ֵȡ���ڱ���Ƶ�ʺͼ��������(16Bit)
									  int nCNTChannel);      // ������ͨ���ţ�0-8��

	//################### ����I/O��������������ϲ��û��ӿڣ� ######################
	// �û�����ʹ��WritePortULong��ReadPortULong�Ⱥ���ֱ�ӿ��ƼĴ�������I/O
	// �����������ʹ����������������ʡ�£�������Ҫ�����ļĴ��������λ�����ȣ���ֻ
	// ����VB�����Ե����Բ�����ô�򵥵�ʵ�ָ�������ͨ���Ŀ��ơ�
    DEVAPI BOOL FAR PASCAL PCI2361_SetDeviceDOL(             // ���������״̬
										HANDLE hDevice,     // �豸���								        
										PPCI2361_PARA_DO pPara);  // ����״̬
    DEVAPI BOOL FAR PASCAL PCI2361_SetDeviceDOH(             // ���������״̬
										HANDLE hDevice,     // �豸���								        
										PPCI2361_PARA_DO pPara);  // ����״̬

	DEVAPI BOOL FAR PASCAL PCI2361_GetDeviceDIL(             // ȡ�ÿ�����״̬     
										HANDLE hDevice,     // �豸���								        
										PPCI2361_PARA_DI pPara);  // ����״̬

	DEVAPI BOOL FAR PASCAL PCI2361_GetDeviceDIH(             // ȡ�ÿ�����״̬     
										HANDLE hDevice,     // �豸���								        
										PPCI2361_PARA_DI pPara);  // ����״̬
	
	
	
	//############### I/O�˿�ֱ�Ӳ�������д����(�ײ��û��ӿ�) #####################
	// �������û��Ա��豸��ֱ�ӡ������⡢���Ͳ㡢�����ӵĿ��ơ�������������
	// ���ƶ�����Ҫ����Ŀ������̺Ϳ���Ч��ʱ�����û�����ʹ����Щ�ӿ�����ʵ�֡�
	// ����Щ������Ҫ�����ڴ�ͳ�豸����ISA���ߡ����ڡ����ڵ��豸
	DEVAPI BOOL FAR PASCAL PCI2361_GetDeviceAddr( // ȡ��ָ����ָ���豸ID�ŵ�ӳ��Ĵ��������Ի���ַ�������豸����
												HANDLE hDevice,  // �豸������
												PULONG LinearAddr, // ����ָ��ӳ��Ĵ��������Ե�ַ
											    PULONG PhysAddr,   //  ����ָ��ӳ��Ĵ����������ַ												
												int RegisterID); // �豸ӳ��Ĵ�����ID�ţ�0-5��
    DEVAPI BOOL FAR PASCAL PCI2361_WritePortByte(HANDLE hDevice, UINT nPort, BYTE Value);
    DEVAPI BOOL FAR PASCAL PCI2361_WritePortWord(HANDLE hDevice, UINT nPort, WORD Value);
    DEVAPI BOOL FAR PASCAL PCI2361_WritePortULong(HANDLE hDevice, UINT nPort, ULONG Value);

    DEVAPI BYTE FAR PASCAL PCI2361_ReadPortByte(HANDLE hDevice, UINT nPort);
    DEVAPI WORD FAR PASCAL PCI2361_ReadPortWord(HANDLE hDevice, UINT nPort);
    DEVAPI ULONG FAR PASCAL PCI2361_ReadPortULong(HANDLE hDevice, UINT nPort);

   	//########################### �ļ��������� #####################################
    DEVAPI HANDLE FAR PASCAL PCI2361_CreateFileObject(                    // ��ʼ�ļ�ϵͳ
										  HANDLE hDevice,     // �豸����
										  LPCTSTR NewFileName,  // ���ļ���
										  int Mode);		 // �ļ�������ʽ    
    DEVAPI BOOL FAR PASCAL PCI2361_WriteFile(      // �����û��ռ�������
										HANDLE hFileObject,  // �豸����
										PVOID pDataBuffer, // �û����ݿռ��ַ
										ULONG nWriteSizeBytes); // ��������С(�ֽ�)

    DEVAPI BOOL FAR PASCAL PCI2361_ReadFile(  // ������
										  HANDLE hFileObject,     // �豸����
										  PVOID pDataBuffer, // �����ļ����ݵ��û��ڴ滺����
										  ULONG OffsetBytes,   // ���ļ�ǰ�˿�ʼ��ƫ��λ��
										  ULONG nReadSizeBytes); // ��ƫ��λ�ÿ�ʼ�����ֽ���

	DEVAPI ULONG FAR PASCAL PCI2361_GetFileLength(HANDLE hFileObject); // ȡ��ָ���ļ����ȣ��ֽڣ�
	DEVAPI BOOL FAR PASCAL PCI2361_SetFileOffset( // �����ļ�ƫ��ָ��
										  HANDLE hFileObject,   // �ļ�����
										  ULONG nOffsetBytes);  // �ļ�ƫ��λ�ã�����Ϊ��λ��  

    DEVAPI BOOL FAR PASCAL PCI2361_ReleaseFile(HANDLE hFileObject);
    DEVAPI ULONGLONG FAR PASCAL PCI2361_GetDiskFreeBytes(               // ���ָ���̷��Ĵ��̿ռ�
								      LPCTSTR DiskName);            // �̷���,��C��Ϊ"C:\\", D��Ϊ"D:\\"

	//################# �̲߳������� ########################
	DEVAPI HANDLE FAR PASCAL PCI2361_CreateSystemEvent(void); // �����ں��¼�����
	DEVAPI BOOL FAR PASCAL PCI2361_ReleaseSystemEvent(HANDLE hEvent); // �ͷ��ں��¼�����
	DEVAPI BOOL FAR PASCAL PCI2361_CreateVBThread(HANDLE *hThread, LPTHREAD_START_ROUTINE RoutineAddr);
    DEVAPI BOOL FAR PASCAL PCI2361_TerminateVBThread(HANDLE hThreadHandle);
	DEVAPI BOOL FAR PASCAL PCI2361_DelayTime(HANDLE hDevice, LONG nTime);
	DEVAPI BOOL FAR PASCAL PCI2361_DelayTimeUs(HANDLE hDevice, LONG nTimeUs);

	//////////////////////////////////////////////////////////////////////////////// 
#ifdef __cplusplus
}
#endif
