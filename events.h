#ifndef EVENTS_H
#define EVENTS_H

#include "FreeRTOS.h"
#include "semphr.h"


void eventsInit();
void windowJam();
void safetyButton();
SemaphoreHandle_t getJamSemaphore();
SemaphoreHandle_t getSafetySemaphore();

#endif