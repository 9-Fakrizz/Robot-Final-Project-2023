#include <Servo.h>
#define trigPin 11
#define echoPin 10

Servo servo;
int led[3] = {2,3,4};
int idr = A0;
int pir = 8;
int pirState = 0;
bool door_status = false;
bool *ptrStatus = &door_status;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(idr,INPUT);
  pinMode(pir, INPUT);
  servo.attach(9);

  pinMode(led,OUTPUT);
}
void led_Emerg(){
  /*ไฟติด 3 ดวง เรียงกัน 1 ติด แล้ว 2 ติด ตามด้วย3  1ดับ 2ดับ แล้วตามด้วย3*/
  
for(int i=0;i<=2;i++){ 
digitalWrite(led[i],1);
  delay(100);  
}
for(int i=0;i<3;i++){
  digitalWrite(led[i],0);
  delay(100);

}
}

void Door_Open(bool door_status){
   
 if(door_status != true){
   for (int pos = 0; pos <= 100; pos += 1) {
      servo.write(pos);  
      Serial.println("S"); 
      delay(50);               
    }
    door_status = true;
        
  }
  /*ไฟติด 3 ดวง*/
  digitalWrite(led[0],1);
  delay(1000);
  digitalWrite(led[1],1);
  delay(1000);
  digitalWrite(led[2],1);
  delay(1000);
}

void Door_Closed(){

}

void Half_Door(){
  /*ไฟติด 1 ดวง*/
  digitalWrite(led[0],1);
  delay(1000);    
}

void water() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
 
  if (distance < 10) {
    servo.write(0); 
    delay(1000); 
    servo.write(90);
    delay(1000);
    servo.write(180); 
    delay(1000);
  }

  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(100);
}

void light() {
  int val = analogRead(idr);
  Serial.print("Light : ");
  Serial.println(val);  
  
  if(val < 100){
    servo.write(0); 
    delay(1000); 
  }
  else{
    servo.write(300); 
    delay(1000); 
  }
}

void motion_pir(){
  pirState = digitalRead(pir);

  Serial.print("pirState : "); Serial.println(pirState);

  if (pirState == HIGH) {
    Serial.println("PIR ON");
    servo.write(0); 
    delay(1000);    
  }

  else if (pirState == LOW) {
    servo.write(300); 
    delay(1000);

  }
  
}

void loop(){
  
  Door_Open();
  /*Serial.println(*ptrStatus);
  delay(1000);
  Door_Open(false);
  Serial.println(*ptrStatus);*/
  
}