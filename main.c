#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "utils.h"

#include "FreeRTOS.h"
#include "task.h"

#include "manual.h"
#include "automatic.h"
#include "events.h"

#define GPIO_PORTA_MIS_R (*((volatile unsigned long *)0x40004418))
#define mainSW_INTURRUPT_PortA ((IRQn_Type)0)






int main(void) {
	uartInit(9600);
	peripheralEnable(SYSCTL_PERIPH_GPIOF);
	pinsInit(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 1);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	peripheralEnable(SYSCTL_PERIPH_GPIOA);
	pinsInit(GPIO_PORTA_BASE, 0xFC, 1);
	
	peripheralEnable(SYSCTL_PERIPH_GPIOB);
	pinsInit(GPIO_PORTB_BASE,GPIO_PIN_2 | GPIO_PIN_3,0);
	
	GPIOPadConfigSet(GPIO_PORTA_BASE, 0xFC, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
	GPIOIntTypeSet(GPIO_PORTA_BASE, 0xFC, GPIO_RISING_EDGE);
	//GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_RISING_EDGE);
	GPIOIntEnable(GPIO_PORTA_BASE, 0xFC);
	GPIOIntRegister(GPIO_PORTA_BASE, MAN_WINH);
	NVIC_SetPriority(mainSW_INTURRUPT_PortA,5);
	
	eventsInit();
	MAN_INIT();
	AUTO_INIT();
	AUTO_SUSP();
	
	vTaskStartScheduler();
}

