# AntennaTest
2 simple programs written for the Arduino GUI.
For compiling you need to install esp32 by Expressiff Systems. 
For the WeMos you need to add this line "package_esp8266com_index.json" under preferences in the 'Additional Boards Manager URL's'.

There is a receiver program for a WeMos module: AntennaTestRec_wemos
There is a receiver program for a ESP32 module. tested on Tbeam and Heltec v1

The sender program can be used with a Tbeam:


These programs are based on the programs publishes by SensorsIot found here:
https://github.com/SensorsIot/Antenna-Tester
The programs are simplified  by removing the GPS parts, which are not needed for comparing antenna's
