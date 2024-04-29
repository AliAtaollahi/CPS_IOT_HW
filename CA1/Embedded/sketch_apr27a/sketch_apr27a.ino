#include <Servo.h>
#include <EtherCard.h>

#define GREEN_LED 2
#define RED_LED 3
#define RX_PIN 0
#define TX_PIN 1
#define SERVO_PIN 4

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

byte Ethernet::buffer[700];   // a very small tcp/ip buffer is enough here


String inputString = "";
boolean doorOpen = false;
unsigned long doorOpenTime = 0;

static void my_result_cb(byte status, word off, word len)
{
  Serial.println("Server received the message.");
}

// Function to check the sequence
boolean checkSequence(String sequence) {
  String expectedSequence = "1111111111";
  return (sequence == expectedSequence);
}

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
    if (millis() - doorOpenTime >= 5000) {
      doorOpen = false;
      doorServo.write(0);
      digitalWrite(GREEN_LED, LOW);
      inputString = "";
    }
  }

    // If the receivedString has reached 10 characters
    if (inputString.length() == 10) {

      ether.browseUrl(PSTR("/rfid?massage=hello"), "", website, my_result_cb);
      boolean sequenceResult = checkSequence(inputString);

      Serial.print("\nInput Length: ");
      Serial.println(inputString.length());
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
