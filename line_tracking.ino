//Motor A
#define InputA 8 //create variables for motor
#define PulseA 5
//Motor B
#define InputB 7//create variables for motor
#define PulseB 6
#define Stand 3 //create variables for standby
#define SensMid A1 //creates variables for line tracking 
#define SensRight A0
#define SensLeft A2

int position = 0; 
void setup()  
{
//Motors
  pinMode(InputA, OUTPUT); //identify motors as outputs
  pinMode(PulseA, OUTPUT);
  pinMode(InputB, OUTPUT);
  pinMode(PulseB, OUTPUT);
  digitalWrite(Stand, 1); //enable standby

//LineSensors
  pinMode(SensMid, INPUT); //define the line tracking sensors as inputs
  pinMode(SensRight, INPUT);
  pinMode(SensLeft, INPUT);
  Serial.begin(9600); // serial begin 
}
void loop() 
{
//Values
  int RightVal = analogRead(SensRight); // create variable for right sensor
  int LeftVal = analogRead(SensLeft); //create variable for left sensor
  int MidVal = analogRead(SensMid);  //create variable for middle sensor
//Line Tracking
  if(MidVal >= 500 && RightVal >= 500 && LeftVal >= 500) 
  {
    while(MidVal >= 500 && RightVal >= 500 && LeftVal >= 500)
    {
      Stop();
      break;   
    }
  }  
  else if(MidVal >= 500)
  {
    Forward(100);
  }
  else if(RightVal >= 500 && LeftVal >= 500)
  {
    Stop();
   }
  else if(RightVal >= 500)
  {
    Right(100);
  }
  else if(LeftVal >= 500)
  {
    Left(100);
  }
  else if ( RightVal >= 500 && MidVal >= 500){
    Left(100);
  }
  else {
    Right(100);
  }
}

//Movements
void Forward(int speed) // function for forward
{
// Motors A
  digitalWrite(InputA, HIGH);
  analogWrite(PulseA, speed);
// Motors B
  digitalWrite(InputB, HIGH);
  analogWrite(PulseB, speed);
}

void Right(int speed) //function for right
{
// Motors A
  digitalWrite(InputA, HIGH);
  analogWrite(PulseA, speed);
// Motors B
  digitalWrite(InputB, LOW);
  analogWrite(PulseB, speed);
}

void Left(int speed) //function for left
{
// Motors A
  digitalWrite(InputA, LOW);
  analogWrite(PulseA, speed);
// Motors B
  digitalWrite(InputB, HIGH);
  analogWrite(PulseB, speed);
}

void Stop() //function for stop
{
// Motors A
  digitalWrite(InputA, HIGH);
  analogWrite(PulseA, 0);
// Motors B
  digitalWrite(InputB, 0);
  analogWrite(PulseB, 0);
}
