//*******************************************************
//* Author: M. Hernandez
//
//* Date: 3-28-2019
//
//* Purpose: The program is timer that reads a 4-DIP
//* switch and outputs a 0.9Mhz, 50% duty-cycle signal at 
//* will be on at Digital Pin 9
//* The time the signal is ON depends on what DIP switch 
//* moves to the ON position. 
//* The switch is set to be Active HIGH: it is normally 
//* pulled low. By moving the switch to the ON position.
//*       1000 =>  15minutes
//*       x100 =>  30minutes
//*       xx10 =>  45minutes
//*       xxx1 =>  60minutes
//* x is Don't care
//
//******************************************************* 

int ledPin = 13;  // LED connected to digital pin 13
int Point9HzPin = 9;  // Output pin


int FifteenMinPin = 2;    // Switch pin 1 connected to digital pin 2
int ThirtyMinPin = 3;     // Switch pin 2 connected to digital pin 3
int FortyFiveMinPin = 4;    // Switch pin 3 connected to digital pin 4
int SixtyMinPin = 5;     // Switch pin 4 connected to digital pin 5


int val = 0;      // variable to store the read value
int valArray[4] = {0,0,0,0}; 
int ii = 0; 
int ledState = LOW;

unsigned long int myCycles = 0; 
unsigned long int interval = 0; 
unsigned long myInitMillis = 0;  
unsigned long previousMillis =0;
unsigned long myPreviousMillis =0;
const long point9HzInterval = 555; 

void setup() {
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT);  // sets the digital pin 13 as output
  pinMode(Point9HzPin, OUTPUT);  // sets the digital pin 9 as output

  for(ii=2; ii<=5; ii++) pinMode(ii, INPUT);    // sets the digital pins as input
    
   // Find the time loop set by the user
   do{ 
      // read the input pin and stay there until we read anything >0 
      for(ii=0; ii<4; ii++) valArray[ii] = digitalRead(ii+2); // Store them first in an array
    
      // now test each member of the array and go back to read 
      // if we have not received a 1 in one of the pins go back to read
      for(ii=0; ii<4; ii++){
        if (valArray[ii] == 1) {
            val=1; 
            val=val<<ii;
        };
      };
   }while(val==0);
  
  switch (val) {
    case 1: // First pin in the closed position 15 min 
      //do 15min when val equals 1   
      Serial.println("At pin 1");
      //myCycles = 1; // 15 minutes for option 1 to test
      myCycles = 15; // 15 minutes for option 1 to test
      break;

    case 2:
      //do something when val equals 2
       Serial.println("At pin 2");
       myCycles = 30; // 30 minutes for option 2
      break;
    
    case 4:
      //do something when val equals 4
      Serial.println("At pin 3");
      myCycles =45; 
      break;
    
    case 8:
      //do something when val equals 8
      Serial.println("At pin 4");
      myCycles =60;
      break;
    
    default:
      // if nothing else matches, do the default
      // default is optional
      // invalid state, make the signal low
      Serial.println("At default");
      myCycles =0;
      digitalWrite(ledPin, LOW);
      digitalWrite(Point9HzPin, LOW);
      break;
  };
  interval = myCycles*60*1000;
  Serial.print("interval = "); 
  Serial.println(interval); 
  
  unsigned long myInitMillis = millis();   
}

void loop() {
    unsigned long myCurrentMillis = millis(); 
    if (myCurrentMillis - myInitMillis <= interval ) { // has the interval in seconds elapsed? 
          Point9HzFunction(); 
    } else {
          digitalWrite(ledPin, LOW);
          digitalWrite(Point9HzPin, LOW);
    } 
}

void Point9HzFunction(){

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= point9HzInterval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    digitalWrite(Point9HzPin, ledState);
  }
}

