#include <htc.h>
#include"Define.h"
extern unsigned char ReceviceData[8];
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
extern unsigned int SystemTime;
extern unsigned int GetStartDepth(void);
extern unsigned char SystemError;


void putchar(unsigned char byte)
{
/* output one byte */
    while(!TXIF)	/* set when register is empty */
    continue;
    TXREG = byte;
}


void SendData(unsigned char *p,unsigned char n)
{
    unsigned char i;
    for(i = 0; i < n; i ++)
    {
        putchar(*p);
        p ++;
    }
}


void ProcessUart(void)
{
    static unsigned char SendStates;
    if((ReceviceData[0] == 0xA5) && (ReceviceData[1] == 0x5A))
    {
        putchar(SendStates);//Ó¦´ð
        if(ReceviceData[6] == (ReceviceData[2] + ReceviceData[3] + ReceviceData[4] + ReceviceData[5]))
        {
            if(SendStates == 0)
            {
                SendStates = 0xff;
                
            }
            else
            {
                SendStates = 0;
            }
            LED = ~LED;
//            putchar(SendStates);//Ó¦´ð
            switch(ReceviceData[3])
            {
                case test:
//                    mindepth = initdepth + ReceviceData[4] - 70;
//                    maxdepth = initdepth + ReceviceData[4] * 50 + 50;
                    break;
               case depth://
                   SystemStates.SetDis = ReceviceData[4];
                   SystemStates.SetHallCounter = ReceviceData[4] * 3;
                   SystemStates.MinDepth = SystemStates.StartDepth -  TOPOFFSET;
                   SystemStates.MaxDepth = SystemStates.StartDepth + ReceviceData[4] * 6 + BUTOFFSET;
                   break;
               case frequency:
//                   workfrequency = ReceviceData[4];
                   break;
               case workmode:
                   if(ReceviceData[4] == 0)
                   {
                       SystemStates.WorkMode = Mode30_2;
                   }
                   else if(ReceviceData[4] == 1)
                   {
                       SystemStates.WorkMode = ModeCon;
                   }
                   break;
               case startmode:
                   if(ReceviceData[4] == 0)
                   {
                       SystemStates.WorkStates = StatesStop;
                   }
                   else if(ReceviceData[4] == 1)
                   {
                       SystemStates.WorkStates = StatesRun;
                       SystemStates.RunTime = 0;
                   }
                   else if(ReceviceData[4] == 2)
                   {
                       SystemStates.WorkStates = StatesPause;
                   }
                   break;
                case adjust:
                    if(SystemStates.WorkStates == stop)
                    {
                        if((ReceviceData[4] == 1) && (ReceviceData[5] == 0))
                        {
                            if(SystemError)
                            {
                                SystemError = 0;
                                DRIVERBY304;
                            }
                        }
                        else if((ReceviceData[4] == 0) && (ReceviceData[5] == 1))
                        {
                            SystemTime = 0;
                            SystemStates.StartDepth = GetStartDepth();
                            if(SystemStates.StartDepth < POTBUTMIN)
                            {
                                SystemError = 7;//
                            }
                            else if(SystemStates.StartDepth > POTTOPMAX)
                            {
                                SystemError = 8;//
                            }
                            SystemStates.MinDepth = SystemStates.StartDepth - TOPOFFSET;
                            SystemStates.MaxDepth = SystemStates.StartDepth + SystemStates.SetDis * 6 + BUTOFFSET;
                        }
                    }
                    break;
               case rest:
//                   asm("reset");
                   while(1);//wait for rest
                   break;
                case clear:
                    SystemError = 0;
                    DRIVERBY304;
                    break;
                default:
                   break;
            }
        }
    }
    RecFlag = EMPTY;
}
