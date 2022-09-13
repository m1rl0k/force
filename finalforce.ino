

int fsrPin = A0;



int fsrReading = 0;
int sensorVal       = 0;    // store the value coming from the sensor
int smoothedVal     = 0;    // smoothed result
int samples         = 4;  
 
int value = 0;
int resistance;


int fsrVoltage; 

unsigned long fsrResistance; 
unsigned long fsrConductance; 
long fsrForce;
float force;

int hits = 0; // impact count
int forceTrig = 1000; // impact sensitivity




int val;



void setup() {Serial.begin(57600);}
void loop() {
 
  {
 uint16_t force[] = { 0, 0 , 0};
  
  uint16_t gAll = (abs(fsrForce)+abs(fsrForce)+abs(fsrForce));

  if ((gAll > 1000));
        Serial.println( hits );
    delay(50); // prevent duplicate detection
  
if (fsrForce > 2) { Bean.setLed(0,0,255); } // blue
    if (fsrForce > 5) { Bean.setLed(255,0,0); } // red
    if (fsrForce > 3) { Bean.setLed(0,255,0); } // green
    if (fsrForce < 0) { Bean.setLed(0,0,0); } //NONE
    hits++; 
    
    fsrReading = analogRead(fsrPin);
 Serial.print("Analog:");
    
      sensorVal = analogRead(fsrReading); 
  smoothedVal = smoothedVal + ((sensorVal -smoothedVal)/samples);
     
  Serial.print("Smoothed Analog:");
  Serial.println(smoothedVal, DEC);
 
  // slow down amount of readings and prints
  delay(100); 

  float voltage = sensorVal * (2.7 / 1023.0);
  
  Serial.print("Voltage:");
  Serial.println(voltage,DEC);
  
 
  delay(100);

  value = analogRead(sensorVal);
  resistance = ((9200 * value)/(1-(value/1023.0)));
  Serial.print("Resistance:");
  Serial.println(resistance,DEC);  
  
  delay(200);

    



if (voltage == 0)
{Serial.println("0");
} else {
fsrResistance = 2700 - voltage;
fsrResistance *= 9200;
 fsrResistance /= voltage;
 Serial.print("FSR resistance in ohms = ");
Serial.println(fsrResistance);
fsrConductance = 920000;
fsrConductance /= resistance*100;
Serial.print("Conductance in microMhos: ");
Serial.println(fsrConductance);
            if (fsrConductance <= 1000) {
fsrForce = fsrConductance / 80;
Serial.print("Newtons");

            Serial.println(fsrForce); 
} else {
fsrForce = fsrConductance - 1000;
fsrForce /= 30;
            Serial.println(fsrForce); 


}}}}
