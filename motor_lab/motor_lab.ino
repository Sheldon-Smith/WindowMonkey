////declare pins
//const int en1 = 11;
//const int dir11 = 12;
//const int dir12 = 13;
//const int en2 = 10;
//const int dir21 = 8;
//const int dir22 = 9;
//
//const int motorEn1 = 2;
//const int motorEn2 = 7;

// PID motor position control.
// Thanks to Brett Beauregard for his nice PID library http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/

//#include <PinChangeInt.h>
//#include <PID_v1.h>
//#define encodPinA1      2                       // Quadrature encoder A pin
//#define encodPinB1      7                       // Quadrature encoder B pin
//#define M1              8                       // PWM outputs to L298N H-Bridge motor driver module
//#define M2              9
//
//double kp = 5 , ki = 1 , kd = 0.01;             // modify for optimal performance
//double input = 0, output = 0, setpoint = 0;
//long temp;
//volatile long encoderPos = 0;
//PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);  // if motor will only run at full speed try 'REVERSE' instead of 'DIRECT'
//
//void setup() {
//  pinMode(encodPinA1, INPUT_PULLUP);                  // quadrature encoder input A
//  pinMode(encodPinB1, INPUT_PULLUP);                  // quadrature encoder input B
//  attachInterrupt(0, encoder, FALLING);               // update encoder position
//  TCCR1B = TCCR1B & 0b11111000 | 1;                   // set 31KHz PWM to prevent motor noise
//  myPID.SetMode(AUTOMATIC);
//  myPID.SetSampleTime(1);
//  myPID.SetOutputLimits(-255, 255);
//  Serial.begin (115200);                              // for debugging
//}
//
//void loop() {
//  setpoint = analogRead(0) * 5;                       // modify to fit motor and encoder characteristics, potmeter connected to A0
//  input = encoderPos ;                                // data from encoder
//  // Serial.println(encoderPos);                      // monitor motor position
//  myPID.Compute();                                    // calculate new output
//  pwmOut(output);                                     // drive L298N H-Bridge module
//}
//
//void pwmOut(int out) {                                // to H-Bridge board
//  if (out > 0) {
//    analogWrite(M1, out);                             // drive motor CW
//    analogWrite(M2, 0);
//  }
//  else {
//    analogWrite(M1, 0);
//    analogWrite(M2, abs(out));                        // drive motor CCW
//  }
//}
//
//void encoder()  {                                     // pulse and direction, direct port reading to save cycles
//  if (PINB & 0b00000001)    encoderPos++;             // if(digitalRead(encodPinB1)==HIGH)   count ++;
//  else                      encoderPos--;             // if(digitalRead(encodPinB1)==LOW)   count --;
//}





////////////////////////////
//const byte pin_a = A1;   //for encoder pulse A
//const byte pin_b = A2;   //for encoder pulse B
//const byte pin_fwd = 8; //for H-bridge: run motor forward
//const byte pin_bwd = 9; //for H-bridge: run motor backward
//const byte pin_pwm = 10; //for H-bridge: motor speed
int encoder = 0;
int m_direction = 0;
int sv_speed = 100;     //this value is 0~255
double pv_speed = 0;
int timer1_counter; //for timer
//
//void setup() {
//  pinMode(pin_a,INPUT_PULLUP);
//  pinMode(pin_b,INPUT_PULLUP);
//  pinMode(pin_fwd,OUTPUT);
//  pinMode(pin_bwd,OUTPUT);
//  pinMode(pin_pwm,OUTPUT);
////  attachInterrupt(digitalPinToInterrupt(pin_a), detect_a, RISING);
//  // start serial port at 9600 bps:
//  Serial.begin(9600);
////  //--------------------------timer setup
////  noInterrupts();           // disable all interrupts
////  TCCR1A = 0;
////  TCCR1B = 0;
////  timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
////
////  TCNT1 = timer1_counter;   // preload timer
////  TCCR1B |= (1 << CS12);    // 256 prescaler
////  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
////  interrupts();             // enable all interrupts
////  //--------------------------timer setup
////
////  while (!Serial) {
////    ; // wait for serial port to connect. Needed for native USB port only
////  }
//
//}
//void loop() {
//    digitalWrite(pin_fwd,LOW);        //run motor backward
//    digitalWrite(pin_bwd,HIGH);        //run motor backward
//    analogWrite(pin_pwm,sv_speed);  //set motor speed
//    delay(1000);
//    digitalWrite(pin_fwd,LOW);        //run motor backward
//    digitalWrite(pin_bwd,LOW);        //run motor backward
//    analogWrite(pin_pwm,0);  //set motor speed
//    delay(1000);
//    Serial.print("speed (rpm) is : ");
//    Serial.print(pv_speed);         //Print speed value to Computer
//    Serial.print("  --  ");
//    Serial.print("Direction = ");
//    Serial.println(m_direction);
//    delay(500);
//}
//
//void detect_a() {
//  encoder+=1;
//  m_direction = digitalRead(pin_b);
//}
//ISR(TIMER1_OVF_vect)        // interrupt service routine - tick every 0.5sec
//{
//  TCNT1 = timer1_counter;   // set timer
//  pv_speed = 60*(60/200.0)/0.5;
////  encoder=0;
//}
////////////////////////////////////////////
////setup all pins as outputs
//void setup(){
//  pinMode(en1, OUTPUT);
//  pinMode(dir11, OUTPUT);
//  pinMode(dir12, OUTPUT);
//  pinMode(en2, OUTPUT);
//  pinMode(dir21, OUTPUT);
//  pinMode(dir22, OUTPUT);
//  Serial.begin(9600);
//}
// 
//void loop(){
//  readEn();
// //spin motors one way at half speed
////  analogWrite(en1, 0);
////  digitalWrite(dir11, HIGH);
////  digitalWrite(dir12, LOW);
//  analogWrite(en2, 128);
//  digitalWrite(dir21, HIGH);
//  digitalWrite(dir22, LOW);
//  delay(1000);
//  readEn();
//// //stall motors
////  digitalWrite(en1, HIGH);
////  digitalWrite(dir11, HIGH);
////  digitalWrite(dir12, HIGH);
//  digitalWrite(en2, HIGH);
//  digitalWrite(dir21, LOW);
//  digitalWrite(dir22, LOW);
//  delay(1000);
//  readEn();
//// //turn motors the other way at 3/4 speed
////  analogWrite(en1, 192);
////  digitalWrite(dir11, LOW);
////  digitalWrite(dir12, HIGH);
//  analogWrite(en2, 192);
//  digitalWrite(dir21, LOW);
//  digitalWrite(dir22, HIGH);
//  delay(1000);
//  readEn();
//// //turn motors off
//  digitalWrite(en1, LOW);
//  digitalWrite(en2, LOW);
//  delay(1000);
//  readEn();
//}
//
//void readEn() {
//  int encoder1 = 0;
//  encoder1 = digitalRead(motorEn1);
//  Serial.print(encoder1);
//  Serial.print(' ');
//
//  int encoder2 = 0;
//  encoder2 = digitalRead(motorEn2);
//  Serial.print(encoder2);
//  Serial.println();
//}
////declare pins
//#include <Servo.h>
////////////////
//// Servo Motor
////////////////
//Servo myservo;
//int pos = 0; 
//
/////////////////////
//// Stepper Motor
/////////////////////
//const int stepPin = 3; 
//const int dirPin = 4; 
//
/////////////////////
//// DC Motor
/////////////////////
//const int en1 = 11;
//const int dir11 = 12;
//const int dir12 = 13;
//const int en2 = 10;
//const int dir21 = 8;
//const int dir22 = 9;
// 
////setup all pins as outputs
//void setup(){
//  ////////////////////
//  // Servo Motor
//  ///////////////////
//  myservo.attach(5);
//  
//  ////////////////////
//  // Stepper Motor
//  ////////////////////
//  pinMode(stepPin,OUTPUT); 
//  pinMode(dirPin,OUTPUT);
//
//  ///////////////////
//  // DC Motor
//  ///////////////////
//  pinMode(en1, OUTPUT);
//  pinMode(dir11, OUTPUT);
//  pinMode(dir12, OUTPUT);
//  pinMode(en2, OUTPUT);
//  pinMode(dir21, OUTPUT);
//  pinMode(dir22, OUTPUT);
//}
// 
//void loop(){
//  /////////////////////
//  // Servo Motor
//  /////////////////////
////  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
////    // in steps of 1 degree
////    myservo.write(pos);              // tell servo to go to position in variable 'pos'
////    delay(15);                       // waits 15ms for the servo to reach the position
////  }
////  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
////    myservo.write(pos);              // tell servo to go to position in variable 'pos'
////    delay(15);                       // waits 15ms for the servo to reach the position
////  }
////  
//  ////////////////////
//  // Stepper Motor
//  ////////////////////
//  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
//  // Makes 200 pulses for making one full cycle rotation
//  for(int x = 0; x < 200; x++) {
//    digitalWrite(stepPin,HIGH); 
//    delayMicroseconds(500); 
//    digitalWrite(stepPin,LOW); 
//    delayMicroseconds(500); 
//  }
//  delay(1000); // One second delay
//  Serial.print(stepPin);
//  digitalWrite(dirPin,LOW); //Changes the rotations direction
//  // Makes 400 pulses for making two full cycle rotation
//  for(int x = 0; x < 400; x++) {
//    digitalWrite(stepPin,HIGH);
//    delayMicroseconds(500);
//    digitalWrite(stepPin,LOW);
//    delayMicroseconds(500);
//  }
//  delay(1000);
//
//  ///////////////////
//  // DC Motor
//  ///////////////////
//  //spin motors one way at half speed
//  analogWrite(en1, 128);
//  digitalWrite(dir11, HIGH);
//  digitalWrite(dir12, LOW);
//  analogWrite(en2, 128);
//  digitalWrite(dir21, HIGH);
//  digitalWrite(dir22, LOW);
//  delay(100);
//
//// //stall motors
////  digitalWrite(en1, HIGH);
////  digitalWrite(dir11, HIGH);
////  digitalWrite(dir12, HIGH);
////  digitalWrite(en2, HIGH);
////  digitalWrite(dir21, LOW);
////  digitalWrite(dir22, LOW);
////  delay(100);
//// //turn motors the other way at 3/4 speed
////  analogWrite(en1, 192);
////  digitalWrite(dir11, HIGH);
////  digitalWrite(dir12, LOW);
////  analogWrite(en2, 192);
////  digitalWrite(dir21, HIGH);
////  digitalWrite(dir22, LOW);
////  delay(100);
//// //turn motors off
//  digitalWrite(en1, LOW);
//  digitalWrite(en2, LOW);
//  delay(100);
//}

