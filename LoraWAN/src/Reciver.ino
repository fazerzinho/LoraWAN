#include <SPI.h>
#include <LoRa.h>

#define ss 5
#define rst 34
#define timeoff 1000

void getPacket();//Printing information about packet: message recived and rssi

void initLora();//Initiaizing SPI and Lora chip

void setup() {
    Serial.begin(9600);
  pinMode(27,OUTPUT);
  digitalWrite(27,HIGH);
  pinMode(32,OUTPUT);
  digitalWrite(32,HIGH);
  initLora();
}

void loop() {
  // try to parse packet
  getPacket();
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

void getPacket(){
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");
    digitalWrite(32,LOW);
    delay(timeoff);
     digitalWrite(32,HIGH);
    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
  }