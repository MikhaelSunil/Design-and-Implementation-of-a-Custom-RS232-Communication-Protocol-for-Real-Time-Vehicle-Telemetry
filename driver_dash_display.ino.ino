#include <LiquidCrystal.h>

// Define LCD pins
#define LCD_RS 8
#define LCD_E1 9
#define LCD_E2 10
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

// Define LED and Sound pins
#define DO_LED 13
#define DO_SOUND 12

// Initialize two LiquidCrystal instances
LiquidCrystal lcdTop(LCD_RS, LCD_E1, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
LiquidCrystal lcdBottom(LCD_RS, LCD_E2, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Variables to store incoming data
String distanceData = "";
String fuelData = "";

void setup() {
  // Initialize serial communications
  Serial.begin(9600);    // USB Serial Monitor
  Serial1.begin(9600);   // Serial1 for Distance Sensor Unit
  Serial2.begin(9600);   // Serial2 for Fuel and Speed Sensor Unit

  // Initialize LCDs
  lcdTop.begin(40, 2);
  lcdBottom.begin(40, 2);

  // Display initialization message
  lcdTop.setCursor(0, 0);
  lcdTop.print("Initializing...");
  lcdBottom.setCursor(0, 0);
  lcdBottom.print("Please wait...");
  delay(20);

  // Clear the display
  cleartp();
  clearbt();

  // Initialize LED and Sound pins
  pinMode(DO_LED, OUTPUT);
  pinMode(DO_SOUND, OUTPUT);
  digitalWrite(DO_LED, LOW);
  digitalWrite(DO_SOUND, LOW);
}

void loop() {
  // Read from Serial1 (Distance Sensor Unit)
  if (Serial1.available()) {
    distanceData = Serial1.readStringUntil('\n');
    distanceData.trim(); // Remove any trailing newline or spaces
    displayDistanceData(distanceData);
  }

  // Read from Serial2 (Fuel and Speed Sensor Unit)
  if (Serial2.available()) {
    fuelData = Serial2.readStringUntil('\n');
    fuelData.trim(); // Remove any trailing newline or spaces
    displayFuelData(fuelData);
  }
}

// Function to display distance data
void displayDistanceData(String data) {
  // Expected format: D0,D1,D2,D3,Min
  cleartp();
  lcdTop.setCursor(0, 0);
  lcdTop.print("Distances: ");
  lcdTop.print(data);

  // Parse minimum distance
  int lastComma = data.lastIndexOf(',');
  if (lastComma != -1 && lastComma < data.length() - 1) {
    String minDistStr = data.substring(lastComma + 1);
    int minDist = minDistStr.toInt();

    // Display minimum distance
    lcdTop.setCursor(0, 1);
    lcdTop.print("Min Distance: ");
    lcdTop.print(minDist);
    lcdTop.print(" cm");

    // If minimum distance is less than 30 cm, turn on LED and Sound
    if (minDist < 30) {
      digitalWrite(DO_LED, HIGH);
      digitalWrite(DO_SOUND, HIGH);
    } else {
      digitalWrite(DO_LED, LOW);
      digitalWrite(DO_SOUND, LOW);
    }
  }

  // Also print to Serial Monitor
  Serial.println("Distance Data:");
  Serial.println(data);
}

// Function to display fuel data
void displayFuelData(String data) {
  // Expected format: Fuel:0.001L,Speed:60.00km/h,Distance:0.02km,AvgFuel:5.00L/100km
  clearbt();
  lcdBottom.setCursor(0, 0);
  lcdBottom.print("Fuel Data: ");
  lcdBottom.print(data);

  // Optionally, parse and display each parameter on separate lines
  // For brevity, displaying the entire string as is

  // Also print to Serial Monitor
  Serial.println("Fuel Data:");
  Serial.println(data);
}

void cleartp() {
  for (int row = 0; row < 2; row++) {
    lcdTop.setCursor(0, row);
    lcdTop.print("                                        "); // 40 spaces
  }
}

void clearbt() {
  for (int row = 0; row < 2; row++) {
    lcdBottom.setCursor(0, row);
    lcdBottom.print("                                        "); // 40 spaces
  }
}
