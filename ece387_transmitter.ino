/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#define BUTTON_UP 2
#define BUTTON_RIGHT 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define BUTTON_1 6
#define BUTTON_2 7
#define BUTTON_XY 8
#define PIN_ANALOG_X A0
#define PIN_ANALOG_Y A1

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  byte a = 0;
  byte b = 0;
  byte c = 0;
  byte d = 0;
  int e = 0;
  int f = 0;
};

Data_Package data; // Create a variable with the above structure

// variables will change:
int upState = 0;
int rightState = 0;
int downState = 0;
int leftState = 0;
int oneState = 0;
int twoState = 0;
int xyState = 0;
int xPosition = 0;
int yPosition = 0; 

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_UP, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  upState = digitalRead(BUTTON_UP);
  rightState = digitalRead(BUTTON_RIGHT);
  downState = digitalRead(BUTTON_DOWN);
  leftState = digitalRead(BUTTON_LEFT);
  oneState = digitalRead(BUTTON_1);
  twoState = digitalRead(BUTTON_2);
  xyState = digitalRead(BUTTON_XY);
  xPosition = analogRead(PIN_ANALOG_X);
  yPosition = analogRead(PIN_ANALOG_Y);

  if (upState == HIGH) {
    // turn LED on:
    data.a = 0;
  } else {
    // turn LED off:+
    data.a = 1;
  }
  if (rightState == HIGH) {
    // turn LED on:
    data.b = 0;
  } else {
    // turn LED off:+
    data.b = 1;
  }
  if (downState == HIGH) {
    // turn LED on:
    data.c = 0;
  } else {
    // turn LED off:+
    data.c = 1;
  }
  if (leftState == HIGH) {
    // turn LED on:
    data.d = 0;
  } else {
    // turn LED off:+
    data.d = 1;
  }
  data.e = xPosition;
  data.f = yPosition;
  
  // const char text[] = "Hello World";
  radio.write(&data, sizeof(Data_Package));
  delay(100);
}
