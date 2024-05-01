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

#### Key Libraries

- **Servo.h**: Manages the servo motor used to open and close the door.
- **EtherCard.h**: Facilitates Ethernet communications for interfacing with the cloud server.

#### Configuration

```cpp

#define TIMEOUT_TIME 1000
#define GREEN_LED 2
#define RED_LED 3
#define RX_PIN 0
#define TX_PIN 1
#define SERVO_PIN 4
```
Defines the pin configuration and timeout settings for the system, ensuring that components such as LEDs and servo motors are correctly managed.

#### Initialization

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

#### Main Functions:

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
  while(!sendHandshake());
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

#### checkRFID Function
```cpp
bool checkRFID(String tag) {
  ether.packetLoop(ether.packetReceive());
  byte stash_desc = stash.create();
  stash.print(tag);
  stash.save();

  Stash::prepare(PSTR("POST http://$F/$F HTTP/1.1\r\n"
                      "Host: $F\r\n"
                      "Content-Length: $D\r\n"
                      "Content-Type: text/plain\r\n"
                      "\r\n"
                      "$H"),
                 website, PSTR("rfid"), website, stash.size(), stash_desc);

  byte session = ether.tcpSend();

  unsigned long startTime = millis();
  while (millis() - startTime < TIMEOUT_TIME) {
    ether.packetLoop(ether.packetReceive());
    
    const char* reply = ether.tcpReply(session);
    if (reply != 0) {

      
      char status[3];
      getStatus(reply, status);
      /*Serial.println(reply);
      Serial.println(status);*/

      return strcmp(status, "OK") == 0 ? true : false;
    }
    delay(200);

  }

  return false; // no access
}
```
This function encapsulates a network interaction pattern where an RFID tag is sent to a server for authorization. The use of a TCP/IP stack (via the EtherCard library) and careful handling of Ethernet buffers and sessions allows for efficient network communications on resource-constrained devices like those running Arduino. The decision to grant or deny access is made based on the server's response to the transmitted RFID tag.

**1. Packet Processing and Stash Setup**
- **Packet Processing**: The function starts by handling any pending Ethernet packets with `ether.packetReceive()` and immediately passes them to `ether.packetLoop()`. This ensures the Ethernet buffer is processed and ready for new operations.
- **Stash Buffer**: A stash buffer is created with `stash.create()` for building the HTTP POST request. The RFID tag data is added to the stash using `stash.print(tag)` and finalized with `stash.save()`.

**2. HTTP POST Request Preparation**
- **HTTP Request Setup**: An HTTP POST request is constructed with a path and host extracted from predefined variables (`website`). The `Stash::prepare` method is used, inserting various elements into the HTTP headers such as the path, host, content length (determined by `stash.size()`), and the stash descriptor.
- **Sending the Request**: `ether.tcpSend()` is called to open a TCP connection and send the prepared HTTP request. The ID of the TCP session is stored for later reference.

**3. Response Handling**
- **Response Timeout Loop**: The function waits for a server response within `TIMEOUT_TIME`. It continuously checks for responses by processing incoming packets and using `ether.tcpReply(session)` to check for replies specifically related to the opened TCP session.
- **Extracting Status from Response**: If a response is detected, the function extracts a status code using a helper function `getStatus(reply, status)`. It then compares this status string with "OK".
  - **Access Granted**: If the status is "OK", the function returns `true`, indicating that access has been authorized based on the server's positive acknowledgment of the RFID data.
  - **No Response or Non-OK Status**: If the timeout expires without a response, or if the response status is not "OK", the function returns `false`, indicating that access has been denied.

**4. Delay Handling**
- **Network Delay**: Between each check for responses, there is a delay of 200 milliseconds to reduce the load on the network interface and prevent flooding the network with rapid packet checks.

### sendHandshake Function
```cpp
bool sendHandshake() {
  ether.packetLoop(ether.packetReceive());
  byte stash_desc = stash.create();
  stash.print("Handshake");
  stash.save();

  Stash::prepare(PSTR("POST http://$F/$F HTTP/1.1\r\n"
                      "Host: $F\r\n"
                      "Content-Length: $D\r\n"
                      "Content-Type: text/plain\r\n"
                      "\r\n"
                      "$H"),
                 website, PSTR("rfid"), website, stash.size(), stash_desc);

  byte session = ether.tcpSend();

  unsigned long startTime = millis();
  while (millis() - startTime < 5000) { // Timeout after 5 seconds
    ether.packetLoop(ether.packetReceive());

    // Flush the Ethernet buffer
      const char* reply = ether.tcpReply(session);
      if(reply != 0)
        return true;
  }

  return false;
}
```
The sendHandshake function in our code is designed to establish an initial communication session between the Arduino-based system and a server. This handshake is critical as it sets up a preliminary connection with the server, reducing the overhead for subsequent RFID tag transmissions by ensuring the communication channel is open and responsive. Here’s a breakdown focusing on the core components and their purposes:

**1. Packet Handling and Data Preparation**
- **Packet Processing**: The function starts by receiving and processing packets to maintain an active Ethernet interface using `ether.packetReceive()` and `ether.packetLoop()`.
- **Stash Setup**: A stash (temporary storage) is created using the `Stash` class, and the string "Handshake" is stored. This prepares the message for the upcoming HTTP request.
- **HTTP Request Preparation**: Constructs an HTTP POST request. This request is formatted with headers that include the host, content length, and content type, alongside the "Handshake" message.

**2. Sending the Request and Monitoring Response**
- **Sending Request**: A TCP session is initiated with `ether.tcpSend()`, through which the prepared HTTP request is transmitted to the server.
- **Response Handling**: The function then enters a loop that waits for a response within a 5-second timeout. During this period, it continuously processes incoming packets to ensure the Ethernet interface remains active.

**3. Cleanup and Return**
- **Buffer Flushing and Response Verification**: The function checks for a reply from the server using `ether.tcpReply(session)`. If a reply is detected (`reply != 0`), the function returns `true`, indicating a successful connection.
- **Timeout Handling**: If no reply is received within the 5-second window, the function returns `false`, signifying that the handshake attempt was unsuccessful.



---
### Client Folder
This folder contains the code for the Qt-based GUI monitoring system, which is used to display entry events.
The initial source code was provided, and significant enhancements have been made to tailor it to our project's specific requirements and functionalities.

**Modifications and Enhancements:**
#### `cpsapplication.h`

- **Signal and Slot Definitions**: Updated the header file to include new signals and slots that facilitate the communication between the GUI components and the backend processes.
```cpp
#ifndef CPSAPPLICATION_H
#define CPSAPPLICATION_H

#include <QObject>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>

#include "cpsmainwindow.h"
#include "cpshistorywindow.h"
#include "cpswindowsapitools.h"
#include "cpssocket.h"

namespace CPS {

class Application : public QObject
{
    Q_OBJECT

public:

    explicit Application(QObject *parent = nullptr);
    ~Application();

    void show();

Q_SIGNALS:


private Q_SLOTS:
    void showHistoryWindow(const QJsonObject &jsonObject);
    void sendHistoryRequest();
    void connectToServer(const QString &serverAddress, const QString &username, const QString &password);

private: // methods

private: // members
    MainWindow    *_window;
    HistoryWindow *_history;
    CPSSocket *_socket;
};

} // end of CPS

#endif // CPSAPPLICATION_H
```
#### `cpsapplication.cpp`

Several key modifications and new features were integrated into `cpsapplication.cpp` to enhance functionality and user experience:

1. **Requesting History Data:**
   ```cpp
   QObject::connect(_window, &MainWindow::historyBtnClicked, this, &Application::sendHistoryRequest);
   ```
   This line connects the `historyBtnClicked` signal from the `MainWindow` class to the `sendHistoryRequest` slot of the `Application` class. When the history button is clicked in the GUI, this connection triggers a request to retrieve the history log from the server.

2. **Server Connection Initialization:**
   ```cpp
   QObject::connect(_window, &MainWindow::connectBtnClicked, this, &Application::connectToServer);
   ```
   This line establishes a connection between the `connectBtnClicked` signal in the `MainWindow` and the `connectToServer` slot in the `Application`. It initiates the process to establish a network connection to the server when the connect button is clicked.

3. **Displaying New User Details:**
   ```cpp
   QObject::connect(_socket, &CPSSocket::newUser, _window, &MainWindow::showUserDetails);
   ```
   Here, the `newUser` signal from the `CPSSocket` class is connected to the `showUserDetails` slot in the `MainWindow`. This setup is used for displaying the details of a new user (e.g., RFID tag recognized, entry granted/denied) in the GUI in real time as these events occur.

4. **Handling New History Data:**
   ```cpp
   QObject::connect(_socket, &CPSSocket::newHistory, this, &Application::showHistoryWindow);
   ```
   This connection links the `newHistory` signal emitted by the `CPSSocket` class to the `showHistoryWindow` slot in the `Application`. It is triggered when new history data is received from the server, prompting the application to display this data in the history window.

5. **Changing GUI Elements Based on Connection Status:**
   ```cpp
   QObject::connect(_socket, &CPSSocket::connectionChanged, _window, &MainWindow::changeRightPanelEnabled);
   ```
   This line connects the `connectionChanged` signal from the `CPSSocket` class to the `changeRightPanelEnabled` slot in the `MainWindow`. It enables or disables GUI elements based on the current network connection status (e.g., disabling the connect button to prevent duplicate connections).
   
Also We have made an update to the method responsible for enabling or disabling UI components in the `MainWindow` class. This change enhances the usability and responsiveness of the user interface. (in cpsmainwindow.cpp)
Previous Code:
```cpp
void MainWindow::changeRightPanelEnabled(bool enabled)
{
    _rightPanel->setEnabled(enabled);
}
```
Updated Code:
```cpp
void MainWindow::changeRightPanelEnabled(bool enabled){
    _connectBtn->setEnabled(enabled);
}
```


These connections are fundamental for the interactivity and responsiveness of our client application, allowing the GUI to react dynamically to backend changes and user inputs. They enable our system to handle data efficiently, ensuring that the GUI reflects the most current system status and logs.

##### History Window Display Logic:  
Developed a method to process and display the history data received from the server. The method parses the JSON data, extracting necessary details and passing them to the history window for display.

```cpp
void Application::showHistoryWindow(const QJsonObject &jsonObject)
{
    setWindowsThemeToDark<HistoryWindow>(*_history);

    QJsonArray historyArray = jsonObject["data"].toArray();

    QVariantList list;

    for (const QJsonValue &value : historyArray) {
        QJsonObject historyObject = value.toObject();
        QJsonObject obj;
        obj["username"] = historyObject["username"].toString();
        obj["date"] = historyObject["date"].toString();
        obj["time"] = historyObject["time"].toString();
        list.append(obj);
    }

    QJsonArray data = QJsonArray::fromVariantList(list);

    _history->show(data);
}
```
### Client Socket Implementation
This section details the implementation of the `CPSSocket` class, which handles all TCP/IP communications between the client-side application and the server. This class is pivotal for sending and receiving data over the network, authenticating admin, and retrieving updates about entry events and history.

#### `cpssocket.h`

```cpp
#ifndef CPSSOCKET_H
#define CPSSOCKET_H

#include <QObject>
#include <QTcpSocket>

class CPSSocket : public QObject {
    Q_OBJECT
public:
    explicit CPSSocket(QObject *parent = nullptr);
    QTcpSocket* getSocket() const;

public Q_SLOTS:
    void connectToServer(const QString &serverAddress, const QString &username, const QString &password);
    void collectingNewData();

private:
    QTcpSocket *socket;
    void ExtractNewUserData(const QJsonObject &jsonObject);

Q_SIGNALS:
    void newUser(const QString &username, const QString &date, const QString &time);
    void connectionChanged(bool enabled);
    void newHistory(const QJsonObject &jsonObject);
};

#endif // CPSSOCKET_H
```
- **Class CPSSocket**: Inherits from `QObject` and manages TCP socket communications.
- **Constructor**: Initializes a new TCP socket.
- **getSocket()**: Returns the active TCP socket.
- **Slots**:
  - **connectToServer()**: Connects to the server using the provided credentials.
  - **collectingNewData()**: Handles incoming data from the server.
- **Signals**:
  - **newUser**: Emitted when new user data is received.
  - **connectionChanged**: Emitted to update UI components based on connection status.
  - **newHistory**: Emitted when new history data is received from the server.

#### `cpssocket.cpp` 
**1. Constructor**
Initializes the `CPSSocket` object and creates a new `QTcpSocket`.
```cpp
CPSSocket::CPSSocket(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
}
```

**2. Get Socket Method**  
Provides external access to the internal TCP socket. Which Allows other parts of the application to use the socket for various networking tasks if needed.  

```cpp
QTcpSocket* CPSSocket::getSocket() const {
    return socket;
}
```
**3. Connect to Server**  
Establishes a connection to the server and sends authentication data.
```cpp
void CPSSocket::connectToServer(const QString &serverAddress, const QString &username, const QString &password) {
    socket->connectToHost(serverAddress, 5050);
    if (socket->waitForConnected()) {
        QString message = username + ":" + password;
        QTextStream(stdout) << "Connected to server. Sending message: " << message << Qt::endl;
        socket->write(message.toUtf8());
        if (socket->waitForReadyRead()) {
            QByteArray responseData = socket->readAll();
            QTextStream(stdout) << "Received response from server:" << responseData << Qt::endl;
            if(responseData == "1") {
                emit connectionChanged(false);
                QObject::connect(socket, &QTcpSocket::readyRead, this, &CPSSocket::collectingNewData);
            }
        } else {
            QTextStream(stdout) << "Timeout while waiting for server response" << Qt::endl;
        }
    } else {
        QTextStream(stdout) << "Failed to connect to server:" << socket->errorString() << Qt::endl;
    }
}
```
  - **Connection Attempt**: Attempts to connect to the specified server address on port 5050.
  - **Authentication**: Sends a combined string of username and password.
  - **Response Handling**: Waits for a response from the server to confirm connection and authentication success.
  - **Signal Emission**: If authenticated (`responseData` equals "1"), disables further connection attempts and sets up to receive new data. (using `collectingNewData` )
  - **Error Handling**: Outputs errors if connection fails or times out.

**4. Collecting New Data**
Handles new data received from the server.
```cpp
void CPSSocket::collectingNewData() {
    QByteArray responseData = socket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
    if (!jsonDocument.isNull() && jsonDocument.isObject()) {
        QJsonObject jsonObject = jsonDocument.object();
        if (jsonObject.contains("type") && jsonObject["type"].toString() == "user") {
            ExtractNewUserData(jsonObject);
        } else if (jsonObject.contains("type") && jsonObject["type"].toString() == "history") {
            emit newHistory(jsonObject);
        } else {
            QTextStream(stdout) << "Invalid type field in JSON data" << Qt::endl;
        }
    } else {
        QTextStream(stdout) << "Failed to parse JSON data" << Qt::endl;
    }
}
```
  - **Data Reception**: Reads all available data from the socket.
  - **JSON Parsing**: Converts the byte array to a `QJsonDocument` and checks for validity.
  - **Data Handling**: Depending on the "type" field in the JSON object, it either processes new user data or emits history data.
  - **Error Handling**: Logs an error if the JSON data is invalid or cannot be parsed.

**5. Extract New User Data**
Extracts user details from the received JSON object and emits them.
```cpp
void CPSSocket::ExtractNewUserData(const QJsonObject &jsonObject) {
    QString username = jsonObject["username"].toString();
    QString date = jsonObject["date"].toString();
    QString time = jsonObject["time"].toString();
    emit newUser(username, date, time);
}
```
This method retrieves the username, date, and time from the JSON object and emits the `newUser` signal with these details.

---

### Server Folder
This folder contains all necessary files for setting up and running the server that manages communication between the IoT devices (Arduino boards) and the client applications. The server is designed to handle requests over HTTP from Arduino boards for RFID authentication and to communicate with client applications via WebSocket.

#### `request.cpp` & `request.h`
These files encapsulate the functionality required to handle incoming HTTP requests.  
The `.h` file declares the structure of the `Request` class, which includes methods for initializing a request object, parsing the content, and retrieving specific elements like headers or the body.The `.cpp` file implements these methods, detailing how the server processes and extracts data from incoming HTTP requests, which is critical for actions like RFID verification or command execution.  

**`.h` file:**
```cpp
#ifndef REQUEST_H
#define REQUEST_H

#include <QJsonObject>
#include <QJsonDocument>

class Request
{
public:
    Request();
    Request(const QString &type, const QVariant  &data);

    QString getType() const;
    void setType(const QString &type);

    QVariant  getData() const;
    void setData(const QVariant  &data);

    QJsonObject toJson() const;
    static Request fromJson(const QJsonObject &json);

private:
    QString type_;
    QVariant  data_;
};

#endif // REQUEST_H
```
**`.cpp` file:**
```cpp

#include "request.h"

Request::Request() {}


Request::Request(const QString &type, const QVariant  &data) : type_(type), data_(data) {}

QString Request::getType() const {
    return type_;
}

void Request::setType(const QString &type) {
    type_ = type;
}

QVariant  Request::getData() const {
    return data_;
}

void Request::setData(const QVariant  &data) {
    data_ = data;
}

QJsonObject Request::toJson() const {
    return QJsonObject{{"type", type_}, {"data", QJsonValue::fromVariant(data_)}};
}

Request Request::fromJson(const QJsonObject &json) {
    return Request(json["type"].toString(), json["data"].toVariant());
}

```

#### `response.cpp` & `response.h`
The `Response` class, declared in the `.h` file and implemented in the `.cpp` file, manages the server's output to clients. This includes generating the appropriate HTTP response based on the processing of the request. It allows the server to easily set status codes and craft response bodies, which are essential for notifying clients of the results of their requests, whether they are accessing resources or executing commands.  

**`.h` file:**
```cpp
#ifndef RESPONSE_H
#define RESPONSE_H

#include <QJsonObject>
#include <QJsonDocument>

class Response
{
public:
    Response();
    Response(const QVariant &data);

    QVariant getData() const;
    void setData(const QVariant &data);

    QJsonObject toJson() const;
    static Response fromJson(const QJsonObject &json);

private:
    QVariant data_;
};

#endif // RESPONSE_H
```
**`.cpp` file:**
```cpp
#include "response.h"

Response::Response() {}

Response::Response(const QVariant &data) : data_(data) {}

QVariant Response::getData() const {
    return data_;
}

void Response::setData(const QVariant &data) {
    data_ = data;
}

QJsonObject Response::toJson() const {
    QJsonObject json;
    json["data"] = data_.toJsonObject();
    return json;
}

Response Response::fromJson(const QJsonObject &json) {
    return Response(QVariant::fromValue(json["data"]));
}

```


#### `customizedhttpserver.cpp` & `customizedhttpserver.h`
These files together define and implement a custom HTTP server tailored for our IoT system. The header file declares the server class and necessary methods, while the implementation file details how the server handles HTTP requests and responses.

**`.h` file:**
```cpp
#ifndef CUSTOMIZEDHTTPSERVER_H
#define CUSTOMIZEDHTTPSERVER_H

#include <QObject>
#include <QCoreApplication>
#include <QHttpServer>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonObject>
#include "employeesdatabase.h"

class CustomizedHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit CustomizedHttpServer(int port, const QString &initialDataPath, QObject *parent = nullptr);
    bool startServer(int port);

signals:
    void resultRfidCheck(bool isMatch, const QDateTime &currentTime, const QString &rfid);

private slots:
    QHttpServerResponse handleRequest(const QHttpServerRequest &request);

private:
    QHttpServer* httpServer_;
    EmployeesDatabase employeesDatabase_;
};

#endif // CUSTOMIZEDHTTPSERVER_H
```
**`.cpp` file:**

- **Constructor (`CustomizedHttpServer`)**: Sets up the employees database and configures the HTTP server to route `/rfid` POST requests through a designated handler that processes RFID data for authentication.
```cpp
CustomizedHttpServer::CustomizedHttpServer(int port, const QString &initialDataPath, QObject *parent) :
    QObject(parent), employeesDatabase_(EmployeesDatabase(initialDataPath)), httpServer_(new QHttpServer())
{
    httpServer_->route("/rfid",QHttpServerRequest::Method::Post, [this](const QHttpServerRequest& request) {
        return this->handleRequest(request);
    });

    startServer(port);
}
```  

- **`startServer(int port)`**: Launches the server to listen on the specified port across all network interfaces, enabling it to receive incoming requests.
```cpp
bool CustomizedHttpServer::startServer(int port)
{
    return httpServer_->listen(QHostAddress::Any, port);
}
```  

- **`handleRequest(const QHttpServerRequest& request)`**: Processes each POST request to `/rfid`, extracting RFID data, verifying it against the employee database, and returning the appropriate HTTP response based on whether the access is authorized. Also emits detailed results for system monitoring or logging.
```cpp
QHttpServerResponse CustomizedHttpServer::handleRequest(const QHttpServerRequest& request)
{
    QByteArray requestData = request.body();
    QString rfid = requestData;

    bool isAuthorized = employeesDatabase_.handleRfidReceived(rfid);

    QDateTime currentTime = QDateTime::currentDateTime();
    emit resultRfidCheck(isAuthorized, currentTime, rfid);

    QByteArray result;
    QHttpServerResponse::StatusCode statusCode;
    if (isAuthorized) {
        result = "1";
        statusCode = QHttpServerResponse::StatusCode::Ok;
    }
    else {
        result = "0";
        statusCode = QHttpServerResponse::StatusCode::Unauthorized;
    }

    return QHttpServerResponse(result, statusCode);
}
```
This setup ensures robust handling of access control requests, providing secure and efficient authentication management tailored to the needs of the IoT system. T

#### `employee.cpp` & `employee.h`
These files define and implement the Employee class, responsible for encapsulating employee-related data within the system.
**`.h` file:**  
```cpp
#include "employee.h"

Employee::Employee() {
    rfidTag_ = nullptr;
}

Employee::Employee(const QString &rfidTag) : rfidTag_(rfidTag) {};

bool Employee::checkRFIDTagMatched(const QString &rfidTag) const{
    return rfidTag_ == rfidTag;
}
```
**`.cpp` file:**
These class provides a straightforward implementation suited for systems where RFID is the primary identifier for employees.
```cpp
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QJsonObject>
#include <QJsonDocument>

class Employee
{
public:
    Employee();
    Employee(const QString &rfidTag);
    bool checkRFIDTagMatched(const QString &rfidTag) const;
private:
    QString rfidTag_;
};

#endif // EMPLOYEE_H
```

#### `employeesdatabase.cpp` & `employeesdatabase.h`  
These files encompass the `EmployeesDatabase` class, The `EmployeesDatabase` class manages a collection of employees, specifically their RFID tags, to facilitate access control within the system. It loads employee data from a JSON file at initialization and provides methods to verify RFID tags against this data.

**`.h` file:**  
```cpp
#ifndef EMPLOYEESDATABASE_H
#define EMPLOYEESDATABASE_H

#include <QObject>
#include <QVector>
#include "employee.h"

class EmployeesDatabase : public QObject
{
    Q_OBJECT
public:
    explicit EmployeesDatabase(const QString &initialDataPath, QObject *parent = nullptr);

    const QVector<Employee>& getEmployeesVector() const;
    bool handleRfidReceived(const QString &rfid);

private:
    QVector<Employee> employeesVector_;

    void readEmployeesFromJson(const QString &path);
};

#endif // EMPLOYEESDATABASE_H
```
**`.cpp` file:**

- **Constructor (`EmployeesDatabase`)**: Loads employee data from a JSON file specified by the path provided, initializing the database with the necessary employee information for immediate use.
```cpp
EmployeesDatabase::EmployeesDatabase(const QString &initialDataPath, QObject *parent) : QObject(parent)
{
    readEmployeesFromJson(initialDataPath);
}
```
- **`getEmployeesVector`**: Grants read-only access to the vector of employees, useful for operations requiring data on all employees.
```cpp
const QVector<Employee>& EmployeesDatabase::getEmployeesVector() const
{
    return employeesVector_;
}
```
- **`readEmployeesFromJson`**: Parses employee data from a JSON file, creating employee records for each valid entry. This method ensures the database is populated with current and accurate information from the specified file.
```cpp
void EmployeesDatabase::readEmployeesFromJson(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open " + path;
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format in " + path;
        return;
    }

    QJsonArray employeesArray = doc.array();
    for (const QJsonValue& employeeValue : employeesArray) {
        if (!employeeValue.isObject()) {
            qDebug() << "Invalid employee data in " + path;
            continue;
        }

        QJsonObject employeeObject = employeeValue.toObject();
        QString rfidTag = employeeObject["rfid"].toString();

        Employee employee(rfidTag);
        employeesVector_.append(employee);
    }
}
```
- **`handleRfidReceived`**: Verifies a received RFID tag against the database, returning a boolean to indicate whether the tag is authorized, critical for implementing effective access controls in security-sensitive environments.
```cpp
bool EmployeesDatabase::handleRfidReceived(const QString &rfid) {
    bool isMatch = false;
    for (const Employee &employee : employeesVector_) {
        if (employee.checkRFIDTagMatched(rfid)) {
            isMatch = true;
            break;
        }
    }

    return isMatch;
}
```
This class is a foundational component of the system's security infrastructure, handling the crucial task of RFID-based employee authentication.

#### `main.cpp`
The `main` function of the application serves as the entry point, initializing and running the HTTP server that forms the core of the system's network interactions.

- **Configuration**:
  - **Files**: Configures paths to crucial data files (`employees.json`, `admins.json`, `history.json`), ensuring the server has access to essential data for operations.
```cpp
const QString USERS_FILE_PATH = "../../data/employees.json";
const QString ADMINS_FILE_PATH = "../../data/admins.json";
const QString HISTORY_FILE_PATH = "../../data/history.json";
```
  - **Port**: Sets the server to listen on HTTP standard port 80, facilitating easy access via standard web protocols.
```cpp
const int HTTP_SERVER_PORT = 80;
```
- **Execution**:
```cpp
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    CustomizedHttpServer customizedHttpServer = CustomizedHttpServer(HTTP_SERVER_PORT, USERS_FILE_PATH);
    

    qInfo("Server running on port 80");
    return app.exec();
}
```
  - **Server Initialization**: A `CustomizedHttpServer` instance is created and started with predefined settings, including the port and user data file path.
  - **Running State Notification**: Outputs a log message to confirm the server's operational status, helping in diagnostics and monitoring.
  - **Event Loop**: Enters the Qt event loop, which is crucial for processing incoming network requests and internal events, maintaining the server's responsiveness.

This setup demonstrates a straightforward, robust server initialization and execution strategy, leveraging Qt's capabilities for effective network communication and event handling within a server environment.

### Data Folder
Contains JSON files used for initial data setup and storage, facilitating quick data retrieval and management.
1. `admins.json`
- **Content**: Stores administrative user details necessary for system management.
2. `employees.json`
- **Content**: Contains employee records that populate the `EmployeesDatabase`.
3. `history.json`
- **Content**: Logs entry and access history.

### Server Response Examples
The following screenshots demonstrate the server's response to various RFID tag requests via a simulated HTTP client. These tests verify that the server correctly identifies authorized and unauthorized access attempts based on RFID data.

#### Authorized Access
Here, the server successfully recognizes an authorized RFID tag, returning a `200 OK` status, indicating the request is authorized:
![Authorized Access](CA1/Pics/screenshot(server)/success.png)

#### Unauthorized Access
This screenshot shows the server handling an unauthorized RFID tag, returning a `401 Unauthorized` status, highlighting the security measures in place:
![Authorized Access](CA1/Pics/screenshot(server)/failed.png)

