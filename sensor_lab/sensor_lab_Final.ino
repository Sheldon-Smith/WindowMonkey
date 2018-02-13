const int potPin = A0;
const int flexPin = A1;
const int trigPin = 9;
const int echoPin = 10;
int D = 1;
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
    
    D = ultrasound(D);
    
    flex();
    delay(20);
  }
  
}


void flex() {
  
  int flexValue;

  flexValue = analogRead(flexPin);
  Serial.print(.75*flexValue-620);
  //Serial.print("Flex: ");
  Serial.print(",");
  
}
void pot() {

    int potValue;
    
    potValue = analogRead(potPin);

    int realVal;
    realVal = 0.2612*potValue;
  
    //Serial.print("Pot value: ");
    Serial.print(realVal);
    Serial.print(",");
}


int ultrasound(int distance) {

  long duration;
  int distanceN;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distanceN = duration*0.034/2;
  

if (distanceN == 0 || distanceN > 350 || distanceN - distance > 100)
{
   Serial.print(distance);
}

else 
{
  distance = (distanceN + 10*distance) / 11;
  Serial.print(distance);
}
  Serial.println();
  return distance;
}

