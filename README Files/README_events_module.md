# Events Handling Module

## Overview
This module provides functionality for handling events related to the automatic window control system. It includes functions for initializing event semaphores and tasks to handle safety button presses and window jamming events.

## Contents
- `eventsInit()`: Initializes event semaphores and tasks.
- `safetyButton()`: Task for handling safety button presses.
- `windowJam()`: Task for handling window jamming events.
- `getJamSemaphore()`: Returns the semaphore for window jamming events.
- `getSafetySemaphore()`: Returns the semaphore for safety button events.

## Usage
Include this module in your project to handle safety button presses and window jamming events. Call `eventsInit()` to initialize event semaphores and tasks. Use `getJamSemaphore()` and `getSafetySemaphore()` to access the respective semaphores.

## Dependencies
- FreeRTOS
- TivaWare Peripheral Driver Library
