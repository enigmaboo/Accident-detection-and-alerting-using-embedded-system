# Accident detection and alerting using embedded system

The goal of this project is to rescue the vehicle accident victims on time.
It can detect accidents and send message alerts to saved phone numbers and rescue team.

## Libraries used

  - SoftwareSerial.h
  - SPI.h
  - SD.h>
  - TinyGPS++.h
  - Adafruit_GFX.h
  - Adafruit_PCD8544.h
  - Fonts/FreeSans9pt7b.h
  - NewPing.h

## Components used

  - ARDUINO MEGA
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

![Circuit](https://github.com/enigmaboo/Accident-detection-and-alerting-using-embedded-system/blob/main/circuit/CIRCUIT.png?raw=true)
  
## Working

*	When vehicle starts, the system also turns on.
*	Whenever an accident happens, the vehicle will experience a huge impact.
*	This impact is the key point of detection of accident.
    *	We are using a Vibration sensor to know the level of impact.
    *	We are using an Ultrasonic sensor to detect the obstacles.
    *	Bluetooth module and Memory card module is used to store mobiles numbers.
    *	GPS module is used to getting signals from the satellites (already existing GPS technology) in the form of longitudes and latitudes, to know where accident happened.
    *	GSM module is used for sending text message to specified mobile numbers (telecommunication technology).
*	The micro controller (in our case ARDUINO) already getting data from GPS module (from the time of starting of vehicle).
*	If the impact is high, then the Vibration sensor will send a signal to the micro controller.
*	That signal will activate the program in the micro controller.
*	The program is like: when vibration sensor gives signal, then measure the distances of obstacles from the vehicle using ultrasonic sensor. If accident happens then there will be some obstacles in atleast any one side (front, back,sides and top). If the distance is less than a limit, take the data coming from GPS module and process it (change longitude latitude format into Google map link), then give the Google map link in addition with some other message (like “Help me”) to the GSM module.
*	Then GSM module will send the message to the mobile number specified.
*	For added safety the gsm module will make miss call alerts to given numbers


[__Note__: There is also a smartphone application to add or change the phone numbers. The smartphone connects to the device via Bluetooth. ]

#

Exceptional cases like minor accidents, pits in roads, or others can also causes impact in vehicle. That impact may trigger the sensor. Then the system will send message. To avoid this, we add a Button, a Buzzer and Display to the system.

*	The purpose of the display is to show longitude and latitude values (or date and time). 
*	When impact is experienced then it will show “ARE YOU SAFE” and beeps for 30 seconds.
*	If user is safe then the user can press the button within 30 second. It will stop the message.
*	If user is not safe then the system will send message.

## Configuration

* The sensors must be placed in such a way that, it can sense and give accurate values
* To getting best & accurate readings: 
    * It requires a total of 5 ultrasonic sensors & 6 vibration sensors
     (for small vehicles like cars; number of sensors may vary for other vehicles)
        * Four ultrasonic sensors are installed at front, back, both sides and on top of the vehicle
        * Four vibration sensors are installed inside the doors and one sensor is installed inside the dashboard. Last one is installed on the back of the vehicle
* Initially the system has no phone numbers 
    * There is a smartphone application to setup the phone numbers
    * It helps to add, remove & update the numbers
    * Also helps to view saved numbers
    
## Gallery

#### Prototype

![Prototype](https://github.com/enigmaboo/Accident-detection-and-alerting-using-embedded-system/blob/main/images/001.jpg)

#### App UI

![App UI](https://github.com/enigmaboo/Accident-detection-and-alerting-using-embedded-system/blob/main/images/app_interface.jpg)

#### Alert sample

![Alert sample](https://github.com/enigmaboo/Accident-detection-and-alerting-using-embedded-system/blob/main/images/location_msg.png)

## Authors

1. [Karthik Parameswaran](https://github.com/enigmaboo/)
2. [Aravind V V](https://github.com/arvndvv)
