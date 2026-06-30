#include <Joystick.h>

const int trigPin = 2;
const int echoPin = 3;

Joystick_ Joystick;

void setup() {
  Serial.begin(9600);
  Joystick.begin();
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Read sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  
  // Constrain
  if (distance > 400) distance = 400;
  if (distance < 2) distance = 2;
  
  // Map to joystick (0-255)
  // Close = 255, Far = 0
  int axisValue = map(distance, 2, 400, 255, 0);
  
  // Send as gamepad
  Joystick.setXAxis(axisValue);
  Joystick.sendState();
  
  // Debug
  Serial.print("Dist: ");
  Serial.print(distance);
  Serial.print(" cm\tAxis: ");
  Serial.println(axisValue);
  
  delay(50);
}
