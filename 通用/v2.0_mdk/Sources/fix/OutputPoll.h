

#define ElementType  unsigned int
	
//使能输出
void SerialOutputEnable( void );

//关闭输出
void SerialOutputDisable( void );

//串口发送初始化
void SerialOutputInit( void );

//串口发送轮询
int SerialOutputPoll( void );


//数据入列
int SetSerialOutPutData( ElementType data );

//放到DMA发送完成中断
void SetFinishSendCallBack( void );


