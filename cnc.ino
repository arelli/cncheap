#include <AccelStepper.h>
#include <Servo.h>//the library that allows it to work with the stylus servo
//it does not use the Stepper.H library!The EasyDriver does part of the job,and the AccelStepper library the rest.
Servo stylus_servo;

#define HALFSTEP 8
#define motorPin1  7    // IN1 on the ULN2003 driver 
#define motorPin2  8     // IN2 on the ULN2003 driver 
#define motorPin3  9     // IN3 on the ULN2003 driver 
#define motorPin4  10     // IN4 on the ULN2003 driver 

#define  PIXEL 0.3

#define stp 2 //trigger to make one step
#define dir 3 //trigger to change step direction
#define MS1 4
#define MS2 5
#define EN  6 //enable or disable the EasyDriver controller

AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);//initialize the x axis stepper

char user_input;
int i,pos,lastX,lastY,x;//counetrs and memory of the last movement


void setup() {
  stylus_servo.attach(11); //pin to attach control cable of servo
  stepper1.setMaxSpeed(2000.0);
  stepper1.move(1);
  stepper1.setSpeed(900);
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  resetEDPins(); //fucntion to Set step direction microstep and enable pins to default 
  Serial.begin(9600); //Open Serial connection for debugging
  //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1.up");
  Serial.println("2.down");
  Serial.println("3.right");
  Serial.println("4.left");
  Serial.println("5. Stylus Down");
  Serial.println("6. Stylus Up");
  Serial.println("Open cu at -s 9600 and type ~$filename_with_vectors to enter vector \n sequence from a file." );
  stylus_servo.write(5);//initializes the stylus servo to the up position   
  delay(500);//give the head time to reach up position

}

void loop() {
    while(Serial.available()){
      user_input = Serial.read(); //Read user input and trigger appropriate function
      digitalWrite(EN, LOW); //Pull enable pin low to turn on motor control on the EasyDriver
      if (user_input =='1')//up
      {
        digitalWrite(dir, LOW);
        for(x= 1; x<PIXEL*7; x++){  //Loop the forward stepping enough times for motion to be visible
               digitalWrite(stp,HIGH); //Trigger one step forward
               delay(1);
               digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
               delay(1);
        }
      }
      else if(user_input =='2')//down
      {
        digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
        for(x= 1; x<PIXEL*7; x++)  //Loop the stepping enough times for motion to be visible
            {
              digitalWrite(stp,HIGH); //Trigger one step
              delay(1);
              digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
              delay(1);
        }
      }
      
      else if(user_input =='3')//right
      {
        for(i=0;i<PIXEL*2300;i++){//loop to leave time for the AccelStepper library to work its magic
        stepper1.move(100);
        stepper1.setSpeed(900);
        stepper1.runSpeedToPosition();
        }
      }
      
      else if(user_input =='4')//left
      {
        for(i=0;i<PIXEL*2300;i++){//loop to leave time for the AccelStepper library to work its magic
        stepper1.move(-100);
        stepper1.setSpeed(900);
        stepper1.runSpeedToPosition();
        }
      }
      else if(user_input=='5')//moves the stylus to the up position
      {
          stylus_servo.write(55);
          delay(200);
       }   
       else if(user_input=='6')//moves the stylus to the up position
      {
         stylus_servo.write(5);
       }           
      else
      {
        Serial.print("Invalid option  entered: ");
        Serial.println(user_input);
      }
      resetEDPins();
    }
  }

//end of MAIN

void resetEDPins()//resetting the logical pins on the EasyDriver 
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
}





