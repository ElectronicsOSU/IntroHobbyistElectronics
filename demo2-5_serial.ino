#define DEBUG 0

void setup()
{
  Serial.begin(9600); //begin serial at 9600 Baud
}

void loop()
{
  Serial.println("Hello World");
  if(DEBUG){ Serial.print("This is a debug message"); }
  
}
