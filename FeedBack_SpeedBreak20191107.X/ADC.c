#include"GlobalVar.h"
#include "ADC.h"
//==============================================================
//AD初始化
//获得AD值		
//返回的结果为8位
//==============================================================

unsigned int get1_ad(void)			//获得AD值
{
	unsigned int adval = 0;
    unsigned int t;
    t = ADIF;
	ADIF=0;	//清除A/D转换标志
	GO_DONE=1; 			//ADGO就是GO/DONE的位操作标识
    ADRESH = 0;
    ADRESL = 0;
	while(GO_DONE);		//ADGO为0转换完成。查询方式。
	adval |=(ADRESH << 8);
    adval |= ADRESL;   

	return (adval);	
}

//==============================================================
//4次AD结果的平均值
//入口：工作模式与转换通道		
//返回的结果为8位
//==============================================================
unsigned int ReadADC(unsigned char ADC_Channel)
{
    static unsigned int ADC_VALUE;
    unsigned char i;
    ADC_Channel %=16; 
    /* Selecting ADC channel */
    ADCON0 = 0x80 +(ADC_Channel<<2) + 0x01;    //Fosc/32 ,????,Enable ADC
    ADIE =	0;                	               /* Masking the interrupt */
    ADIF = 0;	                                   /* Resetting the ADC interupt bit */
    ADRESL	=	0;	                           /* Resetting the ADRES value register */
    ADRESH	=	0;
    GO = 1;	                                  /* Staring the ADC process */
    while(!ADIF) continue;			          /* Wait for conversion complete */
    ADC_VALUE	=	 ADRESL;	                  /* Getting HSB of CCP1 */
    ADC_VALUE	+= (ADRESH << 8);	            /* Getting LSB of CCP1 */
    return (ADC_VALUE);                        /* Return the value of the ADC process */
}