#include <Servo.h>
#define trigPin 11
#define echoPin 10
#define BUTTON_PIN 5
#define BUTTON_PIN2 13

Servo servo;
const int buzzerPin = 6;
int led[3] = {3,2,4};
int ldr0 = A0;
int ldr1 = A1;
int pir = 8;
int count = 0;
int frame=0;
int pirState = 0;
long duration, distance;
bool door_status = false;
bool tasking_available = true;
bool half = false;

void setup() {
  Serial.begin (115200);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUTTON_PIN2, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ldr0,INPUT);
  pinMode(ldr1,INPUT);
  pinMode(pir, INPUT);
  servo.attach(9);
  pinMode(led,OUTPUT);

}
void buzzer_normal(){
  delay(250);
  tone(buzzerPin, 300, 100);
  delay(100);
  tone(buzzerPin, 490, 100);
  }
void buzzer_emerg(){
  analogWrite(buzzerPin, 100);
  delay(200);
  tone(buzzerPin, 350, 100);
  analogWrite(buzzerPin, 0);
  }

void door_close(){
  servo.writeMicroseconds(1350);
  delay(100);
  servo.writeMicroseconds(1500);
}

void door_open(){
  servo.writeMicroseconds(1595);
  delay(300);
  servo.writeMicroseconds(1500);
}

int light0() {
  int val = analogRead(ldr0);
  return val;
}

int light1() {
  int val = analogRead(ldr1);
  return val;
}

void loop(){
  byte emergency = digitalRead(BUTTON_PIN);
  byte buttonState = digitalRead(BUTTON_PIN2);
  ////////////////////////////////////
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  pirState = digitalRead(pir);
  ////////////////////////////////////
   Serial.print("ldr0: ");
   Serial.print(light0());

   Serial.print("   ldr1: ");
   Serial.println(light1());

   Serial.print("PIR: ");
   Serial.print( pirState);

   Serial.print("   UltraSonic: ");
   Serial.println(distance);

   Serial.print("Door Status: ");
   Serial.print(door_status);

   Serial.print("     Tasking Available :  ");
   Serial.println(tasking_available);

   Serial.print("Yellow button: ");
   Serial.print(buttonState);

   Serial.print("     Emergency :  ");
   Serial.println(emergency);

   Serial.print("   FRAME ----------  ");
   Serial.println(frame);

   
  
  if(light1()<600){//noon
    count = 8;
    digitalWrite(led[0],LOW);
    digitalWrite(led[1],LOW);
    digitalWrite(led[2],LOW);
    Serial.println("Setto ---> 8");
    }
  else if(light1()>600){//night
    count = 4;
    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],HIGH);
    digitalWrite(led[2],HIGH);
    Serial.println("Setto ---> 4");
    }
  
  if(light0()> 100) door_status = true;
  if(door_status == false) frame = 0;
  if(frame == 35 && door_status == true){
      while(light0() > 60){
              emergency = digitalRead(BUTTON_PIN);
              if(emergency == 0) exit(0);
              else {
                door_close();
                Serial.println("spin++++++++++++");
                }
              }
              
           
           door_status = false;
           half = false;
           buzzer_normal();
    }
  //////////////////////////////////
  

  if(emergency == 0){
      exit(0);
    }
  else{
     
     ///////////////////////////////////////////////////////////////
     /*while(light0() > 70){
        if(emergency == 1) exit(0);
        else door_close();SS
      }door_status = false;
     */
     ////////////////////////////////////////////////////////////////
   
     
     ////////////////////////////////////////////////////////////////////
   /* if ( pirState == HIGH && tasking_available == true){
       Serial.println("PPPPPIIIIIIRRRRRR");
       if(door_status == false){
           for(int i = 0 ; i < count ; i++){
                 emergency = digitalRead(BUTTON_PIN);
                 if(emergency == 0) exit(0);
                 else{
                    door_open();
                    }
                }
          door_status = true;
        } 
         buzzer_normal();        
    }*/
  //////////////////////////////////////////////////////////
 
     if (buttonState == 0&& tasking_available == true){
       Serial.println("BBBBBUUUUUTTTTTOOOONNNN");
       if(door_status == false){
          if(count<5 ) {
            half = true;
            Serial.println("helllllllllllllllllllllllllllllllllllll");
            }
           Serial.println(half);
          for(int i = 0 ; i < count ; i++){
                 if(i%2==0)digitalWrite(led[0],LOW);
                 else digitalWrite(led[0],HIGH);
                 emergency = digitalRead(BUTTON_PIN);
                 if(emergency == 0) exit(0);
                 else{
                    door_open();
                    Serial.println("spin++++++++++++");
                    }
                }
          door_status = true;
        }
       else{
           while(light0() > 90){
              emergency = digitalRead(BUTTON_PIN);
              if(emergency == 0) exit(0);
              else {
                door_close();
                Serial.println("spin++++++++++++");
                }
              }
              half = false;
              door_status = false;
           }
           
           buzzer_normal();
        }
     
    
   ////////////////////////////////////////////////////////
   ///camera here///
   ////////////////////////////////////////////////////////
  Serial.print("   Half ----------  ");
  Serial.println(half);

  Serial.println("             ");
      if (distance < 8){
          if(led[0] == HIGH){
              digitalWrite(led[0],LOW);
              digitalWrite(led[1],LOW);
              digitalWrite(led[2],LOW);
            }
          if(led[0] == LOW){
              digitalWrite(led[0],HIGH);
              digitalWrite(led[1],HIGH);
              digitalWrite(led[2],HIGH);
            }
          Serial.println("WAAATTTERRRR");
          tasking_available = false; 
          buzzer_emerg();
          if(emergency == 0)exit(0);
          if(door_status == false && half == false){
              for(int i = 0 ; i < 8 ; i++){
                 emergency = digitalRead(BUTTON_PIN);
                 if(i%3 == 0){
                  digitalWrite(led[0],HIGH);digitalWrite(led[1],LOW);digitalWrite(led[2],LOW);
                  }
                 if(i%3 == 1){
                  digitalWrite(led[0],LOW);digitalWrite(led[1],HIGH);digitalWrite(led[2],LOW);
                  }
                 if(i%3==2){
                  digitalWrite(led[0],LOW);digitalWrite(led[1],LOW);digitalWrite(led[2],HIGH);
                  }
                 if(i % 3 == 0)  analogWrite(buzzerPin, 100);
                 if(i % 3 == 1) analogWrite(buzzerPin, 0);
                 if(emergency == 0) exit(0);
                 else{
                    door_open();
                    }
                }
                door_status = true;
                frame = 0;
            }
           if(door_status == true && half == true){
              for(int i = 0 ; i < 4 ; i++){
                 emergency = digitalRead(BUTTON_PIN);
                 if(i%3 == 0){
                  digitalWrite(led[0],HIGH);digitalWrite(led[1],LOW);digitalWrite(led[2],LOW);
                  }
                 if(i%3 == 1){
                  digitalWrite(led[0],LOW);digitalWrite(led[1],HIGH);digitalWrite(led[2],LOW);
                  }
                 if(i%3==2){
                  digitalWrite(led[0],LOW);digitalWrite(led[1],LOW);digitalWrite(led[2],HIGH);
                  }
                 if(i % 3 == 0)  analogWrite(buzzerPin, 100);
                 if(i % 3 == 1) analogWrite(buzzerPin, 0);
                 if(emergency == 0) exit(0);
                 else{
                    door_open();
                    }
                }
                door_status = true;
                half = false;
                frame = 0;
            }
           
     }
     if (distance > 9) tasking_available = true;
     ///////////////////////////////////////////////
    /////////////////////////////////////////////////////
    delay(100);
    }
  frame++;
}
  
