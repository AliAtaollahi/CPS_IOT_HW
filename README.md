# IoT-Based Entry and Exit Management System

## Project Overview

This project develops a system to control the entry and exit of individuals in a company using IoT technologies. The system utilizes RFID for identification and an Arduino board equipped with an ENC28J60 Ethernet module to handle door mechanisms and data transmission. A simple web server is implemented in the cloud to manage access permissions, and a monitoring system is set up to track and display entry events.

## Features

- **RFID Authentication:** Utilizes RFID sensors and tags to identify individuals entering or exiting the facility.
- **Arduino Control:** Manages door operations such as opening and closing based on authentication status using a servo motor.
- **Web Server:** Hosts a simple server in the cloud to store a list of authorized individuals and handle authentication requests.
- **Monitoring System:** A GUI monitoring system that displays entry events as they occur, developed using Qt and WebSockets for live data updates.

## System Setup

### Hardware Components

- RFID sensor and tags
- Arduino board
- ENC28J60 Ethernet module
- Servo motor for door control
- LEDs for status indication (green for access granted, red for denied)

### Software Requirements

- **Arduino IDE:** For programming the Arduino board.
- **Qt Creator:** For developing the GUI monitoring system.
- **Proteus Software:** For simulating the hardware setup. (Physical components are not available.)

## Installation and Configuration

1. **Arduino Setup:**
   - Install the Arduino IDE and load the provided script.
   - Connect the ENC28J60 module and configure it for Ethernet access.
   - Attach the RFID sensor, servo motor, and LEDs as per the circuit diagram provided.

2. **Web Server Implementation:**
   - Set up a basic HTTP server that can handle requests and send responses to the Arduino board.
   - Ensure the server can perform updates on client using WebSockets.

3. **Monitoring System:**
   - Use Qt Creator to develop the GUI.
   - Implement the WebSocket client in the GUI to receive updates from the web server.

## Project Directory Structure and Contents

### Proteus Folder
This folder holds simulation files for Proteus software, allowing us to simulate the hardware setup virtually. Here's a detailed description of the simulation setup:

1. **Simulation Environment**:
   - The Proteus project file, **CPS CA1.pdsprj**, provides the simulation environment where we can visualize and test the behavior of the IoT-based entry and exit management system.

2. **Components**:
   - **Terminal for Entering RFID Tag**: This component simulates the RFID tag reader terminal where individuals can tap their RFID cards for authentication. In the simulation, we can input RFID tag data to emulate different user interactions.
   
   - **Arduino Board**: The Arduino microcontroller is simulated to execute the control logic for the entry and exit management system. It interfaces with the RFID reader, servo motor, LEDs, and Ethernet module to perform authentication and control door access.
   
   - **ENC28J60 Ethernet Module**: This module is simulated to provide Ethernet connectivity for the Arduino board. It enables communication between the Arduino and the cloud-based server for authentication and data transmission.
   
   - **Servo Motor for Door Control**: The servo motor is simulated to mimic the physical door mechanism controlled by the Arduino board. In the simulation, we can observe how the servo motor responds to commands from the Arduino, such as opening and closing the door.
   
   - **LEDs for Status Indication**: LED components are included in the simulation to visually represent the status of access control operations. Green LEDs indicate access granted, while red LEDs indicate access denied.


This comprehensive simulation environment allows us to test and validate the functionality of the IoT-based entry and exit management system before deploying it in a real-world environment. It enables thorough testing of various scenarios and interactions to ensure the system operates reliably and efficiently.



