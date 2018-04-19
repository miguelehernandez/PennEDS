//*******************************************
// * Turns on an IR LED for 4 seconds 
// * after reading a low to high transistion from 
// * the Labjack.
// * 
// * Author: M. Hernandez
// * Date: 4-10-2018
//*******************************************

/*-----( Import needed libraries )-----*/
/*-----( Declare Constants )-----*/
#define IR_ON 1
#define IR_OFF 0
/*-----( Declare objects )-----*/
/*-----( Declare Variables )-----*/

#define IRLED_1  2  // Arduino Digital I/O pin number
#define InPin    7  // Pin 7 will be the InPin

int val = 0;        // value to be tested

void setup()   /****** SETUP: RUNS ONCE ******/
{
  //-------( Initialize Pins so IR are inactive at reset)----
  pinMode(InPin, INPUT);        // sets the digital pin 7 as input
  digitalWrite(IRLED_1, IR_OFF);
 
  //---( THEN set pins as outputs )----  
  pinMode(IRLED_1, OUTPUT);     
  delay(4000); //Check that pins are inactive at Reset

} //--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  // -- read the value from the LabJack
  val = digitalRead(InPin);

  if (val==0) {
    //---( Turn IRLED ON )---
    digitalWrite(IRLED_1, IR_ON);// set the IR ON
    delay(4000);              // wait for 4 seconds
  } else{ 
    digitalWrite(IRLED_1, IR_OFF);// set the IR OFF
  }
 
}//--(end main loop )---

//*********( THE END )***********

