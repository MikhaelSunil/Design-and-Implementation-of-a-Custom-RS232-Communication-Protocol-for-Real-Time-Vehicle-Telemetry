// Pin definitions for sensors
#define FUEL_SENSOR_PIN 5
#define SPEED_SENSOR_PIN 6

// Variables to store sensor data
volatile int fuelPulseCount = 0;
volatile int speedPulseCount = 0;
float fuelConsumption = 0.0;
float speed = 0.0;

// Constants for calculations
#define FUEL_PULSE_TO_LITERS 0.001 // Adjust based on your sensor
#define SPEED_PULSE_TO_KMPH 1.0    // Adjust based on your sensor

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Set up sensor pins
  pinMode(FUEL_SENSOR_PIN, INPUT);
  pinMode(SPEED_SENSOR_PIN, INPUT);

  // Attach interrupts for pulse counting
  attachInterrupt(digitalPinToInterrupt(FUEL_SENSOR_PIN), countFuelPulse, FALLING);
  attachInterrupt(digitalPinToInterrupt(SPEED_SENSOR_PIN), countSpeedPulse, FALLING);
}

void loop() {
  // Calculate fuel consumption and speed
  fuelConsumption = fuelPulseCount * FUEL_PULSE_TO_LITERS;
  speed = speedPulseCount * SPEED_PULSE_TO_KMPH;

  // Send data to Display Unit
  Serial.print(fuelConsumption);
  Serial.print(" ");
  Serial.println(speed);

  // Reset pulse counts
  fuelPulseCount = 0;
  speedPulseCount = 0;

  delay(1000); // Wait before the next calculation
}

void countFuelPulse()
::contentReference[oaicite:0]{index=0}
 
