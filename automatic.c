#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"


#include "inc/hw_memmap.h"
#include "inc/hw_types.h"


#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

#include "automatic.h"
#include "manual.h"
#include "events.h"
#include "utils.h"



uint32_t counter = 0;
long receivedValue;

SemaphoreHandle_t semaphoreUp;
SemaphoreHandle_t semaphoreDown;
SemaphoreHandle_t semaphoreLimitUp;
SemaphoreHandle_t semaphoreLimitDown;
SemaphoreHandle_t semaphoreSuspend;

TaskHandle_t DB_Handle;
TaskHandle_t WU_Handle;
TaskHandle_t WD_Handle;
TaskHandle_t LU_Handle;
TaskHandle_t LD_Handle;
TaskHandle_t SUSP;

void AUTO_INIT(){
	xTaskCreate(AUTO_DBTN, "Detect", 240, NULL, 2, &DB_Handle);
	xTaskCreate(AUTO_WINU, "Window Up", 240, NULL, 1, &WU_Handle);
	xTaskCreate(AUTO_WIND, "Window Down", 240, NULL, 1, &WD_Handle);
	xTaskCreate(AUTO_LIMU, "Window Limit Up", 240, NULL, 3, &LU_Handle);
	xTaskCreate(AUTO_LIMD, "Window Limit Down", 240, NULL, 3, &LD_Handle);
	xTaskCreate(AUTO_SWMN, "Suspend All Tasks", 240, NULL, 3, &SUSP);
	
	semaphoreUp = xSemaphoreCreateBinary();
	semaphoreDown = xSemaphoreCreateBinary();
	semaphoreLimitUp = xSemaphoreCreateBinary();
	semaphoreLimitDown = xSemaphoreCreateBinary();
	semaphoreSuspend = xSemaphoreCreateBinary();
}

void AUTO_SUSP(){
	vTaskSuspend(WU_Handle);
	vTaskSuspend(WD_Handle);
	vTaskSuspend(DB_Handle);
	vTaskSuspend(LU_Handle);
	vTaskSuspend(LD_Handle);
}

void AUTO_SWMN(){
	while(1){
		xSemaphoreTake(semaphoreSuspend, portMAX_DELAY);
		vTaskSuspend(WU_Handle);
		vTaskSuspend(WD_Handle);
		vTaskSuspend(DB_Handle);
		vTaskSuspend(LU_Handle);
		vTaskSuspend(LD_Handle);
		xSemaphoreGive(semaphoreUp);
		xSemaphoreGive(semaphoreDown);
		xSemaphoreGive(semaphoreLimitUp);
		xSemaphoreGive(semaphoreLimitDown);
		xSemaphoreTake(semaphoreUp, portMAX_DELAY);
		xSemaphoreTake(semaphoreDown, portMAX_DELAY);
		xSemaphoreTake(semaphoreLimitDown, portMAX_DELAY);
		MAN_CONT();
		vTaskSuspend(NULL);
	}
}

void AUTO_CONT(){
	GPIOIntUnregister(GPIO_PORTA_BASE);
	GPIOIntRegister(GPIO_PORTA_BASE, AUTO_WINH);
	
	xTaskResumeFromISR(WU_Handle);
	xTaskResumeFromISR(WD_Handle);
	xTaskResumeFromISR(LU_Handle);
	xTaskResumeFromISR(LD_Handle);
	xTaskResumeFromISR(DB_Handle);
	xTaskResumeFromISR(SUSP);
}

void AUTO_DBTN(){
	while(1){
		int x = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
		if((x==0x10) & (eTaskGetState(WD_Handle)!= eSuspended)){
			xSemaphoreGive(semaphoreDown);
			vTaskSuspend(NULL);
		}else if((x==0x01) & (eTaskGetState(WU_Handle)!= eSuspended)){
			xSemaphoreGive(semaphoreUp);
			vTaskSuspend(NULL);
		}
	}
}

void AUTO_WINU(){
	while(1){
		xSemaphoreTake(semaphoreUp, portMAX_DELAY);
		//sendToUart("Window Up");
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_3);
		xSemaphoreGive(semaphoreUp);
	}
}

void AUTO_WIND(){
	while(1){
		xSemaphoreTake(semaphoreDown, portMAX_DELAY);
		//sendToUart("Window Down");
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_2);
		xSemaphoreGive(semaphoreDown);
	}
}

void AUTO_LIMU(){
	while(1){
		xSemaphoreTake(semaphoreLimitUp, portMAX_DELAY);
		//sendToUart("Limited Up");
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3,0x0);
		vTaskSuspend(WU_Handle);
		vTaskResume(WD_Handle);
		vTaskResume(DB_Handle);
	}
}

void AUTO_LIMD(){
	while(1){
		xSemaphoreTake(semaphoreLimitDown, portMAX_DELAY);
		//sendToUart("Limited Down");
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3,0x0);
		vTaskSuspend(WD_Handle);
		vTaskResume(WU_Handle);
		vTaskResume(DB_Handle);
	}
}


void AUTO_WINH(){
	int x = GPIOPinRead(GPIO_PORTA_BASE, 0xFC);
	BaseType_t pxHigherTask = pdFALSE;
	if((x&0x8)){
		while(GPIOPinRead(GPIO_PORTA_BASE, 0xFC));
		sendToUart("Given limit up");
		xSemaphoreGiveFromISR(semaphoreLimitUp, &pxHigherTask);
	}else if((x&0x4)){
		while(GPIOPinRead(GPIO_PORTA_BASE, 0xFC));
		sendToUart("Given limit down");
		xSemaphoreGiveFromISR(semaphoreLimitDown, &pxHigherTask);
	}else if((x&0x10)){
		while(GPIOPinRead(GPIO_PORTA_BASE, 0xFC));
		AUTO_CONT();
	}else if((x&0x20)){
		while(GPIOPinRead(GPIO_PORTA_BASE, 0xFC));
		xSemaphoreGiveFromISR(semaphoreSuspend, &pxHigherTask);
	}else if((x&0x40)){
		while(GPIOPinRead(GPIO_PORTA_BASE, 0xFC));
		xSemaphoreGiveFromISR(getJamSemaphore(), &pxHigherTask);
	}else if((x&0x80))
		xSemaphoreGiveFromISR(getSafetySemaphore(), &pxHigherTask);
	GPIOIntClear(GPIO_PORTA_BASE, 0xFC);
}

void vApplicationIdleHook(void){
	sendToUart("All Suspended");
	//vTaskResume(DB_Handle);
}