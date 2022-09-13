#include <Wire.h>
#include <Arduino.h>


class filter
{
  public:
    filter()
    {
      v[0] = 0;
      v[1] = 0;
    }
  private:
    short v[2];
  public:
    short step(short x)
    {
      v[0] = v[1];
      long tmp = ((((x * 4089446L) >> 6)	//= ( 3.0468747091e-2 * x)
                   + ((v[0] * 3938714L) >> 1)	//+( 0.9390625058*v[0])
                  ) + 1048576) >> 21; // round and downshift fixed point /2097152

      v[1] = (short)tmp;
      return (short)((
                       (v[0] + v[1]))); // 2^
    }
};


const int fsrPin = A0;
int sensorVal;


int fsrReading = 0;
int smoothedVal     = 0;
int samples         = 4;


int fsrVoltage;
int value;

int resistance;

unsigned long fsrResistance;
unsigned long fsrConductance;
long fsrForce;

uint8_t (force) = fsrForce;
uint16_t (Newtons) = fsrForce;




String beanName = "Ninja";


const int numReadings = 100;


int readings[numReadings]; // the readings from the analog input
int index = 0; // the index of the current reading
int total = 0; // the running total
int average = 0;


uint16_t pinMap[] = {A0};
uint16_t pinValues[] = {0, 1};

int inByte;
int incomingByte = 0;

int val;




void setup() {
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;

    
    
  Serial.begin(57600);
  Serial.setTimeout(25);

  
    

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
    



}





void loop() {



  fsrReading = analogRead(fsrPin);
  Serial.print("Analog:");

  sensorVal = analogRead(fsrReading);
  smoothedVal = smoothedVal + ((sensorVal - smoothedVal) / samples);

  Serial.print("Smoothed Analog:");
  Serial.println(smoothedVal);

  // slow down amount of readings and prints



  float voltage = sensorVal * (3.29 / 1023.0);

  Serial.print("Voltage:");
  Serial.println(voltage);
   }
