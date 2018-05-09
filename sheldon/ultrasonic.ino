#include <NewPing.h>
#include <Filter.h>

// Use 10 data points for the filters
Moving_average maFrontLeft(10);
Moving_average maBackLeft(10);
Moving_average maFrontRight(10);
Moving_average maBackRight(10);

NewPing frontLeft(A4, A5);
NewPing backLeft(A3, A2);
NewPing backRight(2, 3);
NewPing frontRight(A0, A1);

int frontLeftDist() {
  int dist = frontLeft.ping_in();
  return maFrontLeft.filter(dist);
}

int backLeftDist() {
  int dist = backLeft.ping_in();
  return maBackLeft.filter(dist);
}

int frontRightDist() {
  int dist = frontRight.ping_in();
  return maFrontRight.filter(dist);
}

int backRightDist() {
  int dist = backRight.ping_in();
  return maBackRight.filter(dist);
}

void ultrasonic_read() {
  Serial.print("Front left: ");
  Serial.println(frontLeftDist());
  delay(500);
  Serial.print("Front right: ");
  Serial.println(frontRightDist());
  delay(500);
  Serial.print("Back right: ");
  Serial.println(backRightDist());
  delay(500);
  Serial.print("Back left: ");
  Serial.println(backLeftDist());
  delay(500);
  Serial.println("Loop");
}

