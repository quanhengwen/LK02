

#define ElementType  unsigned int
	
//ʹ�����
void SerialOutputEnable( void );

//�ر����
void SerialOutputDisable( void );

//���ڷ��ͳ�ʼ��
void SerialOutputInit( void );

//���ڷ�����ѯ
int SerialOutputPoll( void );


//��������
int SetSerialOutPutData( ElementType data );

//�ŵ�DMA��������ж�
void SetFinishSendCallBack( void );


