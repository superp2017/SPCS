#ifndef _PCI2323_DEVICE_
#define _PCI2323_DEVICE_

//***********************************************************
// 中断函数PCI2323_InitDeviceInt中的INTSelect使用的中断选择选项
const long PCI2323_INTSRC_COSINT		= 0x00;	// 使能COS中断(使能该中断后，还需使能数字量输入，使能任意数字量输入通道，当所使能的数字量输入通道状态改变时产生该中断)
const long PCI2323_INTSRC_DI0INT		= 0x01;	// 使能DI0中断(数字量输入通道0上升沿产生中断), =TRUE使能, =FALSE禁止
const long PCI2323_INTSRC_DI1INT		= 0x02;	// 使能DI1中断(数字量输入通道1上升沿产生中断), =TRUE使能, =FALSE禁止
const long PCI2323_INTSRC_DI01INT		= 0x03;	// 使能DI0与DI1中断(数字量输入通道0或1上升沿产生中断), =TRUE使能, =FALSE禁止

// 中断状态参数
typedef struct _PCI2323_STATUS_INT	// 中断信息控制参数
{
	LONG bCOSINT;						// COS触发中断(16路数字量输入状态改变产生中断)
	LONG bDI0INT;						// DI0上升沿触发中断
	LONG bDI1INT;						// DI1上升沿触发中断
} PCI2323_STATUS_INT, *PPCI2323_STATUS_INT;
//######################## 常量定义 #################################
// CreateFileObject所用的文件操作方式控制字(可通过或指令实现多种方式并操作)
#define PCI2323_modeRead          0x0000			// 只读文件方式
#define PCI2323_modeWrite         0x0001			// 只写文件方式
#define	PCI2323_modeReadWrite     0x0002			// 既读又写文件方式
#define PCI2323_modeCreate        0x1000			// 如果文件不存可以创建该文件，如果存在，则重建此文件，并清0
#define PCI2323_typeText          0x4000			// 以文本方式操作文件

//***********************************************************
// 用于DA的复位方式（适用于PCI2323_InitDevProDA函数的ResetMode参数）
#define PCI2323_RESET_MODE_NEGATIVE        0x0000	// 负满度（-5V或-10V...）
#define PCI2323_RESET_MODE_ZERO			   0x0001	// 零点(0V)

//***********************************************************
// 用户函数接口
#ifndef _PCI2323_DRIVER_
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	//######################## 常规通用函数 #################################
	// 适用于本设备的最基本操作
	HANDLE DEVAPI FAR PASCAL PCI2323_CreateDevice(int DeviceID = 0);		// 创建设备对象
	int DEVAPI FAR PASCAL PCI2323_GetDeviceCount(HANDLE hDevice);			// 取得设备总台数
	BOOL DEVAPI FAR PASCAL PCI2323_GetDeviceCurrentID(HANDLE hDevice, PLONG DeviceLgcID, PLONG DevicePhysID);
	BOOL DEVAPI FAR PASCAL PCI2323_ListDeviceDlg(HANDLE hDevice);			// 列表系统当中的所有的该PCI设备
    BOOL DEVAPI FAR PASCAL PCI2323_ReleaseDevice(HANDLE hDevice);			// 关闭设备,禁止传输,且释放资源

	//####################### 数字I/O输入输出函数 #################################
	// 用户可以使用WriteRegisterULong和ReadRegisterULong等函数直接控制寄存器进行I/O
	// 输入输出，但使用下面两个函数更省事，它不需要您关心寄存器分配和位操作等，而只
	// 需象VB等语言的属性操作那么简单地实现各开关量通道的控制。
	BOOL DEVAPI FAR PASCAL PCI2323_SetDeviceDO(             // 设置数字量输出状态     
										HANDLE hDevice,     // 设备句柄								        
										BYTE bDOSts[16]);	// 置位与复位状态状态(0为复位状态，1为置位状态)

	BOOL DEVAPI FAR PASCAL PCI2323_GetDeviceDI(             // 取得数字量输入状态     
										HANDLE hDevice,     // 设备句柄								        
										BYTE bDISts[16]);	// 开关状态	

	//####################### 中断函数 #################################
	// 它由硬件信号的状态变化引起CPU产生中断事件hEventInt。
	BOOL DEVAPI FAR PASCAL PCI2323_InitDeviceInt(			// 初始化中断
										HANDLE hDevice,     // 设备句柄	
										HANDLE hEventInt,	// 中断事件句柄,它由CreateSystemEvent创建
										LONG INTSrc);		// 中断源选择
	BOOL DEVAPI FAR PASCAL PCI2323_SetCOSINTCH(				// 当中断源选择为COSINT时设置产生COS中断的通道
										HANDLE hDevice,		// 设备句柄	
										BYTE bDIInt[16]);	// 16路DI通道中断使能, =1使能, =0禁止
	LONG DEVAPI FAR PASCAL PCI2323_GetDeviceIntCount(HANDLE hDevice);  // 在中断初始化后，用它取得中断服务程序产生的次数
	BOOL DEVAPI FAR PASCAL PCI2323_GetDeviceIntSrc(HANDLE hDevice, PPCI2323_STATUS_INT pINTSts);  // 在中断初始化后，用它取得中断源
	BOOL DEVAPI FAR PASCAL PCI2323_ReleaseDeviceInt(HANDLE hDevice); // 释放中断资源

	//################# 内存映射寄存器直接操作及读写函数 ########################
	// 适用于用户对本设备更直接、更特殊、更低层、更复杂的控制。比如根据特殊的
	// 控制对象需要特殊的控制流程和控制效率时，则用户可以使用这些接口予以实现。
	BOOL DEVAPI FAR PASCAL PCI2323_GetDeviceAddr(			// 取得指定的指定设备寄存器组的线性基地址和物理地址
									HANDLE hDevice,			// 设备对象句柄,它由CreateDevice函数创建
									PULONG LinearAddr,		// 返回指定寄存器组的线性地址
									PULONG PhysAddr,		// 返回指定寄存器组的物理地址
									int RegisterID = 0);	// 设备寄存器组的ID号（0-5）

	BOOL DEVAPI FAR PASCAL PCI2323_GetDeviceBar(			// 取得指定的指定设备寄存器组BAR地址
									HANDLE hDevice,			// 设备对象句柄,它由CreateDevice函数创建
									ULONG  pulPCIBar[6]);	// 返回PCI BAR所有地址,具体PCI BAR中有多少可用地址请看硬件说明书

	BOOL DEVAPI FAR PASCAL PCI2323_GetDevVersion(			// 获取设备固件及程序版本
									HANDLE hDevice,			// 设备对象句柄,它由CreateDevice函数创建
									PULONG pulFmwVersion,	// 固件版本
									PULONG pulDriverVersion);// 驱动版本

    BOOL DEVAPI FAR PASCAL PCI2323_WriteRegisterByte(		// 往指定寄存器空间位置写入单节字数据
									HANDLE hDevice,			// 设备对象句柄,它由CreateDevice函数创建
									ULONG LinearAddr,		// 指定寄存器的线性基地址,它等于GetDeviceAddr中的LinearAddr参数返回值
									ULONG OffsetBytes,		// 相对于线性基地址基地址的偏移位置(字节)
									BYTE Value);			// 往指定地址写入单字节数据（其地址由线性基地址和偏移位置决定）

	BOOL DEVAPI FAR PASCAL PCI2323_WriteRegisterWord(		// 写双字节数据（其余同上）
									HANDLE hDevice, 
									ULONG LinearAddr, 
									ULONG OffsetBytes,  
									WORD Value);

	BOOL DEVAPI FAR PASCAL PCI2323_WriteRegisterULong(		// 写四节字数据（其余同上）
									HANDLE hDevice, 
									ULONG LinearAddr, 
									ULONG OffsetBytes,  
									ULONG Value);

	BYTE DEVAPI FAR PASCAL PCI2323_ReadRegisterByte(		// 读入单字节数据（其余同上）
									HANDLE hDevice, 
									ULONG LinearAddr, 
									ULONG OffsetBytes);

	WORD DEVAPI FAR PASCAL PCI2323_ReadRegisterWord(		// 读入双字节数据（其余同上）
									HANDLE hDevice, 
									ULONG LinearAddr, 
									ULONG OffsetBytes);

	ULONG DEVAPI FAR PASCAL PCI2323_ReadRegisterULong(		// 读入四字节数据（其余同上）
									HANDLE hDevice, 
									ULONG LinearAddr, 
									ULONG OffsetBytes);

	//################# I/O端口直接操作及读写函数 ########################
	// 适用于用户对本设备更直接、更特殊、更低层、更复杂的控制。比如根据特殊的
	// 控制对象需要特殊的控制流程和控制效率时，则用户可以使用这些接口予以实现。
	// 但这些函数主要适用于传统设备，如ISA总线、并口、串口等设备，不能用于本PCI设备
    BOOL DEVAPI FAR PASCAL PCI2323_WritePortByte(HANDLE hDevice, UINT nPort, BYTE Value);
    BOOL DEVAPI FAR PASCAL PCI2323_WritePortWord(HANDLE hDevice, UINT nPort, WORD Value);
    BOOL DEVAPI FAR PASCAL PCI2323_WritePortULong(HANDLE hDevice, UINT nPort, ULONG Value);

    BYTE DEVAPI FAR PASCAL PCI2323_ReadPortByte(HANDLE hDevice, UINT nPort);
    WORD DEVAPI FAR PASCAL PCI2323_ReadPortWord(HANDLE hDevice, UINT nPort);
    ULONG DEVAPI FAR PASCAL PCI2323_ReadPortULong(HANDLE hDevice, UINT nPort);


   	//######################### 文件操作函数 ##############################
    HANDLE DEVAPI FAR PASCAL PCI2323_CreateFileObject(			// 初始文件系统
										  HANDLE hDevice,		// 设备对象
										  LPCTSTR NewFileName,	// 新文件名
										  int Mode);			// 文件操作方式    
    BOOL DEVAPI FAR PASCAL PCI2323_WriteFile(					// 保存用户空间中数据
										HANDLE hFileObject,		// 设备对象
										PVOID pDataBuffer,		// 用户数据空间地址
										ULONG nWriteSizeBytes); // 缓冲区大小(字节)

    BOOL DEVAPI FAR PASCAL PCI2323_ReadFile(					// 读数据
										  HANDLE hFileObject,	// 设备对象
										  PVOID pDataBuffer,	// 接受文件数据的用户内存缓冲区
										  ULONG OffsetBytes,	// 从文件前端开始的偏移位置
										  ULONG nReadSizeBytes); // 从偏移位置开始读的字节数

	BOOL DEVAPI FAR PASCAL PCI2323_SetFileOffset(				// 设置文件偏移指针
										  HANDLE hFileObject,   // 文件对象
										  ULONG nOffsetBytes);  // 文件偏移位置（以字为单位）  

	ULONG DEVAPI FAR PASCAL PCI2323_GetFileLength(HANDLE hFileObject); // 取得指定文件长度（字节）

    BOOL DEVAPI FAR PASCAL PCI2323_ReleaseFile(HANDLE hFileObject);
    ULONGLONG DEVAPI FAR PASCAL PCI2323_GetDiskFreeBytes(		// 获得指定盘符的磁盘空间(注意使用64位变量)
								      LPCTSTR DiskName);		// 盘符名,如C盘为"C:\\", D盘为"D:\\"

	//########################### 线程操作函数 ######################################
	HANDLE DEVAPI FAR PASCAL PCI2323_CreateSystemEvent(void);			// 创建内核事件对象，供InitDeviceInt和VB子线程等函数使用
	BOOL DEVAPI FAR PASCAL PCI2323_ReleaseSystemEvent(HANDLE hEvent);	// 释放内核事件对象
	
 	BOOL DEVAPI FAR PASCAL PCI2323_CreateVBThread(HANDLE *hThread, LPTHREAD_START_ROUTINE StartThread);
    BOOL DEVAPI FAR PASCAL PCI2323_TerminateVBThread(HANDLE hThreadHandle);

	//############################### 辅助函数 ###################################
	BOOL DEVAPI FAR PASCAL PCI2323_SaveParaInt(HANDLE hDevice, LPCTSTR strParaName, int nValue); // 将整型数据保存到注册表中(Device-x\Others)
	UINT DEVAPI FAR PASCAL PCI2323_LoadParaInt(HANDLE hDevice, LPCTSTR strParaName, int nDefaultVal); // 将整型数据从注册表中回读出来(Device-x\Others)
	BOOL DEVAPI FAR PASCAL PCI2323_SaveParaString(HANDLE hDevice, LPCTSTR strParaName, LPCTSTR strParaVal); // 将字符串数据保存到注册表中(Device-x\Others)
	BOOL DEVAPI FAR PASCAL PCI2323_LoadParaString(HANDLE hDevice, LPCTSTR strParaName, LPCTSTR strParaVal, LPCTSTR strDefaultVal); // 将字符串数据从注册表中回读出来(Device-x\Others)

 	DWORD DEVAPI FAR PASCAL PCI2323_GetLastErrorEx(			// 从错误信息库中获得指定函数的最后一次错误信息
									LPCTSTR strFuncName,	// 出错的函数名，注意大小写
									LPTSTR strErrorMsg);    // 返回的错误信息

	BOOL DEVAPI FAR PASCAL PCI2323_RemoveLastErrorEx(		// 从错误信息库中移除指定函数的最后一次错误信息
									LPCTSTR strFuncName);	// 出错的函数名，注意大小写
	BOOL DEVAPI FAR PASCAL PCI2323_DelayTimeUs(HANDLE hDevice, LONG nTimeUs); // 微秒级延时，（但不向其他线程抛时间）

#ifdef __cplusplus
}
#endif

// 自动包含驱动函数导入库
#ifndef _PCI2323_DRIVER_
	#pragma comment(lib, "PCI2323.lib")
	#pragma message("======== Welcome to use our art company's products!")
	#pragma message("======== Automatically linking with PCI2323.dll...")
	#pragma message("======== Successfully linked with PCI2323.dll")
#endif

#endif // _PCI2323_DEVICE_
