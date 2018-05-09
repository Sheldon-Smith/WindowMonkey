#include <Servo.h>

Servo right;
Servo left;

void servoInit() {
  right.attach(10);
  left.attach(9);
  leftServo(leftAngle);
  rightServo(rightAngle);
}
// Max milli is 2250
void rightServo(int angle) {
  float coeff = 4.58; // Max is 2250 min is 600
  int milli = 600 + angle*coeff;
  if (milli > 2250) {
    right.writeMicroseconds(2250);
  } else if (milli < 600) {
    right.writeMicroseconds(600); 
  } else {
    right.writeMicroseconds(milli);
  }
}

// Max milli is 2200
void leftServo(int angle) {
  float coeff = 4.44;
    int milli = 600 + angle*coeff;
  if (milli > 2200) {
    left.writeMicroseconds(2200);
  } else if (milli < 600) {
    left.writeMicroseconds(600); 
  } else {
    left.writeMicroseconds(milli);
  } 
}
