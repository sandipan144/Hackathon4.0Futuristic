#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

String loc_ = "lat=26.879660&lon=75.812482";
String url;
const char* ssid = "nigga";
const char* password = "nigga123";
SoftwareSerial mySerial(13, 15);//to arduino
SoftwareSerial mySerial2(12, 14);//from arduino
int i;
String number;
void setup () {
  Serial.begin(115200);
  mySerial.begin(9600);
  mySerial2.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("No");
    delay(500);
  }

}

String getNumber() {
  Serial.println("Get NUmber is called");
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;
    url = "http://10.42.0.1.xip.io/getDataScript.php?" + loc_;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      return http.getString();
    }
    http.end();
  }
}

void loop() {
  mySerial2.listen();
  delay(200);
  if (mySerial2.available() > 0) {
    if (mySerial2.read() == 'L') {
      Serial.println("L is Available");
      for (i = 1; i <= 10; i++) {
        number = getNumber();
        delay(50);
      }
      Serial.println(number + loc_ + "F");
      mySerial.print(number + loc_ + "F");
    }
  }
}

