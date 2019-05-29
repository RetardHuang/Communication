#include <SoftwareSerialWithHalfDuplex.h>

SoftwareSerialWithHalfDuplex mySerial(2, 3); // RX, TX

int degree;
char Direction;
String inputString = "";         // a String to hold incoming data 
bool stringComplete = false;  // whether the string is complete
//Define the Received data.

unsigned char Re_buf[11],counter=0;
unsigned char sign=0;
float a[3],w[3],angle[3],T;
/*--------------------------------------------------*/
//counter
int curve_counter = 1;
int cali = 8;
double nowDegree;//即时偏航角
double ay;//左右加速度
double wy;//角速度
#include <Servo.h>
Servo myservo;
int potpin = 0;
int val;
//toushiji

int angle2;


//define the left and right sides of motors' control pins
int IN1 = 7;//leftMotor_1
int IN2 = 6;//leftMotor_2

int IN3 = 9;//rightMotor_1
int IN4 = 10;//rightMotor_2

int ENA = 5;//PWM1
int ENB = 11;//PWM2

unsigned long time = 240000;  //delay time
unsigned long time_s = 5000; //stop time
int value1 = 150;  //go straight;the duty cycle
int value2 = 120; 
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
// defines pins numbers
const int echoPin1 = 13;
const int trigPin = 12;
// defines variables


void setup() 
{

  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);
  Serial.begin(9600); // 9600 bps
//  Serial1.begin(115200); // 9600 bps
  // set pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(cali,OUTPUT);
  digitalWrite(cali, LOW);
}
char direction;
int ultrasonicsensor1(){
  long duration;
  int distance;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  return (distance) ;
}

int distance1=0;
int distance2=0;
//int angle2=0;

double getDegree(){
  double startTime = millis();
  while(millis()-startTime<50) {
    MPU6050_read();
  }
  nowDegree = angle[2];
  ay = a[1];
  wy = w[0];
  return angle[2];
}

/*--------------------------------------------------------*/
//读取MPU6050的数据，并存入三个数组a[]、angle[]、w[]中
void MPU6050_read(){
  while (mySerial.available()) {    
    //char inChar = (char)mySerial.read(); mySerial.print(inChar); //Output Original Data, use this code 
    Re_buf[counter]=(unsigned char)mySerial.read();
    if(counter==0&&Re_buf[0]!=0x55) return;      //第0号数据不是帧头              
    counter++;       
    if(counter==11)             //接收到11个数据
    {    
      counter=0;               //重新赋值，准备下一帧数据的接收 
      sign=1;
    }      
  }

  if(sign)
  {  
    sign=0;
    if(Re_buf[0]==0x55)      //检查帧头
    {  
      switch(Re_buf [1])
      {
      case 0x51:
        a[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*16;
        a[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*16;
        a[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*16;
        T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
        break;
      case 0x52:
        w[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*2000;
        w[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*2000;
        w[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*2000;
        T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
        break;
      case 0x53:
        angle[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*180;
        angle[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*180;
        angle[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*180;
        T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
        break;
      } 
    }
  } 
}


void loop()
{  
  unsigned long starttime;
  unsigned long stoptime;
  unsigned long looptime;
  starttime = millis();
  //analogWrite(ENA,value1);//set speed
  //analogWrite(ENB,value2);//set speed
  switch(direction){
  case 'w': //go straight
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);
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

  case 'z'://Stop
    analogWrite(ENA,230);//set speed
    analogWrite(ENB,200);//set speed
    stopCar();
    delay(3000);
    turnright();
    delay(1200);
    gostraight();
    delay(2000);
    stopCar();
    delay(5000);
    gostraight();
    delay(5000);

    //第二个弯道左转
    while(1){

      distance1=ultrasonicsensor1();
      delay(100);
      //        distance2=ultrasonicsensor2();
      //       delay(100);
      if(distance1<=20 ){
        turnleft();
        while(1){
          angle2 = getDegree();
          Serial.println(angle2);
          if(angle2 >=87){
            digitalWrite(cali,LOW);//关闭MPU6050的电源，为下次重新校准做准备
            delay(200);//保证陀螺仪彻底断电
            break;
          }
        }
        break;
      }
      else{
        gostraight();
        delay(500);
      }
    }    
    while(1){
      digitalWrite(cali,HIGH);//为MPU6050上电，使当前角度记为0°
      delay(1000);
      gostraight();      
      while(1){
        angle2 = getDegree();
        Serial.println(angle2);
      }
    }
    break;

  default:
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);
    stopCar();
    delay(400);
    break;
  }
  stoptime = millis();

  looptime = stoptime - starttime;
  Serial.println(looptime);

}
void serialEvent(){
  if (Serial.available()){
    direction=Serial.read();
    Serial.println(direction);
  }
}
