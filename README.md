2 simple programs written for the Arduino GUI.
For compiling you need to install esp32 by Expressiff Systems with the Board Manager.
For the Wemos you need to add this line "package_esp8266com_index.json" under preferences in the 'Additional Boards Manager URL's'.
At the moment the programs are tested with older library versions, you may need to downgrade them.

ArduinoJson library version 5.13, 

LoRa library by Sandeep Mistry version 0.8.0

AntennaTestRec_wemos is a receiver program for a Wemos module. 

AntennaTestRec_ESP32 is a receiver program for a ESP32 module. It is tested on Tbeam and Heltec v2

AntennaTestSender_tbeam is the sender program and is tested on T-beam:

These programs are based on the programs publishes by SensorsIot found here:
https://github.com/SensorsIot/Antenna-Tester
The programs are simplified  by removing the GPS parts, which are not needed for comparing antenna's
