#include <Arduino.h>

const int analogPin = A0;  // FSR analog pin
const float VCC = 5.0;     // Supply voltage in volts
const int calibrationReadings = 100;  // Number of calibration readings
const float forceRange = 10.0; // Maximum force value in Newtons

int fsrMin = 1023;    // Minimum FSR reading
int fsrMax = 0;       // Maximum FSR reading

void setup() {
  Serial.begin(9600);

  // Perform self-calibration
  calibrateFSR();
}

void loop() {
  int fsrReading = analogRead(analogPin);

  // Calculate force based on calibrated readings
  int fsrRange = fsrMax - fsrMin;
  float force = (fsrReading - fsrMin) * forceRange / fsrRange;

  Serial.print("FSR Reading: ");
  Serial.print(fsrReading);
  Serial.print(", Force: ");
  Serial.print(force);
  Serial.println(" N");

  delay(1000);
}

void calibrateFSR() {
  Serial.print("Calibrating FSR...");

  for (int i = 0; i < calibrationReadings; ++i) {
    int fsrReading = analogRead(analogPin);

    if (fsrReading < fsrMin) {
      fsrMin = fsrReading;
    }
    if (fsrReading > fsrMax) {
      fsrMax = fsrReading;
    }

    delay(10);
  }

  Serial.println("Calibration complete");
}
