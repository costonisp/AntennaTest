/* Antenna-tester for LoRa Heltec V2
BoardManager 2.0.16    Board T-beam
I2C: SSD1306/SSD1309  display(0x3c, 4, 15); (ADRESS,SDA,SCL)
*/
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"'
#include <LoRa.h>    // by Sandeep Mistry ver. 0.8.0
#include <ArduinoJson.h> // ver. 5.13

// WIFI_LoRa_32 ports
// GPIO5  -- SX1278's SCK
// GPIO19 -- SX1278's MISO
// GPIO27 -- SX1278's MOSI
// GPIO18 -- SX1278's CS
// GPIO14 -- SX1278's RESET
// GPIO26 -- SX1278's IRQ(Interrupt Request)

// GPIO16 OLED RESET


#define SS      18
#define RST     14
#define DI0     26

// freq, SF, BW are hardcoded in the setup
#define FREQUENCY 868900000
#define spreadingFactor 9
#define SignalBandwidth 125E3
#define preambleLength 8
#define codingRateDenominator 8

#define TIMEOUT 2000
#define DELAY_MS 400
#define STARTPIN 0

float testmax = 50.0;  // number of pings to average.
int rssi;
int performance;
float average;
char var;

SSD1306  display(0x3c, 4, 15); // TTGo V1 , heltec v2


void initDisplay12() {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
}

void initDisplay24() {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
  display.setColor(WHITE);
}

bool sendMessage() {
  bool success = false;
  char json[500];
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& sendMessage = jsonBuffer.createObject();
  sendMessage["freq"] = FREQUENCY;
  sendMessage["sf"] = spreadingFactor;
  sendMessage["RSSI"] = "";

  // Send Packet
  String sMessage;
  Serial.println("Send");
  sendMessage.printTo(sMessage);
  //LoRa.setTxPower(power);
  LoRa.beginPacket();
  LoRa.print(sMessage);
  LoRa.endPacket();

  // Receive Message
  unsigned long entry = millis();
  Serial.println("wait for receive");
  while (LoRa.parsePacket() == 0 && (millis() < entry + TIMEOUT));
  Serial.println("receive");
  if (millis() < entry + TIMEOUT - 1) {
    // received a packet
    json[0] = '\0';
    while (LoRa.available()) {
      byte hi = strlen(json);
      json[hi] = (char)LoRa.read();
      json[hi + 1] = '\0';
    }
    JsonObject & recMessage = jsonBuffer.parse(json);
    if (recMessage.success()) {
      rssi = recMessage["RSSI"];
      Serial.print(" RSSI: ");
      Serial.print(rssi);
      Serial.print(" Performance: ");
      performance = (rssi);
      Serial.println(performance);

      success = true;
    } else  Serial.println("parseObject() failed");
  } else Serial.println("Timeout");
  return success;
}

void initLoRa() {

  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(FREQUENCY)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.print("FREQUENCY ");
  Serial.println(FREQUENCY);
  //LoRa.setTxPower(1);
  Serial.print("LoRa Spreading Factor: ");
  Serial.println(spreadingFactor);
  LoRa.setSpreadingFactor(spreadingFactor);
  Serial.print("LoRa Signal Bandwidth: ");
  Serial.println(SignalBandwidth);
  LoRa.setSignalBandwidth(SignalBandwidth);
  Serial.println("LoRa Initial OK!");
}

void setup()
{
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);           // OLED reset
  pinMode(STARTPIN, INPUT_PULLUP);
  
  initDisplay12();
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Freq = ");
  display.drawString(54, 0, "868.9MHz");  //"868.9MHz"
  display.drawString(0, 16, "SF = ");
  display.drawString(54, 16, "9");
  display.drawString(0, 32, "BW = ");
  display.drawString(54, 32, "125kHz");
  display.drawString(0, 49, "Press StartButton");
  display.display();
  while (digitalRead(STARTPIN) > 0) { // Wait for start
  }
  delay(500);

  /*
  initDisplay24();
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 0, "Press");
  display.drawString(64, 35, "Button");
  display.display();
  */
 
  initLoRa();
}

void loop()
{
  Serial.println("Press button");
  while (digitalRead(STARTPIN) > 0) { // Wait for start
  }
  Serial.println("waiting");
  display.clear();
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 15, "Waiting");
  display.display();
  delay(4000);

  Serial.println("Start ");
  float sum = 0;
  for (int i = 0; i < testmax; i++) {
    while (!sendMessage()) {
      Serial.println("Failure");
      delay(DELAY_MS);
    }
    sum = sum + performance;
    display.clear();
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "RSSI: " + String(rssi));
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_24);
    display.drawString(60, 35, String(i+1));//: " + String(performance));
    display.display();
    delay(DELAY_MS);
  }

  average = (sum / testmax);
  Serial.print("Average RSSI ");
  Serial.println(average);

  char line3[15];
  dtostrf(average, 7, 2, line3);
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "AVG" );
  display.drawString(50, 0, line3);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 35, "Button");
  display.display();
}
