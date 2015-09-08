#include <BuzzerMusic.h>
#include <pitches.h>
#include <scales.h>
#include <stdlib.h>
#include <Energia.h>
/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground
 
 created 29 Dec. 2008
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A5;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to
const int buttonPin = PUSH2;     // the number of the pushbutton pin

BuzzerMusic buzzer(NOTE_F3, MINOR_HARMONIC, 3);

int sensorValue = 0;        // value read from the pot
int noteValue = 0;          // value of the index for the note scale
int outputValue = 0;        // value output to the PWM (analog out)
int numNotes = 0; 
int noteFreq = 0;
int scaleCounter = 0; //index of which scale to use

int scales[] = {MAJOR, MINOR, MINOR_HARMONIC, CHROMATIC, WHOLE, DIMINISHED, PENTATONIC_MAJOR, PENTATONIC_MINOR, BLUES_MINOR};
char * scalesSTR[] = {"Major", "Minor", "Harmonic Minor", "Chromatic", "Whole", "Diminished", "Major Pentatonic", "Minor Pentatonic", "Minor Blues"};


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  numNotes = buzzer.GetNoteCount();
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);  
}

void loop() {
  //determine if the button was pushed:
  if(!digitalRead(buttonPin))
  {
     //Change the scale
     scaleCounter++;
     if(scaleCounter>=9){ scaleCounter = 0; }
     buzzer.SetScale(scales[scaleCounter]);
     numNotes = buzzer.GetNoteCount();
  }
  
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  noteValue = map(sensorValue, 0, 1023, 0, numNotes-1);  
  // change the analog out value:
  noteFreq = buzzer.GetFrequency(noteValue);
  tone(analogOutPin, noteFreq);           

  // print the results to the serial monitor:
  Serial.print("scale = " );                       
  Serial.print(scalesSTR[scaleCounter]); 
  Serial.print("sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.print(noteValue); 
  Serial.print("\t Freq = ");      
  Serial.println(noteFreq);  
  
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(10);                     
}
