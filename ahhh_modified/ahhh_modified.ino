//define the left and right sides of motors' control pins
int IN1 = 7;//leftMotor_1
int IN2 = 6;//leftMotor_2

int IN3 = 9;//rightMotor_1
int IN4 = 10;//rightMotor_2

int ENA = 5;//PWM1
int ENB = 11;//PWM2

unsigned long time = 240000;  //delay time
unsigned long time_s = 5000; //stop time
int value1 = 230;  //the duty cycle
int value2 = 200;  //the duty cycle
int value3 = 120; 
int value4 = 100; 

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
switch(direction){
    case 'w': //go straight
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);
    gostraight();
    delay(800);
    stopCar();
    delay(200); 
    break;                                                                                                                                                                                                                                                                                                                     
  
    case 'a'://turn left
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);
    turnleft();
    delay(400);
    stopCar();
    delay(200);
    break;
    
    case 'd'://turn right
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);
    turnright();
    delay(400);
    stopCar();
    delay(3000);
    break;

    default:
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);
    gostraight();
    delay(400);
    break;
    }
  
}
void serialEvent(){
  if (Serial.available()){
    direction=Serial.read();
  }
  }
