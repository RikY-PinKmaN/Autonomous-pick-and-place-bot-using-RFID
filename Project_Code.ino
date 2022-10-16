#include <Servo.h>
#define big_servo 10            // pin10 assigned for Larger servo 
#define small_servo 11          // pin11 assigned for smaller servo
#include <SharpIR.h>
#define IRAPin A1
#define IRBPin A3
#define IRCPin A5


int distanceA;
int distanceB;
int distanceC;

int lim = 20;
int lim2 = 25;
int temp = 0;
int servo_big_angle = 45;
int servo_small_angle = 26;

SharpIR sensorA( SharpIR::GP2Y0A21YK0F, IRAPin );
SharpIR sensorB( SharpIR::GP2Y0A21YK0F, IRBPin );
SharpIR sensorC( SharpIR::GP2Y0A21YK0F, IRCPin );

Servo servo_big;
Servo servo_small;

// Pin Allocation for Motors 
const int Motor_1A = 2;         //pin1 assigned for motor 1
const int Motor_1B = 4;         //pin2 assigned for motor 1
const int Motor_2A = 7;         //pin1 assigned for motor 2
const int Motor_2B = 8;         //pin2 assigned for motor 2
const int robotA_speed_pin = 5;
const int robotB_speed_pin = 3;
const int PinStandBy = 9;
const int speed_controller=A0;

// Assigning initial values to the variables for motor rotation 
boolean M1A = 0;
boolean M1B = 0;
boolean M2A = 0;
boolean M2B = 0;
boolean StandBy = 0; 
boolean rotDirection = 0;
unsigned char speed_value = 0;

void MoveForward ( int speed_value)
{
  M1A=true;
  M1B=false;
  M2A=false;
  M2B=true;
  digitalWrite(Motor_1A,M1A);
  digitalWrite(Motor_1B,M1B);
  digitalWrite(Motor_2A,M2A);
  digitalWrite(Motor_2B,M2B);
  analogWrite(robotA_speed_pin,speed_value-6);
  analogWrite(robotB_speed_pin,speed_value);
}
void MoveLeft ( int speed_value)
{
  M1A=false;
  M1B=true;
  M2A=false;
  M2B=true;
  digitalWrite(Motor_1A,M1A);
  digitalWrite(Motor_1B,M1B);
  digitalWrite(Motor_2A,M2A);
  digitalWrite(Motor_2B,M2B);
  analogWrite(robotA_speed_pin,speed_value-6);
  analogWrite(robotB_speed_pin,speed_value);
}
void MoveRight ( int speed_value)
{
  M1A=true;
  M1B=false;
  M2A=true;
  M2B=false;
  digitalWrite(Motor_1A,M1A);
  digitalWrite(Motor_1B,M1B);
  digitalWrite(Motor_2A,M2A);
  digitalWrite(Motor_2B,M2B);
  analogWrite(robotA_speed_pin,speed_value-6);
  analogWrite(robotB_speed_pin,speed_value);
}
void Stop ()
{
  M1A=false;
  M1B=false;
  M2A=false;
  M2B=false;
  digitalWrite(Motor_1A,M1A);
  digitalWrite(Motor_1B,M1B);
  digitalWrite(Motor_2A,M2A);
  digitalWrite(Motor_2B,M2B);
  analogWrite(robotA_speed_pin,speed_value);
  analogWrite(robotB_speed_pin,speed_value);
}

void Grab_Object()
{
  servo_small.write(0);
  delay(500);
  servo_big.write(servo_big_angle);
  delay(500);
  servo_small.write(servo_small_angle);
  delay(500);
  servo_big.write(0);
}

void Release_Object()
{
  servo_big.write(0);
  delay(500);
  servo_big.write(servo_big_angle);
  delay(500);
  servo_small.write(0);
  delay(500);
  servo_big.write(0);
  delay(500);
  servo_small.write(servo_small_angle);
}
void setup() 
{
  pinMode(Motor_1A,OUTPUT);
  pinMode(Motor_1B,OUTPUT);
  pinMode(Motor_2A,OUTPUT);
  pinMode(Motor_2B,OUTPUT);
  pinMode(robotA_speed_pin,OUTPUT);
  pinMode(robotB_speed_pin,OUTPUT);
  pinMode(PinStandBy,OUTPUT);
  pinMode(speed_controller,INPUT);
  Serial.begin(9600);  //Initialize the serial port
  StandBy = true;
  digitalWrite(PinStandBy,StandBy);

  servo_big.attach(big_servo);
  servo_small.attach(small_servo);
  servo_big.write(0);
  servo_small.write(40);
  
 }


void loop() 
{
  // setting robot's speed 
  int speed_val;
  speed_value = 75;
  //speed_val=analogRead(speed_controller);
  //speed_value=map(speed_val,0,1023,0,250);
  //delay(500);
  distanceA = sensorA.getDistance();
  distanceB = sensorB.getDistance();
  distanceC = sensorC.getDistance();
  Serial.print("A");
  Serial.println(distanceA);
  Serial.print("B");
  
  Serial.println(distanceB);
  Serial.print("C");
  Serial.println(distanceC);

  /*if(temp == 0)  //grab cube
  {
    Stop();
    //delay(500);
    Grab_Object();
    temp = 1;
    }*/

  if(distanceB < lim || distanceC < lim  || distanceA < lim)  //left corner
  {
    if(distanceB < distanceC){
      MoveRight(speed_value);
      delay(1);
     // temp = temp++;
    }
    else{
      MoveLeft(speed_value);
      delay(1);
     // temp = temp++;
    }
  }

  /*else if( distanceA < lim )  //grab cube
  {
    Stop();
    //delay(500);
    Grab_Object();
    }*/
 
  else if(distanceA < lim2)
  {
    Stop();
    //delay(500);
    Release_Object();
    }    
    
  else
  {
    MoveForward(speed_value);
    temp = 0;
    }
}
