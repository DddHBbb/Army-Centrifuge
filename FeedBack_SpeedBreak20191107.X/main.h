
#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
//版本：LXJ-F886-V1.0.X 完成了闭环调速功能。
//版本：LXJ-F886-V2.0.X 该版本加计时5分钟离心功能，还未调试成功20190107

//__CONFIG(0XE0FC);

__CONFIG(FOSC_INTRC_CLKOUT  & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_ON & IESO_ON & FCMEN_ON & LVP_OFF);    
__CONFIG(BOR4V_BOR40V & WRT_OFF);
//__CONFIG(0XE0F4);	//内部晶振


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

