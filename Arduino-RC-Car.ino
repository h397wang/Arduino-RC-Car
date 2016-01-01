/* RC Car has two modes: Remote Control Mode or Line Following Mode
 * The wheels on my car are imbalanced with a balanced speed of: left = 157 and right = 200
 * This example assumes a balanced pair of wheels
 * 
 */

#include <IRremote.h>

int ReceivePin = 6;

IRrecv irrecv(ReceivePin);
decode_results results;

// Establish remote control keys
long keyCHminus = 0x00FFE21D; // veer right, makes the left wheel faster
long keyCHplus = 0x00FFA25D; // veer left, makes the right wheel faster
long keyCH = 0x00FF629D;  // straight/accelerate
long keyPause = 0x00FFC23D; // halt
long keyNext = 0x00FF02FD; // deaccelerate
long keyPositive = 0x00FFA857;

// Establish Motorshield pins
int leftMotorForward = 8;
int leftMotorBackward = 11;
int leftMotorSpeed = 9;

int rightMotorForward = 12;
int rightMotorBackward = 13;
int rightMotorSpeed = 10;

#DEFINE LEFTSENSOR A0
#DEFINE RIGHTSENSOR A1

// ultrasonic sensor
int pingPin = 7; 

// other parameters
int think = 2000;
int turningTime = 500; 
int runTime = 5000;
int slow = 100; // minimum output required
int fast = 200; // max
int acceleration = 50;

int leftSpeed = 0; 
int rightSpeed = 0;

int immobile = 1;

int state = 0;

#DEFINE RC 0
#DEFINE LINE 1


void setup(){
  // car is initially immobile
  
  state = RC;     
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(leftMotorSpeed, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  pinMode(rightMotorSpeed, OUTPUT);

  pinMode(LEFTSENSOR, INPUT);
  pinMode(RIGHTSENSOR, INPUT);
  
  irrecv.enableIRIn(); // start the receiver
  Serial.begin(9600); // for troubleshooting
}

void loop(){
  
  analogWrite(leftMotorSpeed, leftSpeed);
  analogWrite(rightMotorSpeed, rightMotor);
  
  switch(state):
    case RC:
      // going forwards by default
      
      digitalWrite(leftMotorBackward, LOW);
      digitalWrite(rightMotorBackward, LOW);
      digitalWrite(leftMotorForward, HIGH);
      digitalWrite(rightMotorForward, HIGH);

      int i = 0; // not sure why this is neccesary...
      if (irrecv.decode(&results)){
        irrecv.resume(); // receives the next value
        
        if (results.value == keyCHplus){
          rightTurn();
          Serial.println("right turn");
        }else if (results.value == keyCHminus){
          leftTurn();
          Serial.println("left turn");
        }else if (results.value == keyCH){
          straight();
          Serial.println("straight");
        }else if (results.value == keyNext){
          
          if (!immobile){
              slowDown(); 
          }else{
              goBackwards();
          }
          
        }else if (results.value == keyPause){
          halt();
        }else if (results.value == keyPositive){
          rotateCCW();
        }
      }
      break;
    case LINE:
        leftSensor = analogRead(A0);
        rightSensor = analogRead(A1);
        Serial.println(leftSensor);
        Serial.println(rightSensor);

        if (leftSensor >= 800){
            // turn left
            leftSpeed = 0;
            rightSpeed = 150;
            
        }else if (rightSensor >= 800){
            // veer right
            leftSpeed = 150;
            rightSpeed = 0;
            
        }else{
            // go straight
            leftSpeed = 150;
            rightSpeed = 150;
        }
        break;
    }
}

void straight(){ 
  // starts the car forward, or goes straight, or accelerates it
  if (immobile){ // initiate movement, moderate speed
    leftSpeed = 150;
    rightSpeed = 150;
    immobile = 0;

  /*
  }else if (leftSpeed != rightSpeed){ // picks the smaller of speeds to realign
    int newSpeed = min(leftSpeed, rightSpeed);
    leftSpeed = newSpeed;
    rightSpeed = newSpeed;
  
  */
  
  }else{ // accelerate
    leftSpeed += acceleration;
    rightSpeed += acceleration;
    check();
  }
}

void slowDown(){
    // reduces the speed of the wheels by the value of acceleration
    // if the value is to go below 100, then it halts the car instead
    
  leftSpeed -= acceleration;
  rightSpeed -= acceleration;
  
  if (leftSpeed < 100 && rightSpeed < 100){
    halt(); //sets speeds back to 0
  }
}

void goBackwards(){
  // if the car is currently immobile then the car reverses one carlength and stops
  
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, LOW);
  analogWrite(leftMotorSpeed, 100);
  analogWrite(rightMotorSpeed, 100);
  delay(1000);
  
}

void rightTurn(){
  // this makes the head of the car turn some angle right
  // the speed of the left wheel is increased for a second
  // does not actually modify the value of left and right speed
  analogWrite(leftMotorSpeed, leftSpeed + acceleration);
  analogWrite(rightMotorSpeed, rightSpeed);
  delay(turningTime);
}

void leftTurn(){
  analogWrite(leftMotorSpeed, leftSpeed);
  analogWrite(rightMotorSpeed, rightSpeed + accleration);
  delay(turningTime);
}

void halt(){
  // sets speeds to zero, and immobile to true
  leftSpeed = 0;
  rightSpeed = 0;
  immobile = 1;
}

void rotateCCW(){
  // keeps rotating until another command
  leftSpeed = 0;
  immobile = 1;
}

void check(){
  // re-assigns values of motor speeds if they go out of limits
  if (leftSpeed > 200){
    leftSpeed = 200;
  }else if (leftSpeed < 100){
    leftSpeed = 100;
  }
  if (rightSpeed > 200){
    rightSpeed = 200;
  }else if (rightSpeed < 100){
    rightSpeed = 100;
  }
  
}
/*void update(){
  if (leftSpeed > 250){
    leftSpeed = 250;
  }else if (leftSpeed < 100){
    leftSpeed = 100;
  }
  if (rightSpeed > 250){
    rightSpeed = 250;
  }else if (rightSpeed < 100){
    rightSpeed = 100;
  }
  
  analogWrite(leftMotorSpeed, leftSpeed);
  analogWrite(rightMotorSpeed,rightSpeed);
}

*/

/*
int getDistance(){
  long duration;
  long distance;
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  distance = duration*340*pow(10,-8); // in cm
  Serial.println(distance);
  delay(1000);
  return distance;
}
*/
