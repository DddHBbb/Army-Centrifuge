#include"GlobalVar.h"
#include "IIC.h"

void write_IIC(unsigned char wdate_H,unsigned char wdate_L)
{ 
    int t=0;
    SSPIF=0;
    SEN=1;            //�����ź�
    while(SSPIF==0)//1��ʱ������  0��ʱ���Ǽ�  ��SSPIFΪ���棬Ϊ���˳����
    {
        t++;
      if(t > 1000)   break;
    }
    t=0;
    SSPIF=0;          //�������  �����Զ�����
    
    SSPBUF=0X98;      //�����豸��ַ
    Delay(1);
    while(SSPIF==0)  //�ж��Ƿ������
    {
        t++;
      if(t > 1000)   break;
    }
    t=0;
    SSPIF=0;
      
    SSPBUF=wdate_H;     //д����ֽ�����
    Delay(1);
    while(SSPIF==0) //ÿ����һ�����ݶ�Ҫ����Ƿ�ɹ�
    {
        t++;
      if(t > 1000)   break;
    }
    t=0;
    SSPIF=0;
 
    SSPBUF=wdate_L;     //д����ֽ�����
    Delay(1);
    while(SSPIF==0)  //ÿ����һ�����ݶ�Ҫ����Ƿ�ɹ�
    {
        t++;
      if(t > 1000)   break;
    }
    t=0;
    SSPIF=0;
    
    PEN=1;            //����ֹͣ�ź�
    while(SSPIF==0)  //����յ�ֹͣ�ź�ͬ������λ
    {
        t++;
      if(t > 1000)   break;
    }
    t=0;
    SSPIF=0;
//    delaynms(2);
}
  
//unsigned char read(unsigned char add)
//{
//    unsigned char rdate;
//    SSPIF=0;
//    SEN=1;
//    while(SSPIF==0);
//    SSPIF=0;
//    SSPBUF=0xA0;            //�����豸��ַ
//    while(SSPIF==0);
//    SSPIF=0;
//    SSPBUF=add;             //addΪ�������ݵ�ַ���������
//    while(SSPIF==0);
//    SSPIF=0;
// 
//   RSEN=1;
//   while(SSPIF==0);
//   SSPIF=0;
//   SSPBUF=0xA1;            //A��ȻΪ����豸��ַ��1��ʾ���룬��ʼ������豸��ȡ����
//   while(SSPIF==0);
//   SSPIF=0;
// 
//   RCEN=1;
//   while(SSPIF==0);
//   rdate=SSPBUF;
//   while(SSPIF==0);
//   SSPIF=0;
// 
// 
//   ACKDT=1;              //д��Ӧ���ź�
//   ACKEN=1;              //����Ӧ���ź�
//   while(SSPIF==0);
//   SSPIF=0; 
// 
//   PEN=1;
//   while(SSPIF==0);
//   SSPIF=0;
//   return(rdate);
//}

void Delay(unsigned int n)        //��ʱ7.5us  �����������ڲ�8M�����߼������ǲ���20181218
{
    while(n)
    {
        n--;
    }
}


void delaynms(unsigned int n)      //��ʱ12.5ms  �����������ڲ�8M����ʾ��������20181218
{
	unsigned int i,j;
    
		for(i=0;i<n;i++)
			for(j=0;j<1600;j++);
}