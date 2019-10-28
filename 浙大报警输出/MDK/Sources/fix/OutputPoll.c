
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
 
//��ѯ��һ֡�Ƿ����
//���ͺ��������
typedef struct SerialOutputStr
{
	uchar SerialSta;
	uchar SendEnable; 
	uchar SendFinishedFlag;
	unsigned int SerialData;
	char SerialBuf[20];
}SerialOutputStr_t;

SerialOutputStr_t OutputDataStr;

//���ڳ�ʼ��
void SerialOutputInit()
{
	QueueInitialise();
	OutputDataStr.SerialSta = PortIdle;
	OutputDataStr.SendFinishedFlag = 0;
}
extern unsigned char testflag;
//������ѯ
int SerialOutputPoll()
{
//	if(OutputDataStr.SendEnable == OUTPUT_DISABLE)
//		return 0;
	
	if(LsOutputSta()){//�鿴����׼��״̬
		ResetOutputSta();
		//����Ҫ���͵����ݷŵ����Ͷ�����
		SetSerialOutPutData(t_GetFilterDist());
		//��ǰ״̬���� ʹ�ܷ���
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
				//�������ݳ���
				//�������
				//dma ���� �ŵ�dma������
				if(QueueEmpty != PopQueue_t(&OutputDataStr.SerialData)){
					sprintf(OutputDataStr.SerialBuf,"%.2fm\r\n",OutputDataStr.SerialData/100.0);
					Uart1_DMASendOutOnce(OutputDataStr.SerialBuf,strlen(OutputDataStr.SerialBuf));
				}else{
					OutputDataStr.SerialSta = PortIdle;
				}
				//״̬��æ
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

//��������
int SetSerialOutPutData( ElementType data )
{
	unsigned char retval = PushQueue_t(data);
	return (retval == QueueOperateOk ? 0 : -1);
}

//�ر����
void SerialOutputDisable()
{
	SerialOutputInit();
	OutputDataStr.SendEnable = OUTPUT_DISABLE;
}

//ʹ�����
void SerialOutputEnable()
{
	SerialOutputInit();
	OutputDataStr.SendEnable = OUTPUT_ENABLE;
}

//�ŵ�DMA��������ж�
void SetFinishSendCallBack()
{
	if(OutputDataStr.SendFinishedFlag == 0){
		OutputDataStr.SendFinishedFlag = 1;
		OutputDataStr.SerialSta = PortSending;
	}
}
