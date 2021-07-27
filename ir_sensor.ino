//ir sensor
//pin A7 doesnt work unfortunately


//white<<threshold--25
//black >> threshold -- 1020 
#define left_sensor A6
#define center_sensor A5
#define right_sensor A4
#define ext_right_sensor A3

float left_sensor_value;
float center_sensor_value;
float right_sensor_value;
float ext_right_sensor_value;

void setup() {
   //put your setup code here, to run once:
  pinMode(left_sensor,INPUT);
  pinMode(center_sensor,INPUT);
  pinMode(right_sensor,INPUT);
  pinMode(ext_right_sensor,INPUT);
  Serial.begin(300);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  left_sensor_value  = analogRead(left_sensor);
  center_sensor_value  = analogRead(center_sensor);
  right_sensor_value  = analogRead(right_sensor);
  ext_right_sensor_value = analogRead(ext_right_sensor);
  
  Serial.println(left_sensor_value);
  Serial.println(center_sensor_value);
  Serial.println(right_sensor_value);
  Serial.println(ext_right_sensor); 
}
