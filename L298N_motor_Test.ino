//#include<L298N_motor_Test.h>
//l298N motor run
//L293N connection

const int v_speed = 150;
const int motorLspeed = 5;
const int motorRspeed = 6;
const int motorL1 = 7;
const int motorL2 = 8;
const int motorR1 = 9;
const int motorR2 = 10;
int flag = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(motorR2,OUTPUT);
  pinMode(motorR1,OUTPUT);
  pinMode(motorL1,OUTPUT);
  pinMode(motorL2,OUTPUT);
  pinMode(motorLspeed,OUTPUT);
  pinMode(motorRspeed,OUTPUT);
  
  Serial.begin(300);

}


void forward(){
  analogWrite(motorRspeed,120);
  analogWrite(motorLspeed,120);//0.8v
  digitalWrite(motorR1,HIGH);
  digitalWrite(motorR2,LOW);
  digitalWrite(motorL1,HIGH);
  digitalWrite(motorL2,LOW);
  Serial.println("FORWARD");
}

void backward(){
  digitalWrite(motorR1,LOW);
  digitalWrite(motorR2,HIGH);
  digitalWrite(motorL1,LOW);
  digitalWrite(motorL2,HIGH);
  Serial.println("BACKWARD");
  
}

void right(){
  analogWrite(motorRspeed,0);
  analogWrite(motorLspeed,160);//1.65 aactually 6v
  digitalWrite(motorL1,HIGH);
  digitalWrite(motorL2,LOW);
  digitalWrite(motorR1,LOW);
  digitalWrite(motorR2,LOW);
  Serial.println("RIGHT");
  
}

void left(){
  analogWrite(motorRspeed,160);//1.65
  analogWrite(motorLspeed,0);
  digitalWrite(motorR1,HIGH);
  digitalWrite(motorR2,LOW);
  digitalWrite(motorL1,LOW);
  digitalWrite(motorL2,LOW);
  Serial.println("LEFT");
    
}

void reverse(){
  analogWrite(motorRspeed,150);//1.5v
  analogWrite(motorLspeed,150);
  digitalWrite(motorR1,HIGH);
  digitalWrite(motorR2,LOW);
  digitalWrite(motorL1,LOW);
  digitalWrite(motorL2,HIGH);
  Serial.println("REVERSE");
   
}

void Stop(){
  analogWrite(motorRspeed,0);
  analogWrite(motorLspeed,0);
  analogWrite(motorR1,LOW);
  analogWrite(motorR2,LOW);
  analogWrite(motorL1,LOW);
  analogWrite(motorL2,LOW);
  Serial.println("STOP");
}

void loop() {
  // put your main code here, to run repeatedly:

  int flag = 0;
  do{
    right();
    flag = flag++;
  }while(flag<10);

  if (flag == 0){
    Serial.println(flag);
    forward();
    flag =1;
    delay(1000);
    
  }
  else if(flag == 1){
    Serial.println(flag);
    left();
    flag = 2;
    delay(1000);
  }
  else if(flag ==2){
    Serial.println(flag);
    right();
    flag = 3;
   delay(1000);
  }
  else if(flag == 3){
    Serial.println(flag);
    backward();
    flag =4;
    delay(1000);
  }
  else if(flag == 4){
    Serial.println(flag);
    reverse();
   flag = 5;
    delay(1000);
  }
  else{
    Serial.println(flag);
    Stop();
    flag = 0;
    delay(1000);

  }
  
}
