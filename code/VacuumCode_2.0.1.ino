//Code: VacuumCode
//Version: 2.0.1
//Author: Wiley Anorue, refer to anoruewilson@gmail.com
//Last change: 14/12/2022
//Changes: included library and using L293D motor shield


#include <math.h>
#include <AFMotor.h>


//DECLARE PINS

//buzzer
const int buzzer = 2;

//IndicatorLED
const int indicatorled = 13;

//sensors
const int PIRsensor = A0;

//Bumper
const int bumpersensor = A2;

//L293D driver motors
AF_DCMotor left_wheel_motor(1); //first wheel motor (left wheel)
AF_DCMotor right_wheel_motor(2); //second wheel motor (right wheel)
AF_DCMotor fan_motor(3); //drivers for fan
AF_DCMotor sweeper_motor(4); //drivers for sweepers


//constants


// Variables that will change:
int PIRstate = 0;  //PIRsensor sensor is low without human motion but high otherwise
int bumperstate = 0;  // variable for reading the bumpersensor status, bumperstate is high without being pressed but low when pressed
boolean control = true;
int counter = 0; //   to allow the robot to initialise sucessfully
int i = 5; // used to reduce the frequency of PIR sensor update


//CODE BEGINS

void setup() {
  //Initialize outputs and inputs
  //OUTPUTS
  //buzzer
  pinMode(buzzer, OUTPUT);
  
  //LED
  pinMode(indicatorled, OUTPUT);
  
  //INPUTS
  //PIR sensor
  pinMode(PIRsensor, INPUT);
  
  //Bumper sensor
  pinMode(bumpersensor, INPUT);  
  
  
  // Initialize serial
  //Serial.begin();

  //display blinking as initialisation
  waitBlinking(3,1); //3 seconds at 1 Hz
  delay(1000); //For 1000ms
  /*fan_motor.setSpeed(200);
  fan_motor.run(FORWARD);
  sweeper_motor.setSpeed(100);
  sweeper_motor.run(FORWARD); */
}

//Declare Functions To Use

void waitBlinking(int n, int frequency){
  //blink for n seconds at frequency hz
  for (int i=1; i <= n; i++){
    for(int j=1; j<=frequency; j++){
      digitalWrite(indicatorled, HIGH);   
      delay((1000/frequency)/2);   //Half time on            
      digitalWrite(indicatorled, LOW);   
      delay((1000/frequency)/2);   //Half time off
    }
   } 
}

void checkPIRsensor() {
  PIRstate = digitalRead(PIRsensor);
}

void checkBumpersensor() {
  bumperstate = digitalRead(bumpersensor);
}

void forwardMotion(int moveTime){  
  //Manipulate direction according the desired movement of the motor, for the forward motion, the right wheel have been made to move faster than the left wheel because the wheels are not properly aligned, the robot tends to move to the rightand i needed straight motion.
  left_wheel_motor.setSpeed(42);
  left_wheel_motor.run(FORWARD);
  right_wheel_motor.setSpeed(48);
  right_wheel_motor.run(FORWARD);
  delay(moveTime);
}

void rightTurn(int moveTime){ 
  left_wheel_motor.setSpeed(50);
  left_wheel_motor.run(FORWARD);
  right_wheel_motor.setSpeed(50);
  right_wheel_motor.run(BACKWARD);
  delay(moveTime);
  stopMotion(50);
  checkBumpersensor();  //check bumpersensor
  if (bumperstate == LOW) {           //bumper is pressed, obstacle is detected
        stopMotion(100);
        backwardMotion(300);
        stopMotion(100);
  }
}

void leftTurn(int moveTime){ 
  left_wheel_motor.setSpeed(50);
  left_wheel_motor.run(BACKWARD);
  right_wheel_motor.setSpeed(50);
  right_wheel_motor.run(FORWARD);
  delay(moveTime);
  stopMotion(50);
  checkBumpersensor();  //check bumpersensor
  if (bumperstate == LOW) {           //bumper is pressed, obstacle is detected
        stopMotion(100);
        backwardMotion(300);
        stopMotion(100);
   }
}

void backwardMotion(int moveTime){
  left_wheel_motor.setSpeed(50);
  left_wheel_motor.run(BACKWARD);
  right_wheel_motor.setSpeed(50);
  right_wheel_motor.run(BACKWARD);
  delay(moveTime);
}

void stopMotion(int moveTime){ 
  left_wheel_motor.setSpeed(0);
  left_wheel_motor.run(RELEASE);
  right_wheel_motor.setSpeed(0);
  right_wheel_motor.run(RELEASE);
  delay(moveTime);
}


//MAIN CODE
void loop(){
  
    digitalWrite(indicatorled, HIGH);
  
    if (i == 5) {
    checkPIRsensor();     //check PIR sensor
    i = 0;
    }

    i++;
    checkBumpersensor();  //check bumpersensor
  
    if (PIRstate == LOW) {           //does not detect human motion
      
      digitalWrite(buzzer, LOW);
      fan_motor.setSpeed(150);
      fan_motor.run(FORWARD);
      sweeper_motor.setSpeed(120);
      sweeper_motor.run(FORWARD);
      
      if (bumperstate == HIGH) {           //bumper is not pressed, obstacle is not detected
        forwardMotion(0);
      }

      else {            //bumper is pressed, i.e obstacle detected
        stopMotion(100);
        backwardMotion(300);
        stopMotion(100);
        i = 0;
        
        if (counter == 1) {
          leftTurn(910);
          stopMotion(100);
          forwardMotion(750);
          stopMotion(100);
          leftTurn(910);
          stopMotion(100);
          counter = 2;
        }

        else if (counter == 2) {
          rightTurn(910);
          stopMotion(100);
          forwardMotion(850);
          stopMotion(50);
          rightTurn(910);
          stopMotion(50);
          counter = 1;
        }

        //this code tries to initialise the robot to a required state
        else if (counter == 0) {
          leftTurn(910);
          stopMotion(100);
          counter = 1;
        }
      }
    
    }

    //if human motion is detected
    else {
      i = 5;
      stopMotion(100);
      digitalWrite(buzzer, HIGH);
      fan_motor.setSpeed(0);
      fan_motor.run(RELEASE);
      sweeper_motor.setSpeed(0);
      sweeper_motor.run(RELEASE);
    }
  
  delay(0);
  
}
