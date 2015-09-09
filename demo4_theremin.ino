#include <BuzzerMusic.h>
#include <pitches.h>
#include <scales.h>


// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A5;  // Analog input pin that the photoresistor is attached to. Pin 7
const int analogOutPin = 9; // Analog output pin that the buzzer is connected to
const int scaleButton = PUSH2;     // the number of the pushbutton pin on the board
const int keyButton = 6;     // the number of the pushbutton pin of the

BuzzerMusic buzzer(NOTE_A3, BLUES_MINOR, 3);

int sensorValue = 0;        // value read from the pot
int noteValue = 0;          // value of the index for the note scale
int outputValue = 0;        // value output to the PWM (analog out)
int numNotes = 0;           // number of notes in a particular scale
int noteFreq = 0;           // frequency of the indexed note that will be played
int scaleCounter = 0;       // index of which scale to use
int keyCounter = 0;         // index of which key to use

int scales[] = {MAJOR, MINOR, MINOR_HARMONIC, CHROMATIC, WHOLE, DIMINISHED, PENTATONIC_MAJOR, PENTATONIC_MINOR, BLUES_MINOR};
char * scalesSTR[] = {"Major", "Minor", "Harmonic Minor", "Chromatic", "Whole", "Diminished", "Major Pentatonic", "Minor Pentatonic", "Minor Blues"};
int keys[] = {NOTE_A3, NOTE_AS3, NOTE_B3, NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3};
char * keysSTR[] = {"A", "A# / Bb", "B", "C", "C# / Db", "D", "D# / Eb", "E", "F", "F# / Gb", "G", "G# / Ab"};

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  numNotes = buzzer.GetNoteCount();
  // initialize the pushbutton pin as an input:
  pinMode(scaleButton, INPUT_PULLUP);  
  pinMode(keyButton, INPUT);
}

void loop() {
  //determine if the scale button was pushed:
  if(!digitalRead(scaleButton))
  {
     //Change the scale
     scaleCounter++;
     if(scaleCounter>=9){ scaleCounter = 0; }
     buzzer.SetScale(scales[scaleCounter]);
     numNotes = buzzer.GetNoteCount();
  }
  
  //determine if the key button was pushed:
  if(digitalRead(keyButton))
  {
     //Change the scale
     keyCounter++;
     if(keyCounter>=12){ keyCounter = 0; }
     buzzer.SetKey(keys[keyCounter]);
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
  Serial.print("\t| key = " );                       
  Serial.print(keysSTR[keyCounter]); 
  Serial.print("\t| sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t| output = ");      
  Serial.print(noteValue); 
  Serial.print("\t| Freq = ");      
  Serial.println(noteFreq);  
  
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(100);                     
}
