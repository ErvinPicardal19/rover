#include<Servo.h>
#include <Wire.h>


#define en1 3
#define input1 4
#define input2 5

#define en2 6
#define input3 7
#define input4 8

#define SPEED_INPUT 11

double channel;

Servo Claw;

String flag = "";
bool speed_change_mode = false;
int speed = 0;
int angle = 0;
// String dir = "";

void setup(){
  Serial.begin(115200);
  Serial.println("Started!");
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Claw.attach(10);
  Claw.write(0);
  // delay(500);

  // for(int i=0; i<=60; i++){
  //   myservo.write(i);
  //   delay(100);
  // }

  pinMode(en1, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);

  pinMode(en2, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(input4, OUTPUT);  
 
  pinMode(SPEED_INPUT, INPUT);  
}

void receiveEvent(int howMany)
{
  // Serial.print("HowMany: ");
  // Serial.println(howMany);
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    // Serial.print(c);         // print the character
    flag += c;        
  }
  Serial.print(flag + " :");
  if(flag == "speed"){
    int val = Wire.read();
    changeSpeed(val);
    Serial.println(val);
    flag=""; 
    return;   
  } else if(flag == "claw"){
    int temp = Wire.read();
    int val = map(temp, 0, 180, 0, 50);
    if(val != angle){
      changeClaw(val);
      Serial.println(val);
    }
    flag="";
    return;
  } else if(flag == "control"){
    byte tmp = Wire.read();
    char dir = tmp;
    Serial.println(dir);   
    delay(100);

  if(dir == 'u'){
    Serial.println("Going Up");
    forward();
  }
  else if(dir == 'l'){
    Serial.println("Going left");
    left();
  }
  else if(dir == 'r'){
    Serial.println("Going right");
    right();
  }
  else if(dir == 'd'){
    Serial.println("Going down");
    reverse();
  }
  else if(dir == 's'){
    Serial.println("Stopping");
    // for(int i = speed; i > 0; i--){
    //   analogWrite(en1, i);
    //   analogWrite(en2, i);
    //   Serial.print("Slowing speed: ");
    //   Serial.println(i);
    //   delay(10);
    // }
    analogWrite(en1, 0);
    analogWrite(en2, 0);
    digitalWrite(input1, 0);
    digitalWrite(input2, 0);
    digitalWrite(input3, 0);
    digitalWrite(input4, 0);
    Serial.println("Stopped");
  }
  dir="";
  flag=""; 
  return; 
  }
  Wire.flush();
}

void changeSpeed(int newSpeed){
  speed = newSpeed;
}

void changeClaw(int newAngle){
  angle = newAngle;
  Claw.write(newAngle);
}


void loop(){
  delay(100);
}

void forward(){
  Serial.print("Speed: ");
  Serial.println(speed);
  analogWrite(en1, speed);
  analogWrite(en2, speed);      
  digitalWrite(input1, 1);
  digitalWrite(input2, 0);
  digitalWrite(input3, 0);
  digitalWrite(input4, 1);
}

void reverse(){
  Serial.print("Speed: ");
  Serial.println(speed);
  analogWrite(en1, speed);
  analogWrite(en2, speed);      
  digitalWrite(input1, 0);
  digitalWrite(input2, 1);
  digitalWrite(input3, 1);
  digitalWrite(input4, 0);
}

void left(){
  Serial.print("Speed: ");
  Serial.println(speed);
  analogWrite(en1, 240);
  analogWrite(en2, 240);      
  digitalWrite(input1, 0);
  digitalWrite(input2, 1);
  digitalWrite(input3, 0);
  digitalWrite(input4, 1);
  // delay(50000);
  // Serial.println("Stop");
  // analogWrite(en1, 0);
  // analogWrite(en2, 0);      
  // digitalWrite(input1, 0);
  // digitalWrite(input2, 0);
  // digitalWrite(input3, 0);
  // digitalWrite(input4, 0);
  
}

void right(){
  Serial.print("Speed: ");
  Serial.println(speed);
  analogWrite(en1, speed);
  analogWrite(en2, speed);      
  digitalWrite(input1, 1);
  digitalWrite(input2, 0);
  digitalWrite(input3, 1);
  digitalWrite(input4, 0);
}