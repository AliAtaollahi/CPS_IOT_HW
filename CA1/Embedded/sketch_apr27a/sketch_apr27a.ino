#include <Servo.h>
#include <EtherCard.h>
#include <LiquidCrystal.h>

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



void getStatus(char* reply, char* status) { 
  memcpy(status, &reply[13], 2);
  status[2] = '\0';
}

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
    delay(200);

  }

  return false; // no access
}


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
    if (millis() - doorOpenTime >= 30000) {
      doorOpen = false;
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
