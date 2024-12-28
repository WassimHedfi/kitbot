# KitBot - Educational Robotics Platform

KitBot is an educational and prototyping robotics platform designed to facilitate learning in robotics and programming. With its compact design and versatile features, it is an ideal tool for students, hobbyists, and educators. This repository contains example code, technical documentation, and resources to help you get started with KitBot.

## Table of Contents
1. [Installation](#installation)
2. [Setup](#setup)
3. [Example Codes](#example-codes)
    - [Ultrasonic Distance with Buzzer](#ultrasonic-distance-with-buzzer)
    - [Button Test](#button-test)
    - [Line Following](#line-following)
    - [Obstacle Avoidance](#obstacle-avoidance)
    - [Remote Control via Bluetooth](#remote-control)
4. [Technical Documentation](#technical-documentation)
5. [Resources](#resources)
6. [License](#license)

## Installation

### Prerequisites
1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Download the KitBot repository to your local machine.

### Connecting KitBot
1. Connect KitBot to your computer using a USB cable.
2. Install any necessary drivers for the Arduino Nano.

## Setup

1. **Load the Code:**
   - Open the Arduino IDE and select `Arduino Nano` under **Tools > Board > Arduino AVR Boards** and `ATmega328 (Old Bootloader)` under **Tools > Processor**.
   - Select the correct port under **Tools > Port**.
   - Upload the desired sketch from the `examples` folder to KitBot.

2. **Power On KitBot:**
   - Switch on KitBot using the power switch.
   - The red LED will indicate the power status.

3. **Using the Bluetooth:**
   - Pair your smartphone with KitBot using Bluetooth (Kit-Bot).
   - Enter the pairing code: `kitbot`.

## Example Codes

### Ultrasonic Distance with Buzzer

**Location**: `examples/ultrasonic_distance_with_buzzer/ultrasonic_distance_with_buzzer.ino`

**Description**: 
This code uses an ultrasonic sensor to measure the distance between KitBot and obstacles. 
- When an obstacle is closer than a predefined safe distance, the red LED lights up, and the buzzer sounds.
- When the obstacle is farther away, the green LED turns on, and the buzzer turns off.
- The distance is displayed on the LCD screen.

### Button Test

**Location**: `examples/button_test/button_test.ino`

**Description**:
This code demonstrates a simple button interaction using KitBot's LEDs and LCD screen. Here's how it works:

- The green LED remains ON by default.
- Pressing the red button:
  * Turns the red LED ON.
  * Turns the green LED OFF.
- Pressing the blue button:
  * Turns the blue LED ON.
  * Turns the green LED OFF.
  
The LCD screen dynamically displays the current button status, providing real-time feedback.

### Line Following

**Location**: `examples/line_following/line_following.ino`

**Description**:
This code enables KitBot to follow a line using two infrared sensors. KitBot detects the line and adjusts its motors to stay on track.

### Obstacle Avoidance

**Location**: `examples/obstacle_avoidance/obstacle_avoidance.ino/`

**Description**:
This code allows KitBot to avoid obstacles using the ultrasonic sensor. It will turn when an obstacle is detected in its path.

### Remote Control via Bluetooth

**Location**: `examples/remote_control/remote_control.ino`

**Description**:
This code allows you to control KitBot via a Bluetooth connection. You can send commands like forward, backward, left, and right from a smartphone app.

## Technical Documentation

You can access the full technical documentation of KitBot in the `docs` folder, including hardware components, wiring, and setup instructions. [Download the PDF here](https://github.com/user-attachments/files/18267063/KitBot_Tech_Manual.pdf).

## Resources

- [Arduino IDE Download](https://www.arduino.cc/en/software)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
