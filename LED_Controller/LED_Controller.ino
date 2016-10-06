#include <SoftwareSerial.h>
#include "string.h"

SoftwareSerial xbeeSerial(2,3);
// LED array where each elemetn corresponds to a physical pin
int LED[] = {1,2,3,4};
// 
int R = 0;
int B = 1;
int G = 2;
int Y = 3;
// Better Id of LED manipulation 

void setup() 
{
  xbeeSerial.begin(115200);
  Serial.begin(9600);
  for(int i = 0; i < sizeof(LED); i++)
  {
    pinMode(LED[i],OUTPUT);
    digitalWrite(LED[i], LOW);
  }
  // Alternate method
  pinMode(R,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(Y,OUTPUT);
}

void loop() 
{
  char input;
  String command = "";
  while(xbeeSerial.available() > 0)
  {
    input = (char)xbeeSerial.read();
    command += input;

    switch(command)
    {
      case "PR" :
        digitalWrite(R,HIGH);
        break;
    }
    
  }

}

// Make sure we send confirmation of the LED change back to the requestor 
