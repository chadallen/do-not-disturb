

/*

 DO NOT DISTURB
Jan 9 2015 by Chad Allen
  
 Adapted from: Arduino Starter Kit example Project 11  - Crystal Ball
 Crystal Ball Created 13 September 2012 by Scott Fitzgerald

 "DO NOT DISTURB" adds functionality that causes the display to return to a 'resting' state after a given interval using stopwatch.h library
 Also includes blinking cursor at resting state
 
 Parts required:
 220 ohm resistor
 10 kilohm resistor
 10 kilohm potentiometer
 16x2 LCD screen
 tilt switch

 */

// include libraries for LCD and stopwatch
#include <LiquidCrystal.h>
#include <stopwatch.h>

// initialize the lcd library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//initialize timer used to put the display into 'resting' mode
StopWatch timer;

// initalize timer to govern blinking cursor
StopWatch blinkTimer;

// varialbe to hold the resting state of the device, which will start at rest
boolean resting = true;

//variable to tell us if the device has just started up and has not yet been activated
boolean startingUp = true;

// constant to hold the display message when the device is at rest
char restingMessage[] = "DO NOT DISTURB";

//constant to determine amount of time (ms) to wait after activation before the device rests
const int timeToRest = 2000;

// constant for the tilt switchPin
const int switchPin = 6;

// variable to hold the value of the switchPin
int switchState = 0;

// variable to hold previous value of the switchpin
int prevSwitchState = 0;



// a variable to choose which reply to display when the device is activated
int reply;

void setup() {
  Serial.begin(9600);
  //start timers
  timer.start();
  blinkTimer.start();
  // set up the number of columns and rows on the LCD 
  lcd.begin(16, 2);

  // set up the switch pin as an input
  pinMode(switchPin,INPUT);

}

void loop() {

  Serial.println(timer.elapsed());
  // check the status of the switch
  switchState = digitalRead(switchPin);
  // if the timer has been running for n milliseconds and the unit is not at rest then make the unit rest
  // if the device is still in startup mode and has been activated, then treat it as if it is at rest
  if ((timer.elapsed() > timeToRest and resting == false) or (startingUp == true)) {

    //because the device has been used it is no longer in "startup" mode
    startingUp = false;
    
    //put the device in resting state
    resting = true; 

    lcd.clear();   
    lcd.setCursor(0, 0);
    lcd.print("Arduino says:");
    // move the cursor to the second line
    lcd.setCursor(0, 1);
    // display our resting message
    lcd.print(restingMessage);
      
    

  }

  // blink a cursor if resting

  if (resting == true and blinkTimer.elapsed() < 500) {
    lcd.cursor();  
  }
  

  if (resting == true and blinkTimer.elapsed() > 500 and blinkTimer.elapsed() < 1000) {
    lcd.noCursor();  
  }

  if (resting == true and blinkTimer.elapsed() > 1000) { 
    blinkTimer.reset();
    blinkTimer.start();
  }
  
  // compare the switchState to its previous state
  if (switchState != prevSwitchState) {




    // if the state has changed from HIGH to LOW
    // you know that the device has been tilted from 
    // one direction to the other 
    if (switchState == LOW) {

      //reset our timer and restart
      timer.reset();
      timer.start();

      //the device has been moved so it is not at rest
      resting = false;


      // randomly chose a reply
      reply = random(8);
      // clean up the screen before printing a new reply
      lcd.clear();
      // set the cursor to column 0, line 0     
      lcd.setCursor(0, 0);
      // print some text
      lcd.print("Arduino says:");
      // move the cursor to the second line
      lcd.setCursor(0, 1);

      lcd.noCursor();

      // choose a saying to print baed on the value in reply 
      switch(reply){
        case 0:
        lcd.print("Don't touch!");
        break;

        case 1:
        lcd.print("Stop moving!");
        break;

        case 2:
        lcd.print("Leave me alone!");
        break;

        case 3:
        lcd.print("Knock it off!");
        break;

        case 4:
        lcd.print("Blerg");
        break;

        case 5:
        lcd.print("WTF!");
        break;

        case 6:
        lcd.print("Jerkface!");
        break;

        case 7:
        lcd.print("Go away!");
        break;
      }
    }
  }
  // save the current switch state as the last state 
  prevSwitchState = switchState;
}



