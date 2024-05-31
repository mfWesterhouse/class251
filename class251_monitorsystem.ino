#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Wifi.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHTPIN 19
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define WLAN_SSID     "WR3005N3-757E"
#define WLAN_PASS     "70029949"

Adafruit_BMP085 bmp;

void setup(){
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if(!bmp.begin()){
    Serial.println("Could not fina a valid BMP085/BMP180 sensor, check wiring!");
    while(1){}
  }
  dht.begin();
}

void loop(){
  if(WiFi.status()==WL_CONNECTED){
    WiFiClient client;
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.print(" *C");

    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    float h = dht.readHumidity();
    if(isnan(h)){
      Serial.println("Failed to read from DHT sensor!"){
        return;
      }
      else
      {
        Serial.print("Humidity: ");
        Serial.print(h);
      }
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    delay(5000);
  }
}