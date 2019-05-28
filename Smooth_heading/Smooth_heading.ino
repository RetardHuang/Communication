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

int value1 = 130;  //go straight;the duty cycle
int value2 = 100; 


//go straight
void gostraight(void)
{
  //the left motor rotates forward, the right motor rotates forward
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

//turn left
void turnleft(void)
{
  //the left motor rotates reversed, the right motor rotates forward
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

//turn right
void turnright(void)
{
  //the left motor rotates forward, the right motor rotates reversed
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
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

int calcuPWM1(int Degr){
  int VALUE1=100-Degr*2;
  return VALUE1;
}

int calcuPWM2(int Degr){
  int VALUE2=100+Degr*2;
  return VALUE2;
}

void loop()
{
  if(stringComplete){

    switch(Direction){
    case 'w': //go straight
      analogWrite(ENA,value1);//set speed
      analogWrite(ENB,value2);//set speed
      gostraight();
      break;

    case 'a'://turn left
      analogWrite(ENA,calcuPWM1(degree));//set speed
      analogWrite(ENB,calcuPWM2(degree));//set speed
      turnleft();
      break;

    case 'd'://turn right
      analogWrite(ENA,calcuPWM1(degree));//set speed
      analogWrite(ENB,calcuPWM2(degree));//set speed
      turnright();
      break;

    case 'q'://Stop
      analogWrite(ENA,0);//set speed
      analogWrite(ENB,0);//set speed
      stopCar();
      break;
    }

    inputString = "";   
    stringComplete = false;
    degree=0;
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




