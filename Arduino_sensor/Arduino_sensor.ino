#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>     
SoftwareSerial s(5,6);



int cnt;
int Signal;
int val;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

void setup() {
  
  s.begin(115200);
  pulseSensor.analogInput(0);   
  pulseSensor.setThreshold(Threshold);   

}



void loop() {
                     
   val = analogRead(1);
   float mv = ( val/1024.0)*5000;
   float cel = mv/10+2;

   float farh = (cel*9)/5 + 32;
 
 
  int myBPM = pulseSensor.getBeatsPerMinute();  
  
  
//  Serial.println(farh);
//  Serial.println(myBPM);
  root["pulse"]= myBPM;    
   
  root["temp"]=cel;                               
  

  
 
if(s.available()>0)
{
 root.printTo(s);
}
delay(200);

}
