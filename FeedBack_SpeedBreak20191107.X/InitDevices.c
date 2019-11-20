#include"GlobalVar.h"
#include"InitDevices.h"

extern unsigned char RecFlag;

typedef struct{
    unsigned char WorkMode;
    unsigned char WorkStates;
    unsigned char SetDis;
    unsigned char Direction;
    unsigned char RunTime;
    unsigned int  HallCounter;
    unsigned int  SetHallCounter;
    unsigned int  MinDepth;
    unsigned int  MaxDepth;
    unsigned int  StartDepth;
    unsigned char RecTime;
    unsigned char PressCounter;
    unsigned char DisErrorStates;
    unsigned char CurErroeStates;
}States;
extern States SystemStates;

void systemOSC(void)
{
    OSCCON = 0X71;  //8M  
}

void PortInit(void)
{
    PORTA = 0x00;  
    PORTB = 0x00;
    TRISA = 0xEB;     //7 6 5 3 1 0  输入 A
    TRISB = 0X12;    // 4 1 输入 B
    PORTC = 0X00;
    TRISC = 0XE2;    // 7 6 5 1 输入C
    ANSELH = 0x00;
//    ANSEL = 0x19;    // 5  3  0  ADC A
//    WPUB = 0xf8;   //弱上拉功能设置
}

void InitialiseADC(void)
{
//     TRISAbits.TRISA6 = 0;
//    TRISBbits.TRISB1 = 1;
//    TRISBbits.TRISB4 = 1;
    ANSEL = 0x08;  //analog   AN3
  //  ADCON0 = 0x8F;
    ADCON1 = 0x80;  
    ADRESL = 0;	 
    ADRESH = 0;
    ADIE = 0;
    PEIE = 1;
    ADIF = 0;
    GO_DONE = 1;
    ADON = 1;
}

//void InitialiseADC(void)
//{
//    TRISB |= 0x3c;  //输入
//    ANSELH |= 0x2d;  //模拟 注意端口的一一对应关系   见数据手册P50
//    ADCON1 = 0x00;  //数据zuo对齐
//}

void IIC_init(void)
{
    TRISC3=1;     
    TRISC4=1;
    SSPSTAT=0x80;
    SSPCON=0x28;    //CKP高电平空闲，因为I2C必须加上拉电阻，所以设定高电平空闲
    SSPCON2=0;      //开始设为0，在读写的过程中相应改变其中的寄存器
//    SSPADD=0x09;   //主频是4M时设置波特率100KHz，时钟=Fosc/[4*(SSPADD+1)
  // I2C波特率=Fosc/(4*(SSPADD+1))
  // SSPADD=[(Fosc/(BandRate*4)]-1
    SSPADD=0x13;    //主频是8M时设置波特率100KHz，时钟=Fosc/[4*(SSPADD+1)
}


void InitTimer0(void)      //定时64uS
{
    OPTION_REG = 0X86;      //使用内部指令周期时钟；预分频分配给Timer0；预分频比为1:128
    TMR0 = 0XFF;
    T0IE=0;                 //不允许中断
}
void InitTimer1(void)     //定时50ms
{
    T1CON=0x00;   
    TMR1CS = 0;              //Timer1 使用内部时钟,时钟源的频率为 FOSC/4    2MHz    
    T1CONbits.T1CKPS0=1;    //clock pre_div 1:2    1MHz   1us 
    T1CONbits.T1CKPS1=0;
//    TMR1=50000;             //1us*(65536-50000)=15ms     
    TMR1=15536;             //1us*(65536-15536)=50ms 
    TMR1IE=1;
    TMR1IF = 0;
    TMR1ON=0;          //关闭定时器1
}

void InitTimer2(void)   //定时100us
{
    T2CON = 0X00;        //Timer2 预分频1：1 后分频1：1   时钟2MHz  0.5uS
    TMR2=0;
    PR2=199;             //T2, 199：（199+1）*0.5us=100us   197:（197+1）*0.5us=99us   19：（19+1）*0.5us=10us  
    TMR2IE=1;
    TMR2IF = 0;
    TMR2ON = 0;
}

void InitCn(void)
{
   IOCB=0X10;       //电平变化中断选择位RB4
   RBIE=1;
   RBIF=0;
}

void InitDevices(void)
{
    systemOSC();
    PortInit();
    InitTimer0();
    InitTimer1();
    IIC_init();
    InitialiseADC();
    InitTimer2();
    InitCn();
    PEIE = 1;
    TMR1ON=1; 
    GIE=1; 
      //WDTCON = 0x17;//2048ms
    WDTCON = 0x12;//512ms  

}
