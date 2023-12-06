 // identify pins for the motors
int InputA = 8;
int PulseA = 5;
// identify pins for motors
int InputB = 7;
int PulseB = 6;
int Stand  = 3; // identify standby pin
int speedA = 100; //identify speed
int speedB = 100; //identify speed
#define trigPin 13 //identify trigpin for the ultrasonic
#define echoPin 12 //identify echopin for ultrasonic
float duration, distance;  
#include <Servo.h> //include library for servo
Servo myservo; // identify servo
#define SensMid A1
#define SensLeft A0
#define SensRight A2

void setup(){
  delay(5000);
pinMode(InputA,OUTPUT); //make the motor an output
pinMode(PulseA,OUTPUT);
pinMode(InputB ,OUTPUT);
pinMode(PulseB, OUTPUT);
digitalWrite(Stand,HIGH);
pinMode(SensMid, INPUT); //make standby high
Serial.begin(9600);  // serial begin
pinMode(trigPin, OUTPUT); //trig pin output
pinMode(echoPin, INPUT); //echo pin input
myservo.attach(10); //servo control pin
}
void Forward() // function to move forward
{
// Motors A
  digitalWrite(InputA,HIGH);
  analogWrite(PulseA, speedA);
// Motors B
  digitalWrite(InputB ,HIGH);
  analogWrite(PulseB, speedB);
}

void Backward(){ // function to move backward
// Motors A
  digitalWrite(InputA,LOW);
  analogWrite(PulseA, speedA);
// Motors B
  digitalWrite(InputB,LOW);
  analogWrite(PulseB, speedB);
}
void Right(){ // function to move right
// Motors A
  digitalWrite(InputA,HIGH);
  analogWrite(PulseA, speedA);
// Motors B
  digitalWrite(InputB,LOW);
  analogWrite(PulseB, speedB);
}

void Left(){ //function to move left
  
// Motors A
  digitalWrite(InputA,LOW);
  analogWrite(PulseA, speedA);
// Motors B
  digitalWrite(InputB,HIGH);
  analogWrite(PulseB, speedB);
}

void LeftForward(){ // left forward at the same time
// Motors A
  digitalWrite(InputA,HIGH);
  analogWrite(PulseA, speedA);
// Motors B
  digitalWrite(InputB,HIGH);
  analogWrite(PulseB, speedB/2);
}

void LeftBackward(){ // left and backward at same time
// Motors A
  digitalWrite(InputA,LOW);
  analogWrite(PulseA, speedA);
// Motors B
  digitalWrite(InputB,LOW);
  analogWrite(PulseB, speedB/2);
}

void RightForward() //right and forward at same time
{// Motors A
  digitalWrite(InputA,HIGH);
  analogWrite(PulseA, speedA/2);
// Motors B
  digitalWrite(InputB,HIGH);
  analogWrite(PulseB, speedB);
}

void RightBackward(){ // right and backwards at the same time
// Motors A
  digitalWrite(InputA,LOW);
  analogWrite(PulseA, speedA/2);
// Motors B
  digitalWrite(InputB,LOW);
  analogWrite(InputB, speedB);
}

void Stop(){ // function to stop
// Motors A
  digitalWrite(InputA,HIGH);
  analogWrite(PulseA, LOW);
// Motors B
  digitalWrite(InputB,0);
  analogWrite(PulseB, 0);
} 
void ultrasonic(){ // function for ultrasonic sensor to send and receive distance signal
  digitalWrite(trigPin, LOW); // trigpin is low
delayMicroseconds(2); //delay for 2 microseconds
digitalWrite(trigPin, HIGH); // trig pin high
delayMicroseconds(10); //delay for 10 microseconds
digitalWrite(trigPin, LOW); // trigpin low
duration = pulseIn(echoPin, HIGH); //create variable called durartion
distance = (duration/ 2) * 0.0343;  //create distance equation
return(int)distance; //return distance
}

void loop() {
  analogRead(A1);
  analogRead(A0);
  analogRead(A2);
  int leftsens = analogRead(A0);
  int rightsens = analogRead(A2);
 int midsens = analogRead(A1);
  Serial.println(SensMid);
  distance = (duration/ 2) * 0.0343;  //distance formula again
  myservo.write(90); // set servo to look forward
 ultrasonic(); // make ultrasonic sensor work before anything
 if (midsens && leftsens && rightsens >= 100){
  Stop();
 }
 

 if (distance < 20){ // if distance is less than 20, stop
  Stop();
  myservo.write(0); // look right
  delay(200);
  ultrasonic();
  delay(500);
  if (distance < 20){ // if distance less than 20
    Stop();
    myservo.write(180); //look left
    delay(200);
    ultrasonic();
    delay(200);
    Stop();
    ultrasonic();
    delay(500);
    if (distance > 20){ // if distabce is greater than 20
      Left(); // turn left
      delay(600);
      myservo.write(90);
    }
    
    else{ // if you cannot go left or right, go backward and do a 180
      Backward();  //backward
      delay(400);
      Left();
      delay(1200);
      myservo.write(90);
  
      
    }
  }
  else { // if distance greater than 20 turn right
     Right(); // right
     delay(600);
     myservo.write(90);
   }
   
 } 
 else { // move forward while distance is greater than 20
  Forward();
 }
 analogRead(A1);
 if (midsens > 100){
  Stop();
 }
 
}  
  





  



  

 






