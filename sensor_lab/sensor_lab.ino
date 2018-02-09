const int potPin = A0;
const int flexPin = A1;
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  while(1) {
    pot();
    ultrasound();
    flex();
    Serial.println();
    delay(1000);
  }
  
}


void flex() {
  
  int flexValue;

  flexValue = analogRead(flexPin);

  Serial.print("Flex: ");
  Serial.println(flexValue);
}
void pot() {

    int potValue;
    
    potValue = analogRead(potPin);
    Serial.print("Pot value: ");
    Serial.println(potValue);
}


void ultrasound() {

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
}

