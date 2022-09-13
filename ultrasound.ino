const int pingPin = 2;

int sensingRangeUnit = 1; int buzzerLimit = 100; int buzzerFrequency;

void setup() {

pinMode(3, OUTPUT); // sets the digital pin 3 as output for a buzzer pinMode(4, OUTPUT); // sets the digital pin 4 as output for an LED pinMode(5, OUTPUT); // sets the digital pin 5 as output for an LED pinMode(6, OUTPUT); // sets the digital pin 6 as output for an LED pinMode(7, OUTPUT); // sets the digital pin 7 as output for an LED pinMode(8, OUTPUT); // sets the digital pin 8 as output for an LED pinMode(9, OUTPUT); // sets the digital pin 9 as output for an LED pinMode(10, OUTPUT); // sets the digital pin 10 as output for an LED pinMode(11, OUTPUT); // sets the digital pin 11 as output for an LED pinMode(12, OUTPUT); // sets the digital pin 12 as output for an LED pinMode(13, OUTPUT); // sets the digital pin 13 as output for an LED Serial.begin(9600);

}

void loop() { long duration, inches, cm;

pinMode(pingPin, OUTPUT); digitalWrite(pingPin, LOW); delayMicroseconds(2); digitalWrite(pingPin, HIGH); delayMicroseconds(5); digitalWrite(pingPin, LOW);

pinMode(pingPin, INPUT); duration = pulseIn(pingPin, HIGH);

// convert the time into a distance inches = microsecondsToInches(duration); cm = microsecondsToCentimeters(duration); Serial.print(inches); Serial.print("in, "); Serial.print(cm); Serial.print("cm"); Serial.println();

if (inches < (sensingRangeUnit*1)) { digitalWrite(4, HIGH); } else { digitalWrite(4, LOW); }

if (inches < (sensingRangeUnit*2)) { digitalWrite(5, HIGH); } else { digitalWrite(5, LOW); }

if (inches < (sensingRangeUnit*3)) { digitalWrite(6, HIGH); } else { digitalWrite(6, LOW); }

if (inches < (sensingRangeUnit*4)) { digitalWrite(7, HIGH); } else { digitalWrite(7, LOW); }

if (inches < (sensingRangeUnit*5)) { digitalWrite(8, HIGH); } else { digitalWrite(8, LOW); }

if (inches < (sensingRangeUnit*6)) { digitalWrite(9, HIGH); } else { digitalWrite(9, LOW); }

if (inches < (sensingRangeUnit*7)) { digitalWrite(10, HIGH); } else { digitalWrite(10, LOW); }

if (inches < (sensingRangeUnit*8)) { digitalWrite(11, HIGH); } else { digitalWrite(11, LOW); }

if (inches < (sensingRangeUnit*9)) { digitalWrite(12, HIGH); } else { digitalWrite(12, LOW); }

if (inches < (sensingRangeUnit*10)) { digitalWrite(13, HIGH); } else { digitalWrite(13, LOW); }

if (inches < buzzerLimit) { buzzerFrequency = (((buzzerLimit - inches)*255)/buzzerLimit); analogWrite(3, buzzerFrequency); } else { analogWrite(3, 0); } delay(100); }

long microsecondsToInches(long microseconds) { // According to Parallax's datasheet))), there are // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per // second). This gives the distance travelled by the ping, outbound // and return, so we divide by 2 to get the distance of the obstacle. return microseconds / 74 / 2; }

long microsecondsToCentimeters(long microseconds) { // The speed of sound is 340 m/s or 29 microseconds per centimeter. // The ping travels out and back, so to find the distance of the // object we take half of the distance travelled. return microseconds / 29 / 2; }
