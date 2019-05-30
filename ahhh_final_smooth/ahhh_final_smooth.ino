//define the left and right sides of motors' control pins
int IN1 = 7;//leftMotor_1
int IN2 = 6;//leftMotor_2

int IN3 = 9;//rightMotor_1
int IN4 = 10;//rightMotor_2

int ENA = 5;//PWM1
int ENB = 11;//PWM2


int value1 = 160;  //go straight;the duty cycle
int value2 = 130; 
int value3 = 200; //turn left
int value4 = 170; 
int value5 = 200; //turn right
int value6 = 170; 
//go straight
void gostraight(void)
{
  //the left motor rotates forward, the right motor rotates forward
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

//retreat
void retreat(void)
{
  //the left motor rotates reversed, the right motor rotates reversed
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
//turn left
void turnleft(void)
{
  //the left motor rotates reversed, the right motor rotates forward
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

//turn right
void turnright(void)
{
  //the left motor rotates forward, the right motor rotates reversed
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

//stop
void stopCar(void)
{
  //the left motor brakes, the right motor brakes
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}


void setup() 
{   
  
  Serial.begin(9600); // 9600 bps
  // set pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}
char direction;
void loop()
{
  //analogWrite(ENA,value1);//set speed
  //analogWrite(ENB,value2);//set speed
  unsigned long starttime;
  unsigned long stoptime;
  unsigned long looptime;
  starttime = millis();
  switch(direction){
  case 'w': //go straight
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);
    gostraight();
    break;

  case 'W': //go straight
    analogWrite(ENA,230);//set speed
    analogWrite(ENB,200);
    gostraight();
    break;

  case 'a'://turn left
    analogWrite(ENA,value3);//set speed
    analogWrite(ENB,value4);
    turnleft();
    break;

  case 'd'://turn right
    analogWrite(ENA,value5);//set speed
    analogWrite(ENB,value6);
    turnright();
    break;

  case 's'://Back
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);//set speed
    retreat();
    delay(200);
    stopCar();
    delay(400);
    break;

  case 'q'://Stop
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);//set speed
    stopCar();
    delay(200);
    break;

  case 'x'://Stop
    analogWrite(ENA,230);//set speed
    analogWrite(ENB,200);//set speed
    stopCar();
    delay(500);
    retreat();
    delay(800);
    turnright();
    delay(1000);
    break;

  case 'y'://Stop
    analogWrite(ENA,230);//set speed
    analogWrite(ENB,200);//set speed
    stopCar();
    delay(500);
    retreat();
    delay(800);
    turnleft();
    delay(1000);
    break;

  default:
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);
    stopCar();
    delay(3000);
    break;
  }
  stoptime = millis();
  looptime = stoptime - starttime;
}
void serialEvent(){
  if (Serial.available()){
    direction=Serial.read();
  }
  while(Serial.read()>=0){
  }

}

