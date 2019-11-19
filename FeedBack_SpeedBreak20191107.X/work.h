
#ifndef WORK_H
#define	WORK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
void MotorStart(void);      //空载10S加速到12000转
void MotorClose(void);
void Motor_adjusting_speed(void);
void Motor_working_time(void);
unsigned int ReadADC(unsigned char ADC_Channel);


void ErrorControl(unsigned char n);
unsigned char SystemCheck(void);

unsigned int  VOLT=1150;        //空载12000转时的电压值2.3V，AD值为1883
unsigned char  VOLT_H;
unsigned char  VOLT_L;


extern unsigned char  FG_CN_Count;                  //FG电平中断计数,进入中断3次时，FG为一个周期。
extern unsigned char  Flag_FG_Period;             //FG一个周期的标志位
extern unsigned int  Flag_FG_Period_time;        //FG到达一个周期时间的标志位
extern unsigned int  FG_Period_time;             //FG一个周期时间
extern unsigned int  Flag_adjusting_speed;       //调整速度标志位
extern unsigned int   Flag_working_time;          //定时工作5分钟标志位

#ifdef	__cplusplus
}
#endif

#endif	/* WORK_H */

