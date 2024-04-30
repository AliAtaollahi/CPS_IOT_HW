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

## Flowchart
<img src="CA1/Pics/Flowchart.png" alt="flowchart" width="50%">

The flowchart provides a visual guide to the sequence of operations when an individual attempts to enter the premises using our IoT-based Access Control System. Below is the detailed process as shown in the flowchart:

1. **Start (Setup)**: The system initializes and sets the RFID reader to standby mode, preparing to detect any RFID tag presented by an individual trying to gain entry.

2. **RFID Tag Detection**: When a person approaches, the system checks if the door is closed and then waits for an RFID signal. If a tag is present, it reads the information from the RFID tag.

3. **Data Handling**: Once the RFID reader detects a tag, it sends the data to the Arduino board, which then transmits this information to the cloud for authentication.

4. **Cloud-Based Authentication**: The cloud server receives the RFID data and authenticates the identity of the individual by comparing the received data against a list of authorized IDs.

5. **Response and Action**: Upon authentication, the cloud sends the identity information to the monitoring system, displaying all details and saving the event in the system's history. It also sends the authentication result back to the Arduino board to take the appropriate action.

6. **Access Control Decision**:
   - **Granting Access**: If authentication is successful, the Arduino commands the servo motor to open the door for 30 seconds, the LED indicator turns green, and the individual’s information is displayed on the monitor.
   - **Denying Access**: If authentication fails, the system will not open the door; the LED indicator turns red, and an "Access Denied" message is displayed.

7. **Closing the Door**: If the door was opened, it is programmed to close automatically after 30 seconds or immediately if required for security reasons.

8. **End**: The flow concludes once the door is securely closed or the denied access protocol is completed.


## Project Directory Structure and Contents

### Proteus Folder
This folder holds simulation files for Proteus software, allowing us to simulate the hardware setup virtually. Here's a detailed description of the simulation setup:

#### Simulation Environment
   - The Proteus project file, `CPS CA1.pdsprj`, provides the simulation environment where we can visualize and test the behavior of the IoT-based entry and exit management system.

#### Components:
   - **Terminal for Entering RFID Tag**: This component simulates the RFID tag reader terminal where individuals can tap their RFID cards for authentication. In the simulation, we can input RFID tag data to emulate different user interactions.
   
   - **Arduino Board**: The Arduino microcontroller is simulated to execute the control logic for the entry and exit management system. It interfaces with the RFID reader, servo motor, LEDs, and Ethernet module to perform authentication and control door access.
   
   - **ENC28J60 Ethernet Module**: This module is simulated to provide Ethernet connectivity for the Arduino board. It enables communication between the Arduino and the cloud-based server for authentication and data transmission.
   
   - **Servo Motor for Door Control**: The servo motor is simulated to mimic the physical door mechanism controlled by the Arduino board. In the simulation, we can observe how the servo motor responds to commands from the Arduino, such as opening and closing the door.
   
   - **LEDs for Status Indication**: LED components are included in the simulation to visually represent the status of access control operations. Green LEDs indicate access granted, while red LEDs indicate access denied.

#### Screenshots (imulation in Proteus)
1. "Starting and Waiting for Handshake"
![Screenshot 1 - Starting and Waiting for Handshake](CA1/Pics/screenshot(SimulationInProteus)/1.jpg)
*Description: This screenshot captures the initial state of the system where the Arduino board is powered on and waiting to establish a connection with the cloud server. The system is in standby mode, indicated by the LEDs showing no activity.*

2. "Handshake is Done"
![Screenshot 2 - Handshake is Done](CA1/Pics/screenshot(SimulationInProteus)/2.jpg)
*Description: This screenshot shows the system after successfully establishing a connection with the cloud server. The monitor shows that the handshake process is complete, and the system is ready to receive RFID authentication requests.*

3. "Input a Correct RFID -> Open Door and Green LED"
![Screenshot 3 - Input a Correct RFID](CA1/Pics/screenshot(SimulationInProteus)/3.jpg)
*Description: In this screenshot, a correct RFID tag is presented to the system for authentication. The Arduino board processes the RFID data, communicates with the cloud server for authentication, and receives a positive response. As a result, the servo motor opens the door, and the green LED lights up, indicating access granted.*

4. "Input an Incorrect RFID -> Close Door and Red LED"
![Screenshot 4 - Input an Incorrect RFID](CA1/Pics/screenshot(SimulationInProteus)/4.jpg)
*Description: This screenshot depicts the scenario where an incorrect RFID tag is presented for authentication. The Arduino board sends the RFID data to the cloud server, but authentication fails. Consequently, the servo motor closes the door, and the red LED lights up, signaling access denied.*

5. "Sequential RFID Authentication - Open Door, Then Close for Second Person"
![GIF - Sequential RFID Authentication](CA1/Pics/screenshot(SimulationInProteus)/5.gif)

*Description: This GIF demonstrates a sequential scenario where a correct RFID tag is initially presented, granting access and opening the door. Subsequently, an incorrect RFID tag is presented, resulting in access denial and the door closing. Delays are observable due to processing time required for 1. Arduino to process the RFID data and control the servo motor, and 2. HTTP request and response between the Arduino and the cloud server for authentication.*


This comprehensive simulation environment allows us to test and validate the functionality of the IoT-based entry and exit management system before deploying it in a real-world environment. It enables thorough testing of various scenarios and interactions to ensure the system operates reliably and efficiently.
___
### Embedded Folder
The embedded software for the IoT-based Entry and Exit Management System is designed to run on an Arduino board. It integrates several components including a servo motor for door control, RFID reader for identity verification, and an Ethernet module for network communication. The following sections describe the key parts of the Arduino sketch, highlighting how each contributes to the system's operations.

### Key Libraries

- **Servo.h**: Manages the servo motor used to open and close the door.
- **EtherCard.h**: Facilitates Ethernet communications for interfacing with the cloud server.

### Configuration

```cpp
#define TIMEOUT_TIME 200
#define GREEN_LED 2
#define RED_LED 3
#define RX_PIN 0
#define TX_PIN 1
#define SERVO_PIN 4
```
Defines the pin configuration and timeout settings for the system, ensuring that components such as LEDs and servo motors are correctly managed.

### Initialization

```cpp
Servo doorServo;


static byte mymac[] = { 0x75,0x69,0x69,0x2D,0x30,0x31 };
// ethernet interface ip address
static byte myip[] = { 192,168,2,2 };
// gateway ip address
static byte gwip[] = { 192,168,2,1 };
// remote website ip address and port
static byte hisip[] = { 192,168,2,1 };
// remote website name
const char website[] PROGMEM = "192.168.2.1";

byte Ethernet::buffer[900];   // a very small tcp/ip buffer is enough here


String inputString = "";
boolean doorOpen = false;
unsigned long doorOpenTime = 0;
Stash stash;
```
Initializes the servo motor and sets up networking parameters including MAC address, IP addresses, and the remote server details.

### Main Functions

#### Setup Function
```cpp
void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);
  doorServo.attach(SERVO_PIN);
  doorServo.write(0);
  Serial.begin(9600);
  
  ether.begin(sizeof Ethernet::buffer, mymac, SS);

  ether.staticSetup(myip, gwip);

  ether.copyIp(ether.hisip, hisip);
  ether.printIp("Server: ", ether.hisip);

  ether.clientWaitingGw();
  Serial.println("Gateway found");
  sendHandshake();
  Serial.println("Handshake completed");
}
```
Configures the GPIO pins and attaches the servo to its designated pin. Network initialization and diagnostic outputs are also set here.
Here’s a brief and focused explanation for each subject within our `setup()` function:  

**1. Selecting Pins** 
Configures GPIO pins for the LEDs and RX/TX pins, setting the directionality (input or output) for each.  

**2. Closing Door**   
Attaches the servo motor to its control pin and initializes it to a closed position, ensuring the door starts closed upon system reset.

**3. Initializing Serial and Ethernet Port**    
Initializes serial communication at 9600 baud rate for debugging and configures the Ethernet module with static IP settings.  

**4. Performing Handshake**   
Establishes a network route to the server, prints server IP for verification, waits for gateway availability, then sends a handshake to the server confirming network connectivity.

#### Main Loop
```cpp
void loop() {
  ether.packetLoop(ether.packetReceive());

  
  String receivedData = "";
  while (Serial.available()) {
    receivedData += Serial.readString();
  }
  
  // If the receivedData has data
  if (receivedData.length() > 0) {
    inputString += receivedData;
  }
  
  if (doorOpen) {
    // Check if 30 seconds have elapsed since the door was opened
    if (millis() - doorOpenTime >= 5000) {
      doorOpen = false;
      doorServo.write(0);
      digitalWrite(GREEN_LED, LOW);
      inputString = "";
    }
  }

    // If the receivedString has reached 10 characters
    if (inputString.length() == 10) {
        boolean sequenceResult = checkRFID(inputString);

      //boolean sequenceResult = checkSequence(inputString);

      Serial.println("  \n ");
      Serial.print("Sequence Check Result: ");
      Serial.println(sequenceResult ? "Correct" : "Incorrect");
      
      if (sequenceResult) {
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(RED_LED, LOW);
        doorServo.write(90);
        doorOpen = true;
        doorOpenTime = millis(); // Record the time when the door was opened
      } else {
        // If the sequence is incorrect, close the door
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        doorServo.write(0);
		    //const char jsonPayload[] PROGMEM = "{\"message\":\"hello\"}";
		    
        delay(500);
        digitalWrite(RED_LED, LOW);
        doorOpen = false;
      }
      inputString = "";
    }
}
```
Continuously reads RFID tags, checks them against server-side validation, and controls door access. Updates LED status based on authentication results. Here's a breakdown of the specific parts of the Arduino `loop()` function provided, detailing how it handles the RFID data received from the terminal, checks its validity, and manages access control logic based on the RFID check result:

**1. Receiving RFID from Terminal**
- **Network Data Handling**: Maintains the Ethernet connection and processes any packets that have been received.
- **Serial Data Collection**: Gathers all available data from the serial buffer, appending it to a string. This is presumed to be RFID data from a terminal.
- **Data Aggregation**: Adds newly received data to a cumulative string (`inputString`) if data is present.

**2.Validating and Checking the RFID** 
- **RFID Length Check**: Ensures that the `inputString` has accumulated exactly 10 characters, assumed to be the complete RFID sequence.
- **RFID Validation**: Calls `checkRFID(inputString)` to validate the RFID sequence. Outputs the result to the terminal for debugging.

**3. Handling Logic**  
- **For Correct RFID**:
  - **LEDs and Door**: Turns the GREEN LED on and the RED LED off, indicating access granted. Opens the door by setting the servo to 90 degrees.
  - **Time Tracking**: Marks the time the door was opened to check for auto-close timing.
- **For Incorrect RFID**:
  - **LEDs and Door**: Turns the GREEN LED off and the RED LED on, signaling access denied. Resets the door to a closed position by setting the servo to 0 degrees.
  - **Reset LEDs**: Briefly displays the RED LED before turning it off after a delay, preparing for the next access attempt.
- **String Reset**: Clears `inputString` to ready the system for the next RFID read cycle.

This detailed description maps out how the system handles each step of RFID data processing and the corresponding access control logic, ensuring clarity in how security and access are managed within the system.


This Arduino sketch is crucial for the operation of the IoT-based Entry and Exit Management System, providing the necessary logic and functions to interface with physical hardware and network communications effectively. For detailed function definitions and further code implementation, refer to the full sketch in the repository.

---




