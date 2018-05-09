

void transition() {
  if (activeServo == 0) { //Right Side is active
    moveLeft(50);
    leftValve();
    delay(2000);
    rightValve();
    moveLeft(0);
    rightServo(180);
    rightAngle = 180;
    activeServo = !activeServo;
    activeSide = !activeSide;
  } else { //Left side is active
    moveRight(50);
    rightValve();
    delay(2000);
    leftValve();
    moveRight(0);
    leftServo(180);
    leftAngle = 180;
    activeServo = !activeServo;
    activeSide = !activeSide;
  }
}

