
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

///////////////////
// DC Motor
///////////////////
const int en1 = 11;
const int dir11 = 12;
const int dir12 = 13;
const int en2 = 10;
const int dir21 = 8;
const int dir22 = 9;
 
//setup all pins as outputs
void setup(){
  ////////////////////
  // Servo Motor
  ///////////////////
  myservo.attach(5);
  
  ////////////////////
  // Stepper Motor
  ////////////////////
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  ///////////////////
  // DC Motor
  ///////////////////
  pinMode(en1, OUTPUT);
  pinMode(dir11, OUTPUT);
  pinMode(dir12, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(dir21, OUTPUT);
  pinMode(dir22, OUTPUT);
}
 
void loop(){
  /////////////////////
  // Servo Motor
  /////////////////////
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  ////////////////////
  // Stepper Motor
  ////////////////////
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  delay(1000); // One second delay
  Serial.print(stepPin);
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 400; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  }
  delay(1000);

  ///////////////////
  // DC Motor
  ///////////////////
  //spin motors one way at half speed
  analogWrite(en1, 128);
  digitalWrite(dir11, HIGH);
  digitalWrite(dir12, LOW);
  analogWrite(en2, 128);
  digitalWrite(dir21, HIGH);
  digitalWrite(dir22, LOW);
  delay(100);

// //stall motors
//  digitalWrite(en1, HIGH);
//  digitalWrite(dir11, HIGH);
//  digitalWrite(dir12, HIGH);
//  digitalWrite(en2, HIGH);
//  digitalWrite(dir21, LOW);
//  digitalWrite(dir22, LOW);
//  delay(100);
// //turn motors the other way at 3/4 speed
//  analogWrite(en1, 192);
//  digitalWrite(dir11, HIGH);
//  digitalWrite(dir12, LOW);
//  analogWrite(en2, 192);
//  digitalWrite(dir21, HIGH);
//  digitalWrite(dir22, LOW);
//  delay(100);
// //turn motors off
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
  delay(100);
}

