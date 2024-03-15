const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(13,OUTPUT);
   pinMode(12,OUTPUT);
}

void loop() {
   long duration, inches, c;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   c = microsecondsToCentimeters(duration);
   if (c<100)
   {
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
   }
   else
   {
    digitalWrite(13,LOW);
   }
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(c);
   Serial.print("cm");
   Serial.println();
   delay(100);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
