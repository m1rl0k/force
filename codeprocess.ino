


int fsrPin = A1;
int fsrReading = fsrPin;
int fsrVoltage;
unsigned long fsrResistance;
unsigned long fsrConductance;
long fsrForce;

void setup(void) {
  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);
  pinMode(A1, INPUT_PULLUP);

  Serial.begin(57600);
};

void loop()
 { 
    fsrVoltage = map(fsrReading, 0, 1023, 0, 2400);


  fsrResistance = 3500 - fsrVoltage;
  fsrResistance *= 9200;
  fsrResistance /= fsrVoltage;


  fsrConductance = 920000;
  fsrConductance /= fsrResistance;


  if (fsrConductance <= 1000) {
    fsrForce = fsrConductance / 80;
 

      Serial.println(analogRead(fsrForce));

 if (Serial.available()) {
    int fsrForce = Serial.read();
    int inByte = Serial.read();
    Serial.write(inByte);
    
  Serial.println(fsrForce);
 
fsrForce = digitalRead(HIGH);

  } else {

    fsrForce /= 30;

    Serial.println(analogRead(fsrForce));

 if (Serial.available()) {
    int fsrForce = Serial.read();
    int inByte = Serial.read();
    Serial.write(inByte);
fsrForce = digitalRead(HIGH);
  Serial.println(fsrForce);

                Serial.println();

  
  }
};




    delay(6000);
  }
}
