/* 
 * File:   ADC.h
 * Author: Administrator
 *
 * Created on December 12, 2018, 5:12 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

unsigned char adsum; //四次AD采集所得的平均值
unsigned char ADC_RESULT_BAT;
unsigned int REALVOLTAGE_BAT_DC; 
bit RELAY_BAT=0;
bit RELAY_AC=0;
unsigned int get1_ad(void);			//获得AD值
unsigned int ReadADC(unsigned char ADC_Channel);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

