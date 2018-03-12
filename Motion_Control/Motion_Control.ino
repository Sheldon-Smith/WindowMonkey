// Caution: The small gear of the right motor is slippery, which may cause wrong angular postion
#include <Servo.h>
// Servo on the right
Servo myRightServo;
// Servo on the left
Servo myLeftServo;
// Record the angular position of each motor
int rightPos = 0;
int leftPos = 0;
/////////////////////
// Initial Data
/////////////////////
int isInit = 0;
int pattern = 1;
int transition = 0;
float windowWidth = 5, windowHeight = 6;
float robotLength = 0.95;
float cupRadius = 0.125;
float x = 0.0 + robotLength + cupRadius, y = 0.0 + cupRadius;
int currMotor = 0;//0 == right, 1 == left

void setup() {
  // put your setup code here, to run once:
    myRightServo.attach(5);
    myLeftServo.attach(9);
    Serial.begin(9600);
}

void initialize_servos() {
  myRightServo.write(51);
  rightPos = 180;
  myLeftServo.write(48);
  leftPos = 180;
  delay(10000);
//  myRightServo.write(10);
//  rightPos = 0;
//  myLeftServo.write(5);
//  leftPos = 0;
//  delay(10000);
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

void loop() {
    if (isInit == 0) {
      initialize_servos();
      isInit = 1;
    }
  //Testing 
//    right_turn(-180);
//    left_turn(-180);
//    delay(5000);
//    right_turn(540);
//    left_turn(540);
//    delay(10000);// need 10 seconds to turn 540
    hardCodeMotion();
    printLocation();
}

////////////////
// Motion 
////////////////
void rotate(int degreeToTurn, int degreeToWrite) {
    if (currMotor == 0) {
        right_turn(degreeToTurn);
        left_writePos(degreeToWrite);
        currMotor = 1;
    }
    else if (currMotor == 1) {
        left_turn(degreeToTurn);
        right_writePos(degreeToWrite);
        currMotor = 0;
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
        if (x - cupRadius - robotLength < 0) {
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
                rotate(180, 0);
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
                x -= robotLength;
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
            }
            if (transition == 2) {
                rotate(-180, 540);
                switchCup();
                transition = 3;
                y += robotLength;
            }
            if (transition == 3) {
                rotate(-90, 540);
                switchCup();
                transition = 0;
                x -= robotLength;
                pattern = 2;
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
  } else {
    delay(10000);
  }
}


