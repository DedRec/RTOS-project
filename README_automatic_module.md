# Automatic Window Control Module

## Overview
This module implements functions for automatic window control using FreeRTOS tasks and semaphores. It includes tasks for detecting button presses, moving the window up or down, handling limit conditions, and suspending all control tasks. Semaphores are utilized for synchronization between tasks.

## Contents
- `AUTO_INIT()`: Initializes tasks and semaphores for automatic window control.
- `AUTO_SUSP()`: Suspends all control tasks.
- `AUTO_SWMN()`: Suspends all tasks and enters manual control mode.
- `AUTO_CONT()`: Resumes automatic window control.
- Tasks for detecting button presses (`AUTO_DBTN()`), moving the window up (`AUTO_WINU()`), moving the window down (`AUTO_WIND()`), handling limit detection for upward movement (`AUTO_LIMU()`), and handling limit detection for downward movement (`AUTO_LIMD()`).
- Interrupt handler for window control events (`AUTO_WINH()`).

## Usage
Include this module in your project to enable automatic window control functionalities. Call `AUTO_INIT()` to initialize tasks and semaphores. Use the provided functions to control window movement automatically.

## Dependencies
- FreeRTOS
- TivaWare Peripheral Driver Library
