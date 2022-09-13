
int fsrPin = A0;
int fsrReading;
int fsrVoltage; 
unsigned long fsrResistance; 
unsigned long fsrConductance; 
long fsrForce;
int batteryV;
uint16_t val = 0; 
   

void setup() { 
    analogReference(INTERNAL);
    pinMode(A0, INPUT);
    pinMode(0, OUTPUT);
    pinMode(0,HIGH);
    


     Serial.begin(57600);
    
    
 
}
void loop() {



    
    
    
 {
       
  uint16_t batteryV = 0;
  
 
  
  batteryV = Bean.getBatteryVoltage();
  
  Serial.print("Battery voltage: ");
  Serial.println(batteryV, DEC);
        
        fsrReading = analogRead(fsrPin);  
Serial.print("Analog reading = ");
Serial.println(fsrReading);

fsrVoltage = batteryV;


Serial.println(fsrVoltage); 

if (fsrVoltage == 0)
        
{
            Serial.println("0"); 
} else {
// %The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
// so FSR = ((Vcc - V) * R) / V yay math!
fsrResistance = 5000 - batteryV; // fsrVoltage is in millivolts so 5V = 5000mV
fsrResistance *= 11000;
            fsrResistance /= batteryV;
Serial.print("FSR resistance in ohms = ");
Serial.println(fsrResistance);

fsrConductance = batteryV*1000; //we measure in micromhos so 
fsrConductance /= fsrResistance;
Serial.print("Conductance in microMhos: ");
Serial.println(fsrConductance);

// Use the two FSR guide graphs to approximate the force
                if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;
      Serial.print("Newtons: ");
      Serial.println(fsrForce);     
                Serial.write(fsrForce);
               


 

                
                
       {    
                    
                       val=analogRead(fsrForce);
                    {
        if(val>35)
                    
       Bean.setLed(0,0,255);
                            if (val<20) Bean.setLed(0,0,0);
                   }

  }
}}}}
