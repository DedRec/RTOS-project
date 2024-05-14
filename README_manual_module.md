# Manual Control Module

## Overview
This module implements functions for manual window control, including tasks for detecting button presses, moving the window up or down, handling limit conditions, and suspending all control tasks. Semaphores are utilized for synchronization between tasks.

## Contents
- `MAN_INIT()`: Initializes manual control tasks and semaphores.
- `MAN_SUSP()`: Suspends all manual control tasks.
- `MAN_CONT()`: Resumes manual window control.
- Tasks for detecting button presses (`MAN_DBTN()`), moving the window up (`MAN_WINU()`), moving the window down (`MAN_WIND()`), handling limit conditions for upward movement (`MAN_LIMU()`), and handling limit conditions for downward movement (`MAN_LIMD()`).
- Interrupt handler for manual window control events (`MAN_WINH()`).

## Usage
Include this module in your project to enable manual window control functionalities. Call `MAN_INIT()` to initialize manual control tasks and semaphores. Use the provided functions to control window movement manually.

## Dependencies
- FreeRTOS
- TivaWare Peripheral Driver Library
