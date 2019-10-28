
#include "fifo.h"



typedef struct FifoQueue
{
    unsigned short front;     //队列头
    unsigned short rail;        //队列尾
    unsigned short count;       //队列计数
    ElemType DatArray[QueueSize];
}FifoQueue_t;
 
FifoQueue_t thisQueue;
 
//队列初始化
void QueueInitialise()
{
	FifoQueue_t *Queue = &thisQueue;
	Queue->front = Queue->rail;//初始化时队列头队列首相连
	Queue->count = 0;   //队列计数为0
}

//数据入列
unsigned char PushQueue_t(ElemType sdat)
{
	FifoQueue_t *Queue = &thisQueue;
	if((Queue->front == Queue->rail) && (Queue->count == QueueSize))
	{                    // full //判断如果队列满了
			return QueueFull;    //返回队列满的标志
	}else
	{                    // in
			Queue->DatArray[Queue->rail] = sdat;
			Queue->rail = (Queue->rail + 1) % QueueSize;
			Queue->count = Queue->count + 1;
			return QueueOperateOk;
	}
}

//数据出列
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



