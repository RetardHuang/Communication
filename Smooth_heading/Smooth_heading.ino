int degree;
char Direction;
String inputString = "";         // a String to hold incoming data 
bool stringComplete = false;  // whether the string is complete
//Define the Received data.


//define the left and right sides of motors' control pins
int IN1 = 7;//leftMotor_1
int IN2 = 6;//leftMotor_2

int IN3 = 9;//rightMotor_1
int IN4 = 10;//rightMotor_2

int ENA = 5;//PWM1
int ENB = 11;//PWM2

int value1 = 230;  //go straight;the duty cycle
int value2 = 200; 
int value3 = 230; //turn left
int value4 = 200; 
int value5 = 120; //turn right
int value6 = 100; 

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
/////////////////////////////////////////////////////////////
/*
int * calcuPWM(int degree){
  int value[2];
  value[0]=.....;
  value[1]=.....;
  return value;
}
//When we wanna use it:
int VALUE*;//!!!!
VALUE= calcuPWM;
*/
///////////////////////////////////////////////////////////////////////////////
/*
I also suggest you that use if, beacuse after we calculated the PWM of the tire
The Direction seems MEANINGLESS
*/
///////////////////////////////////////////////////////////////////////////////
void loop()
{
  //analogWrite(ENA,value1);//set speed
  //analogWrite(ENB,value2);//set speed
  switch(Direction){
  case 'w': //go straight
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);
    gostraight();
    delay(100);
    stopCar();
    delay(100); 
    break;                                                                                                                                                                                                                                                                                                                     

  case 'a'://turn left
    analogWrite(ENA,value3);//set speed
    analogWrite(ENB,value4);
    turnleft();
    delay(100);
    stopCar();
    delay(100);
    break;

  case 'd'://turn right
    analogWrite(ENA,value5);//set speed
    analogWrite(ENB,value6);
    turnright();
    delay(100);
    stopCar();
    delay(100);
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

  default:
    analogWrite(ENA,value1);//set speed
    analogWrite(ENB,value2);
    stopCar();
    delay(400);
    break;
  }

}
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
 routine is run between each time loop() runs, so using delay inside loop can
 delay response. Multiple bytes of data may be available.
 */

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar >='a'  && inChar <='z') {
      stringComplete = true;
      Direction=inChar;
      degree=inputString.toInt();  
    }
    else{
      inputString+= inChar;
    }
  }
}

