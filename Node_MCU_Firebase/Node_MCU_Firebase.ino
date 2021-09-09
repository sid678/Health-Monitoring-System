#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);

#define FIREBASE_HOST "d******2.firebaseio.com"
#define FIREBASE_AUTH "ZPW3uQtPYy***********fiWd8rRnXilVrH"
#define WIFI_SSID "S********u"
#define WIFI_PASSWORD "s**********a"

void setup() {
  
  Serial.begin(115200);
  s.begin(115200);
  while (!Serial) 
    continue;
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

int n = 0;
int t=0;

void loop() {
 
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  
  if (root == JsonObject::invalid())
  {
    Serial.println("invalid JSON!");
    return;
  }
  
  Serial.println("");
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  
  Serial.print("Temperature ");
  float data1=root["temp"];
  Serial.println(data1);
  Serial.print("pulse ");
  int data2=root["pulse"];
  Serial.println(data2);
 
  String tt=String(t);
   
  Firebase.setFloat("body_temperature_in_C/"+tt, data1);
  Firebase.setFloat("pulse/"+tt, data2);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  

//  Serial.print("body_temperature: ");
//  Serial.println(Firebase.getFloat("body_temperature/"));
  delay(1000);

  t+=1;
  

  

}
