#include"GlobalVar.h"
#include"main.h"
#include "ADC.h"

#define	CLRWDT()	asm("clrwdt")

void The_Close(void);
unsigned char Start_Flag=0;
unsigned char Initial_Flag=0;
unsigned char Stop_Flag=0;
unsigned char kai=0;
extern unsigned char Key_Run;
extern unsigned char Onekey_Flag;

extern unsigned char Open_Cover_Flag;
extern unsigned int Open_Cover_times;

extern unsigned char Forbid_input;

unsigned char Once=0;
unsigned char Not_two=0;
unsigned char Count_Flag=0;
unsigned char Work_Flag=0;
unsigned char Start_KeyRun_Flag=0;

unsigned int ADC_Val;
void main(void)
{
    unsigned char i;
    InitDevices(); 
    write_IIC(0x00,0x00 );
	while(1)
    {  
        //DC检测
		if(PORTAbits.RA5 == 1)  {DC_LED_ON;}
		else                    {DC_LED_OFF;}
		//开盖检测
		if((Count_Flag == 0) && (Work_Flag == 1)) {Motor_LED_ON;}
		else if(Key_Run == 0 )                    {Motor_LED_OFF;}
		//电池状态检测 
        for(i=0;i<70;i++)
        {
		ADC_Val += ReadADC(3);
        }
        ADC_Val /=70;
        if(PORTAbits.RA5 == 1)
        {
            if(ADC_Val < 595)  {BAT_LED_ON;}
            else               {BAT_LED_OFF;}
        }
        else
        {
            if(ADC_Val< 510) 
		   {
                BAT_LED_ON;
                delaynms(50);
                BAT_LED_OFF;
                delaynms(50);
		    }        
            else if((ADC_Val >= 510) && (ADC_Val <595))  {BAT_LED_ON;}
            else if(ADC_Val >= 595)                      {BAT_LED_OFF;}
        }

        ///一键开关
		if((Onekey_Flag == 1) &&(Work_Flag == 0))
		{
            POWERON;
            EN_QD_ON;
            Onekey_LED_ON;
            Not_two = 1;
		}
        if((Onekey_Flag == 2) && (Work_Flag == 0))
		{
            DCT_ON;
            delaynms(10);
            DCT_OFF;
            POWEROFF; 
            EN_QD_OFF;
            Onekey_LED_OFF;
            Not_two = 0;
            Onekey_Flag = 0;  
		}
		//合盖运行
		if((PORTAbits.RA1 == 0) &&  (Not_two == 1))
		{      		
			if(Key_Run == 1)
			{  
                WDTCONbits.SWDTEN  = 1;       
				CLRWDT();
				while(Initial_Flag == 0) //给一个初速度
				{
					Work_Flag = 1;
					Count_Flag = 1;
					write_IIC(0x03,0x33 );    //1V  819
					delaynms(1);
					write_IIC(0x04,0x4c );    //1V  1100
					delaynms(1);
					Initial_Flag = 1;
					kai = 1;
					break;
				}
				if((Start_Flag == 0)&&(kai == 1))         
				{
                    CLRWDT();
					Motor_adjusting_speed();
				}
				else  if(Stop_Flag == 1)      
				{
					Open_Cover_Flag = 1;
					if(Once == 0)
					{
						MotorClose();
						Once = 1;
						Forbid_input = 1;
					}
					Count_Flag=0; 
					if(Open_Cover_times >= 2700)
					{     				
						The_Close();
					} 
				}
			}
			else if(Key_Run == 2)
			{
				CLRWDT();
				Open_Cover_Flag = 1;
				Forbid_input = 1;
				if(Once == 0)
				{
					MotorClose();
					Once = 1;
				}   
				Count_Flag=0; 
				if(Open_Cover_times >= 2700)
				{     
					The_Close();
				}
			}
		}
		else if (PORTAbits.RA1 != 0)   write_IIC(0x00,0x00 );
		else if((PORTAbits.RA1 != 0) && (Initial_Flag == 1))
		{
			while(1)
			{
				write_IIC(0x00,0x00 ); ;
			}
		}
     }
}
void The_Close(void)
{
    kai = 0;  
    Stop_Flag = 0;       
    Start_Flag = 0;
    Initial_Flag = 0;
    Work_Flag = 0;       
    VOLT=1150;    
    Open_Cover_Flag = 0;
    Open_Cover_times = 0;
    DCT_ON;
    delaynms(10);
    DCT_OFF;
    Key_Run = 0;
    Once = 0;
    Forbid_input=0;
    WDTCONbits.SWDTEN  = 0;
}