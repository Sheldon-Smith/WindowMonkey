const int rValve = 4;
const int lValve = 5;

int leftState = 1;
int rightState = 0;

void solenoidInit() {
  pinMode(rValve, OUTPUT);
  pinMode(lValve, OUTPUT);
}

void leftValve() {
  digitalWrite(lValve, leftState);
  leftState = !leftState;
}

void rightValve() {
  digitalWrite(rValve, rightState);
  rightState = !rightState;
}

