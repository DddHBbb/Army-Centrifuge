/* 
 * File:   IIC.h
 * Author: 
 *
 * Created on December 12, 2018, 2:57 PM
 */

#ifndef IIC_H
#define	IIC_H

#ifdef	__cplusplus
extern "C" {
#endif

//void write(unsigned char add,unsigned char wdate);
void write_IIC(unsigned char wdate_H,unsigned char wdate_L);
//unsigned char read(unsigned char add);
void Delay(unsigned int n);        //1.5us
void delaynms(unsigned int n);      //1ms

#ifdef	__cplusplus
}
#endif

#endif	/* IIC_H */

