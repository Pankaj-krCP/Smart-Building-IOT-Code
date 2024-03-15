#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

DHT dht(D5, DHT11);

// Set these to run example.
#define FIREBASE_HOST "nodemcu-demo-453ce-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "CVmlYgmQ0WEW6FWB6MVrQdn9hqEY6Ahpee6FngUo"
#define WIFI_SSID "realme 3"
#define WIFI_PASSWORD "87654321"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(D1,OUTPUT);     //BUzzer for high low ground
  pinMode(D2,OUTPUT);     //Led(fire detetcion) for high low ground
  pinMode(D3,OUTPUT);     //Fan for high low ground
  pinMode(D4,OUTPUT);     //Light for High low ground
  dht.begin();

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

  
//LIGHT ON/OFF
  int p = Firebase.getInt("/room3/light");
  (p == 1) ? digitalWrite(D4,HIGH) : digitalWrite(D4,LOW); 


//FAN ON/OFF
  int q = Firebase.getInt("/room3/fan");
  (q == 1) ? digitalWrite(D3,HIGH) : digitalWrite(D3,LOW); 


//READ/WRITE Temperature/Humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Firebase.setFloat("/room3/temperature",t);
  Firebase.setFloat("/room3/humidity",h);


//FIRE DETECTION
  if ((t>30))
  {
    digitalWrite(D2,HIGH);
    digitalWrite(D1,HIGH);
  }
  else
  {
    digitalWrite(D2,LOW);
    digitalWrite(D1,LOW);
  }

  
}
