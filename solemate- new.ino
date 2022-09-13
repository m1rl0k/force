const uint8_t BUF_LEN = 6;
 
/* Pin values */
int d0 = 0;
int d1 = 0;
int d2 = 0;
int d3 = 0;
int d4 = 0;
int d5 = 0;
unsigned long time = 0;
int val;
uint8_t buffer[BUF_LEN];
bool changed = false;
 
void setup() 
{
  Serial.begin(57600);
  // Digital pins
  pinMode(0, INPUT_PULLUP);  
  pinMode(1, INPUT_PULLUP);  
  pinMode(2, INPUT_PULLUP);  
  pinMode(3, INPUT_PULLUP); 
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  buffer[0] = 0x48; //Magic number
}
 
/* Loops through reading the digital values and sends data when something changes */
void loop() 
{
    val = digitalRead(0);
    if(val != d0)
      send_data();
    
    val = digitalRead(1);
    if(val != d1)
      send_data();
      
    val = digitalRead(2);
    if(val != d2)
      send_data();
      
    val = digitalRead(3);
    if(val != d3)
      send_data(); 
      
    val = digitalRead(4);
    if(val != d4)
      send_data();
  
    val = digitalRead(5);
    if(val != d5)
      send_data();
 
    Bean.sleep(10);
}
 
void send_data()
{
  buffer[1] = 0;
  buffer[1] |=  digitalRead(0);
  buffer[1] |= (digitalRead(1) << 1);
  buffer[1] |= (digitalRead(2) << 2);
  buffer[1] |= (digitalRead(3) << 3);
  buffer[1] |= (digitalRead(4) << 4);
  buffer[1] |= (digitalRead(5) << 5);
  time = millis();
  buffer[2] = (time >> 24) & 0xFF;
  buffer[3] = (time >> 16) & 0xFF;
  buffer[4] = (time >> 8) & 0xFF;
  buffer[5] = (time)   & 0xFF;
  Bean.setScratchData(1, buffer, BUF_LEN);
  Serial.println("Data Written\n");
  
}
