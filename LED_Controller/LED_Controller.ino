#include <SoftwareSerial.h>
#include "string.h"

SoftwareSerial xbeeSerial(2,3);
// LED array where each elemetn corresponds to a physical pin 
int R = 8;
int B = 9;
int G = 10;
int Y = 11;

// Global string 
String command;

void setup() 
{
  xbeeSerial.begin(115200);
  Serial.begin(9600);
  
  // Set the pins
  pinMode(R,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(Y,OUTPUT);
}
bool isInitialized = false;
void loop() 
{
  if(!isInitialized){
    Serial.println("Starting...");
    isInitialized = true;
  }
  // Processing the XBEE
  processXbee();
}

void processXbee(void) 
{
    bool stringComplete = false;
    int comma;
    int newLine;
    while (xbeeSerial.available() > 0)                                              // While loop to build the buffer of all chracters that are available (not if)
  {
    char inChar = (char)xbeeSerial.read();
    command += inChar;
    if (inChar == '\n')
    {
      stringComplete = true;
      break;
    }
  }
    if (stringComplete)
  {
    //comma = command.indexOf(',');
    //newLine = command.indexOf('\n');
    //String ID = command.substring(0, (comma - 1));
    char ID = command[0];
    Serial.print("ID is: ");
    Serial.println(ID);
    //String subStringState = command.substring((comma + 1), (newLine - 1));           // MAKE THIS A PARSING FUNCTION
    char subStringState = command[1];
    Serial.print("The state:  ");
    Serial.println(subStringState);
    //int state = subStringState.toFloat();
    int state = (subStringState - '0');
    command = "";
    stringComplete = false;

    // Execute the command
    // RED
      if(ID == 'R')
    {
        if(state == 0)
      {
        digitalWrite(R,LOW);
        xbeeSerial.print(0);
      }
        else if(state == 1)
      {
        digitalWrite(R,HIGH);
        xbeeSerial.print(1);
      }
    }
    // BLUE
      if(ID == 'B')
    {
        if(state == 0)
      {
        digitalWrite(B,LOW);
        xbeeSerial.print(0);
      }
        else if(state == 1)
      {
        digitalWrite(B,HIGH);
        xbeeSerial.print(1);
      }
    }
    // GREEN
      if(ID == 'G')
    {
        if(state == 0)
      {
        digitalWrite(G,LOW);
        xbeeSerial.print(0);
      }
        else if(state == 1)
      {
        digitalWrite(G,HIGH);
        xbeeSerial.print(1);
      }
    }
    // YELLOW
      if(ID == 'Y')
    {
        if(state == 0)
      {
        digitalWrite(Y,LOW);
        xbeeSerial.print(0);
      }
        else if(state == 1)
      {
        digitalWrite(Y,HIGH);
        xbeeSerial.print(1);
      }
    }
  }
}

// Make sure we send confirmation of the LED change back to the requestor 
