#include"GlobalVar.h"
#include"work.h"
#include"Interrupt.h"
extern  unsigned char Sameple;
void MotorStart(void)      //空载10S加速到12000转
{
    write_IIC(0x03,0x33 );    //1V  空载1200转
    delaynms(100);
    write_IIC(0x03,0xD6 );    //1.2V  空载2800转    //688
    delaynms(100);
    write_IIC(0x04,0xCC );
    delaynms(100);
    write_IIC(0x05,0x70 );    //1.7V  空载6000转
    delaynms(100);
    write_IIC(0x06 ,0x66 );    //2V  空载9000转
    delaynms(100);    
    write_IIC(0x07 ,0x09 );    //2.2V  空载11000转
    delaynms(100);
    write_IIC(0x07 ,0x9E );    //2.2V  空载11000转
    delaynms(100);
//    write_IIC(0x08 ,0x02 );    //2.2V  空载11000转
//    delaynms(100);
//    write_IIC(0x08 ,0x66 );    //2.2V  空载11000转
//    delaynms(100);
//    write_IIC(0x09 ,0xc4 );    //2.2V  空载11000转
//    delaynms(100);
//    write_IIC(0x0A ,0x5A );    //2.2V  空载11000转    最大2750
//    delaynms(100);
//    write_IIC(0x0A ,0xBE );    //2.2V  空载11000转    最大2750
//    delaynms(100);
//    write_IIC(0x0A ,0xF0 );    //2.2V  空载11000转    最大2750
//    delaynms(100);
//    
//    FG_CN_Count=0;                   //20181225
//    Flag_adjusting_speed = 0;
//    Flag_FG_Period = 0;
//    Flag_FG_Period_time=0; 
}
void MotorClose(void)     //带有刹车，电机立即停.止，无惯性
{
    write_IIC(0x08 ,0xfc );    //2.2V  空载11000转     2300
   delaynms(100);
    write_IIC(0x07 ,0x9E );    //2.2V  空载11000转    1950
    delaynms(100);
//        write_IIC(0x07 ,0x09 );    //2.2V  空载11000转    1801
//    delaynms(500);
    write_IIC(0x06 ,0x66 );    //2V  空载9000转      1638
    delaynms(100); 
    write_IIC(0x05,0x70 );    //1.7V  空载6000转    1392
    delaynms(100);
//        write_IIC(0x04,0xCC );    //                    1288
//    delaynms(500);
    write_IIC(0x03,0xD6 );   //1.2V  空载2800转    982
    delaynms(100);
//    write_IIC(0x03,0x33 );    //1V  空载1200转     819
//    delaynms(100);
    write_IIC(0x02,0x6B );    //1V  空载1200转      619
    delaynms(100);  
    write_IIC(0x01,0xA3 );    //1V  空载1200转      419
    delaynms(100);
    write_IIC(0x00,0x64 );    //1V  空载1200转      100
    delaynms(100);
    write_IIC(0x00,0x32 );    //1V  空载1200转      50
    delaynms(100);
    write_IIC(0x00,0x14 );    //1V  空载1200转      20
    delaynms(100);
    write_IIC(0x00,0x00 );    //1V  空载1200转
    delaynms(100);
    TMR1ON=1; 
    GIE=1; 
}
void Motor_adjusting_speed(void)     //电机调速
{
    while(Flag_FG_Period == 0);
     Flag_FG_Period=0;
     GIE=0;
    if(Flag_FG_Period_time>25)        //转速慢需要加大电压值
    { 
        VOLT=VOLT+1;                  //0.001V即1个AD值10转进行调整  
        VOLT_H=(VOLT&0xFF00)>>8;      //十六进制的高字节
        VOLT_L=VOLT&0x00FF;           //十六进制的低字节
        write_IIC(VOLT_H,VOLT_L );
        FG_Period_time=0; 
    }
    if(Flag_FG_Period_time<10)        //转速快需要减小电压值
    {           
        VOLT=VOLT-1;                  //0.001V即1个AD值10转进行调整  
        VOLT_H=(VOLT&0xFF00)>>8;
        VOLT_L=VOLT&0x00FF;
        write_IIC(VOLT_H,VOLT_L );
        FG_Period_time=0; 
    } 
     GIE=1; 
}
void Motor_working_time(void)           //离心机工作5分钟定时
{
    if(Flag_working_time>=500)            //定时5分钟
    {
        Flag_working_time==0;
        Flag_FG_Period_time = 0;
        MotorClose();                      //5分钟到停止电机运行
        TMR1ON =0;
        TMR2ON =0;
        GIE = 0;
    }
}
unsigned char SystemCheck(void)
{
    
}


void ErrorControl(unsigned char n)
{

}
