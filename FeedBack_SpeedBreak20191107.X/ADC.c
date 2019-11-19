#include"GlobalVar.h"
#include "ADC.h"
//==============================================================
//AD��ʼ��
//���ADֵ		
//���صĽ��Ϊ8λ
//==============================================================

unsigned int get1_ad(void)			//���ADֵ
{
	unsigned int adval = 0;
    unsigned int t;
    t = ADIF;
	ADIF=0;	//���A/Dת����־
	GO_DONE=1; 			//ADGO����GO/DONE��λ������ʶ
    ADRESH = 0;
    ADRESL = 0;
	while(GO_DONE);		//ADGOΪ0ת����ɡ���ѯ��ʽ��
	adval |=(ADRESH << 8);
    adval |= ADRESL;   

	return (adval);	
}

//==============================================================
//4��AD�����ƽ��ֵ
//��ڣ�����ģʽ��ת��ͨ��		
//���صĽ��Ϊ8λ
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