
#include "pritype.h"
#include "fifo.h"
#include "outputPoll.h"

#define OUTPUT_ENABLE   1
#define OUTPUT_DISABLE  0

	
enum PortSta
{
	PortIdle = 0,
	PortSending,
	PortBusy,
	PortErr,
};
 
//查询上一帧是否完成
//发送后进的数据
typedef struct SerialOutputStr
{
	uchar SerialSta;
	uchar SendEnable; 
	uchar SendFinishedFlag;
	unsigned int SerialData;
	char SerialBuf[20];
}SerialOutputStr_t;

SerialOutputStr_t OutputDataStr;

//串口初始化
void SerialOutputInit()
{
	QueueInitialise();
	OutputDataStr.SerialSta = PortIdle;
	OutputDataStr.SendFinishedFlag = 0;
}
extern unsigned char testflag;
//串口轮询
int SerialOutputPoll()
{
//	if(OutputDataStr.SendEnable == OUTPUT_DISABLE)
//		return 0;
	
	if(LsOutputSta()){//查看数据准备状态
		ResetOutputSta();
		//将需要发送的数据放到发送队列中
		SetSerialOutPutData(t_GetFilterDist());
		//当前状态空闲 使能发送
		if(PortIdle == OutputDataStr.SerialSta){
			OutputDataStr.SerialSta = PortSending;
			OutputDataStr.SendFinishedFlag = 1;
		}
	}
	switch(OutputDataStr.SerialSta)
	{
		case PortIdle:
			break;
		case PortSending:
			OutputDataStr.SerialSta = PortBusy;
			if(OutputDataStr.SendFinishedFlag == 1){
				OutputDataStr.SendFinishedFlag = 0;
				//发送数据出列
				//打包数据
				//dma 发送 放到dma缓存中
				if(QueueEmpty != PopQueue_t(&OutputDataStr.SerialData)){
					sprintf(OutputDataStr.SerialBuf,"%.2fm\r\n",OutputDataStr.SerialData/100.0);
					Uart1_DMASendOutOnce(OutputDataStr.SerialBuf,strlen(OutputDataStr.SerialBuf));
				}else{
					OutputDataStr.SerialSta = PortIdle;
				}
				//状态置忙
			}
			
			break;
		case PortBusy:
			break;
		case PortErr:
			break;
		default:
			break;
	}
	return 0;
}

//数据入列
int SetSerialOutPutData( ElementType data )
{
	unsigned char retval = PushQueue_t(data);
	return (retval == QueueOperateOk ? 0 : -1);
}

//关闭输出
void SerialOutputDisable()
{
	SerialOutputInit();
	OutputDataStr.SendEnable = OUTPUT_DISABLE;
}

//使能输出
void SerialOutputEnable()
{
	SerialOutputInit();
	OutputDataStr.SendEnable = OUTPUT_ENABLE;
}

//放到DMA发送完成中断
void SetFinishSendCallBack()
{
	if(OutputDataStr.SendFinishedFlag == 0){
		OutputDataStr.SendFinishedFlag = 1;
		OutputDataStr.SerialSta = PortSending;
	}
}
