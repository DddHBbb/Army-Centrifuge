
#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
//�汾��LXJ-F886-V1.0.X ����˱ջ����ٹ��ܡ�
//�汾��LXJ-F886-V2.0.X �ð汾�Ӽ�ʱ5�������Ĺ��ܣ���δ���Գɹ�20190107

//__CONFIG(0XE0FC);

__CONFIG(FOSC_INTRC_CLKOUT  & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_ON & IESO_ON & FCMEN_ON & LVP_OFF);    
__CONFIG(BOR4V_BOR40V & WRT_OFF);
//__CONFIG(0XE0F4);	//�ڲ�����


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

