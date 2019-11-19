
#ifndef WORK_H
#define	WORK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
void MotorStart(void);      //����10S���ٵ�12000ת
void MotorClose(void);
void Motor_adjusting_speed(void);
void Motor_working_time(void);
unsigned int ReadADC(unsigned char ADC_Channel);


void ErrorControl(unsigned char n);
unsigned char SystemCheck(void);

unsigned int  VOLT=1150;        //����12000תʱ�ĵ�ѹֵ2.3V��ADֵΪ1883
unsigned char  VOLT_H;
unsigned char  VOLT_L;


extern unsigned char  FG_CN_Count;                  //FG��ƽ�жϼ���,�����ж�3��ʱ��FGΪһ�����ڡ�
extern unsigned char  Flag_FG_Period;             //FGһ�����ڵı�־λ
extern unsigned int  Flag_FG_Period_time;        //FG����һ������ʱ��ı�־λ
extern unsigned int  FG_Period_time;             //FGһ������ʱ��
extern unsigned int  Flag_adjusting_speed;       //�����ٶȱ�־λ
extern unsigned int   Flag_working_time;          //��ʱ����5���ӱ�־λ

#ifdef	__cplusplus
}
#endif

#endif	/* WORK_H */

