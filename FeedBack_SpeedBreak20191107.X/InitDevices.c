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
    TRISA = 0xEB;     //7 6 5 3 1 0  ���� A
    TRISB = 0X12;    // 4 1 ���� B
    PORTC = 0X00;
    TRISC = 0XE2;    // 7 6 5 1 ����C
    ANSELH = 0x00;
//    ANSEL = 0x19;    // 5  3  0  ADC A
//    WPUB = 0xf8;   //��������������
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
//    TRISB |= 0x3c;  //����
//    ANSELH |= 0x2d;  //ģ�� ע��˿ڵ�һһ��Ӧ��ϵ   �������ֲ�P50
//    ADCON1 = 0x00;  //����zuo����
//}

void IIC_init(void)
{
    TRISC3=1;     
    TRISC4=1;
    SSPSTAT=0x80;
    SSPCON=0x28;    //CKP�ߵ�ƽ���У���ΪI2C������������裬�����趨�ߵ�ƽ����
    SSPCON2=0;      //��ʼ��Ϊ0���ڶ�д�Ĺ�������Ӧ�ı����еļĴ���
//    SSPADD=0x09;   //��Ƶ��4Mʱ���ò�����100KHz��ʱ��=Fosc/[4*(SSPADD+1)
  // I2C������=Fosc/(4*(SSPADD+1))
  // SSPADD=[(Fosc/(BandRate*4)]-1
    SSPADD=0x13;    //��Ƶ��8Mʱ���ò�����100KHz��ʱ��=Fosc/[4*(SSPADD+1)
}


void InitTimer0(void)      //��ʱ64uS
{
    OPTION_REG = 0X86;      //ʹ���ڲ�ָ������ʱ�ӣ�Ԥ��Ƶ�����Timer0��Ԥ��Ƶ��Ϊ1:128
    TMR0 = 0XFF;
    T0IE=0;                 //�������ж�
}
void InitTimer1(void)     //��ʱ50ms
{
    T1CON=0x00;   
    TMR1CS = 0;              //Timer1 ʹ���ڲ�ʱ��,ʱ��Դ��Ƶ��Ϊ FOSC/4    2MHz    
    T1CONbits.T1CKPS0=1;    //clock pre_div 1:2    1MHz   1us 
    T1CONbits.T1CKPS1=0;
//    TMR1=50000;             //1us*(65536-50000)=15ms     
    TMR1=15536;             //1us*(65536-15536)=50ms 
    TMR1IE=1;
    TMR1IF = 0;
    TMR1ON=0;          //�رն�ʱ��1
}

void InitTimer2(void)   //��ʱ100us
{
    T2CON = 0X00;        //Timer2 Ԥ��Ƶ1��1 ���Ƶ1��1   ʱ��2MHz  0.5uS
    TMR2=0;
    PR2=199;             //T2, 199����199+1��*0.5us=100us   197:��197+1��*0.5us=99us   19����19+1��*0.5us=10us  
    TMR2IE=1;
    TMR2IF = 0;
    TMR2ON = 0;
}

void InitCn(void)
{
   IOCB=0X10;       //��ƽ�仯�ж�ѡ��λRB4
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
