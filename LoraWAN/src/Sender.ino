#include <SPI.h>
#include <LoRa.h>
#include "string.h"

#define ss 5
#define rst 34
#define timeoff 1000

int counter = 0;

void initLora();//Initiaizing SPI and Lora chip
void sendPacket(String message);//Sending packet, requires initLora() to work!!

void setup() {
  Serial.begin(9600);
  pinMode(27,OUTPUT);
  digitalWrite(27,HIGH);
  pinMode(32,OUTPUT);
  digitalWrite(32,HIGH);
  initLora();
}

void loop() {
  sendPacket("Hello World");
}

void initLora(){
    SPI.begin(18,19,23);
 LoRa.setSPI(SPI);
 LoRa.setPins(ss, rst, 7);
 LoRa.setSPIFrequency(1e6);

  Serial.println("LoRa Receiver");

    while (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa");
     LoRa.begin(868E6); 
    delay(timeoff);
  }
  }

  void sendPacket(String message){
      // wait until the radio is ready to send a packet
  Serial.print("Sending packet non-blocking: ");
  Serial.println(counter);

  // send in async / non-blocking mode
  LoRa.beginPacket();
  digitalWrite(32,LOW);
  LoRa.print(message);
  LoRa.endPacket(true); // true = async / non-blocking mode
  delay(timeoff);
  digitalWrite(32,HIGH);
  delay(timeoff);
  }