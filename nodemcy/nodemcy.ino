#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
DHT dht(D5, DHT11);

WiFiClient client;

long myChannelNumber = 2095656;
long myChannelNumber2 = 2095661;
const char myWriteAPIKey[] = "GDK4GQMEHM6QVM9W";
const char myWriteAPIKey2[] = "WRH4ACKFBA80RX9V";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("realme 3", "87654321");
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D0,INPUT);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}

void loop() {
 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int SensorValue = analogRead(D0);
 
  int p =ThingSpeak.readFloatField(myChannelNumber, 1);
  if (p==1)
  {
    
    digitalWrite(D3,HIGH);
    digitalWrite(D4,LOW);
  }
  else
  {
    digitalWrite(D3,LOW);
  }
  Serial.println(SensorValue);
  if ((t>30) or (SensorValue<1000))
  {
    digitalWrite(D2,HIGH);
    digitalWrite(D1,HIGH);
  }
  else
  {
    digitalWrite(D2,LOW);
    digitalWrite(D1,LOW);
  }
  
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
 
ThingSpeak.writeField(myChannelNumber2, 4, t, myWriteAPIKey2);
ThingSpeak.writeField(myChannelNumber2, 5, h, myWriteAPIKey2);
  
}
