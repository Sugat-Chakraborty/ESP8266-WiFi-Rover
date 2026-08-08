# ESP8266 Wi-Fi Rover

A Wi-Fi controlled robotic rover built with ESP8266 and L298N motor driver

<p align="center">
  <img src="rover.jpg" alt="ESP8266 Wi-Fi Rover" width="600">
</p>

## Overview

This project is a Wi-Fi controlled robotic rover built using an ESP8266 NodeMCU. The rover is controlled wirelessly using the **ESP8266 WiFi Robot Car** mobile application.

The ESP8266 operates as a Wi-Fi access point and runs a web server that receives movement and speed commands from the mobile application.

## Features

- Wi-Fi based wireless control
- Forward and backward movement
- Left and right movement
- Diagonal movement
- Multiple speed levels
- Dual headlights
- ESP8266-based control
- L298N motor driver

## Hardware

- ESP8266 NodeMCU
- L298N Motor Driver
- BO Motors
- Wheels
- Robot chassis
- LEDs for headlights
- 7.4V battery
- Connecting wires

## Circuit Diagram

The Fritzing diagram shows the connections between the ESP8266, L298N motor driver, motors, headlights.

<p align="center">
  <img src="Circuit/circuit diagram.jpg" alt="Fritzing Circuit Diagram" width="800">
</p>

## Power Supply Note

> **Do not use the 5V output of the L298N motor driver to power the ESP8266. Instead, a buck converter is used to step down the 7.4V battery supply to 5V, which is then used to power the ESP8266 development board.**

## Control

The rover is controlled using the **ESP8266 WiFi Robot Car** mobile application.

The ESP8266 creates its own Wi-Fi network:

```text
NodeMCU Car
The mobile device connects to this network and sends movement and speed commands to the rover.

```
## Firmware

The Arduino code used to control the rover is included in this repository:

[code.ino](code.ino)

## How It Works

The ESP8266 is configured as a Wi-Fi access point and runs an HTTP web server.

The mobile application sends commands to the ESP8266. These commands are interpreted by the code and used to control the L298N motor driver.

The L298N controls the direction and speed of the four BO motors. The headlights turn on when the rover moves and turn off when the rover stops.

## Project Demo

Photos and videos of the rover in operation are shared on my Instagram project page.

[View the project on Instagram]()

## Project Status

**Completed**


