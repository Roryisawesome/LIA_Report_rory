//This is the code to control the robot with a remote. The speed is adjusted aswell (unecessary step you asked for in class).
#include <IRremote.hpp> // include the library for the remote to work. 
#define InputA 8 //define pins for motor a 
#define PulseA 5
#define InputB 7 //define pins for motor b
#define PulseB 6

#define Stand 3 // standby pin
#define IReceive 9 // receiver pin for remote
//Arrows
#define UP    70 //define hex values
#define RIGHT 67  //rigt hex value
#define LEFT  68  //left hex value
#define OK    64  //ok or stop hex value
#define SpeedUp 12 //speedup (1) hex value
#define SpeedDown 24 //speeddown (2) hex value
int speed = 100; //create variable for speed of 100

void setup() 
{//Motors

  pinMode(InputA, OUTPUT);  // identify the motors as outputs 
  pinMode(PulseA, OUTPUT); // identify the motors as outputs 
  pinMode(InputB, OUTPUT); // identify the motors as outputs 
  pinMode(PulseB, OUTPUT); // identify the motors as outputs 
  digitalWrite(Stand, HIGH); // enable stand by

  Serial.begin(9600); // serial begin
  IrReceiver.begin(IReceive, ENABLE_LED_FEEDBACK); //necessary to allow the infrared sensor to function
}

void loop() 
{
int Newspeed = (speed+10); // variable for speed increase
//Control
 if (IrReceiver.decode())  
 {
    Serial.println(IrReceiver.decodedIRData.command); // serial print hex values
    if(IrReceiver.decodedIRData.command == OK) // if ok is pressed, car will stop
    {
      Stop(); //  stop
    }
    else if(IrReceiver.decodedIRData.command == UP) // if up is pressed, moce forward
    {
      Forward(speed); // forward
    }
    else if(IrReceiver.decodedIRData.command == RIGHT) // if right is pressed, turn right
    {
      Right(speed); //right
      delay(450); // move for 450 ms
      Stop(); //stop after the turn to prevent a 360
    }
    else if(IrReceiver.decodedIRData.command == LEFT) //if left is pressed turn left 
    {
      Left(speed); //left 
      delay(450); // for 450ms
      Stop(); //stop after to prevent 360
    }
    else if(IrReceiver.decodedIRData.command == DOWN) // if down is pressed, go backwards
    {
      Backward(speed); //backwards
      
    }
    else if(IrReceiver.decodedIRData.command == SpeedUp) //if Speed up (1) is pressed, speed will increase by 10
    {
       speed = min(255, Newspeed); //paramater to make speed increase possible 
    }
    else if (IrReceiver.decodedIRData.command == SpeedDown) //if speed down (2) is pressed, speed should decrease by 10
    {
      speed = max(0, Newspeed); //paramater to make speed decrease possible
    } 
 } IrReceiver.resume(); //return to the top
}
void Forward(int speed){ // forward with speed
// Motors A
  digitalWrite(InputA, HIGH);
  analogWrite(PulseA, speed);
// Motors B
  digitalWrite(InputB, HIGH);
  analogWrite(PulseB, speed);
}

void Right(int speed){ // right with speed
// Motors A
  digitalWrite(InputA, HIGH);
  analogWrite(PulseA, speed);
// Motors B
  digitalWrite(InputB, LOW);
  analogWrite(PulseB, speed);
}

void Left(int speed){ // left with speed
// Motors A
  digitalWrite(InputA, LOW);
  analogWrite(PulseA, speed);
// Motors B
  digitalWrite(InputB, HIGH);
  analogWrite(PulseB, speed);
}

void Backward(int speed){ // backward with speed
// Motors A
  digitalWrite(InputA, LOW);
  analogWrite(PulseA, speed);
// Motors B
  digitalWrite(InputB, LOW);
  analogWrite(PulseB, speed);
}

void Stop(){ //stop
// Motors A
  digitalWrite(InputA, HIGH);
  analogWrite(PulseA, LOW);
// Motors B
  digitalWrite(InputB, HIGH);
  analogWrite(PulseB, LOW);
}