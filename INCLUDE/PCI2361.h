//***********************************************************
typedef struct _PCI2361_PARA_COUNTER_CTRL      // 计数器控制字(CONTROL)
{
	BYTE OperateType;  // 操作类型(D5D4)
	BYTE CountMode;    // 计数方式(D3-D1) 
	BYTE BCD;          // 计数类型(D0)
} PCI2361_PARA_COUNTER_CTRL,*PPCI2361_PARA_COUNTER_CTRL;

//***********************************************************
// 8253硬件参数PCI2361_PARA_COUNTER_CTRL中的OperateType成员所使用选项
// 操作类型
#define PCI2361_OperateType_0	  0x00  // 计数器锁存操作
#define PCI2361_OperateType_1	  0x01  // 只读/写低字节
#define PCI2361_OperateType_2     0x02  // 只读/写高字节
#define PCI2361_OperateType_3     0x03  // 先读/写低字节，后读/写高字节
//***********************************************************
// 8253硬件参数PCI2361_PARA_COUNTER_CTRL中的CountMode成员所使用选项
// 计数方式
#define PCI2361_CountMode_0		  0x00  // 计数方式0，计数器结束中断方式
#define PCI2361_CountMode_1		  0x01  // 计数方式1，可编程单次脉冲方式
#define PCI2361_CountMode_2		  0x02  // 计数方式2，频率发生器方式
#define PCI2361_CountMode_3		  0x03  // 计数方式3，方波频率发生器方式
#define PCI2361_CountMode_4		  0x04  // 计数方式4，软件触发选通方式
#define PCI2361_CountMode_5		  0x05  // 计数方式5，硬件触发选通方式
//***********************************************************
// 8253硬件参数PCI2361_PARA_COUNTER_CTRL中的BCD成员所使用选项
// 计数类型
#define PCI2361_BCD_0			  0x00  // 计数类型0，二进制计数
#define PCI2361_BCD_1			  0x01  // 计数类型1，BCD码计数

//***********************************************************
// 用于开关量的参数结构
#ifndef _PCI2361_PARA_DO
typedef struct _PCI2361_PARA_DO      // 数字量输出参数
{
	BYTE DO0;       // 0通道
	BYTE DO1;       // 1通道
	BYTE DO2;       // 2通道
	BYTE DO3;       // 3通道
	BYTE DO4;       // 4通道
	BYTE DO5;       // 5通道
	BYTE DO6;       // 6通道
	BYTE DO7;       // 7通道
	BYTE DO8;       // 8通道
	BYTE DO9;       // 9通道
	BYTE DO10;       // 10通道
	BYTE DO11;       // 11通道
	BYTE DO12;       // 12通道
	BYTE DO13;       // 13通道
	BYTE DO14;       // 14通道
	BYTE DO15;       // 15通道
} PCI2361_PARA_DO,*PPCI2361_PARA_DO;
#endif

#ifndef _PCI2361_PARA_DI
typedef struct _PCI2361_PARA_DI      // 数字量输入参数
{
	BYTE DI0;       // 0通道
	BYTE DI1;       // 1通道
	BYTE DI2;       // 2通道
	BYTE DI3;       // 3通道
	BYTE DI4;       // 4通道
	BYTE DI5;       // 5通道
	BYTE DI6;       // 6通道
	BYTE DI7;       // 7通道
	BYTE DI8;       // 8通道
	BYTE DI9;       // 9通道
	BYTE DI10;       // 10通道
	BYTE DI11;       // 11通道
	BYTE DI12;       // 12通道
	BYTE DI13;       // 13通道
	BYTE DI14;       // 14通道
	BYTE DI15;       // 15通道
} PCI2361_PARA_DI,*PPCI2361_PARA_DI;
#endif


//***********************************************************
// InitDeviceFile所用的文件操作方式控制字(可通过或指令实现多种方式并操作)
#define PCI2361_modeRead          0x0000   // 只读文件方式
#define PCI2361_modeWrite         0x0001   // 只写文件方式
#define	PCI2361_modeReadWrite     0x0002   // 既读又写文件方式
#define PCI2361_modeCreate        0x1000   // 如果文件不存可以创建该文件，如果存在，则重建此文件，并清0

//***********************************************************
#ifndef DEFINING
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	//################### 常规通用函数(上层底层用户接口)####################
	// 适用于本设备的最基本操作
	DEVAPI HANDLE FAR PASCAL PCI2361_CreateDevice(int DeviceID);  // 创建设备对象
	DEVAPI int FAR PASCAL PCI2361_GetDeviceCount(HANDLE hDevice); // 取得设备总台数
	DEVAPI BOOL PCI2361_ListDeviceDlg(HANDLE hDevice); // 列表系统当中的所有的该PCI设备
	DEVAPI BOOL PCI2361_ListDeviceDlgEx(HANDLE hDevice); // 列表系统当中的所有的该PCI设备
    DEVAPI BOOL FAR PASCAL PCI2361_ReleaseDevice(HANDLE hDevice); // 关闭设备,禁止传输,且释放资源

   	//########################## 计数器操作函数 ##################################
    DEVAPI BOOL FAR PASCAL PCI2361_InitDevCounter( // 初始化各路计数器
										HANDLE hDevice,     // 设备句柄
										PPCI2361_PARA_COUNTER_CTRL pCtrlPara, // 计数器控制字
										LONG CntrValue,      // 计数器的16位值
										int nCntrChannel);   // 计数器通道号（0-8）

	DEVAPI BOOL FAR PASCAL PCI2361_GetDevCounter(			// 取得计数器值
										HANDLE hDevice,			// 设备句柄
										PLONG pCntrValue,	    // 取得16位计数器值
										int nCntrChannel);    // 计数器通道号（0-8）

	DEVAPI double FAR PASCAL PCI2361_MeasureFreq(			 // 取得计数器测量频率(赫兹)
									  HANDLE hDevice,		 // 设备句柄
									  LONG nTimeMs,          // 定时时间(毫秒),最小值为10毫秒，最大值取决于被测频率和计数器宽度(16Bit)
									  int nCNTChannel);      // 计数器通道号（0-8）

	//################### 数字I/O输入输出函数（上层用户接口） ######################
	// 用户可以使用WritePortULong和ReadPortULong等函数直接控制寄存器进行I/O
	// 输入输出，但使用下面两个函数更省事，它不需要您关心寄存器分配和位操作等，而只
	// 需象VB等语言的属性操作那么简单地实现各开关量通道的控制。
    DEVAPI BOOL FAR PASCAL PCI2361_SetDeviceDOL(             // 输出开关量状态
										HANDLE hDevice,     // 设备句柄								        
										PPCI2361_PARA_DO pPara);  // 开关状态
    DEVAPI BOOL FAR PASCAL PCI2361_SetDeviceDOH(             // 输出开关量状态
										HANDLE hDevice,     // 设备句柄								        
										PPCI2361_PARA_DO pPara);  // 开关状态

	DEVAPI BOOL FAR PASCAL PCI2361_GetDeviceDIL(             // 取得开关量状态     
										HANDLE hDevice,     // 设备句柄								        
										PPCI2361_PARA_DI pPara);  // 开关状态

	DEVAPI BOOL FAR PASCAL PCI2361_GetDeviceDIH(             // 取得开关量状态     
										HANDLE hDevice,     // 设备句柄								        
										PPCI2361_PARA_DI pPara);  // 开关状态
	
	
	
	//############### I/O端口直接操作及读写函数(底层用户接口) #####################
	// 适用于用户对本设备更直接、更特殊、更低层、更复杂的控制。比如根据特殊的
	// 控制对象需要特殊的控制流程和控制效率时，则用户可以使用这些接口予以实现。
	// 但这些函数主要适用于传统设备，如ISA总线、并口、串口等设备
	DEVAPI BOOL FAR PASCAL PCI2361_GetDeviceAddr( // 取得指定的指定设备ID号的映射寄存器的线性基地址，返回设备总数
												HANDLE hDevice,  // 设备对象句柄
												PULONG LinearAddr, // 返回指定映射寄存器的线性地址
											    PULONG PhysAddr,   //  返回指定映射寄存器的物理地址												
												int RegisterID); // 设备映射寄存器的ID号（0-5）
    DEVAPI BOOL FAR PASCAL PCI2361_WritePortByte(HANDLE hDevice, UINT nPort, BYTE Value);
    DEVAPI BOOL FAR PASCAL PCI2361_WritePortWord(HANDLE hDevice, UINT nPort, WORD Value);
    DEVAPI BOOL FAR PASCAL PCI2361_WritePortULong(HANDLE hDevice, UINT nPort, ULONG Value);

    DEVAPI BYTE FAR PASCAL PCI2361_ReadPortByte(HANDLE hDevice, UINT nPort);
    DEVAPI WORD FAR PASCAL PCI2361_ReadPortWord(HANDLE hDevice, UINT nPort);
    DEVAPI ULONG FAR PASCAL PCI2361_ReadPortULong(HANDLE hDevice, UINT nPort);

   	//########################### 文件操作函数 #####################################
    DEVAPI HANDLE FAR PASCAL PCI2361_CreateFileObject(                    // 初始文件系统
										  HANDLE hDevice,     // 设备对象
										  LPCTSTR NewFileName,  // 新文件名
										  int Mode);		 // 文件操作方式    
    DEVAPI BOOL FAR PASCAL PCI2361_WriteFile(      // 保存用户空间中数据
										HANDLE hFileObject,  // 设备对象
										PVOID pDataBuffer, // 用户数据空间地址
										ULONG nWriteSizeBytes); // 缓冲区大小(字节)

    DEVAPI BOOL FAR PASCAL PCI2361_ReadFile(  // 读数据
										  HANDLE hFileObject,     // 设备对象
										  PVOID pDataBuffer, // 接受文件数据的用户内存缓冲区
										  ULONG OffsetBytes,   // 从文件前端开始的偏移位置
										  ULONG nReadSizeBytes); // 从偏移位置开始读的字节数

	DEVAPI ULONG FAR PASCAL PCI2361_GetFileLength(HANDLE hFileObject); // 取得指定文件长度（字节）
	DEVAPI BOOL FAR PASCAL PCI2361_SetFileOffset( // 设置文件偏移指针
										  HANDLE hFileObject,   // 文件对象
										  ULONG nOffsetBytes);  // 文件偏移位置（以字为单位）  

    DEVAPI BOOL FAR PASCAL PCI2361_ReleaseFile(HANDLE hFileObject);
    DEVAPI ULONGLONG FAR PASCAL PCI2361_GetDiskFreeBytes(               // 获得指定盘符的磁盘空间
								      LPCTSTR DiskName);            // 盘符名,如C盘为"C:\\", D盘为"D:\\"

	//################# 线程操作函数 ########################
	DEVAPI HANDLE FAR PASCAL PCI2361_CreateSystemEvent(void); // 创建内核事件对象
	DEVAPI BOOL FAR PASCAL PCI2361_ReleaseSystemEvent(HANDLE hEvent); // 释放内核事件对象
	DEVAPI BOOL FAR PASCAL PCI2361_CreateVBThread(HANDLE *hThread, LPTHREAD_START_ROUTINE RoutineAddr);
    DEVAPI BOOL FAR PASCAL PCI2361_TerminateVBThread(HANDLE hThreadHandle);
	DEVAPI BOOL FAR PASCAL PCI2361_DelayTime(HANDLE hDevice, LONG nTime);
	DEVAPI BOOL FAR PASCAL PCI2361_DelayTimeUs(HANDLE hDevice, LONG nTimeUs);

	//////////////////////////////////////////////////////////////////////////////// 
#ifdef __cplusplus
}
#endif
