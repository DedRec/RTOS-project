#ifndef UTILS_H
#define UTILS_H


void uartInit(unsigned int baudrate);
void sendToUart(char* str);
void peripheralEnable(unsigned int peref);
void pinsInit(unsigned int port, unsigned char pins, unsigned char isInput);
void delay(int ms);

#endif