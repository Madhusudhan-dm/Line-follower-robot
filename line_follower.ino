//l298N motor run
//white line follower
//white<<threshold--25
//black >> threshold -- 1020

//Array sensor connection
#define ext_right_sensor A3
#define right_sensor A4
#define center_sensor A5
#define left_sensor A6


//L293N connection
const int v_speed = 150; // minimum speed or voltage level required for a robot to run
const int motorLspeed = 5;
const int motorRspeed = 6;
const int motorL1 = 7 ;
const int motorL2 = 8;
const int motorR1 = 9;
const int motorR2 = 10;

const int threshold = 500;
int boost = 0;
int flag = 0;
int error = 0;//for right turn
int error1 = 0;//for left turn
int error2 = 0;

int left_value = 0;
int right_value = 0;
int ext_right_value = 0;
int center_value = 0;



void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(motorR2, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);
  pinMode(motorLspeed, OUTPUT);
  pinMode(motorRspeed, OUTPUT);
  pinMode(left_sensor, INPUT);
  pinMode(center_sensor, INPUT);
  pinMode(right_sensor, INPUT);
  pinMode(ext_right_sensor, INPUT);
 
  Serial.begin(300);
}


void forward() {
  analogWrite(motorRspeed, v_speed - 40);
  analogWrite(motorLspeed, v_speed - 40);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  Serial.println("FORWARD");
}

void right(int boost) {
  analogWrite(motorRspeed, 0);
  analogWrite(motorLspeed, v_speed + 30 + boost);
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
  Serial.println("RIGHT");
  

}

void left(int boost) {
  analogWrite(motorRspeed, v_speed + 30 + boost);
  analogWrite(motorLspeed, 0);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);
  Serial.println("LEFT");

}

void u_turn() {
  analogWrite(motorRspeed, v_speed + 20);
  analogWrite(motorLspeed, v_speed + 20);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  Serial.println("u_turn");

}

void u_right_turn(){
  analogWrite(motorRspeed, v_speed + 40);
  analogWrite(motorLspeed, v_speed + 40);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  Serial.println("u__right_turn");
  
}

void Stop() {
  analogWrite(motorRspeed, 0);
  analogWrite(motorLspeed, 0);
  analogWrite(motorR1, LOW);
  analogWrite(motorR2, LOW);
  analogWrite(motorL1, LOW);
  analogWrite(motorL2, LOW);
  Serial.println("STOP");
}

void led_blink(){
    digitalWrite(LED_BUILTIN, HIGH);
    delayMicroseconds(400);
    digitalWrite(LED_BUILTIN, LOW);

 }


void loop() {
  // put your main code here, to run repeatedly:
  left_value = analogRead(left_sensor);
  center_value = analogRead(center_sensor);
  right_value = analogRead(right_sensor);
  ext_right_value = analogRead(ext_right_sensor);

  //straight
  if (left_value > threshold && right_value > threshold && center_value < threshold) {
  
    if(error1 == 1){
      
      error = 0;
      error1 = 0;
      //error2 = 1;
      left(50);
      Serial.println("second left");
      
    }
    else{
      
    error = 0;
    error1 = 0;
    error2 = 0;  
    forward();
    
    }
  

  }
  //left
  else if(left_value < threshold && right_value > threshold && center_value > threshold){
   
   error = 0;
   error1 = 0;
   error2 = 0;
   left(0);
  }

  //left l
  else if (left_value < threshold && right_value > threshold && center_value < threshold) {
   
   left(50);
   error = 0;
   error1 = 1;
   error2 = 0;
  
  }

  //T junc
  else if(left_value < threshold && right_value < threshold && center_value > threshold){
    
    Stop();
    error = 0;
    error1 = 0;
    error2 = 0;
    left(50);
    
  }

  //+ junc 
  else if (left_value < threshold && right_value < threshold && center_value < threshold && flag == 0) {
    left(90);
    error = 0;
    error1 = 1;
      if(ext_right_value < threshold && right_value < threshold){
        Stop();
        led_blink();
        flag = 1;
      }
      else{
        left(30);
        flag = 0;
      }
  }
  //right l
  else if (left_value > threshold && right_value < threshold && center_value < threshold ) {
    
    error = 3;
    error1 = 0;
    error2 = 0;
    Stop();
    forward();


  }

  //right
  else if(left_value > threshold && right_value < threshold && center_value > threshold){
    error1 = 0;
 
    right(0);
    if(center_value > threshold){
      flag = 2;
      error = 3;
      right(30);
      Stop();
    }

}
  
  //dead end
  else if (left_value > threshold && right_value > threshold && center_value > threshold) {
    error2 = 0;
    if(flag == 2){
      Stop();
      right(30);
      Serial.print("flag:");
      Serial.println(flag);
      flag = 0;
    }
    else if(error >= 1){
      
      u_right_turn();
      error = error-1;
      Serial.print("error:");
      Serial.println(error);
    }
    else{
      u_turn();
      error = 0;
      Serial.print("flag:");
      Serial.println(flag);
    }
  }

  else {
    Stop();
    led_blink();

  }

}
