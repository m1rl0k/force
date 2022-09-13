int MoPin = 3;
int BUZZER =4;
#define THRESHOLD 100
   
 


const int sensor_pins[] = {A0, A1};
const int analogPin1 = A0;
   const int analogPin2 =A1;





 int val = 0;
 byte sendAnalog= 0;

AccelerationReading previousAccel;



void setup() {Bean.setAccelerationRange(16);
    


  previousAccel = Bean.getAcceleration(); 
}

int getAccelDifference(AccelerationReading readingOne, AccelerationReading readingTwo){
  int deltaX = abs(readingTwo.xAxis - readingOne.xAxis);
  int deltaY = abs(readingTwo.yAxis - readingOne.yAxis);
  int deltaZ = abs(readingTwo.zAxis - readingOne.zAxis);
  // Return the magnitude
  return deltaX + deltaY + deltaZ ;    }
    

void loop() {

 {
 
  
    val=analogRead(analogPin1);
    val=analogRead(analogPin2);
         
        if(val > 600) digitalWrite(BUZZER, HIGH);
        if(val < 600) digitalWrite(BUZZER, LOW);
        if (val > 600 == HIGH)
        {tone(BUZZER, 3500, 165);}
  }
  {
             if(val>0){
       
    val=analogRead(analogPin1);
    val=analogRead(analogPin2);
        if(val > 300) digitalWrite(MoPin, HIGH);
        if(val < 600) digitalWrite(MoPin, LOW);
  }
          for(int i=0; i<6;++i)

 
        {
   val=analogRead(analogPin1);
    val=analogRead(analogPin2);
    if(val>0){
        
        sendAnalog=val;
        Serial.print(sendAnalog);
        if(val>500) Bean.setLed(150,150,0);
        if(val<500) Bean.setLed(0,0,0);
        if(val>700) Bean.setLed(0,255,0);
        if(val<700) Bean.setLed(0,0,0);
        if(val>800) Bean.setLed(255,0,0);
        if(val<800) Bean.setLed(0,0,0);
                }
            
 AccelerationReading currentAccel = Bean.getAcceleration();   
  

  int accelDifference = getAccelDifference(previousAccel, currentAccel); 
 previousAccel = currentAccel;                                            
  
 
  if(accelDifference > THRESHOLD){   
    // Blink the LED
    Bean.setLed(0, 0, 255);
    Bean.sleep(100);
    Bean.setLed(0, 0, 0); 
    Bean.sleep(100);
  }else{
    Bean.sleep(200);
  }
}

}}
