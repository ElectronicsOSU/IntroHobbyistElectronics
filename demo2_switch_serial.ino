// Pin definitions
const int LED = 2; 
const int pushButton = 6;
// variables
int buttonState = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); 
  
  // make the push button configured as a Pull DOWN
  pinMode(pushButton, INPUT);
  pinMode(LED, OUTPUT); 
}

void loop() {
  // read the input pin:
  buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.print("The button reads: ");
  Serial.println(buttonState);
  
  //Turn on LED if the button is on
  if(buttonState == HIGH){
   digitalWrite(LED, HIGH); 
  } else {
    digitalWrite(LED, LOW); 
  }
  
  delay(10);        // delay in between reads for stability
}