
extern int rightAngle = 180;
extern int leftAngle = 180;
extern int activeServo = 0; //Right = 0 Left = 1
extern int initMovement = 0;
extern int barrierDetected = 0; // Bitmask
extern int wallDetected = 0;
extern int activeSide = 0; // Front = 0 Back = 1 Front is the side not facing the barrier on init

void setup() {
  servoInit();
  linearInit();
  solenoidInit();
  startButtonInit();
  leftServo(180);
  rightServo(180);
  moveRight(50);
  delay(5000);
  moveRight(0);
  Serial.begin(9600);

}

void loop() {

  fsm();
  //serial();
}

int moves = 0;

void fsm() {
  
//  Serial.println(initMovement);
//  if (!initMovement) {
//    init_state();
//  } else {

  // checkBarrier();
  
    if (activeServo == 0) { // Right servo
      if (activeSide) { //Front side
        if(rightAngle != 360) {
          movement();
        } else {
          delay(3000);
          transition();
          moves += 1;
        }
      } else { //Back side
        if(rightAngle != 0) {
          movement();
        } else {
          delay(3000);
          transition();
          moves += 1;
        }
      }
    } else { // Left servo
      if (activeSide) { //Front side
        if (leftAngle != 0 && barrierDetected != B111 && wallDetected != B111) {
          movement();
        } else {
          delay(3000);
          transition();
          moves += 1;
        }
      } else { // Back side
        if (leftAngle != 360) {
          movement();
        } else {
          delay(3000);
          transition();
          moves += 1;
        }
      }
    }
}





