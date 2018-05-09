

 void serial() {
  
  if (Serial.available() > 0) {
      int input = Serial.parseInt(); 
      if (input == 1) {
        leftValve();
      } else if (input == 2) {
        rightValve();
      } else if (input == 30) {
        moveLeft(0);
      } else if (input == 31) {
        moveLeft(100);
      } else if (input == 32) {
        moveLeft(50);  
      } else if (input == 40) {
        moveRight(0);
      } else if (input == 41) {
        moveRight(100);
      } else if (input == 42) {
        moveRight(50);
      } else if (input == 50) {
        leftServo(0);
      } else if (input == 590) {
        leftServo(90);
      } else if (input == 5180) {
        leftServo(180);
      } else if (input == 5270) {
        leftServo(270);
      } else if (input == 5360) {
        leftServo(360);
      } else if (input == 60) {
        rightServo(0);
      } else if (input == 690) {
        rightServo(90);
      } else if (input == 6180) {
        rightServo(180);
      } else if (input == 6270) {
        rightServo(270);
      } else if (input == 6360) {
        rightServo(360);
      }  
    }
    delay(1000);
    Serial.println("Loop");
 }

