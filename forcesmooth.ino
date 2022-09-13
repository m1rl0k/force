
#define Platform.h

              

int fsrPin = A0;
int fsrReading;
int fsrVoltage; 
unsigned long fsrResistance; 
unsigned long fsrConductance; 
long fsrForce;
long fsrForce2;
int val;




void setup() { 
    
   

     Serial.begin(57600);
    Serial.setTimeout(25);
    
    

 
}
void loop() {
  
  

               
  
 
        
fsrReading = analogRead(fsrPin);  
Serial.print("Analog reading = ");
Serial.println(fsrReading);

int batteryV = Bean.getBatteryVoltage();
fsrVoltage = batteryV;
Serial.println(fsrVoltage); 

if (fsrVoltage == 0)
        
{
            Serial.println("0");
} else {
// %The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
// so FSR = ((Vcc - V) * R) / V yay math!
fsrResistance = 2800 - batteryV;

fsrResistance *= 9200;
 fsrResistance /= batteryV;
              Serial.print("FSR resistance in ohms = ");
Serial.println(fsrResistance);

fsrConductance = fsrResistance; //we measure in micromhos so 
fsrConductance /= 920000;
Serial.print("Conductance in microMhos: ");
Serial.println(fsrConductance);

// Use the two FSR guide graphs to approximate the force
                if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;
      Serial.print("Newtons:");
      Serial.println(fsrForce);
            } else {
fsrForce = fsrConductance - 1000;
fsrForce /= 30;
            Serial.println(fsrForce);
                   Serial.print("Newtons:");


              {
     val=analogRead(fsrForce);


{
             
                   
                    {
  char buffer[64];
  size_t readLength = 64;
  uint8_t length = 0;  
         
  length = Serial.readBytes(buffer, readLength);    
  
// Return all the serial pins
  if ( 0x02 == buffer[0] && 1 == length)
  

      

      
      buffer[0] = 
      buffer[1] = 
      buffer[3] = 
      buffer[4]= 
      buffer[5]= 
      
      

      Serial.write((uint8_t*)buffer, 6);
                                     {
      
                   }
    }
        

  }
}}}}
