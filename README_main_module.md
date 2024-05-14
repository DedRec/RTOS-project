# Main Module

## Overview
This module contains the main function responsible for initializing peripherals, setting up interrupts, and starting the FreeRTOS scheduler. It also initializes modules for manual control, automatic control, and events handling.

## Contents
- `main()`: Main function responsible for system initialization and starting the scheduler.

## Dependencies
- FreeRTOS
- TivaWare Peripheral Driver Library

## Usage
Include this module in your project and ensure it is set as the entry point. Initialize peripherals, set up interrupts, and initialize modules as required for your application. Call `vTaskStartScheduler()` to start the FreeRTOS scheduler.

