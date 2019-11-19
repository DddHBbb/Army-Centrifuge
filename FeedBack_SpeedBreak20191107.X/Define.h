
#ifndef DEFINE_H
#define	DEFINE_H

#ifdef	__cplusplus
extern "C" {
#endif
    

#define POWERON      PORTCbits.RC0= 1;asm ("NOP")
#define POWEROFF     PORTCbits.RC0 = 0;asm ("NOP")
#define EN_QD_ON      PORTAbits.RA4= 1;asm ("NOP")
#define EN_QD_OFF     PORTAbits.RA4 = 0;asm ("NOP") 
#define DCT_ON        PORTAbits.RA2 = 1;asm ("NOP") 
#define DCT_OFF       PORTAbits.RA2 = 0;asm ("NOP") 
    
#define DC_LED_ON            PORTBbits.RB2 = 1;asm ("NOP") 
#define DC_LED_OFF           PORTBbits.RB2 = 0;asm ("NOP") 
    
#define BAT_LED_ON           PORTBbits.RB3 = 1;asm ("NOP") 
#define BAT_LED_OFF          PORTBbits.RB3 = 0;asm ("NOP") 
    
#define Motor_LED_ON         PORTBbits.RB0 = 1;asm ("NOP") 
#define Motor_LED_OFF        PORTBbits.RB0 = 0;asm ("NOP") 
    
#define Onekey_LED_ON        PORTBbits.RB5 = 1;asm ("NOP") 
#define Onekey_LED_OFF       PORTBbits.RB5 = 0;asm ("NOP") 
    
//#define Volt_12000  23        //空载12000转时的电压值是2.3V
    
//#define TM2_TIME 38         //T2,  38: (38+1)*256us=10ms , n*10ms=the time of open or close valve time
//#define TM1_TIME 40536      //8us*(65536-40536)=200ms,   8us*(65536-63036)=20ms, 8us*(65536-53036)=100ms,8us*(65536-3036)=500ms,    
//ADC定义
//#define voltge_ADC_Channel  4
//#define LeftPosition_ADC_Channel   8
//#define Current_ADC_Channel  10
//#define rightPosition_ADC_Channel  12
//#define LED             PORTCbits.RC1
//#define MOTORON         PORTCbits.RC4 = 1;NOP();
//#define MOTOROFF        PORTCbits.RC4 = 0;NOP();
//#define CON1OFF         PORTCbits.RC5 = 0;NOP();
//#define CON1ON          PORTCbits.RC5 = 1;NOP();
//#define CON2OFF         PORTCbits.RC6 = 0;NOP();
//#define CON2ON          PORTCbits.RC6 = 1;NOP();
//#define timeflag        PORTCbits.RC0
//#define ATOBON          PORTCbits.RC0 = 1;NOP();
//#define ATOBOFF         PORTCbits.RC0 = 0;NOP();
//#define PINAB           PORTCbits.RC0
    

    
    
#ifdef	__cplusplus
}
#endif

#endif	/* DEFINE_H */
