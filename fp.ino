#include <Arduino.h>

const int analogPin = A1;
const int ledPin = 13;
const float referenceVoltage = 3.3; // Reference voltage in volts
const float psiThreshold = 10.0; // Threshold in psi

// Voltage divider constants
const float R1 = 10000.0; // Resistance in ohms connected to Vout
const float R2 = 10000.0; // Resistance in ohms connected to GND

// Butterworth filter variables
const float b0 = 0.0417; // Filter coefficient for current sample
const float b1 = 0.125;  // Filter coefficient for (n-1) sample
const float b2 = 0.125;  // Filter coefficient for (n-2) sample
const float b3 = 0.0417; // Filter coefficient for (n-3) sample
float filteredValue[4] = {0.0}; // Filtered values for last four samples

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(analogPin);

  // Calculate voltage using voltage divider formula
  float voltage = analogValue * (referenceVoltage / 1023.0);
  voltage = voltage * (R1 + R2) / R2;

  // Apply Butterworth low-pass filter
  filteredValue[3] = (b0 * voltage) + (b1 * filteredValue[2]) + (b2 * filteredValue[1]) + (b3 * filteredValue[0]);
  
  // Shift the filtered values
  for (int i = 0; i < 3; i++) {
    filteredValue[i] = filteredValue[i+1];
  }

  // Calculate pressure using FSR calibration curve
  float pressure = (filteredValue[3] - 0.5) * 100.0; // Adjust the formula based on your FSR calibration

  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print(", Voltage: ");
  Serial.print(voltage);
  Serial.print("V, Filtered Voltage: ");
  Serial.print(filteredValue[3]);
  Serial.print("V, Pressure: ");
  Serial.print(pressure);
  Serial.println(" psi");

  if (pressure > psiThreshold) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    delay(3000);                  // Wait for 3 seconds
    digitalWrite(ledPin, LOW);   // Turn off the LED
  }
  
  delay(1000);  // Delay between readings (adjust as needed)
}
