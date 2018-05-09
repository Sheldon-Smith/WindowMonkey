#define THRESH 10

void init_state() {
  if (readStartButton()) {
    initMovement = 1;
  }
}

void movement() {

  if(activeServo == 0) { // Right
    if(activeSide) {
      rightAngle += 5;
      rightServo(rightAngle);
    } else {
      rightAngle -= 5;
      rightServo(rightAngle);
    }
  } else { // Left
    if(activeSide) {
      leftAngle -= 5;
      leftServo(leftAngle);
    } else {
      leftAngle += 5;
      leftServo(leftAngle);
    }
  }
}

void checkBarrier() {

  int left_dist = 0;
  int right_dist = 0;

  if(activeSide) { // Front
    left_dist = frontLeftDist();
    right_dist = frontRightDist();
  } else { // Back
    left_dist = backLeftDist();
    right_dist = backRightDist();
  }

  if (left_dist < THRESH && right_dist < THRESH) {
    wallDetected = wallDetected << 1;
    wallDetected += 1;
  } else if (left_dist < THRESH || right_dist < THRESH) {
    barrierDetected = barrierDetected << 1;
    barrierDetected += 1;
  } else {
    barrierDetected = 0;
    wallDetected = 0;
  }
}

