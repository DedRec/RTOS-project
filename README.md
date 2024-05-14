# Power Window Control System using Tiva C running FreeRTOS

## Overview

![image](https://github.com/DedRec/RTOS-project/assets/89746218/e84e8485-1a43-477e-8813-11b3d628de34)

The Power Window Control System is a project designed to automate the control of windows in buildings using the Tiva C Series TM4C123G LaunchPad microcontroller running FreeRTOS. The system provides both automatic and manual control modes, along with event handling functionalities.

## Features
- **Automatic Control**: The system automatically controls window movement based on predefined conditions such as button presses and limit detections.
- **Manual Control**: Manual control mode allows users to manually operate windows using physical buttons.
- **Event Handling**: The system can detect and handle events such as safety button presses and window jamming situations.
- **Task Synchronization**: FreeRTOS tasks are used for various control and event handling functionalities, with semaphores ensuring proper synchronization.

## Modules
1. **Automatic Control Module**: Implements automatic window control functionalities using tasks and semaphores.
2. **Manual Control Module**: Provides manual window control functionalities with tasks for button detection and movement control.
3. **Events Handling Module**: Handles events such as safety button presses and window jamming situations.
4. **Utilities Module**: Contains utility functions for initializing peripherals, UART communication, GPIO pins, and delay operations.

## Usage
1. **Setup**: Connect the Tiva C Series LaunchPad to the appropriate peripherals and power source.
2. **Initialization**: Initialize the system by calling the initialization functions for automatic control, manual control, and event handling.
3. **Operation**: The system can operate in automatic mode where it automatically controls window movement based on predefined conditions. Alternatively, users can switch to manual mode for direct control using physical buttons.
4. **Event Handling**: The system can detect and handle events such as safety button presses and window jamming situations to ensure safe and efficient operation.

## Dependencies
- FreeRTOS: Real-time operating system for multitasking capabilities.
- TivaWare Peripheral Driver Library: Provides APIs for controlling the peripherals of the Tiva C Series microcontroller.
- Tiva C Series TM4C123G LaunchPad: Hardware platform used for development.

## Contributing
Contributions to enhance functionality, optimize code, or fix bugs are welcome. Please follow the standard contribution guidelines.

