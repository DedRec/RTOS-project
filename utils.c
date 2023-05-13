
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "utils.h"

void uartInit(uint32_t baudrate) {
	// GPIO part of initialization
	peripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	// UART part of initialization
	peripheralEnable(SYSCTL_PERIPH_UART0);
	UARTDisable(UART0_BASE);
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), baudrate, UART_CONFIG_WLEN_8
		| UART_CONFIG_STOP_ONE
		| UART_CONFIG_PAR_NONE);
	UARTEnable(UART0_BASE);
}

/////////////////////////////////////////////////////////////////////

void sendToUart(char* str) {
	while (*str) {
		// Wait if there's no more room for transmit
		while (!UARTSpaceAvail(UART0_BASE)){}
    while (UARTBusy(UART0_BASE)){}
    UARTCharPutNonBlocking(UART0_BASE, *(str++));
	}
	UARTCharPutNonBlocking(UART0_BASE, '\n');
	UARTCharPutNonBlocking(UART0_BASE, '\r');
	
}

/////////////////////////////////////////////////////////////////////

void peripheralEnable(uint32_t peref){
	SysCtlPeripheralEnable(peref);
	while(!SysCtlPeripheralReady(peref));
}

/////////////////////////////////////////////////////////////////////

void pinsInit(uint32_t port, uint8_t pins, uint8_t isInput){
	GPIOUnlockPin(port, pins);
	if(isInput)
		GPIOPinTypeGPIOInput(port, pins);
	else
		GPIOPinTypeGPIOOutput(port, pins);
}

/////////////////////////////////////////////////////////////////////

void delay(int ms) {
  for(int j=0; j<ms; j++) {
   for(int i=0; i<3180; i++) {
   } 
  }
  
}