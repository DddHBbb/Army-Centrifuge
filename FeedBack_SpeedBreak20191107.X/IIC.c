#include"GlobalVar.h"
#include "IIC.h"

void write_IIC(unsigned char wdate_H,unsigned char wdate_L)
{ 
    int t=0;
    SSPIF=0;
    SEN=1;            //启动信号
    while(SSPIF==0)//1的时候是真  0的时候是假  ！SSPIF为非真，为假退出语句
    {
        t++;
      if(t > 1000)   break;
    }
    t=0;
    SSPIF=0;          //软件清零  不会自动清零
    
    SSPBUF=0X98;      //发送设备地址
    Delay(1);
    while(SSPIF==0)  //判断是否发送完毕
    {
        t++;
      if(t > 1000)   break;
    }
    t=0;
    SSPIF=0;
      
    SSPBUF=wdate_H;     //写入高字节数据
    Delay(1);
    while(SSPIF==0) //每发送一个数据都要检测是否成功
    {
        t++;
      if(t > 1000)   break;
    }
    t=0;
    SSPIF=0;
 
    SSPBUF=wdate_L;     //写入低字节数据
    Delay(1);
    while(SSPIF==0)  //每发送一个数据都要检测是否成功
    {
        t++;
      if(t > 1000)   break;
    }
    t=0;
    SSPIF=0;
    
    PEN=1;            //发送停止信号
    while(SSPIF==0)  //如果收到停止信号同样会置位
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
//    SSPBUF=0xA0;            //传输设备地址
//    while(SSPIF==0);
//    SSPIF=0;
//    SSPBUF=add;             //add为读地数据地址，灵活设置
//    while(SSPIF==0);
//    SSPIF=0;
// 
//   RSEN=1;
//   while(SSPIF==0);
//   SSPIF=0;
//   SSPBUF=0xA1;            //A仍然为外接设备地址，1表示输入，开始从外接设备读取数据
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
//   ACKDT=1;              //写入应答信号
//   ACKEN=1;              //发送应答信号
//   while(SSPIF==0);
//   SSPIF=0; 
// 
//   PEN=1;
//   while(SSPIF==0);
//   SSPIF=0;
//   return(rdate);
//}

void Delay(unsigned int n)        //定时7.5us  测试条件：内部8M晶振，逻辑分析仪测试20181218
{
    while(n)
    {
        n--;
    }
}


void delaynms(unsigned int n)      //定时12.5ms  测试条件：内部8M晶振，示波器测试20181218
{
	unsigned int i,j;
    
		for(i=0;i<n;i++)
			for(j=0;j<1600;j++);
}