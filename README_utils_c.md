# Utilities Module

## Overview
This module provides utility functions for initializing peripherals, UART communication, GPIO pins, and delay.

## Contents
- `uartInit(uint32_t baudrate)`: Initializes UART communication with the specified baudrate.
- `sendToUart(char* str)`: Sends a string over UART.
- `peripheralEnable(uint32_t peref)`: Enables the specified peripheral.
- `pinsInit(uint32_t port, uint8_t pins, uint8_t isInput)`: Initializes GPIO pins of a port for input or output.
- `delay(int ms)`: Delays execution for the specified number of milliseconds.

## Dependencies
- TivaWare Peripheral Driver Library
