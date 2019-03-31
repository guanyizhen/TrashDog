#include "Servo.h"

int frontMic = A0;
int backMic = A1;
int leftMic = A2;
int rightMic = A3;

int frontVal = 5;
int backVal = 5;
int leftVal = 5;
int rightVal = 5;

unsigned long myservo1Move = 0;
unsigned long myservo2Move = 0;
unsigned long myservo3Move = 0;

int counter = 0;
int my_dir = 0;
int directList[4] = {0, 0, 0 ,0};
boolean moving = false;

Servo FrontServo;
Servo RightServo;
Servo LeftServo;

int FrontServoValue = 80;
int RightServoValue = 90;
int LeftServoValue = 90;

#define triggerPin 4
#define echoPin 5

unsigned long dist;
unsigned long newdistance;
long t;
unsigned long distanceInCM;

int right1 = 6;
int right2 = 7;
int left1 = 12;
int left2 = 13;
int front1 = 2;
int front2 = 3;

boolean myMove = false;

void setup() {
  Serial.begin(9600);
  //microphones
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(front1, OUTPUT);
  pinMode(front2, OUTPUT);
  //servos
  FrontServo.attach(9);
  RightServo.attach(10);
  LeftServo.attach(11);
  //ultrasonic sensor
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  stand();
  Serial.println("Armed");
}

void loop() {
  
  my_Mic();

}

void my_Mic(){
  my_dir = 0;
  counter = 0;
//  moving = false;
  Serial.println("Listening...");
  leftVal = analogRead(leftMic);
  rightVal = analogRead(rightMic);
  frontVal = analogRead(frontMic);
  backVal = analogRead(backMic);

  if (leftVal > 100){
    Serial.println("Left Detected");
    directList[counter] = 1;
    counter = counter + 1;
    moving = true;
    my_dir = 1;
  }
  if (rightVal > 100){
    Serial.println("right Detected");
    directList[counter] = 2;
    counter = counter + 1;
    moving = true;
    my_dir = 2;
  }
  if (frontVal > 100){
    Serial.println("front Detected");
    directList[counter] = 3;
    counter = counter + 1;
    moving = true;
    my_dir = 3;
  }
  if (backVal > 100){
    Serial.println("back Detected");
    directList[counter] = 4;
    counter = counter + 1;
    moving = true;
    my_dir = 4;
  }

  if (counter > 2){
    stand();
    moving = false;
  }
  else
  {
    my_dir = directList[0];
  }
    
   //start walking
   if (moving == true){
     moving = walk(my_dir);
   }
  
  if (counter > 0){
    Serial.println(counter);   
  }

  if (!moving){
    stand();
    delay(30);
  }

}

boolean walk(int dir){
  Serial.println("Moved!");


  if (dir ==1){
    digitalWrite(right1, LOW);
    digitalWrite(right2, HIGH);
    digitalWrite(left1, LOW);
    digitalWrite(left2, HIGH);
    digitalWrite(front1, LOW);
    digitalWrite(front2, HIGH);
      delay(2000);
  }
  else if (dir == 2){
    digitalWrite(right1, HIGH);
    digitalWrite(right2, LOW);
    digitalWrite(left1, HIGH);
    digitalWrite(left2, LOW);
    digitalWrite(front1, HIGH);
    digitalWrite(front2, LOW);
      delay(2000);
    
  }
  else if (dir == 4){
    digitalWrite(right1, HIGH);
    digitalWrite(right2, LOW);
    digitalWrite(left1, HIGH);
    digitalWrite(left2, LOW);
    digitalWrite(front1, HIGH);
    digitalWrite(front2, LOW);          
    delay(4000);

    
  }
  
  //turn wheel to some angles
//  if (dir == 1 || dir == 2){
//    FrontServo.write(80);
//    RightServo.write(32);
//    LeftServo.write(155);
//  }
//  
//  if (dir == 3 || dir == 4){
//    FrontServo.write(177);
//    RightServo.write(125);
//    LeftServo.write(60);
//  }

  FrontServo.write(177);
  RightServo.write(125);
  LeftServo.write(60);

  
  newdistance = findDist(triggerPin, echoPin);
  //while: walking for a distance
  while (newdistance >= 20){

      digitalWrite(right1, LOW);
      digitalWrite(right2, HIGH);
      digitalWrite(left1, HIGH);
      digitalWrite(left2, LOW);
      digitalWrite(front1, HIGH);
      digitalWrite(front2, LOW);


    
    // Going Left
//    if (dir == 1){
      //right1 HIGH, right2 LOW
      //left1 HIGH, left2 LOW
      //front1 LOW, front2 HIGH
//      digitalWrite(right1, HIGH);
//      digitalWrite(right2, LOW);
//      digitalWrite(left1, HIGH);
//      digitalWrite(left2, LOW);
//      digitalWrite(front1, LOW);
//      digitalWrite(front2, HIGH);        
//    }
    // Going Right
//    else if (dir == 2){
      //right1 LOW, right2 HIGH
      //left1 LOW, left2 HIGH
      //front1 HIGH, front2 LOW
//      digitalWrite(right1, LOW);
//      digitalWrite(right2, HIGH);
//      digitalWrite(left1, LOW);
//      digitalWrite(left2, HIGH);
//      digitalWrite(front1, HIGH);
//      digitalWrite(front2, LOW);
//    }
    // Going Forward
//    else if (dir == 3){
      //right1 LOW, right2 HIGH
      //left1 HIGH, left2 LOW
      //front1 HIGH, front2 LOW
//      digitalWrite(right1, LOW);
//      digitalWrite(right2, HIGH);
//      digitalWrite(left1, HIGH);
//      digitalWrite(left2, LOW);
//      digitalWrite(front1, HIGH);
//      digitalWrite(front2, LOW);
//    }
    // Going Backward
//    else{
      //right1 HIGH, right2 LOW
      //left1 LOW, left2 HIGH
      //front1 LOW, front2 HIGH
//      digitalWrite(right1, HIGH);
//      digitalWrite(right2, LOW);
//      digitalWrite(left1, LOW);
//      digitalWrite(left2, HIGH);
//      digitalWrite(front1, LOW);
//      digitalWrite(front2, HIGH);
//    }
    newdistance = findDist(triggerPin, echoPin);
  }
  Serial.println("Standby");
  return false;
  
}


void stand(){
  //Serial.println("Stand!");
  FrontServo.write(FrontServoValue);
  RightServo.write(RightServoValue);
  LeftServo.write(LeftServoValue);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  digitalWrite(front1, LOW);
  digitalWrite(front2, LOW);
}

int findDist(int trigger, int echo){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(echo, LOW);
  t = pulseIn(echo, HIGH);
  distanceInCM = t*0.034/2.0;
  return distanceInCM;
}
