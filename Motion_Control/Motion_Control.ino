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
const int en1 = 11;
const int dir11 = 12;
const int dir12 = 13;

//Right
const int en2 = 6;
const int dir21 = 7;
const int dir22 = 8;

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
  // put your setup code here, to run once:
    myRightServo.attach(10);
    myLeftServo.attach(9);
    pinMode(en1, OUTPUT);
    pinMode(en2, OUTPUT);
    pinMode(valveL, OUTPUT);
    pinMode(valveR, OUTPUT);
    Serial.begin(9600);
}

void loop() {
//  pullRight();
//  pullLeft();

// Main Motion
    if (isInit == 0) {
      initialize_servos();
      isInit = 1;
    }
    hardCodeMotion();
    if (y + robotLength + cupRadius < windowHeight) {
        printLocation();
    }
}

//////////////////////
// Helper Functions
//////////////////////

//////
// Servo
////////////
void initialize_servos() {
  myRightServo.write(51);
  rightPos = 180;
  myLeftServo.write(48);
  leftPos = 180;
//  myRightServo.write(10);
//  rightPos = 0;
//  myLeftServo.write(5);
//  leftPos = 0;
//  delay(10000);
  pullLeft();
  pushRight();
  delay(10000);
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

int rightServoTransFunc(int incomingDegree) {
  int temp = incomingDegree * (100.0/432.0) + 10;
  return temp;
}

int leftServoTransFunc(int incomingDegree) {
  int temp = incomingDegree*(105.0/432.0) + 5;
  return temp;
}

///////////
// Linear Actuator
////////////////////

void pushLeft() {
    digitalWrite(dir11, LOW);
    digitalWrite(dir12, HIGH);
    analogWrite(en1, 255);
}

void pullLeft() {
    digitalWrite(dir11, HIGH);
    digitalWrite(dir12, LOW);
    analogWrite(en1, 255);
}

void pushRight() {
    digitalWrite(dir21, HIGH);
    digitalWrite(dir22, LOW);
    analogWrite(en2, 255);
}

void pullRight() {
    digitalWrite(dir21, LOW);
    digitalWrite(dir22, HIGH);
    analogWrite(en2, 255);
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
                rotate(-90, 360);
                switchCup();
                transition = 2;
                y += robotLength;
                printLocation();
            }
            if (transition == 2) {
                rotate(-180, 540);
                switchCup();
                transition = 3;
                y += robotLength;
                printLocation();
            }
            if (transition == 3) {
                rotate(-90, 540);
                switchCup();
                transition = 0;
                pattern = 2;
                x -= robotLength;
                printLocation();
            }
        } else {
            rotate(-180, 180);
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
                rotate(90, 0);
                switchCup();
                transition = 2;
                y += robotLength;
                printLocation();
            }
            if (transition == 2) {
                rotate(180, 90);
                switchCup();
                transition = 3;
                y += robotLength;
                printLocation();
            }
            if (transition == 3) {
                rotate(90, 0);
                switchCup();
                transition = 0;
                pattern = 3;
                x += robotLength;
                printLocation();
            }
        } else {
            rotate(-540,540);
            x -= robotLength;
            switchCup();  
        }
    }

    if (pattern == 3) {
        if (x + cupRadius + robotLength > windowWidth) {
            if (transition == 0) {
                right_writePos(180);
                delay(5000);
                transition = 1;
            }
            if (transition == 1) {
                rotate(-90, 360);
                switchCup();
                transition = 2;
                y += robotLength;
                printLocation();
            }
            if (transition == 2) {
                rotate(-180, 540);
                switchCup();
                transition = 3;
                y += robotLength;
                printLocation();
            }
            if (transition == 3) {
                rotate(-90, 540);
                switchCup();
                transition = 0;
                x -= robotLength;
                pattern = 2;
                printLocation();
            }
        } else {
            if (x + cupRadius + 2*robotLength > windowWidth) {
                rotate(540,180);
                x += robotLength;
                switchCup();
            } else {
                rotate(540,0);
                x += robotLength;
                switchCup();
            }
        }
    }
    
  
}

void switchCup() {
  if (pattern == 1 && transition == 0) {
    delay(5000);
  } else if(rightPos == 0 && leftPos == 630) {
    delay(2500);
  }
  else if(pattern == 2 && rightPos == 180 && leftPos == 0) {
    delay(2500);
  }
  else {
    delay(10000);
  }
  if (currMotor == 0) {
      pullLeft();
      pushRight();
      // close the right valve and open the left valve
      digitalWrite(valveR, HIGH);
      digitalWrite(valveL, LOW);
      delay(6000);
  }
  else if (currMotor == 1) {
      pullRight();
      pushLeft();
      // close the right valve and open the left valve
      digitalWrite(valveR, LOW);
      digitalWrite(valveL, HIGH);
      delay(6000);
  }
  delay(5000);
}


