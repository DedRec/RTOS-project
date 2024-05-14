# Manual Control Module Header

## Overview
This header file declares functions and semaphores for manual window control. Include this header file in your source files where manual control functions are implemented.

## Contents
- Function declarations for initializing tasks and semaphores (`MAN_INIT()` and others).
- Semaphore declarations (`xSemaphoreUp`, `xSemaphoreDown`, `xSemaphoreLimitUp`, `xSemaphoreLimitDown`, `xSemaphoreSuspend`).
- Task handles for control tasks (`MDB_Handle`, `MWU_Handle`, etc.).

## Dependencies
- FreeRTOS
- TivaWare Peripheral Driver Library
