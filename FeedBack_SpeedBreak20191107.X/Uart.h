/* 
 * File:   Uart.h
 * Author: admin
 *
 * Created on 20160918
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
void putchar(unsigned char byte);
void SendData(unsigned char *p,unsigned char n);
void ProcessUart(void);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

