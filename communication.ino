//define 5 motion states
#define STOP       0
#define FORWARD   1
#define BACKWARD   2
#define TURNLEFT   3
#define TURNRIGHT  4

//define the left and right sides of motors' control pins
int IN1 = 7;//leftMotor_1
int IN2 = 6;//leftMotor_2

int IN3 = 9;//rightMotor_1
int IN4 = 10;//rightMotor_2

int ENA = 5;//PWM1
int ENB = 11;//PWM2

unsigned long time = 240000;  //delay time
unsigned long time_s = 5000; //stop time
int value1 = 230;  //the duty cycle 230
int value2 = 200;  //the duty cycle 200
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

   void turnning1(void){
     turnleft();
     delay(400);
     gostraight();
     delay(500);
     turnleft();
     delay(300);
     gostraight();
     delay(450);
     turnleft();
     delay(350);
     gostraight();
     delay(450);
     turnleft();
     delay(350);
     gostraight();
     delay(500);
     turnleft();
     delay(350);
     gostraight();
     delay(500);
     turnleft();
     delay(380);
    // gostraight();
     //delay(200);
    }

     void turnning2(void){
     turnright();
     delay(240);
     gostraight();
     delay(240);
     turnright();
     delay(240);
     gostraight();
     delay(240);
     turnright();
     delay(240);
     gostraight();
     delay(240);
     turnright();
     delay(240);
     gostraight();
     delay(240);
     turnright();
     delay(240);
     gostraight();
     delay(240);
     turnright();
     delay(240);
     gostraight();
     delay(240);
    }

    
     void turnning3(void){
     turnright();
     delay(350);
     gostraight();
     delay(500);
     turnright();
     delay(300);
     gostraight();
     delay(650);
     turnright();
     delay(300);
     gostraight();
     delay(800);
     turnright();
     delay(350);
     gostraight();
     delay(520);
     turnright();
     delay(300);
     gostraight();
     delay(600);
     turnright();
     delay(300);
     gostraight();
     delay(600);
    }

    
     void turnning4(void){
     turnleft();
     delay(480);
     gostraight();
     delay(480);
     turnleft();
     delay(480);
     gostraight();
     delay(480);
     turnleft();
     delay(480);
     gostraight();
     delay(520);
     turnleft();
     delay(480);
     gostraight();
     delay(480);
     turnleft();
     delay(480);
     gostraight();
     delay(480);
     turnleft();
     delay(480);
     gostraight();
     delay(480);
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

void loop()
{

    //gostraight();
    //delay(1000);
    //stopCar();
    //delay(1000);
 if ( Serial.available())
{   
  switch(Serial.read()){
    case 'G': //go straight
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);//set speed
    gostraight();
    delay(200);
    //stopCar();
    //delay(100);
    break;                                                                                                                                                                                                                                                                                                                     
  
    case 'L'://turn left
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);//set speed
    turnleft();
    delay(200);
    //stopCar();
    //delay(400);
    break;
    
    case 'R'://turn right
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);//set speed
    turnright();
    delay(200);
    //stopCar();
    //delay(400);
    break;

    case 'B'://Back
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);//set speed
    retreat();
    delay(200);
    //stopCar();
    //delay(400);
    break;

    case 'S'://Stop
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);//set speed
    stopCar();
    delay(200);
    break;
  }//switch end
   // stopCar();
   // delay(1000);
  }
}
