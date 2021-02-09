#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#define DHTPIN 5 
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);
char auth[] = "NupjCc9xKFZN5lT41gypwhv3uYAHf_U3";
char ssid[] = "3BB_2.4GHz";
char pass[] = "1111100000";
//---------------------------------
const int pingPin = 27;
int inPin = 26 ;
//---------------------------------
void setup() {
    Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  dht.begin();
}
void loop() {
  float humidity = dht.readHumidity(); // ดึงค่าความชื้น
  float temperature = dht.readTemperature(); // ดึงค่าอุณหภูมิ
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Blynk.run();
  delay(100);
  Blynk.virtualWrite(V5, temperature);
  Blynk.virtualWrite(V6, humidity);
  Blynk.virtualWrite(V7, cm);
}

long microsecondsToCentimeters(long microseconds)
{
return microseconds / 29 / 2;
}
