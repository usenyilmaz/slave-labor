#include <Wire.h>

#define SDA_PIN D2
#define SCL_PIN D1

//motor pins

#define MOTOR1_PIN //choose accordingly
#define MOTOR2_PIN
#define MOTOR3_PIN 
#define MOTOR4_PIN 


//complemetary filter state
float angleX = 0, angleY = 0;
unsigned long lastTime = 0;

//Need PID State


void setup(){
 //Get comms and sensors initialized
  Wire.begin(SDA_PIN, SCL_PIN);
  SensorInit();
  
  //configure pins as output
  pinMode(MOTOR1_PIN, OUTPUT);
  pinMode(MOTOR2_PIN, OUTPUT);
  pinMode(MOTOR3_PIN, OUTPUT);
  pinMode(MOTOR4_PIN, OUTPUT);

  analogWriteRange(?);//decide
  analogWriteFreq(?);

  LastTime = millis();
}


void loop(){
  unsigned now = millis();
  float dt = (now - LastTime) / 1000.0; //used in PID computation
  LastTime = now;//calculaated now so Last time for the next loop is the current now

  //read sensor values, we get g and ac from here
  Read.Sensor();

  //compute PID stuff to get correction aaand implement 
  float pitchCorrection = computePID();
  float rollCorrection = computePID();

  int m1 = ;
  int m2 = ;
  int m3 = ;
  int m4 = ;


  //mn is the value of PWM for correction to get stable position
  analogWrite(MOTOR1_PIN, m1);
  analogWrite(MOTOR2_PIN, m2);
  analogWrite(MOTOR3_PIN, m3);
  analogWrite(MOTOR4_PIN, m4);  

}

float computePID(){



}





























