/* 
  Receiver with ESP32
  ESP8266 community version 2.6 & 3.0.0 & 3.1.2  OK
  board ESP32
  Receiver tested on:
  Tbeam v1.0
  Tbeam v1.1
  Heltec v1.0
 */
#include <ArduinoJson.h>
#include <LoRa.h>

#define SS     18 // D0
#define RST    14 // D0
#define DI0    26 // D8

#define spreadingFactor 9
#define SignalBandwidth 125E3
#define preambleLength 8
#define codingRateDenominator 8

#define FREQUENCY 868.9E6


double retFrequency;
int retSF;

void receivingMessage () {
  unsigned long eentry = millis();
  StaticJsonBuffer<500> jsonBuffer;
  char json[500];
  //Serial.println("HIGH");
  //digitalWrite(LEDPIN, LOW);

  // Receive Message

    Serial.println("Start receiving ");
    Serial.println(millis());
  while (LoRa.parsePacket() == 0) yield();
  // received a packet
   Serial.println("Received packet");

  // read packet
  json[0] = '\0';
  while (LoRa.available()) {
    byte hi = strlen(json);
    json[hi] = (char)LoRa.read();
    json[hi + 1] = '\0';
  }
    //Serial.println(json);
  JsonObject& recMessage = jsonBuffer.parse(json);

  if (recMessage.success()) {
    Serial.println("Received succes");
    recMessage["RSSI"] = LoRa.packetRssi();


        Serial.println("-------");
        Serial.print("Received  Data / Start sending ");
        Serial.println(millis());
    recMessage.printTo(Serial);
        Serial.println();
    //Serial.println("LOW");
    //digitalWrite(LEDPIN, HIGH);
    delay(200);

    // Send packet back
    String sendMessage;
    recMessage.printTo(sendMessage);
    LoRa.setTxPower(17);
    LoRa.beginPacket();
    LoRa.print(sendMessage);
    LoRa.endPacket();
    Serial.println("Package sent");
  } else Serial.println("parseObject() failed");
  Serial.println(millis() - eentry);
}

void initLoRa() {
  //SPI.begin();
  //LoRa.setPins(D0, D0, D8);
  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(FREQUENCY)) {
    Serial.println("Starting LoRa failed!");
    while (1) {
      //digitalWrite(LEDPIN, 1);
      //delay(200);
      //digitalWrite(LEDPIN, 0);
      //delay(200);
    }
  }
  Serial.print("FREQUENCY ");
  Serial.println(FREQUENCY);
  LoRa.setTxPower(1);
  Serial.print("LoRa Spreading Factor: ");
  Serial.println(spreadingFactor);
  LoRa.setSpreadingFactor(spreadingFactor);
  Serial.print("LoRa Signal Bandwidth: ");
  Serial.println(SignalBandwidth);
  LoRa.setSignalBandwidth(SignalBandwidth);
  Serial.println("LoRa Initial OK!");
}

void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT);    // LEDPIN
  digitalWrite(16, HIGH); // LEDPIN
  //delay(1000);
  //digitalWrite(LEDPIN, 0);
  initLoRa();
}

void loop() {
  receivingMessage();
  yield();
}
