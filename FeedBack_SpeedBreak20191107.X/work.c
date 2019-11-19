#include"GlobalVar.h"
#include"work.h"
#include"Interrupt.h"
extern  unsigned char Sameple;
void MotorStart(void)      //����10S���ٵ�12000ת
{
    write_IIC(0x03,0x33 );    //1V  ����1200ת
    delaynms(100);
    write_IIC(0x03,0xD6 );    //1.2V  ����2800ת    //688
    delaynms(100);
    write_IIC(0x04,0xCC );
    delaynms(100);
    write_IIC(0x05,0x70 );    //1.7V  ����6000ת
    delaynms(100);
    write_IIC(0x06 ,0x66 );    //2V  ����9000ת
    delaynms(100);    
    write_IIC(0x07 ,0x09 );    //2.2V  ����11000ת
    delaynms(100);
    write_IIC(0x07 ,0x9E );    //2.2V  ����11000ת
    delaynms(100);
//    write_IIC(0x08 ,0x02 );    //2.2V  ����11000ת
//    delaynms(100);
//    write_IIC(0x08 ,0x66 );    //2.2V  ����11000ת
//    delaynms(100);
//    write_IIC(0x09 ,0xc4 );    //2.2V  ����11000ת
//    delaynms(100);
//    write_IIC(0x0A ,0x5A );    //2.2V  ����11000ת    ���2750
//    delaynms(100);
//    write_IIC(0x0A ,0xBE );    //2.2V  ����11000ת    ���2750
//    delaynms(100);
//    write_IIC(0x0A ,0xF0 );    //2.2V  ����11000ת    ���2750
//    delaynms(100);
//    
//    FG_CN_Count=0;                   //20181225
//    Flag_adjusting_speed = 0;
//    Flag_FG_Period = 0;
//    Flag_FG_Period_time=0; 
}
void MotorClose(void)     //����ɲ�����������ͣ.ֹ���޹���
{
    write_IIC(0x08 ,0xfc );    //2.2V  ����11000ת     2300
   delaynms(100);
    write_IIC(0x07 ,0x9E );    //2.2V  ����11000ת    1950
    delaynms(100);
//        write_IIC(0x07 ,0x09 );    //2.2V  ����11000ת    1801
//    delaynms(500);
    write_IIC(0x06 ,0x66 );    //2V  ����9000ת      1638
    delaynms(100); 
    write_IIC(0x05,0x70 );    //1.7V  ����6000ת    1392
    delaynms(100);
//        write_IIC(0x04,0xCC );    //                    1288
//    delaynms(500);
    write_IIC(0x03,0xD6 );   //1.2V  ����2800ת    982
    delaynms(100);
//    write_IIC(0x03,0x33 );    //1V  ����1200ת     819
//    delaynms(100);
    write_IIC(0x02,0x6B );    //1V  ����1200ת      619
    delaynms(100);  
    write_IIC(0x01,0xA3 );    //1V  ����1200ת      419
    delaynms(100);
    write_IIC(0x00,0x64 );    //1V  ����1200ת      100
    delaynms(100);
    write_IIC(0x00,0x32 );    //1V  ����1200ת      50
    delaynms(100);
    write_IIC(0x00,0x14 );    //1V  ����1200ת      20
    delaynms(100);
    write_IIC(0x00,0x00 );    //1V  ����1200ת
    delaynms(100);
    TMR1ON=1; 
    GIE=1; 
}
void Motor_adjusting_speed(void)     //�������
{
    while(Flag_FG_Period == 0);
     Flag_FG_Period=0;
     GIE=0;
    if(Flag_FG_Period_time>25)        //ת������Ҫ�Ӵ��ѹֵ
    { 
        VOLT=VOLT+1;                  //0.001V��1��ADֵ10ת���е���  
        VOLT_H=(VOLT&0xFF00)>>8;      //ʮ�����Ƶĸ��ֽ�
        VOLT_L=VOLT&0x00FF;           //ʮ�����Ƶĵ��ֽ�
        write_IIC(VOLT_H,VOLT_L );
        FG_Period_time=0; 
    }
    if(Flag_FG_Period_time<10)        //ת�ٿ���Ҫ��С��ѹֵ
    {           
        VOLT=VOLT-1;                  //0.001V��1��ADֵ10ת���е���  
        VOLT_H=(VOLT&0xFF00)>>8;
        VOLT_L=VOLT&0x00FF;
        write_IIC(VOLT_H,VOLT_L );
        FG_Period_time=0; 
    } 
     GIE=1; 
}
void Motor_working_time(void)           //���Ļ�����5���Ӷ�ʱ
{
    if(Flag_working_time>=500)            //��ʱ5����
    {
        Flag_working_time==0;
        Flag_FG_Period_time = 0;
        MotorClose();                      //5���ӵ�ֹͣ�������
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
