#include <SoftwareSerial.h>
#include "string.h"

SoftwareSerial xbeeSerial(2,3);
// LED array where each elemetn corresponds to a physical pin 
int R = 8;
int B = 9;
int G = 11;
int Y = 12;

#define RED 0
#define GREEN 1
#define BLUE 2
#define YELLOW 3

#define RED_ON        'A'
#define RED_OFF       'B'
#define GREEN_ON      'C'
#define GREEN_OFF     'D'
#define BLUE_ON       'E'
#define BLUE_OFF      'F'
#define YELLOW_ON     'G'
#define YELLOW_OFF    'H'
#define END_SIGNAL    'X'
#define CHECK_RED     'I'
#define CHECK_GREEN   'J'
#define CHECK_BLUE    'K'
#define CHECK_YELLOW  'L'

// Global string 
char command;
// [R,G,B,Y]
char rgby_status[4] = {0,0,0,0};

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
    bool receivedCommand = false;
    if (xbeeSerial.available() > 0)                                              // While loop to build the buffer of all chracters that are available (not if)
  {
    command =  (char)xbeeSerial.read();
    Serial.println("Command is: " + command);
    switch(command){
      case RED_OFF:
        digitalWrite(R,LOW);
        rgby_status[RED] = 0;
        break;
      case RED_ON:
        digitalWrite(R,HIGH);
        rgby_status[RED] = 1;
        break;
      case GREEN_ON:
        digitalWrite(G,HIGH);
        rgby_status[GREEN] = 1;
        break;
      case GREEN_OFF:
        digitalWrite(G,LOW);
        rgby_status[GREEN] = 0;
        break;
      case BLUE_ON:
        digitalWrite(B,HIGH);
        rgby_status[BLUE] = 1;
        break;
      case BLUE_OFF:
        digitalWrite(B,LOW);
        rgby_status[BLUE] = 0;
        break;
      case YELLOW_ON:
        digitalWrite(Y,HIGH);
        rgby_status[YELLOW] = 1;
        break;
      case YELLOW_OFF:
         digitalWrite(Y,LOW);
         rgby_status[YELLOW] = 0;
         break;
      case CHECK_RED:
        xbeeSerial.print(rgby_status[RED]);
        break;
      case CHECK_GREEN:
        xbeeSerial.print(rgby_status[GREEN]);
      break;
      case CHECK_BLUE:
        xbeeSerial.print(rgby_status[BLUE]);
      break;
      case CHECK_YELLOW:
        xbeeSerial.print(rgby_status[YELLOW]);
      break;
      default:
        break;
    }
    command = '\0';
  }
}   
      

// Make sure we send confirmation of the LED change back to the requestor 
