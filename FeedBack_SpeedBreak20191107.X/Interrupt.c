#include"GlobalVar.h"
#include"Interrupt.h"
#include "ADC.h"
void interrupt com(void)    
{ 
    if(RBIF)
    { 
		RBCN_int(); 
    }
    if(TMR2IF)
    {
        TMR2_int();  
    } 
    if(TMR1IF)
    {
		TMR1_int();  
    }
	//       if(ADIF != 0)
	//    {
	//       get1_ad();  
	//    }
    
}
extern unsigned char Start_Flag;
extern unsigned char Initial_Flag;
extern unsigned char Stop_Flag;
//unsigned int ADC_Val;

extern unsigned char Start_KeyRun_Flag;
extern unsigned char Count_Flag;
extern unsigned char Work_Flag;

unsigned char Key_Run_times=0;
unsigned char Key_Run=0;
unsigned char Key_Up=0;

unsigned char Open_Cover_Flag=0;
unsigned int Open_Cover_times=0;

unsigned int Speed_LED_times=0;
unsigned int BAT_LED_times=0;

unsigned char Onekey_Flag=0;
unsigned char Onekey_times=0;
unsigned char Onekey_Key_Up=0;

unsigned char Forbid_input=0;
extern unsigned char Not_two;
void  TMR1_int(void)                  //50ms
{
    unsigned char t,i;
    t = TMR1IF;
    TMR1IF =0;                //clear interrupt flag
    TMR1=15536; 
    //���״̬��� 
	//     for(i=0;i<10;i++)
	//     {
	//          ADC_Val += ReadADC(3);
	//     }
	//     ADC_Val/=10;
	//     if((ADC_Val< 530)) 
	//        {
	//           BAT_LED_times++;
	//           if(BAT_LED_times == 20)
	//           {
	//            PORTBbits.RB5 = ~PORTBbits.RB5;
	//            BAT_LED_times=0;
	//           }
	//        }
	//        else if(ADC_Val > 595) 
	//        {
	//            BAT_LED_OFF;
	//        } 
	//        else  if((ADC_Val < 565) && (ADC_Val> 540))
	//        {
	//            BAT_LED_ON;
	//        }
	
	//��ͣ���ؼ��
    if((PORTAbits.RA1 == 0) &&  (Not_two == 1) && (Forbid_input == 0))
    {
		if(PORTBbits.RB1 == 1)   Key_Up = 0;
		if((PORTBbits.RB1 == 0) && (Key_Up == 0))
		{
			Key_Run_times++;
			if(Key_Run_times == 40) 
			{
				Key_Run++;
				Key_Run_times = 0;
				Key_Up = 1;
			}
		} else   Key_Run_times = 0;  
    }
    //һ�����ؼ��
	if(Work_Flag == 0)
	{
        if(PORTCbits.RC1 == 1)   Onekey_Key_Up = 0;
        if((PORTCbits.RC1 == 0) && (Onekey_Key_Up == 0))
        {
            Onekey_times++;
            if(Onekey_times == 40)
            {
                Onekey_Flag++;
                Onekey_times =0;
                Onekey_Key_Up = 1;
            }
        } else   Onekey_times = 0;
	}
	//�������ʱ������
    if(Open_Cover_Flag == 1)
    {
		Open_Cover_times++;
    }
	//�ٶ�LED��ʾ
    if(Count_Flag == 1)
    {
        Flag_working_time++;       
        if((Flag_working_time >= 6000) )  
        {
            Start_Flag = 1;
            Stop_Flag = 1; 
            Flag_working_time = 0; 
        }    
		if(Flag_working_time > 400) 
        {
            Speed_LED_times++;
            if(Speed_LED_times == 20)
            {
				PORTBbits.RB0 = ~ PORTBbits.RB0;
				Speed_LED_times = 0;
            }
        }else    Motor_LED_ON;
    } else  Flag_working_time = 0; 
}
void TMR2_int(void)                       //100us
{
    TMR2IF=0;  
    TMR2=0;//clear interrupt flag  
    FG_Period_time++;  
    if(FG_Period_time >=300)  FG_Period_time = 300;
}
void RBCN_int(void)
{
    unsigned char Sameple;
    Sameple =  PORTB;
    RBIF=0;  
    FG_CN_Count++;
    if(FG_CN_Count==3)         //FG�Ƿ�Ϊһ�����ڣ�
    {
        FG_CN_Count=0;
        TMR2ON=0; //��ʱ��2ֹͣ����
        Flag_FG_Period=1;      //1�����ڱ�־λ��1    
        Flag_FG_Period_time=FG_Period_time;   
		FG_Period_time=0; 
    }
    else
    {
        TMR2ON=1;
    }
	
}