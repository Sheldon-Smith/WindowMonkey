#include <CommunicationUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <DebugUtils.h>
#include <FreeSixIMU.h>

// # Editor     : Roy from DFRobot
// # Date       : 10.12.2013
// # Product name: 6 Dof shield for Arduino
// # Product SKU : DFR0209
// # Version     : 0.1
// # Description:
// # The sketch for driving the 6 Dof shield for Arduino via I2C interface

#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>

#include <Wire.h>
// Ultrasound 0 1 14 - 19
const int trigPin1 = 1;
const int echoPin1 = 0;

const int trigPin2 = 15;
const int echoPin2 = 14;

const int trigPin3 = 17;
const int echoPin3 = 16;

const int trigPin4 = 19;
const int echoPin4 = 18;

int distance1;
int distance2;
int distance3;
int distance4;

#include <NewPing.h>

#define TRIGGER_PIN  15  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     14  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

////////////
// Timer
////////////
unsigned long previousMillis = 0;

///////////////////////
// IMU
int16_t angle[2]; // pitch & roll

// Set the FreeSixIMU object
FreeSixIMU sixDOF = FreeSixIMU();
int rawSixDof[6];

// Caution: The small gear of the right motor is slippery, which may cause wrong angular postion
#include <Servo.h>
// Servo on the right
Servo myRightServo;
// Servo on the left
Servo myLeftServo;
// Record the angular position of each motor
int rightPos = 0;
int leftPos = 0;

//Linear Servo
//Left
//const int en1 = 11;
//const int dir11 = 12;
//const int dir12 = 13;
const int dir11 = 7;
const int dir12 = 8;

//Right
const int en2 = 6;
//const int dir21 = 7;
//const int dir22 = 8;
const int dir21 = 12;
const int dir22 = 13;

// Valves
const int valveL = 5;
const int valveR = 4;

///////////////////                                                                                                                                                                                                                                                   //
// Initial Data
/////////////////////
int isInit = 0;
int pattern = 1;
int transition = 0;
float windowWidth = 5.0, windowHeight = 6.0;
float robotLength = 0.95;
float cupRadius = 0.125;
float x = 0.0 + robotLength + cupRadius, y = 0.0 + cupRadius;
int currMotor = 0;//0 == right, 1 == left

void setup() {
  // Ultrasound
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  Serial.begin(115200);
  //IMU
  //  Serial.begin(9600);
  Wire.begin();

  delay(5);
  sixDOF.init();                        //begin the IMU
  delay(5);

  //
  myRightServo.attach(10);
  myLeftServo.attach(9);
  pinMode(valveL, OUTPUT);
  pinMode(valveR, OUTPUT);
  Serial.begin(9600);
}

void loop() {
      // Main Motion
      if (isInit == 0) {
        initialize_servos();
        isInit = 1;
      }
      if (isInit == 1) {
        walkRight();
        relocateOnTheRight();
        walkLeft();
        relocateOnTheLeft();
        }
      if (isInit == 2) {
        relocateOnTheLeft();
        isInit = 1;
        }
      if (isInit == 3) {
        relocateOnTheRight();
        isInit = 1;
        }
//      hardCodeMotion();
//      if (y + robotLength + cupRadius < windowHeight) {
//        printLocation();
//      }
      
      ////////////////////////
//  if (Serial.read() == '1') {
//    ultrasound1();
//    ultrasound2();
//    ultrasound3();
//    ultrasound4();
//  }

  /////////////////
  //  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  //
  //  digitalWrite(ECHO_PIN, LOW);
  //
  //  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  //  Serial.print("Ping: ");
  //  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  //  Serial.println("cm");
    pullRight();
    pullLeft();
    delay(3000);
    sixDOF.getRawValues(rawSixDof);
    Serial.println("");
    angle[0] = _atan2(rawSixDof[0], rawSixDof[1]);
    angle[1] = _atan2(rawSixDof[1], rawSixDof[2]);
  
    Serial.print("X:");              //pitch & roll
    Serial.println(angle[0] / 10.0 + 90);// The angle we wanna use
    Serial.print("Y:");
    Serial.println(angle[1] / 10.0);
    Serial.println("");
    delay(1000);
}

//////////////////////
// Helper Functions
//////////////////////

//////
// Servo
////////////
void initialize_servos() {
  for (int i = 360; i > 0; i-= 5) {
    right_writePos(i);
    left_writePos(i);
    delay(70);
  }
  while ((90 +angle[0] / 10.0) > 10) {
    right_writePos(0);
    left_writePos(0);
  }
  rightPos = 0;
  leftPos = 0;
  previousMillis = millis();
  pullLeft();
  pullRight();
  if (millis() - previousMillis > 3000) {
    pushRight();
    digitalWrite(valveR, LOW);
    digitalWrite(valveL, HIGH);
  }
  if (millis() - previousMillis > 8000) {
    isInit = 1;
    x = robotLength + cupRadius;
    y = cupRadius;
    previousMillis = millis();
  }
}

void right_turn(int posChange) {
  rightPos += posChange;
  myRightServo.write(rightServoTransFunc(rightPos));
}

void left_turn(int posChange) {
  leftPos += posChange;
  myLeftServo.write(leftServoTransFunc(leftPos));
}

void right_writePos(int targetPos) {
  rightPos = targetPos;
  myRightServo.write(rightServoTransFunc(rightPos));
}

void left_writePos(int targetPos) {
  leftPos = targetPos;
  myLeftServo.write(leftServoTransFunc(leftPos));
}
// double the degree to fit the new gear box
int rightServoTransFunc(int incomingDegree) {
  //  int temp = incomingDegree * (100.0/432.0) + 10;
  int temp = incomingDegree * (100.0 / 432.0) + 10;
  return temp;
}

int leftServoTransFunc(int incomingDegree) {
  //  int temp = incomingDegree*(105.0/432.0) + 5;
  int temp = incomingDegree * (105.0 / 432.0) + 5;
  return temp;
}

///////////
// Linear Actuator
////////////////////

void pullLeft() {
  digitalWrite(dir11, LOW);
  digitalWrite(dir12, HIGH);
  //    analogWrite(en1, 255);
}

void pushLeft() {
  digitalWrite(dir11, HIGH);
  digitalWrite(dir12, LOW);
  //    analogWrite(en1, 255);
}

void pullRight() {
  digitalWrite(dir21, HIGH);
  digitalWrite(dir22, LOW);
//  analogWrite(en2, 255);
}

void pushRight() {
  digitalWrite(dir21, LOW);
  digitalWrite(dir22, HIGH);
//  analogWrite(en2, 255);
}


void stopLeft() {
  //    analogWrite(en2, 0);
  digitalWrite(dir21, LOW);
  digitalWrite(dir22, LOW);
}

void stopRight() {
  //    analogWrite(en1, 0);
  digitalWrite(dir11, LOW);
  digitalWrite(dir12, LOW);
}

void printLocation() {
  Serial.print("Current Position: ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(" Degree: ");
  Serial.print(leftPos);
  Serial.print(", ");
  Serial.print(rightPos);
  Serial.print('\n');
}

////////////////
// Motion
////////////////
void rotate(int degreeToTurn, int degreeToWrite) {
  if (currMotor == 0) {
    right_turn(degreeToTurn);
    left_writePos(degreeToWrite);
    currMotor = 1;
    Serial.print("Rotate the right motor.\n");
  }
  else if (currMotor == 1) {
    left_turn(degreeToTurn);
    right_writePos(degreeToWrite);
    currMotor = 0;
    Serial.print("Rotate the left motor.\n");
  }

}
void hardCodeMotion() {
  if (y + robotLength + cupRadius >= windowHeight) {
    return;
  }

  if (pattern == 1) {
    if (x + cupRadius + robotLength > windowWidth) {
      if (transition == 0) {
        transition = 1;
      }
      if (transition == 1) {
        rotate(180, 0);
        switchCup();
        transition = 2;
        y += robotLength;
        printLocation();
      }
      if (transition == 2) {
        rotate(360, 0);
        switchCup();
        transition = 3;
        y += robotLength;
        printLocation();
      }
      if (transition == 3) {
        rotate(180, 0);
        switchCup();
        transition = 0;
        pattern = 2;
        x -= robotLength;
        printLocation();
      }
    } else {
      rotate(360, 0);
      x += robotLength;
      switchCup();
    }

  }

  if (pattern == 2) {
    float bias = 0.05;//Fix the problem caused by the accuracy of float type stored in Arduino
    if (x - cupRadius - robotLength + bias < 0.0) {
      if (transition == 0) {
        transition = 1;
      }
      if (transition == 1) {
        switchCup();
        rotate(0, 180);
        switchCup();
        rotate(-180, 360);
        switchCup();
        transition = 2;
        y += robotLength;
        printLocation();
      }
      if (transition == 2) {
        rotate(-360, 180);
        switchCup();
        transition = 3;
        y += robotLength;
        printLocation();
      }
      if (transition == 3) {
        rotate(-180, 0);
        switchCup();
        transition = 0;
        pattern = 3;
        x += robotLength;
        printLocation();
      }
    } else {
      rotate(-360, 360);
      x -= robotLength;
      switchCup();
    }
  }

  if (pattern == 3) {
    if (x + cupRadius + robotLength > windowWidth) {
      if (transition == 0) {
        right_writePos(720); // 360 degrees actually
        delay(5000);
        transition = 1;
      }
      if (transition == 1) {
        rotate(180, 360);
        switchCup();
        transition = 2;
        y += robotLength;
        printLocation();
      }
      if (transition == 2) {
        rotate(360, 360);
        switchCup();
        transition = 3;
        y += robotLength;
        printLocation();
      }
      if (transition == 3) {
        rotate(180, 0);
        switchCup();
        transition = 0;
        x -= robotLength;
        pattern = 2;
        printLocation();
      }
    } else {
      if (x + cupRadius + 2 * robotLength > windowWidth) {
        rotate(360, 0);
        x += robotLength;
        switchCup();
      } else {
        rotate(360, 0);
        x += robotLength;
        switchCup();
      }
    }
  }


}

void switchCup() {
  if (pattern == 1 && transition == 0) {
    delay(5000);
  } else if (rightPos == 0 && leftPos == 1260) {
    delay(2500);
  }
  else if (pattern == 2 && rightPos == 360 && leftPos == 0) {
    delay(2500);
  }
  else {
    delay(10000);
  }
  if (currMotor == 0) {
    pushLeft();
    pullRight();
    // close the right valve and open the left valve
    digitalWrite(valveR, HIGH);
    digitalWrite(valveL, LOW);
    delay(7000);
    //////////////////////
    // Move 1.5 s, stop 1.5s and then pull both cups up
    //    delay(1500);
    //      analogWrite(en1, 0);
    //      analogWrite(en2, 0);
    //    digitalWrite(dir21, LOW);
    //    digitalWrite(dir22, LOW);
    //    digitalWrite(dir11, LOW);
    //    digitalWrite(dir12, LOW);
    //    delay(1500);
    //    pullRight();
    //    pullLeft();
    //    delay(1500);
    /////////////////////////////////////////////
  }
  else if (currMotor == 1) {
    pullLeft();
    pushRight();
    // close the right valve and open the left valve
    digitalWrite(valveR, LOW);
    digitalWrite(valveL, HIGH);
    delay(7000);
    //////////////////////
    // Move 1.5 s, stop 1.5s and then pull both cups up
    //    delay(1500);
    //      analogWrite(en1, 0);
    //      analogWrite(en2, 0);
    //    digitalWrite(dir21, LOW);
    //    digitalWrite(dir22, LOW);
    //    digitalWrite(dir11, LOW);
    //    digitalWrite(dir12, LOW);
    //    delay(1500);
    //    pullRight();
    //    pullLeft();
    //    delay(1500);
    /////////////////////////////////////////////
  }
  delay(0);
}

void detachRight() {
  digitalWrite(valveR, HIGH);
  return;
}

void detachLeft() {
  digitalWrite(valveL, HIGH);
  return;
}
void attachRight() {
  digitalWrite(valveR, LOW);
  return;
}

void attachLeft() {
  digitalWrite(valveL, LOW);
  return;
}
//Serial Control
void movePart(char part[], int val) {
  // servos
  if (part == "SL") {
    left_writePos(val);
    delay(5000);
    return;
  }
  if (part == "SR") {
    right_writePos(val);
    delay(5000);
    return;
  }
  // linear actuators
  if (part == "AL") {
    if (val >= 0) {
      pushLeft();
      return;
    }
    else {
      pullLeft();
      return;
    }
  }
  if (part == "AR") {
    if (val >= 0) {
      pushRight();
      return;
    }
    else {
      pullRight();
      return;
    }
  }
  // valves
  if (part == "VL") {
    if (val >= 0) {
      detachLeft();
      return;
    }
    else {
      attachLeft();
      return;
    }
  }
  if (part == "VR") {
    if (val >= 0) {
      detachRight();
      return;
    }
    else {
      attachRight();
      return;
    }
  }
  delay(5000);
}

//assume a barrier detected and currently left cup is attaching
void hardCodeCrossBarrier() {
  pushLeft();
  pullRight();
  delay(3000);
  left_turn(90);
  delay(3000);
  pushRight();
  attachRight();
  delay(3000);
  detachLeft();
  pullLeft();
  delay(6000);
  right_turn(90);
  delay(3000);
  attachLeft();
  pushLeft();
  delay(3000);
}
int indexUltrasound = 0; // 0(left-bottom),1(right-bottom) on the same side; 2(left-top),3(right-top) on the other.
bool cross(int dist, float deg, int currUltraSound) {
  if (dist > 0 && dist <= 30 && (deg > 170 || deg < 10)) {
    switch (indexUltrasound)
    {
      case 0:
        pushRight();
        pullLeft();
        delay(3000);
        attachRight();
        detachLeft();
        delay(5000);
        left_writePos(180);
        right_turn(180);
        delay(3000);
        pushLeft();
        pullRight();
        delay(3000);
        left_turn(-180);
        delay(3000);
        pushRight();
        attachRight();
        delay(3000);
        detachLeft();
        pullLeft();
        delay(6000);
        right_turn(-180);
        left_writePos(180);
        delay(3000);
        attachLeft();
        pushLeft();
        delay(3000);
//        return true;
        break;
      case 1:
        pushLeft();
        pullRight();
        delay(3000);
        left_turn(180);
        delay(3000);
        pushRight();
        attachRight();
        delay(3000);
        detachLeft();
        pullLeft();
        delay(6000);
        right_turn(180);
        delay(3000);
        attachLeft();
        pushLeft();
        delay(3000);
//        return true;
        break;
      case 2:
        pushRight();
        pullLeft();
        delay(3000);
        right_turn(180);
        delay(3000);
        pushLeft();
        attachLeft();
        delay(3000);
        detachRight();
        pullRight();
        delay(6000);
        left_turn(180);
        delay(3000);
        attachRight();
        pushRight();
        delay(3000);
        return true;
//        break;
      case 3:
        pushRight();
        pullLeft();
        delay(3000);
        right_turn(180);
        delay(3000);
        pushLeft();
        attachLeft();
        delay(3000);
        detachRight();
        pullRight();
        delay(6000);
        left_turn(180);
        delay(3000);
        attachRight();
        pushRight();
        delay(3000);
        return true;
//        break;
    }
    return false;
  }
}

// Ultrasonic sensors
void ultrasound1() {

  long duration;
  //  int distance;

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration = pulseIn(echoPin1, HIGH);

  distance1 = duration * 0.034 / 2;


  Serial.print("Distance1: ");
  Serial.println(distance1);
}

void ultrasound2() {

  long duration;
  int distance;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration = pulseIn(echoPin2, HIGH);

  distance = duration * 0.034 / 2;


  Serial.print("Distance2: ");
  Serial.println(distance);
}

void ultrasound3() {

  long duration;
  //  int distance;

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration = pulseIn(echoPin3, HIGH);

  distance3 = duration * 0.034 / 2;


  Serial.print("Distance3: ");
  Serial.println(distance3);
}

void ultrasound4() {

  long duration;
  int distance;

  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);

  duration = pulseIn(echoPin4, HIGH);

  distance4 = duration * 0.034 / 2;


  Serial.print("Distance4: ");
  Serial.println(distance4);
}

int16_t _atan2(int32_t y, int32_t x)   //get the _atan2
{
  float z = (float)y / x;
  int16_t a;
  if ( abs(y) < abs(x) )
  {
    a = 573 * z / (1.0f + 0.28f * z * z);
    if (x < 0)
    {
      if (y < 0) a -= 1800;
      else a += 1800;
    }
  }
  else
  {
    a = 900 - 573 * z / (z * z + 0.28f);
    if (y < 0) a -= 1800;
  }
  return a;
}

bool isWaiting(unsigned long interval) {
  unsigned long int currMillis = millis();
  if (currMillis - previousMillis >= interval) {
    previousMillis = currMillis;
    return false;
    }
  return true;
  }

///////////
// Relocate 
//////////////////////////
void walkRight() {
  for (int i = 0; i <5; i++) {
    rotate(360, 0);
    x += robotLength;
    switchCup();
  }
  right_writePos(180);
  left_writePos(0);
  delay(3000);
  
}

void walkLeft() {
  for (int i = 0; i < 5; i++) {
    rotate(-360, 360);
    x -= robotLength;
    switchCup();
  }
  left_writePos(180);
  right_writePos(0);
  delay(3000);
}
//
void relocateOnTheRight() {
//  while (readIMU() < 0) {
  for (int i = 0; i < 180; i += 5) {
    // from 180(360)
    right_writePos(180);
    left_writePos(540);
    delay(50);
  }
//  }
  left_writePos(540);
  delay(5000);
  digitalWrite(valveR, HIGH);
  digitalWrite(valveL, LOW);
  pullRight();
  pushLeft();
  delay(8000);
  

  y += robotLength;
//  while (readIMU() > 0) {
  for (int i = 0; i < 360; i+= 5) {
    right_writePos(360);
    left_writePos(0);
    delay(50);
  }
//    }
  x = cupRadius + robotLength*2;
  pushRight();
  pullLeft();
  digitalWrite(valveR, LOW);
  digitalWrite(valveL, HIGH);
  delay(8000);
  right_writePos(360);
  delay(8000);
  currMotor = 1;
}

void relocateOnTheLeft() {
//  while (readIMU() < 0) {
    // from 180(360)
  for (int i = 360; i > 180; i -= 5) {
    left_writePos(180);
    right_writePos(0);
    delay(50);
  }
//  }
  pushRight();
  pullLeft();
  delay(3000);
  digitalWrite(valveR, LOW);
  digitalWrite(valveL, HIGH);
  delay(5000);

  y += robotLength;
//  while (readIMU() < 180) {
  for (int i = 540; i >0 ; i -= 5) {
    right_writePos(540);
    left_writePos(0);
    delay(50);
  }
//    }
  x = cupRadius + robotLength*2;
  pullRight();
  pushLeft();
  delay(3000);
  digitalWrite(valveL, LOW);
  digitalWrite(valveR, HIGH);
  delay(5000);
  right_writePos(0);
  delay(8000);
  currMotor = 1;
}

int readIMU() {
  return (90 +angle[0] / 10.0);
  }
