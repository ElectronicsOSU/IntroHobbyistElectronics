
// Pin definitions
const int LED = 2; 
const int pushButton = 3;
// variables
int buttonState = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); 
  
  // make the on-board pushbutton's pin an input pullup:
  pinMode(pushButton, INPUT);
  pinMode(LED, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);
  //Turn on LED if the button is on
  if(buttonState == true){
   digitalWrite(LED, HIGH); 
  } else {
    digitalWrite(LED, LOW); 
  }
  delay(1);        // delay in between reads for stability
}



