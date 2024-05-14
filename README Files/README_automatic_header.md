# Automatic Window Control Module Header

## Overview
This header file declares functions and semaphores for automatic window control. Include this header file in your source files where automatic control functions are implemented.

## Contents
- Function declarations for initializing tasks and semaphores (`AUTO_INIT()` and others).
- Semaphore declarations (`semaphoreUp`, `semaphoreDown`, `semaphoreLimitUp`, `semaphoreLimitDown`, `semaphoreSuspend`).
- Task handles for control tasks (`DB_Handle`, `WU_Handle`, etc.).

## Usage
Include this header file in your source files where automatic control functions are implemented. Implement the functions as per your project requirements.

## Dependencies
- FreeRTOS
- TivaWare Peripheral Driver Library
