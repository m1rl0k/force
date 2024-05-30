These files are based on my research on force measurement in newtons using Arduino and Piezo Electric fabric known as Eeonyx. The project involved hand-crafting materials with silver threads as wires, connecting both analog and digital sensors to the Arduino. Using smoothing, buffering, and a Butterworth low-pass filter written in C++, I processed the sensor data. Additionally, a Processing sketch was used to simulate the interaction in a real-time 3D representation, bridging the physical and software models. The Arduino sketches were updated over-the-air (OTA) using Bluetooth 4.1, provided by Texas Instruments. All sensors were connected to either "A1" for analog or "D1" for digital pins.

The force voltage was calibrated to match the actual battery, and the resistance was dynamically calculated to provide accurate newton readings on the fabric. This adjustment accounted for changes in resistance as the material moved.

When the force in newtons reached certain thresholds, the system counted them as individual hits (physical impacts on the material). These were indicated by red, yellow, or green LEDs, depending on the force magnitude. Additionally, a piezo-buzzer emitted a sound, and the numerical force values were transmitted via Bluetooth to both the 3D models in Processing and an iOS app written in Swift. The device handled all these functions seamlessly within the same loop.

A 9DOF accelerometer, magnetometer, and gyroscope were used to embed absolute orientation scientifically, matching real-world positioning in motion. The serial output was mapped to a 3D Processing sketch, providing a visual display.

This research, spanning over five years with the ATmega32 processor and various conductive fabrics, successfully demonstrated the use of a Butterworth low-pass filter at the beginning of the C++ loop, along with various smoothing and buffering techniques for real-time data transmission via Bluetooth. All theoretical questions posed by the author were met, marking the research as a success.


# Force Measurement and Hit Detection System

## Overview

This Arduino sketch measures force applied to a piezoelectric sensor, processes the readings using a Butterworth filter and a smoothing technique, and indicates the level of force using an RGB LED. Additionally, it detects hits based on force thresholds and maintains a hit count.

## Components

- **Force Sensitive Resistor (FSR)** connected to analog pin A0
- **RGB LED** connected to pins 9 (Red), 10 (Green), and 11 (Blue)
- **Arduino Board**
- **Butterworth Filter** for signal processing

## Code Explanation

### Libraries and Class Definitions

The code starts by including necessary libraries and defining the `ButterworthFilter` class.

```cpp
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
    long tmp = ((((x * 4089446L) >> 6)
                + ((v[0] * 3938714L) >> 1)
               ) + 1048576) >> 21;

    v[1] = (short)tmp;
    return (short)(v[0] + v[1]);
  }

private:
  short v[2];
};
```
Global Variables and Constants
Define the pin connections, create an instance of the ButterworthFilter, and declare variables for sensor readings and processing.

```cpp
const int fsrPin = A0;
const int ledPinR = 9;
const int ledPinG = 10;
const int ledPinB = 11;

ButterworthFilter butterworthFilter;

int smoothedVal = 0;
const int samples = 10;

int hits = 0;
const int numReadings = 100;
int readings[numReadings];
int index = 0;
int total = 0;
int average = 0;
Setup Function
Initialize serial communication, pin modes, and the readings array.

cpp
Copy code
void setup() {
  Serial.begin(9600);
  pinMode(fsrPin, INPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
```
Loop Function
Sensor Reading and Filtering
Read the analog value from the FSR and apply the Butterworth filter.

```cpp
void loop() {
  int fsrReading = analogRead(fsrPin);
  int filteredReading = butterworthFilter.step(fsrReading);
```
The Butterworth filter is introduced at the beginning of the loop to process the raw analog sensor data. This filter helps in reducing the noise from the sensor readings, providing a cleaner signal for further processing.

Smoothing Technique
Smooth the filtered readings using an averaging technique.

```cpp
  smoothedVal = smoothedVal + ((filteredReading - smoothedVal) / samples);
  total -= readings[index];
  readings[index] = smoothedVal;
  total += readings[index];
  index = (index + 1) % numReadings;
  average = total / numReadings;
```
Display Sensor Values
Print the sensor values, voltage, and resistance.

```cpp
  Serial.print("Analog: ");
  Serial.print(fsrReading);
  Serial.print(" Filtered Analog: ");
  Serial.print(filteredReading);
  Serial.print(" Smoothed Analog: ");
  Serial.println(average);

  float voltage = average * (3.3 / 1023.0);
  Serial.print("Voltage: ");
  Serial.println(voltage, DEC);

  float resistance = ((1023.0 - average) * 10000) / average;
  Serial.print("Resistance: ");
  Serial.println(resistance, DEC);
```
Calculate Force
Calculate the force based on the sensor readings.

```
  float fsrConductance = 1000000.0 / resistance;
  float fsrForce;
  if (fsrConductance <= 1000) {
    fsrForce = fsrConductance / 80.0;
  } else {
    fsrForce = (fsrConductance - 1000) / 30.0;
  }
  Serial.print("Force in Newtons: ");
  Serial.println(fsrForce);
```
Update LED
Update the RGB LED color based on the force measured.

```
  updateLed(fsrForce);
```
Detect Hits
Detect hits based on the force threshold and debounce the signal.
```cpp
  if (detectHit(fsrForce)) {
    hits++;
    Serial.print("Hits: ");
    Serial.println(hits);
  }

  delay(100);
}
```
Helper Functions
Update LED Color
Set the RGB LED color based on the force level.

```cpp
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
```
Hit Detection with Debounce
Detect hits and debounce the signal.

```cpp
bool detectHit(float force) {
  static float lastForce = 0;
  static unsigned long lastHitTime = 0;
  const unsigned long debounceTime = 200;

  unsigned long currentTime = millis();
  if (force > 5 && (currentTime - lastHitTime > debounceTime)) {
    lastHitTime = currentTime;
    lastForce = force;
    return true;
  }
  lastForce = force;
  return false;
}
```
Butterworth Filter
Importance
The Butterworth filter is a type of signal processing filter designed to have a flat frequency response in the passband. It is particularly useful in this application for smoothing out the sensor readings and removing high-frequency noise, ensuring that the measurements are accurate and reliable.

Introduction in Loop
The Butterworth filter is introduced at the beginning of the loop function. Each raw analog reading from the FSR sensor is passed through the filter to produce a filtered reading. This filtered reading is then further processed by the smoothing algorithm and used in force calculation and hit detection.

By incorporating the Butterworth filter, we ensure that the system responds accurately to actual force events while minimizing the impact of random noise or minor variations in sensor readings.

Conclusion
This Arduino sketch effectively measures and processes force using a combination of filtering and smoothing techniques. The Butterworth filter plays a crucial role in providing clean and accurate sensor data, which is essential for reliable hit detection and force measurement. The RGB LED provides a visual indication of the force levels, making it easier to understand the impact in real-time.
