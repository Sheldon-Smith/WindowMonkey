const int vacuum_sensor = 6;

void vacuumSensorInit() {
  pinMode(vacuum_sensor, INPUT);
}

int readVacuum() {
  return digitalRead(vacuum_sensor);
}

