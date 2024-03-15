//Include the NodeMCU ESP8266 Library
#include <ESP8266WiFi.h>

//Include the ThingSpeak Library
#include "ThingSpeak.h"

//Defining an On Board LED, used for indicators when the process of connecting to a wifi router
#define ON_Board_LED D5

//Defining LIGHT/Relay Port
#define LIGHT D4        

//SSID and Password of your WiFi router/hotspot
const char *ssid = "PankajPC";
const char *password = "pankaj123";

unsigned long channel = 2045690;  //Channel ID on ThingSpeak

//Declaration field1, I use field1 for light / relay, if you use many fields, add field1, field2, and so on.
unsigned int field2 = 2;

WiFiClient client;

//SETUP
void setup()
{
  Serial.begin(9600);
  delay(100);

  pinMode(ON_Board_LED, OUTPUT); //On Board LED port Direction output
  pinMode(LIGHT, OUTPUT);        //LIGHT/Relay port Direction output

  digitalWrite(ON_Board_LED, LOW); //Turn off Led On Board.
  digitalWrite(LIGHT, LOW);         //Turn off LIGHT/Relay

  //Wait for connection
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    //Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  digitalWrite(ON_Board_LED, HIGH); //Turn off the On Board LED when it is connected to the wifi router.

  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  
  //ThingSpeak.begin(client)
  ThingSpeak.begin(client);
}

void loop()
{
  int statusCode = 0;
  int last_light_state = ThingSpeak.readFloatField(channel, field2); //get the latest data from the fields on ThingSpeak

  statusCode = ThingSpeak.getLastReadStatus(); //Check the status of the read operation to see if it was successful
  if (statusCode == 200)
  {
    if (last_light_state == 1)
    {
      digitalWrite(LIGHT, HIGH);
    }
    else if (last_light_state == 0)
    {
      digitalWrite(LIGHT, LOW);
    }
  }
  else
  {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }
}
