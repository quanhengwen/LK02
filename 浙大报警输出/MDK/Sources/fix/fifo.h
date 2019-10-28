#ifndef _FIFO_H
#define _FIFO_H
#define ElemType unsigned int  //��������
#define QueueSize      20 //fifo���еĴ�С

//״̬
#define QueueFull      0  //fifo����0
#define QueueEmpty     1  //FIFO����1
#define QueueOperateOk 2  //���в������ ��ֵΪ2



void QueueInitialise( void );
unsigned char PushQueue_t( ElemType sdat);
unsigned char PopQueue_t( ElemType *sdat);

#endif


