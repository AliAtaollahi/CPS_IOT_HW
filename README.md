# IoT-Based Entry and Exit Management System

## Project Overview

This project develops a system to control the entry and exit of individuals in a company using IoT technologies. The system utilizes RFID for identification and an Arduino board equipped with an ENC28J60 Ethernet module to handle door mechanisms and data transmission. A simple web server is implemented in the cloud to manage access permissions, and a monitoring system is set up to track and display entry events.

## Key Features

- **RFID Authentication:** Utilizes RFID sensors and tags for identifying individuals.
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
- LCD display to show feedback on authentication status.
  
### Software Requirements

- **Arduino IDE:** For programming the Arduino board.
- **Qt Creator:** For developing the GUI monitoring system.
- **Proteus Software:** For simulating the hardware setup. (Physical components are not available.)

## Installation and Configuration

1. **Arduino Setup:**
   - Install the Arduino IDE and load the provided script.
   - Connect the ENC28J60 module and configure it for Ethernet access.
   - Attach the RFID sensor, servo motor, LEDs, and LCD.

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
   - **RFID Reader Terminal**: This component simulates the RFID tag reader terminal where individuals can tap their RFID cards for authentication. In the simulation, we can input RFID tag data to emulate different user interactions.
   
   - **Arduino Board**: The Arduino microcontroller is simulated to execute the control logic for the entry and exit management system. It interfaces with the RFID reader, servo motor, LEDs, LCD, and Ethernet module to perform authentication and control door access.
   
   - **ENC28J60 Ethernet Module**: This module is simulated to provide Ethernet connectivity for the Arduino board. It enables communication between the Arduino and the cloud-based server for authentication and data transmission.
   
   - **Servo Motor for Door Control**: The servo motor is simulated to mimic the physical door mechanism controlled by the Arduino board. In the simulation, we can observe how the servo motor responds to commands from the Arduino, such as opening and closing the door.
   
   - **LEDs and LCD for Status Indication**: Indicate system status and display access messages.

#### Screenshots (imulation in Proteus)
1. "Starting and Waiting for Handshake"
![Screenshot 1 - Starting and Waiting for Handshake](CA1/Pics/screenshot(SimulationInProteus)/1.png)
*Description: This screenshot captures the initial state of the system where the Arduino board is powered on and waiting to establish a connection with the cloud server. The system is in standby mode.*

2. "Handshake is Done"
![Screenshot 2 - Handshake is Done](CA1/Pics/screenshot(SimulationInProteus)/2.png)
*Description: This screenshot shows the system after successfully establishing a connection with the cloud server. The monitor shows that the handshake process is complete, and the system is ready to receive RFID authentication requests.*

3. "Input a Correct RFID -> Open Door and Green LED"
![Screenshot 3 - Input a Correct RFID](CA1/Pics/screenshot(SimulationInProteus)/3.png)
*Description: In this screenshot, a correct RFID tag is presented to the system for authentication. The Arduino board processes the RFID data, communicates with the cloud server for authentication, and receives a positive response. As a result, the servo motor opens the door, and the green LED lights up, indicating access granted.*

4. "Input an Incorrect RFID -> Close Door and Red LED"
![Screenshot 4 - Input an Incorrect RFID](CA1/Pics/screenshot(SimulationInProteus)/4.png)
* This screenshot depicts the scenario where an incorrect RFID tag is presented for authentication. The Arduino board sends the RFID data to the cloud server, but authentication fails. Consequently, the servo motor keeps the door closed. The red LED, which is normally on to indicate a secure state, remains lit, signaling that access is denied.*

5. "Sequential RFID Authentication - Open Door, Then Close for Second Person"
![GIF - Sequential RFID Authentication](CA1/Pics/screenshot(SimulationInProteus)/5.gif)

*Description: This GIF demonstrates a sequential scenario where a correct RFID tag is initially presented, granting access and opening the door. Subsequently, an incorrect RFID tag is presented, resulting in access denial and the door closing. Delays are observable due to processing time required for 1. Arduino to process the RFID data and control the servo motor, and 2. HTTP request and response between the Arduino and the cloud server for authentication.*


This comprehensive simulation environment allows us to test and validate the functionality of the IoT-based entry and exit management system before deploying it in a real-world environment. It enables thorough testing of various scenarios and interactions to ensure the system operates reliably and efficiently.
___
### Embedded Folder
The embedded software for the IoT-based Entry and Exit Management System is designed to run on an Arduino board. It integrates several components including a servo motor for door control, RFID reader for identity verification, and an Ethernet module for network communication. The following sections describe the key parts of the Arduino sketch, highlighting how each contributes to the system's operations.

#### Key Libraries

- **`Servo.h`**: Manages the servo motor used to open and close the door.
- **`EtherCard.h`**: Facilitates Ethernet communications for interfacing with the cloud server.
- **`LiquidCrystal.h`**: Controls the LCD display for real-time feedback to the user.
  
#### Configuration
Defines the pin configuration and timeout settings for the system, ensuring that components such as LEDs, LCD and servo motors are correctly managed.  

```cpp
#define TIMEOUT_TIME 1000
#define LEDS 2
#define RX_PIN 0
#define TX_PIN 1
#define SERVO_PIN 3
#define D4 6
#define D5 7
#define D6 8
#define D7 9
#define RS 5
#define EN 4
```

#### Initialization
Initializes the servo motor, LCD, and sets up networking parameters including MAC address, IP addresses, and the remote server details.  

```cpp
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

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

#### setup Function
This section configures the GPIO pins, initializes the LCD, and attaches the servo to its designated pin. Network initialization and diagnostic outputs are also set here.
```cpp
void setup() {
  pinMode(LEDS, OUTPUT);
  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);
  pinMode(EN, OUTPUT);
  lcd.begin(25,2);
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

Here’s a brief and focused explanation for each subject within our `setup()` function:  

**1. Selecting Pins** 
Configures GPIO pins for the LEDs, EN (for LCD) and RX/TX pins, setting the directionality (input or output) for each.  

**2. LCD initialization**
Initializes the LCD display with a specification of 25 characters per line and 2 lines. This is where messages like access status and RFID data will be displayed.  

**3. Closing Door**   
Attaches the servo motor to its control pin and initializes it to a closed position, ensuring the door starts closed upon system reset.

**4. Initializing Serial and Ethernet Port**    
Initializes serial communication at 9600 baud rate for debugging and configures the Ethernet module with static IP settings.  

**5. Performing Handshake**   
Establishes a network route to the server, prints server IP for verification, waits for gateway availability, then sends a handshake to the server confirming network connectivity.

#### Main Loop
Continuously reads RFID tags, checks them against server-side validation, and controls door access. Updates LED status based on authentication results.  

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
    if (millis() - doorOpenTime >= 10000) {
      doorOpen = false;
      digitalWrite(LEDS, LOW);
      doorServo.write(0);
      inputString = "";
    }
  }

    // If the receivedString has reached 10 characters
    if (inputString.length() == 10) {
        lcd.clear();
        boolean sequenceResult = checkRFID(inputString);


      Serial.println("  \n ");
      Serial.print("Sequence Check Result: ");
      Serial.println(sequenceResult ? "Correct" : "Incorrect");
      
      if (sequenceResult) {
        lcd.print(inputString);
        inputString = "";
        
        digitalWrite(LEDS, HIGH);
        doorServo.write(90);
        doorOpen = true;
        doorOpenTime = millis(); // Record the time when the door was opened
      } else {
        // If the sequence is incorrect, close the door
        lcd.print("Access denied");
        
        digitalWrite(LEDS, LOW);
        doorServo.write(0);
		    
        delay(500);
        doorOpen = false;
      }
      inputString = "";
    }
}
```
 Here's a breakdown of the specific parts of the Arduino `loop()` function provided, detailing how it handles the RFID data received from the terminal, checks its validity, and manages access control logic based on the RFID check result:

**1. Receiving RFID from Terminal**
- **Network Data Handling**: Maintains the Ethernet connection and processes any packets that have been received.
- **Serial Data Collection**: Gathers all available data from the serial buffer, appending it to a string. This is presumed to be RFID data from a terminal.
- **Data Aggregation**: Adds newly received data to a cumulative string (`inputString`) if data is present.

**2.Validating and Checking the RFID** 
- **RFID Length Check**: Ensures that the `inputString` has accumulated exactly 10 characters, assumed to be the complete RFID sequence.
- **RFID Validation**: Calls `checkRFID(inputString)` to validate the RFID sequence. Outputs the result to the terminal for debugging.

**3. Handling Logic**  
- **For Correct RFID**:
  - **LEDs, LCD and Door**: Turns the GREEN LED on and the RED LED off, indicating access granted. Opens the door by setting the servo to 90 degrees.
  - **Time Tracking**: Marks the time the door was opened to check for auto-close timing.
- **For Incorrect RFID**:
  - **LEDs and Door**: Turns the GREEN LED off and the RED LED on, signaling access denied. Resets the door to a closed position by setting the servo to 0 degrees.
- **String Reset**: Clears `inputString` to ready the system for the next RFID read cycle.
- 
### getStatus Function
The `getStatus` function is designed to extract a status code from a response string (reply) and store it in the status array.
```cpp
void getStatus(char* reply, char* status) { 
  memcpy(status, &reply[13], 2);
  status[2] = '\0';
}
```

#### checkRFID Function
This function encapsulates a network interaction pattern where an RFID tag is sent to a server for authorization. The use of a TCP/IP stack (via the EtherCard library) and careful handling of Ethernet buffers and sessions allows for efficient network communications on resource-constrained devices like those running Arduino. The decision to grant or deny access is made based on the server's response to the transmitted RFID tag.

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
      // for debugging
      /*Serial.println(reply);
      Serial.println(status);*/

      return strcmp(status, "OK") == 0 ? true : false;
    }
    //delay(200);

  }

  return false; // no access
}
```
Here's a breakdown of the specific parts of this function:

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


### sendHandshake Function
The sendHandshake function in our code is designed to establish an initial communication session between the Arduino-based system and a server. This handshake is critical as it sets up a preliminary connection with the server, reducing the overhead for subsequent RFID tag transmissions by ensuring the communication channel is open and responsive.  

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
 Here’s a breakdown focusing on the core components and their purposes:

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
    void resultRfidCheck(bool isMatch, const QString &rfid);
    void resultRfidCheckHistory(bool isMatch, const QString Date, const QString &currentTime, const QString &rfid);

private:
    QHttpServerResponse handleRequest(const QHttpServerRequest &request);
    QHttpServer* httpServer_;
    EmployeesDatabase employeesDatabase_;
};

#endif // CUSTOMIZEDHTTPSERVER_H
```
**`.cpp` file:**

- **Constructor (`CustomizedHttpServer`)**: Sets up the employees database and configures the HTTP server to route `/rfid` POST requests through a designated handler that processes RFID data for authentication.
```cpp
// customizedhttpserver.cpp
#include "customizedhttpserver.h"

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

    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Extract date and time separately
    QDate currentDate = currentDateTime.date();
    QTime currentTime = currentDateTime.time();

    // Convert date and time to strings
    QString dateString = currentDate.toString("yyyy-MM-dd");
    QString timeString = currentTime.toString("HH:mm:ss");

    bool isAuthorized = employeesDatabase_.checkRFIDMatch(rfid);

    emit resultRfidCheck(isAuthorized, rfid);
    emit resultRfidCheckHistory(isAuthorized, dateString, timeString, rfid);

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

#### `employee.cpp` & `employee.h`
These files define and implement the Employee class, responsible for encapsulating employee-related data within the system.
**`.h` file:**  
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
**`.cpp` file:**
These class provides a straightforward implementation suited for systems where RFID is the primary identifier for employees.
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
    bool checkRFIDMatch(const QString &rfid);

private:
    QVector<Employee> employeesVector_;

    void loadEmployeesFromJson(const QString &path);
    void parseEmployeesJson(const QByteArray &jsonData);
    QByteArray readJsonFile(const QString &path);
};

#endif // EMPLOYEESDATABASE_H

```
**`.cpp` file:**

- **Constructor (`EmployeesDatabase`)**: Loads employee data from a JSON file specified by the path provided, initializing the database with the necessary employee information for immediate use.
```cpp
EmployeesDatabase::EmployeesDatabase(const QString &initialDataPath, QObject *parent) : QObject(parent)
{
    loadEmployeesFromJson(initialDataPath);
}
```
- **`getEmployeesVector`**: Grants read-only access to the vector of employees, useful for operations requiring data on all employees.
```cpp
const QVector<Employee>& EmployeesDatabase::getEmployeesVector() const
{
    return employeesVector_;
}
```

- **`loadEmployeesFromJson`**:
```cpp
void EmployeesDatabase::loadEmployeesFromJson(const QString &path)
{
    QByteArray jsonData = readJsonFile(path);
    if (!jsonData.isEmpty()) {
        parseEmployeesJson(jsonData);
    }
}
```
- **`readJsonFile`**:
```cpp
QByteArray EmployeesDatabase::readJsonFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open " + path;
        return QByteArray();
    }

    QByteArray jsonData = file.readAll();
    file.close();

    return jsonData;
}
```
- **`readJsonFile`**:
```cpp
void EmployeesDatabase::parseEmployeesJson(const QByteArray &jsonData)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format";
        return;
    }

    QJsonArray employeesArray = doc.array();
    for (const QJsonValue& employeeValue : employeesArray) {
        if (!employeeValue.isObject()) {
            qDebug() << "Invalid employee data";
            continue;
        }

        QJsonObject employeeObject = employeeValue.toObject();
        QString rfidTag = employeeObject["rfid"].toString();

        Employee employee(rfidTag);
        employeesVector_.append(employee);
    }
}
```
- **`checkRFIDMatch`**:
```cpp
bool EmployeesDatabase::checkRFIDMatch(const QString &rfid)
{
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
#### `authenticator.cpp` & `authenticator.h`
**`.h` file:**  
```cpp
#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

class Authenticator : public QObject
{
    Q_OBJECT
public:
    explicit Authenticator(QObject *parent = nullptr);

    void authenticateUser(const QByteArray &data, QTcpSocket *clientSocket);

private:
    bool isValidUser(const QString &username, const QString &password);
};

#endif // AUTHENTICATOR_H
```


**`.cpp` file:**
```cpp
#include "authenticator.h"
#include <QDebug>

Authenticator::Authenticator(QObject *parent) : QObject(parent)
{
}

void Authenticator::authenticateUser(const QByteArray &data, QTcpSocket *clientSocket)
{
    QList<QByteArray> parts = data.split(':');

    if (parts.size() >= 2) {
        QString username = QString::fromUtf8(parts[0]);
        QString password = QString::fromUtf8(parts[1]);
        bool isValid = isValidUser(username, password);
        if (isValid) {
            clientSocket->write("1");
            qDebug() << "Access granted for:" << username;
        } else {
            qDebug() << "Access denied for:" << username;
            clientSocket->write("0");
            clientSocket->close();
        }
        qDebug() << "Username:" << username << "Password:" << password;
    } else {
        qDebug() << "Invalid message format";
    }
}

bool Authenticator::isValidUser(const QString &username, const QString &password)
{
    return (username == "test" && password == "1234");
}
```

#### `loginhistory.cpp` & `loginhistory.h`
**`.h` file:**  
```cpp
#ifndef LOGINHISTORY_H
#define LOGINHISTORY_H

#include <QObject>
#include <QDateTime>
#include <QString>


class LoginHistory
{
public:
    LoginHistory();
    LoginHistory(QString username, QString date, QString time, bool permited = false);

    QString getUsername() const;
    QString getDate() const;
    QString getTime() const;
    bool isPermitted() const;

private:
    QString username_;
    QString date_;
    QString time_;
    bool permited_;
};

#endif // LOGINHISTORY_H
```
**`.cpp` file:**
```cpp
#include "loginhistory.h"

LoginHistory::LoginHistory() {}

LoginHistory::LoginHistory(QString username, QString date, QString time, bool permited)
    : username_(username), date_(date), time_(time), permited_(permited){}

QString LoginHistory::getUsername() const
{
    return username_;
}

QString LoginHistory::getTime() const
{
    return time_;
};

QString LoginHistory::getDate() const
{
    return date_;
};

bool LoginHistory::isPermitted() const
{
    return permited_;
};
```
#### `loginhistorydatabase.cpp` & `loginhistorydatabase.h`
**`.h` file:**  
```cpp
#ifndef LOGINHISTORYDATABASE_H
#define LOGINHISTORYDATABASE_H

#include <QObject>
#include <QVector>
#include "loginhistory.h"

class LoginHistoryDatabase : public QObject
{
    Q_OBJECT
public:
    explicit LoginHistoryDatabase(const QString &initialDataPath, QObject *parent = nullptr);

    const QVector<LoginHistory>& getLoginHistoriesVector() const;

signals:
    void loginHistoryResult(const QVector<LoginHistory> &history);

public slots:
    void handleRequestLoginHistory();
    void addLoginHistory(bool isMatch, const QString &date, const QString &time, const QString &rfid);

private:
    QVector<LoginHistory> loginHistoryVector_;

    void readLoginHistoriesFromJson(const QString &path);
    QVector<LoginHistory> parseLoginHistories(const QByteArray &jsonData);
    LoginHistory parseLoginHistory(const QJsonObject &loginHistoryObject);
};

#endif // LOGINHISTORYDATABASE_H
```
**`.cpp` file:**
```cpp
#include "loginhistorydatabase.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

LoginHistoryDatabase::LoginHistoryDatabase(const QString &initialDataPath, QObject *parent)
    : QObject(parent)
{
    readLoginHistoriesFromJson(initialDataPath);
}

const QVector<LoginHistory>& LoginHistoryDatabase::getLoginHistoriesVector() const
{
    return loginHistoryVector_;
}

void LoginHistoryDatabase::readLoginHistoriesFromJson(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open " + path;
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    loginHistoryVector_ = parseLoginHistories(jsonData);
}

QVector<LoginHistory> LoginHistoryDatabase::parseLoginHistories(const QByteArray &jsonData)
{
    QVector<LoginHistory> histories;

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format";
        return histories;
    }

    QJsonArray loginHistoryArray = doc.array();
    for (const QJsonValue& loginHistoryValue : loginHistoryArray) {
        if (!loginHistoryValue.isObject()) {
            qDebug() << "Invalid loginHistory data";
            continue;
        }

        QJsonObject loginHistoryObject = loginHistoryValue.toObject();
        LoginHistory loginHistory = parseLoginHistory(loginHistoryObject);
        histories.append(loginHistory);
    }

    return histories;
}

LoginHistory LoginHistoryDatabase::parseLoginHistory(const QJsonObject &loginHistoryObject)
{
    QString username = loginHistoryObject["username"].toString();
    QString date = loginHistoryObject["date"].toString();
    QString time = loginHistoryObject["time"].toString();
    bool permitted = loginHistoryObject["permited_"].toBool();

    return LoginHistory(username, date, time, permitted);
}

void LoginHistoryDatabase::handleRequestLoginHistory()
{
    emit loginHistoryResult(loginHistoryVector_);
}

void LoginHistoryDatabase::addLoginHistory(bool isMatch, const QString &date, const QString &time, const QString &rfid)
{
    LoginHistory newHistory(rfid, date, time, isMatch);
    loginHistoryVector_.append(newHistory);
    qDebug() << "New history added: " << newHistory.getUsername() << " " << newHistory.getTime() << " " << newHistory.isPermitted();
}
```

#### `socketserver.cpp` & `socketserver.h`
**`.h` file:**  
```cpp
#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include "loginhistory.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>

#include "authenticator.h"

class SocketServer : public QTcpServer {
    Q_OBJECT

public:
    SocketServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    bool isValidRFID(const QString &rfid);
    void processData(QByteArray &data, QTcpSocket *clientSocket);
    //bool isValidUser(const QString &username, const QString &password);
    QByteArray retrieveHistoryData();
   // void authenticateUser(const QByteArray &data, QTcpSocket *clientSocket);

signals:
    void requestLoginHistory();

public slots:
    void sendNewUserDataToAdmin(bool isMatch, const QString &rfid);
    void SendLoginHistoryResult(const QVector<LoginHistory> &loginHistories);

private:
    QStringList hardcodedRFIDs;
    QTcpSocket* clientSocketpointer; // Store pointer to client socket
    Authenticator authenticator;
};

#endif // SOCKETSERVER_H
```
**`.cpp` file:**
```cpp
#include "socketserver.h"

SocketServer::SocketServer(QObject *parent) : QTcpServer(parent) {
    hardcodedRFIDs << "RFID1" << "RFID2" << "RFID3";
}

void SocketServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (!clientSocket->setSocketDescriptor(socketDescriptor)) {
        qDebug() << "Error setting socket descriptor";
        return;
    }

    qDebug() << "New connection from:" << clientSocket->peerAddress().toString();

    connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {

        QByteArray data = clientSocket->readAll();
        qDebug() << "Received:" << data;
        processData(data, clientSocket);
        clientSocketpointer = clientSocket;

    });

    connect(clientSocket, &QTcpSocket::disconnected, this, [clientSocket]() {
        qDebug() << "Connection closed for:" << clientSocket->peerAddress().toString();
        clientSocket->deleteLater();
    });
}

bool SocketServer::isValidRFID(const QString &rfid) {
    return hardcodedRFIDs.contains(rfid);
}

void SocketServer::processData(QByteArray &data, QTcpSocket *clientSocket) {
    qDebug() << "in  SocketServer::processData";
    if(data == "historyRequest"){
        emit requestLoginHistory();
    }
    else{
        //authenticateUser(data, clientSocket);
        authenticator.authenticateUser(data, clientSocket);
    }
}


void SocketServer::sendNewUserDataToAdmin(bool isMatch, const QString &rfid) {

    QDateTime currentDateTime = QDateTime::currentDateTime();

    QDate currentDate = currentDateTime.date();
    QTime currentTime = currentDateTime.time();

    QString dateString = currentDate.toString("yyyy-MM-dd");
    QString timeString = currentTime.toString("HH:mm:ss");

    QJsonObject messageObj;
    messageObj["type"] = "user";
    messageObj["username"] = rfid;
    messageObj["date"] = dateString;
    messageObj["time"] = timeString;

    QJsonDocument jsonDocument(messageObj);

    QByteArray jsonData = jsonDocument.toJson();

    qint64 bytesWritten = clientSocketpointer->write(jsonData);

    if (bytesWritten == -1) {
        qDebug() << "Failed to write data to socket:" << clientSocketpointer->errorString();
    } else {
        qDebug() << "WebSocket message sent to client:" << jsonData;
    }
}


void SocketServer::SendLoginHistoryResult(const QVector<LoginHistory> &loginHistories){
    if (this->clientSocketpointer) {
        QJsonArray dataArray;

        for (const LoginHistory &entry : loginHistories) {
            QJsonObject obj;
            obj["username"] = entry.getUsername();
            obj["date"] = entry.getDate();
            obj["time"] = entry.getTime();
            obj["permitted"] = entry.isPermitted();
            dataArray.append(obj);
        }
        QJsonObject mainObj;
        mainObj["type"] = "history";
        mainObj["data"] = dataArray;

        // Convert the main JSON object to a JSON document
        QJsonDocument jsonDocument(mainObj);

        // Convert the JSON document to a QByteArray
        QByteArray jsonData = jsonDocument.toJson();
        clientSocketpointer->write(jsonData);
    }
}
```

#### `main.cpp`
The `main` function of the application serves as the entry point, initializing and running the HTTP server that forms the core of the system's network interactions.
```cpp
#include <QCoreApplication>
#include "loginhistorydatabase.h"
#include "socketserver.h"
#include "customizedhttpserver.h"

const QString USERS_FILE_PATH = "../../data/employees.json";
const QString ADMINS_FILE_PATH = "../../data/admins.json";
const QString HISTORY_FILE_PATH = "../../data/history.json";
const int HTTP_SERVER_PORT = 80;
const int WEB_SOCKET_PORT = 5050;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    CustomizedHttpServer customizedHttpServer = CustomizedHttpServer(HTTP_SERVER_PORT, USERS_FILE_PATH);
    qDebug() << "Server running on port " << HTTP_SERVER_PORT;

    SocketServer server;
    if (!server.listen(QHostAddress::LocalHost, WEB_SOCKET_PORT)) {
        qDebug() << "Server could not start!";
        return 1;
    }
    qDebug() << "Server started on port" << server.serverPort();

    LoginHistoryDatabase loginHistoryDatabase(HISTORY_FILE_PATH);

    QObject::connect(&customizedHttpServer, &CustomizedHttpServer::resultRfidCheck, &server, &SocketServer::sendNewUserDataToAdmin);
    QObject::connect(&customizedHttpServer, &CustomizedHttpServer::resultRfidCheckHistory, &loginHistoryDatabase, &LoginHistoryDatabase::addLoginHistory);

    QObject::connect(&server, &SocketServer::requestLoginHistory, &loginHistoryDatabase, &LoginHistoryDatabase::handleRequestLoginHistory);
    QObject::connect(&loginHistoryDatabase, &LoginHistoryDatabase::loginHistoryResult, &server, &SocketServer::SendLoginHistoryResult);

    return a.exec();
}
```



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


Here's a refined description for your GIF that will be added to your README. This description concisely outlines each stage of the demonstration, helping viewers understand the sequence of operations and system interactions.

---

## System Demonstration GIF Description
![System Operation Demonstration](CA1/Pics/screenshot(SimulationInProteus)/Test_speedUp.gif)

This GIF demonstrates the complete operational flow of our IoT-Based Entry and Exit Management System, showcasing both the server and client (GUI) initialization, the simulation in Proteus, and the real-time interactions among the terminal, LEDs, door mechanisms, and LCD display. The scenario unfolds as follows:

1. **System Initialization**:
   - The process starts with the server and client applications being launched. This sets up the environment necessary for handling RFID-based access control.

2. **Proteus Simulation**:
   - The GIF shows a simulation in Proteus where all hardware components are visualized. This includes the RFID sensor, Arduino board, servo motor (door control), LEDs, and LCD display.

3. **Operational Sequence**:
   - **Handshaking**: Initial communication between the Arduino and the server is established, verifying connectivity and readiness.
   - **First Valid RFID Entry**: An authorized RFID tag is presented. The green LED lights up, indicating access granted. The RFID tag is displayed on the LCD, and the servo motor opens the door for 30 seconds.
   - **Door Closure**: After the time elapses, the door automatically closes.
   - **Unauthorized RFID Entry**: An unauthorized RFID tag is scanned. The system reacts by displaying "Access Denied" on the LCD. The door remains closed, and the red LED stays illuminated, signaling denied access.
   - **Sequential RFID Authentication**:
     - **Valid RFID**: The door reopens following another valid RFID detection.
     - **Invalid RFID**: Following the valid entry, an invalid RFID is presented again, resulting in the door closing and maintaining the "Access Denied" status.

4. **History Monitoring**:
   - Throughout the process, each RFID interaction is logged and displayed on the client's GUI in real time, allowing for monitoring and review of access events.

This comprehensive demonstration ensures that all system components are functioning correctly and interacting as designed, providing a visual verification of the system’s operational effectiveness.

**Note**: The GIF has been speeded up for a concise demonstration. For a real-time view of the system in action, please visit [this link](https://github.com/AliAtaollahi/CPS_IOT_HW/blob/main/CA1/Pics/screenshot(SimulationInProteus)/Test.mp4).
