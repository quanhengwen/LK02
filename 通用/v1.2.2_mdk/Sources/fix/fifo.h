#ifndef _FIFO_H
#define _FIFO_H
#define ElemType unsigned int  //数据类型
#define QueueSize      20 //fifo队列的大小

//状态
#define QueueFull      0  //fifo满置0
#define QueueEmpty     1  //FIFO空置1
#define QueueOperateOk 2  //队列操作完成 赋值为2



void QueueInitialise( void );
unsigned char PushQueue_t( ElemType sdat);
unsigned char PopQueue_t( ElemType *sdat);

#endif


