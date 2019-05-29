#include <AFMotor.h>



// Adafruit Motor shield library

//Modified by Rahul

//Includes the Adafruit Motor Shield Library


AF_DCMotor motor1(1); // DC motor is hooked up to M1                                          
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);// DC motor is hooked up to M2
AF_DCMotor motor4(4);

//==================INSERT VALUES HERE \/ ====================================================================================================
int pin1 = 24;//CHANGE 24 TO THE NUMBER OF PIN YOU ARE USING!!!!   Digital pins connected to the radio receiver ports 
int pin2 = 30;//CHANGE 30 TO THE NUMBER OF PIN YOU ARE USING!!!!    ^ The receiver is the small black box w/ a red antenna
int pin3 = 34;//CHANGE 34 TO THE NUMBER OF PIN YOU ARE USING!!!!    
int pin4 = 36;//CHANGE 36 TO THE NUMBER OF PIN YOU ARE USING!!!!   
//Make sure that pin1 is hooked up to the throttle port on the receiver (port 2 on 9x)
//and that pin2 is hooked up to the rudder port on the receiver (port 4 on 9x)


int neutralh = 1520;      //PUT YOUR HIGH NEUTRAL VALUE HERE. REPLACE 1520  
int neutrall = 1460;      //PUT YOUR LOW NEUTRAL VALUE HERE. REPLACE 1420  
int maxval = 1999;        //PUT YOUR MAX VALUE HERE   REPLACE 1870          
int minval = 999;         // PUT YOUR MIN VALUE HERE           REPLACE 1050  

//==================INSERT VALUES HERE /\ ====================================================================================================

void setup() {
  Serial.begin(9600);           // set up Serial monitor at 9600 bps

  motor1.run(RELEASE);          //This releases the motors via the motorshield
  motor2.run(RELEASE);
  motor3.run(RELEASE);          // This is to make sure the motors dont start w/o control
  motor4.run(RELEASE);

  pinMode(pin1, INPUT);         //Setting up RC input pins
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);         //Setting up RC input pins
   pinMode(pin4, INPUT);

}
void loop() {
  int sV1;                      //These are all different speed values that will be mapped
  int sV2;
  int sV3;
  int sV4;
  int sV5;
  int sV6;
  int sV7;
  int sV8;
  int sV9;
  int sV10;
int speedValue = pulseIn(pin1, HIGH);           //Getting the pulse in value from pin 1 and defining pin1 as speed
  
  int directionValue = pulseIn(pin2, HIGH);     //Getting the pulse in value from pin 2 and defining pin1 as turning

  int gripspeed = pulseIn(pin3, HIGH);

  int gripholdspeed = pulseIn(pin4, HIGH);

          //Serial.println(speedValue);
          //Serial.println(directionValue);
          //These can be printed for debugging


  

    if (speedValue >= 1460 && speedValue <= 1520) {         //If the sticks are Neutral, then stay still

      motor1.run(RELEASE);                                  //releases motors
      motor2.run(RELEASE);
    delay(50);}

    if (speedValue >= 1350 && speedValue <= 1650)
    {
      motor3.run(RELEASE);                              // releases motors
      motor4.run(RELEASE);                              // releases motors

      delay(50);            //checks again every 50 micro Seconds
    }


    if (speedValue > 1520 && directionValue >= 1460 && directionValue <= 1520) {      //if the throttle is up and turning is neutral

      sV1 = map(speedValue, 1460, 1999, 140, 255);              //Maps the pulseIn speedvalue to numbers the motors can read
                                                          //Motor is set to 140-255 instead of 0-255 so that the motor doesnt stall if 
                                                          //it is powered at too low of a level
                                                   
      if(sV1 > 255){          //If the speed value is over 255 then set it to 255.                             .
        sV1 = 255;            //This prevents overpowering the motor if there is a pulsein glitch                          
      }
     
      motor1.setSpeed(sV1); // Sets the speed of motor1 to the speedValue
      motor2.setSpeed(sV1); // Sets the speed of motor2 to the speedValue
      motor3.setSpeed(0);
      motor1.run(FORWARD);  //Makes the motor go forward at the speed defined above
      motor2.run(FORWARD);
      motor3.run(0);//Makes the motor go forward at the speed defined above
      Serial.println("Forward");
      delay(50);            //Repeat every 50 micro seconds
      
    }

//reverse gear

if (speedValue < 1460 && directionValue >= 1460 && directionValue <= 1520) {      //Speed is reverse and direction value is centered

      sV4 = map(speedValue, 1460, 999, 140, 255);      //REVERSE

      if(sV4 > 255){
        sV4 = 255;
      }

      motor1.setSpeed(sV4);
      motor2.setSpeed(sV4);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      Serial.println("Back");

      delay(50);
    }

//right turn

if (directionValue > 1520 && speedValue > 1520) {     //Speed value is forward, direction is right

      sV2 = map(speedValue, 1520, 1999, 140, 255);    //RIGHT FORWARD

      if(sV2 > 255){
        sV2 = 255;
      }

      motor1.setSpeed(sV2);
      motor2.setSpeed(sV2);
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      Serial.println("Right Forward");
      delay(50);

}

//Left Forward

if (directionValue < 1460 && speedValue > 1520) { //Speed is forward, Direction is left

      sV3 = map(speedValue, 1520, 1999, 140, 255);    //LEFT FORWARD

      if(sV3 > 255){
        sV3 = 255;
      }

      motor1.setSpeed(sV3);
      motor2.setSpeed(sV3);
      motor1.run(FORWARD); 
      motor2.run(BACKWARD);
     Serial.println("Left Forward");

      delay(50);
    }

//right reverse

if (directionValue > 1520 && speedValue < 1460) {

      sV5 = map(speedValue, 1460, 999, 140, 255);  //BACK RIGHT

      if(sV5 > 255){
        sV5 = 255;
      }

      motor1.setSpeed(sV5);
      motor2.setSpeed(sV5);
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      Serial.println("Reverse Right");

      delay(50);
    }

    //Reverse Left 

    if (directionValue < 1460 && speedValue < 1460) {

      sV6 = map(speedValue, 1460, 999, 140, 255);    //BACK LEFT

      if(sV6 > 255){
        sV6 = 255;
      }

       motor1.setSpeed(sV6);
      motor2.setSpeed(sV6);
      motor1.run(FORWARD); 
      motor2.run(BACKWARD);
     Serial.println("Reverse Left");

      delay(50);
    
  }


  if (gripspeed > 1520 && gripspeed < 1999) { //if the throttle is up and turning is neutral

      sV7 = map(speedValue, 1520, 1999, 0, 255);      //Maps the pulseIn speedvalue to numbers the motors can read
                                                   //Motor is set to 140-255 instead of 0-255 so that the motor doesnt stall if 
                                                   //it is powered at too low of a level
                                                   
      if(sV7 > 255){ //If the speed value is over 255 then set it to 255.                             .
        sV7 = 255;    //This prevents overpowering the motor if there is a pulsein glitch                          
      }
     
      motor1.setSpeed(0); // Sets the speed of motor1 to the speedValue
      motor2.setSpeed(0); // Sets the speed of motor2 to the speedValue
      motor3.setSpeed(sV7);
      motor1.run(0);  //Makes the motor go forward at the speed defined above
      motor2.run(0);
      motor3.run(FORWARD);//Makes the motor go forward at the speed defined above
      Serial.println("Grip Forward");
      delay(50);            //Repeat every 50 micro seconds
      
    }


    if (gripspeed >900 && gripspeed <1460) { //if the throttle is up and turning is neutral

      sV8 = map(speedValue, 999, 1460, 0, 255);      //Maps the pulseIn speedvalue to numbers the motors can read
                                                   //Motor is set to 140-255 instead of 0-255 so that the motor doesnt stall if 
                                                   //it is powered at too low of a level
                                                   
      if(sV8 >255){ //If the speed value is over 255 then set it to 255.                             .
        sV8 = 255;    //This prevents overpowering the motor if there is a pulsein glitch                          
      }
     
      //motor1.setSpeed(0); // Sets the speed of motor1 to the speedValue
     // motor2.setSpeed(0); // Sets the speed of motor2 to the speedValue
      motor3.setSpeed(sV8);
      //motor1.run(0);  //Makes the motor go forward at the speed defined above
      //motor2.run(0);
      motor3.run(BACKWARD);//Makes the motor go forward at the speed defined above
      Serial.println(gripspeed);
      delay(50);            //Repeat every 50 micro seconds
      
    }

    
 if (gripholdspeed > 1520 && gripholdspeed < 1999) { //if the throttle is up and turning is neutral

      sV9 = map(speedValue, 1520, 1999, 0, 255);      //Maps the pulseIn speedvalue to numbers the motors can read
                                                   //Motor is set to 140-255 instead of 0-255 so that the motor doesnt stall if 
                                                   //it is powered at too low of a level
                                                   
      if(sV9 > 255){ //If the speed value is over 255 then set it to 255.                             .
        sV9 = 255;    //This prevents overpowering the motor if there is a pulsein glitch                          
      }
     
      motor1.setSpeed(0); // Sets the speed of motor1 to the speedValue
      motor2.setSpeed(0); // Sets the speed of motor2 to the speedValue
      motor4.setSpeed(sV9);
      motor1.run(0);  //Makes the motor go forward at the speed defined above
      motor2.run(0);
      motor4.run(FORWARD);//Makes the motor go forward at the speed defined above
      Serial.println("Grip holding");
      delay(50);            //Repeat every 50 micro seconds
      
    }



    if (gripholdspeed >900 && gripholdspeed <1460) { //if the throttle is up and turning is neutral

      sV10 = map(speedValue, 999, 1460, 0, 255);      //Maps the pulseIn speedvalue to numbers the motors can read
                                                   //Motor is set to 140-255 instead of 0-255 so that the motor doesnt stall if 
                                                   //it is powered at too low of a level
                                                   
      if(sV10 >255){ //If the speed value is over 255 then set it to 255.                             .
        sV10 = 255;    //This prevents overpowering the motor if there is a pulsein glitch                          
      }
     
      //motor1.setSpeed(0); // Sets the speed of motor1 to the speedValue
     // motor2.setSpeed(0); // Sets the speed of motor2 to the speedValue
      motor4.setSpeed(sV10);
      //motor1.run(0);  //Makes the motor go forward at the speed defined above
      //motor2.run(0);
      motor4.run(BACKWARD);//Makes the motor go forward at the speed defined above
      Serial.println("Grip release");
      delay(50);            //Repeat every 50 micro seconds
    }}
