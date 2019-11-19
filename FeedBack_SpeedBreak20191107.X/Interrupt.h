#ifndef INTERRUPT_H
#define	INTERRUPT_H


unsigned char  FG_CN_Count=0;                  //FG��ƽ�жϼ���,�����ж�3��ʱ��FGΪһ�����ڡ�
unsigned char  Flag_FG_Period=1;             //FGһ�����ڵı�־λ
unsigned int  Flag_FG_Period_time=0;        //FG����һ������ʱ��ı�־λ
unsigned int  FG_Period_time=0;             //FGһ������ʱ��
unsigned int  Flag_adjusting_speed=0;       //�����ٶȱ�־λ
unsigned int   Flag_working_time=0;          //��ʱ����5���ӱ�־λ


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
