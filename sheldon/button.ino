const int startButton = 11;

void startButtonInit() {
  pinMode(11, INPUT_PULLUP);
}

int readStartButton() {
  return digitalRead(startButton);
}

