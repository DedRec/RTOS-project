#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

#include "manual.h"
#include "automatic.h"
#include "events.h"
#include "utils.h"



uint32_t count = 0;
portBASE_TYPE xStatus;
long lReceivedValue;

xQueueHandle xQueue;
xSemaphoreHandle xSemaphoreUp;
xSemaphoreHandle xSemaphoreDown;
xSemaphoreHandle xSemaphoreLimitUp;
xSemaphoreHandle xSemaphoreLimitDown;
xSemaphoreHandle xSemaphoreSuspend;
xSemaphoreHandle xMutex;

TaskHandle_t MDB_Handle;
TaskHandle_t MWU_Handle;
TaskHandle_t MWD_Handle;
TaskHandle_t MLU_Handle;
TaskHandle_t MLD_Handle;
TaskHandle_t MSUSP;


void MAN_INIT(){
	xTaskCreate(MAN_DBTN, "Detect", 240, NULL, 1, &MDB_Handle);
	xTaskCreate(MAN_WINU, "Window Up", 240, NULL, 2, &MWU_Handle);
	xTaskCreate(MAN_WIND, "Window Down", 240, NULL, 2, &MWD_Handle);
	xTaskCreate(MAN_LIMU, "Window Limit Up", 240, NULL, 3, &MLU_Handle);
	xTaskCreate(MAN_LIMD, "Window Limit Down", 240, NULL, 3, &MLD_Handle);
	xTaskCreate(MAN_SUSP, "Suspend All Tasks", 240, NULL, 1, &MSUSP);
	
	xQueue = xQueueCreate(5,sizeof(uint32_t));
	xSemaphoreUp = xSemaphoreCreateBinary();
	xSemaphoreDown = xSemaphoreCreateBinary();
	xSemaphoreLimitUp = xSemaphoreCreateBinary();
	xSemaphoreLimitDown = xSemaphoreCreateBinary();
	xSemaphoreSuspend = xSemaphoreCreateBinary();
	xMutex = xSemaphoreCreateMutex();

}

void MAN_SUSP(){
	while(1){
		xSemaphoreTake(xSemaphoreSuspend, portMAX_DELAY);
		vTaskSuspend(MWU_Handle);
		vTaskSuspend(MWD_Handle);
		vTaskSuspend(MDB_Handle);
		vTaskSuspend(MLU_Handle);
		vTaskSuspend(MLD_Handle);
		xSemaphoreGive(xSemaphoreUp);
		xSemaphoreGive(xSemaphoreDown);
		xSemaphoreGive(xSemaphoreLimitUp);
		xSemaphoreGive(xSemaphoreLimitDown);
		xSemaphoreTake(xSemaphoreUp, portMAX_DELAY);
		xSemaphoreTake(xSemaphoreDown, portMAX_DELAY);
		xSemaphoreTake(xSemaphoreLimitDown, portMAX_DELAY);
		AUTO_CONT();
		vTaskSuspend(NULL);
	}
}

void MAN_CONT(){
	GPIOIntUnregister(GPIO_PORTA_BASE);
	GPIOIntRegister(GPIO_PORTA_BASE, MAN_WINH);
	xTaskResumeFromISR(MWU_Handle);
	xTaskResumeFromISR(MWD_Handle);
	xTaskResumeFromISR(MLU_Handle);
	xTaskResumeFromISR(MLD_Handle);
	xTaskResumeFromISR(MDB_Handle);
	xTaskResumeFromISR(MSUSP);
}

void MAN_DBTN(){
	while(1){
		int x = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
		if(x==0x10){
			count++;
			xQueueSendToBack(xQueue,&count,0);
			xSemaphoreGive(xSemaphoreDown);
		}else if(x==0x01){
			count++;
			xQueueSendToBack(xQueue,&count,0);
			xSemaphoreGive(xSemaphoreUp);
		}
	}
}

void MAN_WINU(){
	while(1){
		xSemaphoreTake(xSemaphoreUp, portMAX_DELAY);
		xStatus = xQueueReceive(xQueue, &lReceivedValue, portMAX_DELAY);
		//sendToUart("Manual Window Up");
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_3);
		while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==0);
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2|GPIO_PIN_3, 0x0);
		if(xStatus == pdPASS){
			//DIO_WritePort(&GPIO_PORTF_DATA_R,0x8);
		}
	}
}

void MAN_WIND(){
	while(1){
		xSemaphoreTake(xSemaphoreDown, portMAX_DELAY);
		xStatus = xQueueReceive(xQueue, &lReceivedValue, portMAX_DELAY );
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_2);
		while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0)==0);
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2|GPIO_PIN_3, 0x0);
		//sendToUart("Manual Window Down");
		/*
		DIO_WritePort(&GPIO_PORTA_DATA_R, 0x4);
		while(DIO_ReadPin(&GPIO_PORTF_DATA_R,4)==0);
		DIO_WritePort(&GPIO_PORTA_DATA_R, 0x0);
		*/
		if(xStatus == pdPASS){
			//DIO_WritePort(&GPIO_PORTF_DATA_R,0x4);
		}
	}
}

void MAN_LIMU(){
	while(1){
		xSemaphoreTake(xSemaphoreLimitUp, portMAX_DELAY);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3,0x0);
		//sendToUart("Manual Limit Up");
		//DIO_WritePort(&GPIO_PORTA_DATA_R, 0x0);
		xSemaphoreGive(xMutex);
	}
}

void MAN_LIMD(){
	while(1){
		xSemaphoreTake(xSemaphoreLimitDown, portMAX_DELAY);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3,0x0);
		//sendToUart("Manual Limit Down");
		//DIO_WritePort(&GPIO_PORTA_DATA_R, 0x0);
		xSemaphoreGive(xMutex);
	}
}


void MAN_WINH(){

	int x = GPIOPinRead(GPIO_PORTA_BASE, 0xFC);
	BaseType_t pxHigherTask = pdFALSE;
	if(x==0x80)
		xSemaphoreGiveFromISR(getSafetySemaphore(), &pxHigherTask);
	//while(GPIOPinRead(GPIO_PORTA_BASE, 0xFC));
	if((x&0x8)){
		sendToUart("Given limit up");
		xSemaphoreGiveFromISR(xSemaphoreLimitUp, &pxHigherTask);
	}else if((x&0x4)){
		sendToUart("Given limit down");
		xSemaphoreGiveFromISR(xSemaphoreLimitDown, &pxHigherTask);
	}else if((x&0x10)){
		xSemaphoreGiveFromISR(xSemaphoreSuspend, &pxHigherTask);
	}else if((x&0x20)){
		MAN_CONT();
	}else if((x&0x40)){
		xSemaphoreGiveFromISR(getJamSemaphore(), &pxHigherTask);
	}
	GPIOIntClear(GPIO_PORTA_BASE, 0xFC);
}