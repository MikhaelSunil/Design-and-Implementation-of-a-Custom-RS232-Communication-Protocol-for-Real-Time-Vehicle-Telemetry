#include <SoftwareSerial.h>

// Pin definitions for ultrasonic sensors
#define TRIG0 5
#define ECHO0 6
#define TRIG1 7
#define ECHO1 8
#define TRIG2 9
#define ECHO2 10
#define TRIG3 11
#define ECHO3 12

// Define the RX and TX pins for communication with Mega
#define RX_PIN 2
#define TX_PIN 3

// Create a SoftwareSerial instance for communication with Mega
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // RX, TX

void setup() {
  // Start serial communication
  Serial.begin(9600);      // For debugging (USB Serial Monitor)
  mySerial.begin(9600);    // For communication with Arduino Mega

  // Set up ultrasonic sensor pins
  pinMode(TRIG0, OUTPUT);
  pinMode(ECHO0, INPUT);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);
}

void loop() {
  // Array to store distances
  float distances[4];

  // Measure distances from each sensor
  for (int i = 0; i < 4; i++) {
    distances[i] = measureDistance(i);
  }

  // Send distance data to Display Unit (or another Arduino)
  for (int i = 0; i < 4; i++) {
    mySerial.print(distances[i]);  // Send to SoftwareSerial (TX to Mega)
    mySerial.print(" ");
  }
  mySerial.println();  // End line

  delay(500); // Wait before the next measurement
}

float measureDistance(int sensorIndex) {
  long duration;
  float distance;
  int trigPin, echoPin;

  // Assign pins based on sensor index
  switch (sensorIndex) {
    case 0:
      trigPin = TRIG0;
      echoPin = ECHO0;
      break;
    case 1:
      trigPin = TRIG1;
      echoPin = ECHO1;
      break;
    case 2:
      trigPin = TRIG2;
      echoPin = ECHO2;
      break;
    case 3:
      trigPin = TRIG3;
      echoPin = ECHO3;
      break;
  }

  // Send a 10 µs pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pulse duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  distance = (duration * 0.0344) / 2;

  return distance;
}
