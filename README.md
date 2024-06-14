# AntennaTest
2 simple programs written for the Arduino GUI.
For compiling you need to install esp32 by Expressiff Systems with the Board Manager.
For the WeMos you need to add this line "package_esp8266com_index.json" under preferences in the 'Additional Boards Manager URL's'.

AntennaTestRec_wemos is a receiver program for a WeMos module. 

AntennaTestRec_ESP32 is a receiver program for a ESP32 module. It is tested on Tbeam and Heltec v1

The sender program can be used with a Tbeam:


These programs are based on the programs publishes by SensorsIot found here:
https://github.com/SensorsIot/Antenna-Tester
The programs are simplified  by removing the GPS parts, which are not needed for comparing antenna's
