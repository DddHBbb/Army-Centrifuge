#ifndef INTERRUPT_H
#define	INTERRUPT_H


unsigned char  FG_CN_Count=0;                  //FG电平中断计数,进入中断3次时，FG为一个周期。
unsigned char  Flag_FG_Period=1;             //FG一个周期的标志位
unsigned int  Flag_FG_Period_time=0;        //FG到达一个周期时间的标志位
unsigned int  FG_Period_time=0;             //FG一个周期时间
unsigned int  Flag_adjusting_speed=0;       //调整速度标志位
unsigned int   Flag_working_time=0;          //定时工作5分钟标志位


extern unsigned char Start_Flag;
extern unsigned char Initial_Flag;
extern unsigned char Stop_Flag;

void interrupt com(void); 
void TMR2_int(void);
void TMR1_int(void);
void TMR0_int(void);
void RBCN_int(void);
//void AD_int(void);


#endif	/* INTERRUPT_H */
