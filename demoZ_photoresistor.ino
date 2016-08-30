
const int cdsPin = A5; //this is also pin 7. 'A5' is a pre-defined cosntant for Energia

int sensorValue = 0; 

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}


void loop() {
  // read the analog light intensity
  sensorValue = analogRead(cdsPin);
  
   // print out the value you read:
  Serial.print("Photoresistor Level: ");
  // the value will be somewhere between 0 and 1023 for 10-bit analog to digital conversion
  Serial.println(sensorValue); 
  delay(10); 
}
