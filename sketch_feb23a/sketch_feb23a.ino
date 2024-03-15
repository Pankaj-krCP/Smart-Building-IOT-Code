int freq = 50;

const int triggerPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int SPEAKER = 10; //Speaker
const int LEDHigh = 13; //LED High
const int LEDLow = 12; //LED Low
const int Temp = 4; //Temperature sensor

void setup() {
  pinMode(A0,INPUT); //IR sensor analog read
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(SPEAKER, OUTPUT); 
  pinMode(LEDHigh, OUTPUT); 
  pinMode(LEDLow, OUTPUT);
  pinMode(Temp, OUTPUT);
  Serial.begin(9600);
}


void loop() {

  // IR sensor input
//  int c= IR();

  // UltraSonic Sensor input
  long dis = ultraSonic();
  
  if(dis<200){
    blinkLED();
    speakerON();
  }
  else{
    speakerOFF();
  }

}


void speakerON(){
  freq += 100;
  if (freq > 8000)
  {
     noTone(SPEAKER);
     freq = 50;
  }
  tone(SPEAKER, freq);
  delay(100); 
}


void speakerOFF(){
   noTone(SPEAKER);
   freq = 50;
}


void blinkLED(){
   digitalWrite(LEDLow, LOW);
   digitalWrite(LEDHigh, HIGH);
   delay(200);                   
   digitalWrite(LEDHigh, LOW);  
   delay(200);                 
}


//int IR(){
//  int c= analogRead(A0);
//  Serial.println(c);
//  return c;
//}


long ultraSonic(){
   long duration,distInCM;
   digitalWrite(triggerPin, LOW);
   delayMicroseconds(2);
   digitalWrite(triggerPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(triggerPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   distInCM = duration / 29 / 2;
   return distInCM;
}
