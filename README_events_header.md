# Events Handling Module Header

## Overview
This header file declares functions and semaphores for handling events related to the automatic window control system. Include this header file in your source files where event handling functions are implemented.

## Contents
- Function declarations for initializing event semaphores and tasks (`eventsInit()`, `safetyButton()`, etc.).
- Semaphore declarations (`semaphoreJamEvent`, `semaphoreSafetyButton`, `semaphoreMutexEvent`).

## Usage
Include this header file in your source files where event handling functions are implemented. Implement the functions as per your project requirements.

## Dependencies
- FreeRTOS
- TivaWare Peripheral Driver Library

## Contributing
Contributions to enhance functionality, optimize code, or fix bugs are welcome. Please follow the standard contribution guidelines.

## License
This project is licensed under the [MIT License](LICENSE).
