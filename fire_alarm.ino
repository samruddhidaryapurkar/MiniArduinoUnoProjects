#include <TinyGPS++.h>
#include <SoftwareSerial.h>

int led = 13;
int flame_sensor = 3;
int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;
int flame_detected;

SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial gpsSerial(RXPin, TXPin);
TinyGPSPlus gps;

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
  pinMode(led, OUTPUT);
  pinMode(flame_sensor, INPUT);
}

void loop()
{
  flame_detected = digitalRead(flame_sensor);
    if (flame_detected == 1)
    {
     Serial.println(" Fire ");
     digitalWrite(led, HIGH);
     
       while (ss.available() && flame_detected==1)
        {
         gps.encode(ss.read());
         if (gps.location.isUpdated())
           {
            Serial.print("Latitude= "); 
            Serial.print(gps.location.lat(), 6);
            Serial.print(" Longitude= "); 
            Serial.println(gps.location.lng(), 6);
           }
        }
    }
     else
     {
      Serial.println(" No fire ");
      digitalWrite(led, LOW);
     }
}
