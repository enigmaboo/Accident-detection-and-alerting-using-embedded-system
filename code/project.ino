/*//////////////////////////////////////////////////////////////////////////////////
  SD card module:
    CS   -> pin 53 
    SCK  -> pin 52
    MOSI -> pin 51
    MISO -> pin 50
-----------------------------------
  LCD module:
    RST  -> pin 3
    CS   -> pin 4
    D/C  -> pin 5
    DIN  -> pin 6
    CLK  -> pin 7
-----------------------------------
  Bluetooth module:
    RXD  -> pin 1
    TXD  -> pim 0
-----------------------------------
  GPS & GPRS modules:
    RXD  -> pin 11
    TX   -> pin 10
-----------------------------------
  Vibration sensor module:
    D0   -> pin 9
-----------------------------------
  Ultrasonic sensor module (1):
    trig -> pin 30
    echo -> pin 31
  Ultrasonic sensor module (2):
    trig -> pin 32
    echo -> pin 33
-----------------------------------
  Buzzer:
    OUT  -> pin28
-----------------------------------
  Button:
    IN   -> pin 29 
*///////////////////////////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Fonts/FreeSans9pt7b.h>
#include <NewPing.h>
#define VIBRATION_SENSOR_PIN 9
#define SONAR_NUM 2      //Number of sensors.
#define MAX_DISTANCE 500 //Maximum distance (in cm) to ping.
SoftwareSerial gpgs(10 , 11);
File a,b,c;
int sdcheck=0,sdread=0,found=0;
TinyGPSPlus gps;
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
int motion_detected = LOW;
int start=0,rst=0;
int btconnect,option,add=1;;
int detect=0,msgsend=0,msgdone=0,msg1=0,msg2=0,msg3=0;
String Data= "",num1 = "",num2 = "",num3 = "";
String lati="",longi=""; 
char character;
int sense=0;
NewPing sonar[SONAR_NUM] = {//Sensor object array.
  NewPing(30, 31, MAX_DISTANCE),//trigger pin, echo pin, and max distance to ping. 
  NewPing(32, 33, MAX_DISTANCE), 
};
int dist1=0,dist2=0,dect=0,md=0;
int swap=0;
////////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(28, OUTPUT);// buzzer
  pinMode(29, INPUT_PULLUP);//i am safe button
  Serial.begin(9600);
  gpgs.begin(9600);
  display.begin();
  display.setContrast(50);
  display.clearDisplay();
}
////////////////////////////////////////////////////////////////////////////////////
void loop() {
  if(sdcheck==0){
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.clearDisplay();
    if (!SD.begin(53)) {
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("sd failed!");
      display.display();
      delay(1000);
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("Insert sd ");
      display.display();
      delay(1000);
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("Restart..");
      display.display();
      while(1);
    }
    sdcheck=1;
  }
  if(start==0){
    display.setCursor(20,25);
    display.println("resQ");
    display.display();
    delay(3000);
  }
////////////////////////////////////////////////////////////////////////////////////
  if(add==0){
    while(Serial.available()){
      btconnect=int(Serial.read()); 
      if(btconnect==48){
        Serial.print("1");
      }
      Data ="";
      }
  }
  while(btconnect==48){           //0
    display.clearDisplay();
    display.setCursor(0,20);
    display.println("Seting up...");
    display.display();
    while(Serial.available()){
      option=int(Serial.read());
      if(option== 49){
        Serial.print("3");
      }
      if(option== 50){
        Serial.print("4");
      }
      if(option== 51){
        Serial.print("5");
      }
    }
    while(option== 49){            //1
      display.clearDisplay();
      display.setCursor(0,18);
      display.println("N1:"+num1);
      display.display();
      while(Serial.available()){
        character = Serial.read();
        Data.concat(character);
      }
      if(int(Data[0])==53){
        display.clearDisplay();
        display.setCursor(0,20);
        display.println("Skipped!!!");
        display.display();
        Serial.print("9");
        delay(1000);
        option=0;
        Data ="";
      }
      if(int(Data[1])!=57){
        Data ="";
      }
      if(Data!=""){
        SD.remove("1.txt");
        a = SD.open("1.txt", FILE_WRITE); 
        if (a) {
          display.clearDisplay();
          display.setCursor(0,20);
          display.println("Saving no 1...");
          display.display();
          a.print(Data);
          a.close();
          delay(1000);
          display.clearDisplay();
          display.setCursor(0,20);
          display.println("Done.");
          Serial.print("6");
          display.display();
          delay(1000);
///////////////////////////////////////
          num1 = "";
          if (SD.exists("1.txt")) {
            a = SD.open("1.txt");
            if (a) {
              while (a.available()) {
                character =a.read(); 
                num1.concat(character); 
              }
            a.close();
            }
          }
///////////////////////////////////////        
          option= 0;
          sdread=0;
          } 
        else {
          display.clearDisplay();
          display.setCursor(0,20);
          display.println("error 1");
          display.display(); 
          delay(1000);
          option=0;
        }
        Data ="";
      }
    }
    while(option== 50){          //2
      display.clearDisplay();
      display.setCursor(0,18);
      display.println("N2:"+num2);
      display.display();
      while(Serial.available()){
        character = Serial.read();
        Data.concat(character); 
      }
      if(int(Data[0])==53){
        display.clearDisplay();
        display.setCursor(0,20);
        display.println("Skipped!!!");
        display.display();
        Serial.print("9");
        delay(1000);
        option=0;
        Data ="";
      }
      if(int(Data[1])!=57){
        Data ="";
      }
      if(Data!="" ){
        SD.remove("2.txt");
        b = SD.open("2.txt", FILE_WRITE); 
        if (b) {
          display.clearDisplay();
          display.setCursor(0,20);
          display.println("Saving no 2...");
          display.display();
          b.print(Data);
          b.close();
          delay(1000);
          display.clearDisplay();
          display.setCursor(0,20);
          display.println("Done.");
          Serial.print("7");
          display.display();
          delay(1000);
///////////////////////////////////////
          num2 = "";
          if (SD.exists("2.txt")) {
            b = SD.open("2.txt");
            if (b) {
              while (b.available()) {
                character =b.read(); 
                num2.concat(character); 
              }
            b.close();
            }
          }
///////////////////////////////////////
          option=0;
          sdread=0;
        } 
        else {
          display.clearDisplay();
          display.setCursor(0,20);
          display.println("error 2");
          display.display(); 
          delay(1000);
          option= 0;
        }
        Data ="";
      }
    }
    while(option== 51){            //3
      display.clearDisplay();
      display.setCursor(0,18);
      display.println("N3:"+num3);
      display.display();
      while(Serial.available()){
        character = Serial.read(); 
        Data.concat(character); 
      }
      if(int(Data[0])==53){
        display.clearDisplay();
        display.setCursor(0,20);
        display.println("Skipped!!!");
        display.display();
        Serial.print("9");
        delay(1000);
        option=0;
        Data ="";
      }
      if(int(Data[1])!=57){
        Data ="";
      }
      if(Data!="" ){
        SD.remove("3.txt");
        c = SD.open("3.txt", FILE_WRITE); 
        if (c) {
          display.clearDisplay();
          display.setCursor(0,20);
          display.println("Saving no 3...");
          display.display();
          c.print(Data);
          c.close();
          delay(1000);
          display.clearDisplay();
          display.setCursor(0,20);
          display.println("Done.");
          Serial.print("8");
          display.display();
          delay(1000);
///////////////////////////////////////
          num3 = "";
          if (SD.exists("3.txt")) {
            c = SD.open("3.txt");
            if (c) {
              while (c.available()) {
                character =c.read(); 
                num3.concat(character); 
              }
            c.close();
            }
          }
///////////////////////////////////////
          option=0;
          sdread=0;
        } 
        else {
          display.clearDisplay();
          display.setCursor(0,20);
          display.println("error 3");
          display.display(); 
          delay(1000);
          option= 0;
        }
        Data ="";
      }
    }
    if(option== 52){              //4
      btconnect=0;
      option=0;
      Serial.print("2");
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("Finishing up...");
      display.display();
      delay(1000);
    }
    sdread=0;
  } 
////////////////////////////////////////////////////////////////////////////////////
  if(sdread==0){
    display.clearDisplay();
    display.setCursor(0,18);
    display.println("Reading  numbers.");
    display.display();
    delay(500);
    num1 = "";
    num2 = "";
    num3 = "";
    if (SD.exists("1.txt")) {
      msg1=1;
      a = SD.open("1.txt");
      if (a) {
        while (a.available()) {
          character =a.read(); 
          num1.concat(character); 
        }
        found=0;
        a.close();
      }
      else {
        display.clearDisplay();
        display.setCursor(0,20);
        display.println("error read 1");
        display.display();
        delay(1000);
      }
    }
    else{
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("no. 1 not   found");
      display.display();
      delay(1000);
      found++;
    }
    if (SD.exists("2.txt")) {
      msg2=1;
      b = SD.open("2.txt");
      if (b) {
        while (b.available()) {
          character =b.read(); 
          num2.concat(character);
        }
        found=0;
        b.close();
      }
      else {
        display.clearDisplay();
        display.setCursor(0,20);
        display.println("error read 2");
        display.display();
        delay(1000);
      }
    }
    else{
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("no. 2 not  found");
      display.display();
      delay(1000);
      found++;
    }
    if (SD.exists("3.txt")) {
      msg3=1;
      c = SD.open("3.txt");
      if (c) {
        while (c.available()) {
          character =c.read();
          num3.concat(character);
        }
        found=0;
        c.close();
      }
      else {
        display.clearDisplay();
        display.setCursor(0,20);
        display.println("error read 3");
        display.display();
        delay(1000);
      }
    }
    else{
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("no. 3 not  found");
      display.display();
      delay(1000);
      found++;
    }
    if(found>=3){
      sdread=0;
      sense=1;
      add=0;
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("Give numbers");
      display.display();
      delay(1000);
    }
    else{
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("Done.");
      delay(1000);
      add=0;
      sdread=1;
      sense=0;
    }
  }
////////////////////////////////////////////////////////////////////////////////////
  if(start==0 || rst==1){
    lati="8.5573";
    longi="77.0998";
    display.clearDisplay();
    display.setCursor(0,20);
    display.println("Lat:"+lati);
    display.setCursor(0,40);
    display.print("Lon:"+longi);
    display.display(); 
    start=1;
    rst=0;
  }
  while(gpgs.available() > 0){
    gps.encode(gpgs.read());
      if (gps.location.isUpdated()){
        lati=gps.location.lat();
        longi=gps.location.lng();
        display.clearDisplay();
        display.setCursor(0,20);
        display.println("Lat:"+lati);
        display.setCursor(0,40);
        display.print("Lon:"+longi);
        display.display();
     }
  }  
////////////////////////////////////////////////////////////////////////////////////
  if(sense==0){
    if(msgdone==0){
      motion_detected = digitalRead(VIBRATION_SENSOR_PIN);
      if(motion_detected==HIGH){
        md=1;
      }
      if(md==1){
        for(dect=0;dect<10;dect++){
          if(int(sonar[0].ping_cm())>=1 ){
            if(int(sonar[0].ping_cm())<=6 ){
              delay(90);
              if(int(sonar[0].ping_cm())<=6 ){
                dist1=1;
                md=0;
                dect=10;
              }
            }
          }
          if(int(sonar[1].ping_cm())>=1 ){
            if(int(sonar[1].ping_cm())<=4 ){
              delay(90);
              if(int(sonar[1].ping_cm())<=4 ){
                dist2=1;
                md=0;
                dect=10;
              }
            }
          }
        }
        delay(10);
      }
      if(dist1==0 && dist2==0){
        md=0;
      }
      if(dist1==1 || dist2==1){
        for(detect=0;detect<60;detect++){
          digitalWrite(28,HIGH);
          display.clearDisplay();
          display.setCursor(0,25);
          display.println("ALERT!!!");
          display.display();
          delay(250);
          digitalWrite(28,LOW);
          display.clearDisplay();
          display.setCursor(0,13);
          display.println("ARE YOU SAFE!!");
          display.display();
          delay(250);
          if(digitalRead(29)==LOW){
            msgsend=0;
            detect=60;
            dist1=0;
            dist2=0;
            rst=1;
            motion_detected=LOW;
            digitalWrite(28,LOW);
            display.clearDisplay();
            display.setCursor(0,13);
            display.println("YOU ARE SAFE!!");
            display.display();
            delay(1000);
            display.clearDisplay();
            display.setCursor(0,13);
            display.println("THANK   YOU");
            display.display();
            delay(1000);
          }
          else{
            msgsend=1;
          }
        }
      }
    }
  }
////////////////////////////////////////////////////////////////////////////////////
  if(msgsend==1){
    display.clearDisplay();
    display.setCursor(0,15);
    display.println("Sending MSG");
    display.display();
    if(msg1==1){
      gpgs.println("AT+CMGS=\""+num1+"\"\r");//selecting mobile number
      delay(1000);
      gpgs.println("Accident alert!!");//message
      gpgs.println("");
      gpgs.println("www.google.com/maps/@"+lati+","+longi+",21.5z");
      gpgs.println("");
      gpgs.println("Help Please");
      delay(1000);
      gpgs.println((char)26);//ASCII code of CTRL+Z
      delay(4000);
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("MSG 1    send");
      display.display();
    }
    if(msg2==1){
      gpgs.println("AT+CMGS=\""+num2+"\"\r");//selecting mobile number
      delay(1000);
      gpgs.println("Accident alert!!");//message
      gpgs.println("");
      gpgs.println("www.google.com/maps/@"+lati+","+longi+",21.5z");
      gpgs.println("");
      gpgs.println("Help Please");
      delay(1000);
      gpgs.println((char)26);//ASCII code of CTRL+Z
      delay(4000);
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("MSG 2    send");
      display.display();
    }
    if(msg3==1){
      gpgs.println("AT+CMGS=\""+num3+"\"\r");//selecting mobile number
      delay(1000);
      gpgs.println("Accident alert!!");//message
      gpgs.println("");
      gpgs.println("www.google.com/maps/@"+lati+","+longi+",21.5z");
      gpgs.println("");
      gpgs.println("Help Please");
      delay(1000);
      gpgs.println((char)26);//ASCII code of CTRL+Z
      delay(4000);
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("MSG 3    send");
      display.display();
    }
    delay(5000);
    display.clearDisplay();
    display.setCursor(0,20);
    display.println("Calling...");
    display.display(); 
    if(msg1==1){
      gpgs.println("ATD"+num1+";");
      delay(15000);
      gpgs.println("ATH");
      delay(2000);
    }
    if(msg2==1){
      gpgs.println("ATD"+num2+";");
      delay(15000);
      gpgs.println("ATH");
      delay(2000);
    }
    if(msg3==1){
      gpgs.println("ATD"+num3+";");
      delay(15000);
      gpgs.println("ATH");
      delay(2000);
    }
    msgdone=1;
    msgsend=0;
  }
}
////////////////////////////////////////////////////////////////////////////////////
