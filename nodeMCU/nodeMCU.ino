#include "Adafruit_VL53L0X.h"
#include <ESP8266WiFi.h>
Adafruit_VL53L0X lox = Adafruit_VL53L0X();


#ifndef STASSID
#define STASSID ""
#define STAPSK  ""
#endif
 
const char* ssid     = STASSID;
const char* password = STAPSK;
 
const char* host = "192.168.x.x";
const uint16_t port = 8001;

void setup()
{
Serial.begin(115200);
 
// wait until serial port opens for native USB devices
while (! Serial)
{
delay(1);
}
 
Serial.println("Adafruit VL53L0X test");
if (!lox.begin())
{
Serial.println(F("Failed to boot VL53L0X"));
while(1);
}
// power
Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}

}
 
void loop()
{
  VL53L0X_RangingMeasurementData_t measure;

  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }
  if (client.connected()) {
    Serial.print("Reading a measurement... ");
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
     
    if (measure.RangeStatus != 4)
    { // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    }
    else
    {
    Serial.println(" out of range ");
    }
     
    delay(100);  
    
    
    client.println(measure.RangeMilliMeter);
  }
   
  
}