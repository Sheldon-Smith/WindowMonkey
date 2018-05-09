#include <NewPing.h>

const int trigPin = A5;
const int echoPin = A4;
const int ledPin = 13;
const int BARRIER_DIST = 5; //5 cm
const int WAIT_DETECT = 25; //25 ms
const int MAX_DIST = 200;

NewPing sonar(trigPin, echoPin, MAX_DIST);

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
  unsigned int uS = sonar.ping_cm();
  Serial.print(uS);
  Serial.println("cm");
}

void process_ult_distance() {

  int distance = ultrasound();
  int check_loops = 2;
  int i = 0;
  int detected = 0;

  while(i < check_loops) {
    if(distance < BARRIER_DIST) {
      detected = 1;
      i++;
      delay(WAIT_DETECT);
      distance = ultrasound();
    } else {
      detected = 0;
      break;
    }
  }

  if(detected) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

int ultrasound() {

  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration*0.034/2;
  
  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}
