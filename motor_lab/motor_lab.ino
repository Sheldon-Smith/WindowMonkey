#include <Servo.h>
#include <A4988.h>
#include <BasicStepperDriver.h>
#include <DRV8825.h>
#include <DRV8834.h>
#include <DRV8880.h>
#include <MultiDriver.h>
#include <SyncDriver.h>

const int encoderPinA = 2;
const int encoderPinB = 6;
volatile int encoderPos = 0;

const int potPin = A0;
const int flexPin = A1;
const int trigPin = 8;
const int echoPin = 7;
const int switchPin = A2;
const int stepPin = 3; 
const int dirPin = 4; 
const int motor_steps = 200;
A4988 stepper(motor_steps, dirPin, stepPin);
const int en1 = 11;
const int dir11 = 12;
const int dir12 = 13;
Servo myservo;
int pos = 0;


// Encoder interrupt
void doEncoder() {
  /* If pinA and pinB are both high or both low, it is spinning
     forward. If they're different, it's going backward.

     For more information on speeding up this process, see
     [Reference/PortManipulation], specifically the PIND register.
  */
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    encoderPos++;
  } else {
    encoderPos--;
  }
}

void servo_init() {
 myservo.attach(5);
}

void encoder_init() {
  
  pinMode(encoderPinA, INPUT);
  digitalWrite(encoderPinA, HIGH); 
  pinMode(encoderPinB, INPUT); 
  digitalWrite(encoderPinB, HIGH);
  
  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoder, CHANGE);
}

void switch_init() {
  pinMode(switchPin, INPUT);
}

void stepper_init() {
  stepper.begin(10,1);
}

void motor_init() {
  pinMode(en1, OUTPUT);
  pinMode(dir11, OUTPUT);
  pinMode(dir12, OUTPUT);
}

void ultrasound_init() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void setup(){

  servo_init();
  encoder_init();
  switch_init();
  stepper_init();
  motor_init();
  ultrasound_init();

  Serial.begin(9600);

}

void writeMotor(char motor, int val)
{
  if (motor == 'r'){
    move_servo(val);
    return;
  }
  if (motor == 'd'){
    setDCMotorSpeed(val);
    return;
  }
  if (motor == 's'){
    move_stepper(val);
    return;
  }
  if (motor == 'p') {
    motor_PID(val);
    return;
  }
    return;
}

void move_servo(int pos) {
  myservo.write(pos);
  delay(15); //Delay to allow time for movement
}

void move_stepper(int pos) {
  stepper.rotate(pos);
}

int previousFlexValue = NULL;

void flex_stepper_control() {
  int flexValue = flex();
  if (previousFlexValue == NULL) {
    previousFlexValue = flexValue;
    move_stepper(flexValue);
  }

  else if(abs(previousFlexValue - flexValue) > 20) {
    move_stepper(flexValue);
  }

  previousFlexValue = flexValue;
}

int flex() {
  
  int flexValue;

  flexValue = analogRead(flexPin);
  flexValue = .75*flexValue-620-25;

  return flexValue;
}

void pot_servo_control() {
  int potValue = pot();
  move_servo(potValue*2/3);
}

int pot() {

    int potValue;
    
    potValue = analogRead(potPin);
    potValue = 0.2612*potValue;
    
    return potValue;
}

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; 
int lastButtonState = LOW;
int buttonState;

int read_switch() {

  int reading = digitalRead(switchPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState)
      buttonState = reading;
  }
  lastButtonState = reading;

  return buttonState;
  
}

void ultrasound_motor_control() {
  int distance = ultrasound();
  int motor_speed = distance*10;

  if (motor_speed > 255) {
    motor_speed = 255;
  }

  analogWrite(en1, motor_speed);
  digitalWrite(dir11, HIGH);
  digitalWrite(dir12, LOW);
}

int ultrasound() {

  long duration;
  int distance;
  int motor_speed = 0;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration*0.034/2;

  return distance;
}

void setDCMotorSpeed(int motor_speed) {

  motor_speed *= 2.5;
  
  if (motor_speed >= 0) {
    analogWrite(en1, motor_speed);
    digitalWrite(dir11, HIGH);
    digitalWrite(dir12, LOW);
  }
  if (motor_speed < 0) {
    analogWrite(en1, motor_speed);
    digitalWrite(dir11, LOW);
    digitalWrite(dir12, HIGH);
  }
}

void turn_motor(int distance, int output) {
  int motor_speed = output*2.5;
  if(distance > 0) {
    analogWrite(en1, motor_speed);
    digitalWrite(dir11, HIGH);
    digitalWrite(dir12, LOW);
  }
  else if(distance < 0) {
    analogWrite(en1, motor_speed);
    digitalWrite(dir11, LOW);
    digitalWrite(dir12, HIGH);
  }
  else {
    analogWrite(en1, 0);
    digitalWrite(dir11, LOW);
    digitalWrite(dir12, HIGH);
  }
  
}
int oldDistance = 0;

void motor_PID(int targetPos) {

  int distance = targetPos - encoderPos;

  int kterm = distance * 2; //kp
  int iterm = 2 * (distance - oldDistance); //ki

  int output = abs(kterm + iterm);

  if (output > 100) {
    output = 100;
  }

  if (output <= 10) {
    output = 0;
  }

  oldDistance = distance;

  turn_motor(distance, output);

}

int motorPos = 0;
int prevSwitchState = LOW;
void loop(){

<<<<<<< HEAD
  if(read_switch()) {
    encoderPos = 0;
=======
  int switchState = readSwitch();
  if(switchState) {
    if (prevSwitchState != switchState) {
      encoderPos = 0;
    }
    prevSwitchState = switchState;
>>>>>>> 2e94a403176116eb15179b606e62896d6fad0219
    if (Serial.available()) {
      char motorSpecifier = Serial.read();
      int motorPos = Serial.parseInt();
      writeMotor(motorSpecifier, motorPos);
      }
  } else {
    flex_stepper_control();
    pot_servo_control();
    ultrasound_motor_control();
  }
  Serial.print(pot()); Serial.print(", ");
  Serial.print(ultrasound()); Serial.print(", ");
  Serial.println(flex());
  delay(500);
}
