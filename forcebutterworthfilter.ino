#include <Wire.h>
#include <Arduino.h>

class ButterworthFilter {
public:
  ButterworthFilter() {
    v[0] = 0;
    v[1] = 0;
  }
  
  short step(short x) {
    v[0] = v[1];
    long tmp = ((((x * 4089446L) >> 6)    // = ( 3.0468747091e-2 * x)
                + ((v[0] * 3938714L) >> 1) // + ( 0.9390625058 * v[0])
               ) + 1048576) >> 21;         // round and downshift fixed point /2097152

    v[1] = (short)tmp;
    return (short)(v[0] + v[1]);
  }

private:
  short v[2];
};

const int fsrPin = A0;  // Analog pin connected to FSR
const int ledPinR = 9;  // LED red pin for debugging
const int ledPinG = 10; // LED green pin for debugging
const int ledPinB = 11; // LED blue pin for debugging

ButterworthFilter butterworthFilter;

int smoothedVal = 0;
const int samples = 10; // Number of samples for smoothing

int hits = 0;
const int numReadings = 100;
int readings[numReadings]; // the readings from the analog input
int index = 0;             // the index of the current reading
int total = 0;             // the running total
int average = 0;

void setup() {
  Serial.begin(9600);
  pinMode(fsrPin, INPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);

  // Initialize readings array
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  int fsrReading = analogRead(fsrPin);
  int filteredReading = butterworthFilter.step(fsrReading);

  // Update smoothed value
  smoothedVal = smoothedVal + ((filteredReading - smoothedVal) / samples);

  // Update running average
  total -= readings[index];
  readings[index] = smoothedVal;
  total += readings[index];
  index = (index + 1) % numReadings;
  average = total / numReadings;

  Serial.print("Analog: ");
  Serial.print(fsrReading);
  Serial.print(" Filtered Analog: ");
  Serial.print(filteredReading);
  Serial.print(" Smoothed Analog: ");
  Serial.println(average);

  // Calculate voltage
  float voltage = average * (3.3 / 1023.0);
  Serial.print("Voltage: ");
  Serial.println(voltage, DEC);

  // Calculate resistance
  float resistance = ((1023.0 - average) * 10000) / average;
  Serial.print("Resistance: ");
  Serial.println(resistance, DEC);

  // Calculate force
  float fsrConductance = 1000000.0 / resistance;
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
