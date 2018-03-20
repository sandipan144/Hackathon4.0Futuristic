#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#define tr 12
String s, s1, lat_, long_; char ch; int i = 0;
const int vib = A0;
const int ledPin = 13;
int v;
SoftwareSerial serial(8, 9);// from Node
SoftwareSerial mySerial(10, 11);//to GSM
SoftwareSerial mySerial2(6, 7);//to Node
static const int RXPin = 3, TXPin = 4;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
boolean flag = 0, flag1 = 0;
void setup() {
  Serial.begin(9600);
  serial.begin(9600);
  mySerial.begin(9600);
  mySerial2.begin(9600);
  pinMode(vib, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(tr, OUTPUT);
  digitalWrite(tr, HIGH);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  if (flag1 == 0) {
    v = analogRead(vib);
    delay(100);
    Serial.print("Sensor value is ");
    Serial.println(v);
  }
  if (v > 50 && flag == 0) {
    //send lat long to NodeMCU
    flag = 1;
    delay(500);
    mySerial2.listen();
    Serial.print("Flag value is for sensor ");
    Serial.println(flag);
    mySerial2.print("L");
    Serial.println("L");
    flag1 = 1;
  }
  serial.listen();
  if (serial.available() > 0 && flag == 1) {
    delay(500);
    Serial.println("Getting data from serial..");
    ch = (char)serial.read();
    s += ch;
    if (ch == 'F') {
      s1 = "+91" + s.substring(0, 10);
      lat_ = s.substring(14, 23);
      long_ = s.substring(28, 37);
      Serial.println(s1);
      delay(1000);
      fakesendMessage();
      SendMessage();
      s = "";
    }
  }
}

void fakesendMessage() {
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"" + s1 + "\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println("I had an accident. Please come to my location");// The SMS text you want to send
  delay(100);
  Serial.println("latitude :" + lat_ + " longitude :" + long_);
  delay(100);
  Serial.println("https://www.google.com/maps/?q=" + lat_ + "," + long_);
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessage()
{
  mySerial.listen();
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"" + s1 + "\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I had an accident. Please come to my location");// The SMS text you want to send
  delay(100);
  mySerial.println("latitude :" + lat_ + " longitude :" + long_);
  delay(100);
  mySerial.println("https://www.google.com/maps/?q=" + lat_ + "," + long_);
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("Message Sent Successfully");
}

