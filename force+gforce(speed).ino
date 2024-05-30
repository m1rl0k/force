#include <Arduino.h>

// Constants
const int fsrPin = A0; // Analog pin connected to FSR
const int ledPinR = 9; // LED red pin for debugging
const int ledPinG = 10; // LED green pin for debugging
const int ledPinB = 11; // LED blue pin for debugging

// Variables
uint16_t hits = 0;
float smoothedVal = 0;
const int samples = 10; // Number of samples for smoothing

void setup() {
  Serial.begin(9600);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  // Initialize BLE device here (if applicable)
}

void loop() {
  uint16_t fsrReading = analogRead(fsrPin);
  float sensorVal = analogRead(fsrReading);
  smoothedVal = smoothedVal + ((sensorVal - smoothedVal) / samples);

  Serial.print("Analog: ");
  Serial.print(fsrReading);
  Serial.print(" Smoothed Analog: ");
  Serial.println(smoothedVal, DEC);

  // Calculate voltage
  float voltage = sensorVal * (3.5 / 1023.0);
  Serial.print("Voltage: ");
  Serial.println(voltage, DEC);

  // Calculate resistance
  float resistance = ((9200 * sensorVal) / (1023.0 - sensorVal));
  Serial.print("Resistance: ");
  Serial.println(resistance, DEC);

  // Calculate force and conductance
  float fsrConductance = 1000000.0 / resistance;
  Serial.print("Conductance in microMhos: ");
  Serial.println(fsrConductance);

  float fsrForce;
  if (fsrConductance <= 1000) {
    fsrForce = fsrConductance / 80.0;
  } else {
    fsrForce = (fsrConductance - 1000) / 30.0;
  }
  Serial.print("Force in Newtons: ");
  Serial.println(fsrForce);

  // Update LED based on force
  updateLed(fsrForce);

  // Detect hits based on force threshold
  if (detectHit(fsrForce)) {
    hits++;
    Serial.print("Hits: ");
    Serial.println(hits);
  }

  delay(100);
}

void updateLed(float force) {
  if (force > 20) {
    setLedColor(255, 0, 0); // Red
  } else if (force > 1) {
    setLedColor(0, 0, 255); // Blue
  } else if (force > 0) {
    setLedColor(0, 255, 0); // Green
  } else {
    setLedColor(0, 0, 0); // Off
  }
}

void setLedColor(uint8_t r, uint8_t g, uint8_t b) {
  analogWrite(ledPinR, r);
  analogWrite(ledPinG, g);
  analogWrite(ledPinB, b);
}

bool detectHit(float force) {
  static float lastForce = 0;
  static unsigned long lastHitTime = 0;
  const unsigned long debounceTime = 200; // 200 ms debounce time

  unsigned long currentTime = millis();
  if (force > 5 && (currentTime - lastHitTime > debounceTime)) {
    lastHitTime = currentTime;
    lastForce = force;
    return true;
  }
  lastForce = force;
  return false;
}
