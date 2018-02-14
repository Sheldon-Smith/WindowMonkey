

#include <A4988.h>
#include <BasicStepperDriver.h>
#include <DRV8825.h>
#include <DRV8834.h>
#include <DRV8880.h>
#include <MultiDriver.h>
#include <SyncDriver.h>

const int encoderPinA = 2;
const int encoderPinB = 6;
volatile unsigned int encoderPos = 0;
unsigned int lastReportedPos = 1;

boolean A_set = false;
boolean B_set = false;

const int potPin = A0;
const int flexPin = A1;
const int trigPin = 8;
const int echoPin = 7;
const int switchPin = A2;


// Interrupt on A changing state
void doEncoder() {
  /* If pinA and pinB are both high or both low, it is spinning
     forward. If they're different, it's going backward.

     For more information on speeding up this process, see
     [Reference/PortManipulation], specifically the PIND register.
  */
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    encoderPos++;
  } else {
    encoderPos--;
  }

  //Serial.println (encoderPos, DEC);
}

//declare pins
#include <Servo.h>
//////////////
// Servo Motor
//////////////
Servo myservo;
int pos = 0; 

///////////////////
// Stepper Motor
///////////////////
const int stepPin = 3; 
const int dirPin = 4; 
const int motor_steps = 800;
A4988 stepper(motor_steps, dirPin, stepPin);

///////////////////
// DC Motor
///////////////////
const int en1 = 11;
const int dir11 = 12;
const int dir12 = 13;
 
//setup all pins as outputs
void setup(){

  pinMode(encoderPinA, INPUT);
  digitalWrite(encoderPinA, HIGH); 
  pinMode(encoderPinB, INPUT); 
  digitalWrite(encoderPinB, HIGH);

// encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoder, CHANGE);

  pinMode(switchPin, INPUT);
  
  Serial.begin(9600);
  ////////////////////
  // Servo Motor
  ///////////////////
  myservo.attach(5);
  
  ////////////////////
  // Stepper Motor
  ////////////////////
  stepper.begin(1,1);

  ///////////////////
  // DC Motor
  ///////////////////
  pinMode(en1, OUTPUT);
  pinMode(dir11, OUTPUT);
  pinMode(dir12, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void writeMotor(char motor, int val)
{
  if (motor == 'r'){
    myservo.write(val);
    delay(1000);
    return;
  }
  if (motor == 'd'){
    setDCMotorSpeed(val);
    return;
  }
  if (motor == 's'){
    stepper.rotate(val);
    delay(5000);
    return;
  }
    return;
 }

void loop(){
  delay(5000);
  if (Serial.available()) {
    char motorSpecifier = Serial.read();
    int motorPos = Serial.parseInt();
    writeMotor(motorSpecifier, motorPos);
    }
   delay(5000);

   
  /////////////////////
  // Servo Motor
  /////////////////////
  
//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  
////  ////////////////////
////  // Stepper Motor
////  ////////////////////
//
//    stepper.rotate(10);
    flex();
    pot();
    ultrasound();
}

void flex() {
  
  int flexValue;

  flexValue = analogRead(flexPin);
  flexValue = .75*flexValue-620-25;
// Printing cause problem to GUI control!
//  Serial.print("Flex: ");
//  Serial.println(flexValue);
  stepper.rotate(flexValue);
}
void pot() {

    int potValue;
    
    potValue = analogRead(potPin);
    potValue = 0.2612*potValue;
//    Serial.print("Pot: ");
//    Serial.println(potValue);
    myservo.write(potValue/4);
    delay(1000);
}


void ultrasound() {

  long duration;
  int distance;
  int motor_speed = 0;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration*0.034/2;

  ///////////////////
  // DC Motor
  ///////////////////
  
  if (digitalRead(switchPin)) {
    motor_speed = distance*10;
  } else {
    motor_speed = 0;
  }
  
  
  if (motor_speed > 255) {
    motor_speed = 255;
  }
  
  analogWrite(en1, motor_speed);
  digitalWrite(dir11, HIGH);
  digitalWrite(dir12, LOW);

//  Serial.print("Distance: ");
//  Serial.println(distance);
}

void setDCMotorSpeed(int motorSpeed) {
  int motor_speed = 0;
  if (digitalRead(switchPin)) {
    motor_speed = motorSpeed;
  } else {
    motor_speed = 0;
  }
  
  
  if (motor_speed > 255) {
    motor_speed = 255;
  }

  analogWrite(en1, motor_speed);
  digitalWrite(dir11, HIGH);
  digitalWrite(dir12, LOW);
  delay(5000);
}

