
#include "fifo.h"



typedef struct FifoQueue
{
    unsigned short front;     //����ͷ
    unsigned short rail;        //����β
    unsigned short count;       //���м���
    ElemType DatArray[QueueSize];
}FifoQueue_t;
 
FifoQueue_t thisQueue;
 
//���г�ʼ��
void QueueInitialise()
{
	FifoQueue_t *Queue = &thisQueue;
	Queue->front = Queue->rail;//��ʼ��ʱ����ͷ����������
	Queue->count = 0;   //���м���Ϊ0
}

//��������
unsigned char PushQueue_t(ElemType sdat)
{
	FifoQueue_t *Queue = &thisQueue;
	if((Queue->front == Queue->rail) && (Queue->count == QueueSize))
	{                    // full //�ж������������
			return QueueFull;    //���ض������ı�־
	}else
	{                    // in
			Queue->DatArray[Queue->rail] = sdat;
			Queue->rail = (Queue->rail + 1) % QueueSize;
			Queue->count = Queue->count + 1;
			return QueueOperateOk;
	}
}

//���ݳ���
unsigned char PopQueue_t(ElemType *sdat)
{
	FifoQueue_t *Queue = &thisQueue;
	if((Queue->front == Queue->rail) && (Queue->count == 0))
	{                   
			return QueueEmpty;
	}else
	{    
			*sdat = Queue->DatArray[Queue->front];
			Queue->front = (Queue->front + 1) % QueueSize;
			Queue->count = Queue->count - 1;
			return QueueOperateOk;
	}
}



