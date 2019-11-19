//  Define global variable

#ifndef GLOBALVAR_H
#define	GLOBALVAR_H

#include"Define.h"
#include <htc.h>
extern unsigned int  Flag_FG_Period_time;
extern unsigned char  Flag_FG_Period;
extern unsigned int  Flag_adjusting_speed;
extern unsigned int  Flag_working_time;
extern unsigned char  FG_CN_Count;
extern unsigned int  FG_Period_time;


extern unsigned int  VOLT;
extern unsigned char  VOLT_H;
extern unsigned char  VOLT_L;
extern unsigned int  Volt_12000;

extern unsigned char Start_Flag;
extern unsigned char Initial_Flag;
extern unsigned char Stop_Flag;



extern void write(unsigned char add,unsigned char wdate);
extern void write_IIC(unsigned char wdate_H,unsigned char wdate_L);
extern unsigned char read(unsigned char add);
extern void Delay(unsigned int n);        //1.5us
extern void delaynms(unsigned int n);   

extern void MotorStart(void);      //空载10S加速到12000转
extern void MotorClose(void);
extern void Motor_adjusting_speed(void);
extern void Motor_working_time(void);

extern void InitDevices(void);
extern void ErrorControl(unsigned char n);
extern unsigned char SystemCheck(void);
#endif	/* GLOBALVAR_H */
