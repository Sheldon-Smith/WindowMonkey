const int right1 = 12;
const int right2 = 13;

const int left1 = 8;
const int left2 = 7;

int rightPos = 100;
int leftPos = 100;

void linearInit() {
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  moveRight(0);
  moveLeft(0);
}

void moveRight(int pos) {
  int time_to_move = 35;
  int newPos = rightPos - pos;
  rightPos = pos;
  if (newPos <= 0) {
    digitalWrite(right1, HIGH);
    digitalWrite(right2, LOW);
    Serial.println(abs(newPos)*time_to_move);
    delay(abs(newPos)*time_to_move);
    digitalWrite(right1, LOW);
    digitalWrite(right2, LOW); 
  } else {
    digitalWrite(right1, LOW);
    digitalWrite(right2, HIGH);
    delay(abs(newPos)*time_to_move*2);
    digitalWrite(right1, LOW);
    digitalWrite(right2, LOW);
  }
}

void moveLeft(int pos) {
  int time_to_move = 35;
  int newPos = leftPos - pos;
  leftPos = pos;
  if (newPos <= 0) {
    digitalWrite(left1, HIGH);
    digitalWrite(left2, LOW);
    delay(abs(newPos)*time_to_move);
    digitalWrite(left1, LOW);
    digitalWrite(left2, LOW); 
  } else {
    digitalWrite(left1, LOW);
    digitalWrite(left2, HIGH);
    delay(abs(newPos)*time_to_move*2);
    digitalWrite(left1, LOW);
    digitalWrite(left2, LOW);
  }
}

