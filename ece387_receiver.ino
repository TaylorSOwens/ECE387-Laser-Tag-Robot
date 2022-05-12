#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <IRremote.h>

IRsend sender;

RF24 radio(7, 8); // CE, CSN

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

Data_Package data; //Create a variable with the above structure


int enA = 3;
int in1 = 4;
int in2 = 9;

int enB = 10;
int in3 = 5;
int in4 = 6;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // Check whether there is data to be received
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
  }
  Serial.print("a: ");
  Serial.print(data.a);
  Serial.print(" b: ");
  Serial.print(data.b);
  Serial.print(" c: ");
  Serial.print(data.c);
  Serial.print(" d: ");
  Serial.print(data.d);
  Serial.print(" e: ");
  Serial.print(data.e);
  Serial.print(" f: ");
  Serial.println(data.f);

  if (data.f > 600 && data.e < 600 && data.e > 400) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
   
    // Set speed to 200 out of possible range 0~255
   
    analogWrite(enA, 200);
   
    // Turn on motor B
   
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
   
    // Set speed to 200 out of possible range 0~255
   
    analogWrite(enB, 200);
  } else if (data.f < 400 && data.e < 600 && data.e > 400) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
   
    // Set speed to 200 out of possible range 0~255
   
    analogWrite(enA, 200);
   
    // Turn on motor B
   
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
   
    // Set speed to 200 out of possible range 0~255
   
    analogWrite(enB, 200);
  } else if (data.e < 600 && data.e < 400) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
   
    // Set speed to 200 out of possible range 0~255
   
    analogWrite(enA, 200);
   
    // Turn on motor B
   
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
   
    // Set speed to 200 out of possible range 0~255
   
    analogWrite(enB, 200);
  } else if (data.e > 600 && data.e > 400) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
   
    // Set speed to 200 out of possible range 0~255
   
    analogWrite(enA, 200);
   
    // Turn on motor B
   
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
   
    // Set speed to 200 out of possible range 0~255
   
    analogWrite(enB, 200);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
   
    // Set speed to 200 out of possible range 0~255
   
    analogWrite(enA, 200);
   
    // Turn on motor B
   
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
   
    // Set speed to 200 out of possible range 0~255
   
    analogWrite(enB, 0);
  }

  if (data.a == 1) {
    uint32_t data = 0xFF609F;
    uint8_t len = 32;
    sender.sendNEC(data, len);
  }
}
