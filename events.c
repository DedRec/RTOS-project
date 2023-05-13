#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"


#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

#include "events.h"
#include "utils.h"

SemaphoreHandle_t semaphoreJamEvent;
SemaphoreHandle_t semaphoreSafetyButton;
SemaphoreHandle_t semaphoreMutexEvent;


void eventsInit(){
	semaphoreJamEvent = xSemaphoreCreateBinary();
	semaphoreSafetyButton = xSemaphoreCreateBinary();
	semaphoreMutexEvent = xSemaphoreCreateMutex();
	
	xTaskCreate(windowJam, "Jam",240,NULL,4,NULL);
	xTaskCreate(safetyButton, "safetyButton",240,NULL,4,NULL);
}

void safetyButton(){
	while(1){
		xSemaphoreTake(semaphoreSafetyButton,portMAX_DELAY);
		//sendToUart("Safety ON");
		__asm("CPSID i");
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3,0x0);
		//DIO_WritePort(&GPIO_PORTA_DATA_R, 0x0);
		vTaskSuspendAll();
		while(GPIOPinRead(GPIO_PORTA_BASE, 0x80));
		__asm("CPSIE i");
		xTaskResumeAll();
	}
}

void windowJam(){
	while(1){
		xSemaphoreTake(semaphoreJamEvent, portMAX_DELAY);
		xSemaphoreTake(semaphoreMutexEvent, portMAX_DELAY);
		//sendToUart("Jammed");
		//DIO_WritePort(&GPIO_PORTA_DATA_R, 0x4);
		vTaskSuspendAll();
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_2);
		//vTaskDelay(500/portTICK_PERIOD_MS);
		delay(500);
		//DIO_WritePort(&GPIO_PORTA_DATA_R, 0x0);
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3,0x0);
		xTaskResumeAll();
		xSemaphoreGive(semaphoreMutexEvent);
	}
}

SemaphoreHandle_t getJamSemaphore(){
	return semaphoreJamEvent;
}

SemaphoreHandle_t getSafetySemaphore(){
	return semaphoreSafetyButton;
}