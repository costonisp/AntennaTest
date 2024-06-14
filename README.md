Simple program for comparing the gain of Antenna's


Testing a unknown antenna compared to a reference antenna on one single frequency.
First test the reference antenna, usually a GP or j-beam, which has a gain very close to 2.15dBi
Make a note on the RSSI of your reference antenna.
Now connect the antenna you want to measure to the sender and make a note om the RSSI.
RSSI is usually a negative dBm number. The difference is the gain compared to your reference antenna. 
For a stubby antenna this gain will likely be negative, worse than your reference antenna.


Programs are written for the Arduino GUI.
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
