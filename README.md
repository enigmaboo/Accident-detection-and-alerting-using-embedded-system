# Accident detection and alerting using embedded system

The goal of this project is to rescue the vehicle accident victim on time.
It can detect accidents and send message alerts to saved phone numbers and rescue team.

## Libraries used

  - SoftwareSerial.h
  - SPI.h
  - sD.h>
  - TinyGPS++.h
  - Adafruit_GFX.h
  - Adafruit_PCD8544.h
  - Fonts/FreeSans9pt7b.h
  - NewPing.h

## Components used

  - ARDUINO 
  - GSM Module 
  - GPS Module 
  - Vibration Sensor Module 
  - LCD Module
  - Bluetooth module
  - Ultrasonic sensor
  - Memory card module
  - Buzzer
  - Push button
  
## Circuit diagram

![Circuit](https://github.com/enigmaboo/Accident-detection-and-alerting-using-embedded-system/circuit/CIRCUIT.png?raw=true)
  
## Working

•	When vehicle starts, the system also turns on.
•	Whenever an accident happens, the vehicle will experience a huge impact.
•	This impact is the key point of detection of accident.
•	We are using a Vibration sensor to know the level of impact.
•	We are using an Ultrasonic sensor to detect the obstacles.
•	Bluetooth module and Memory card module is used to store mobiles numbers.
•	GPS module is used to getting signals from the satellites (already existing GPS technology) in the form of longitudes and latitudes, to know where accident happened.
•	GSM module is used for sending text message to specified mobile numbers (telecommunication technology).
•	The micro controller (in our case ARDUINO) already getting data from GPS module (from the time of starting of vehicle).
•	If the impact is high, then the Vibration sensor will send a signal to the micro controller.
•	That signal will activate the program in the micro controller.
•	The program is like: when vibration sensor gives signal, then measure the distances of obstacles from the vehicle using ultrasonic sensor. If accident happens then the distance will be very low. If the distance is low, take the data coming from GPS module and process it (change longitude latitude format into Google map link), then give the Google map link in addition with some other message (like “Help me”) to the GSM module.
•	Then GSM module will send the message to the mobile number specified.
•	For added safety the gsm module will make miss call alerts to given numbers


There is also a smartphone application to add or change the phone numbers. The smartphone connects to the device via Bluetooth. 


Exceptional cases like minor accidents, pits in roads, or others can also causes impact in vehicle. That impact may trigger the sensor. Then the system will send message. To avoid this, we add a Button, a Buzzer and Display to the system.

o	The purpose of the display is to show longitude and latitude values (or date and time). 
o	When impact is experienced then it will show “ARE YOU SAFE” and beeps for 30 seconds.
o	If user is safe then the user can press the button within 30 second. It will stop the message.
o	If user is not safe then the system will send message.
