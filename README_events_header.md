# Events Handling Module Header

## Overview
This header file declares functions and semaphores for handling events related to the automatic window control system. Include this header file in your source files where event handling functions are implemented.

## Contents
- Function declarations for initializing event semaphores and tasks (`eventsInit()`, `safetyButton()`, etc.).
- Semaphore declarations (`semaphoreJamEvent`, `semaphoreSafetyButton`, `semaphoreMutexEvent`).

## Dependencies
- FreeRTOS
- TivaWare Peripheral Driver Library
