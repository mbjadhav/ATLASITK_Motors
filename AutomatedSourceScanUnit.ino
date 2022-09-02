#include <Stepper.h>

const int stepsX = 20000; //just initialization 
const int stepsX_chip1 = 13000;
const int stepsX_chip2 = 17000;
const int stepsX_chip3 = 27000;
const int stepsX_chip4 = 17000;
const int stepsY = 30000;
const int stepsW = 3300;
const int stepsW_chipshift = 1000;
//const int stepsW = 7000;

// for your motor
byte enablePinX = 38;
byte enablePinY = A2;
byte enablePinW = A8;

byte readPinXmin = 3;
byte readPinXmax = 2;
byte readPinYmin = 14;
byte readPinYmax = 15;
byte readPinWmin = 18;
byte readPinWmax = 19;

// initialize the stepper library on pins 8 through 11:
Stepper xStepper(stepsX, A1, A0);
Stepper yStepper(stepsY, A7, A6);
Stepper wStepper(stepsW, 48, 46);

int Ymin =0, Ymax =0;

void setup() {
  // set the speed at 60 rpm:
  xStepper.setSpeed(10);
  yStepper.setSpeed(10);
  wStepper.setSpeed(10);
  // initialize the serial port:
  Serial.begin(9600);

  pinMode(enablePinX, OUTPUT);
  pinMode(enablePinY, OUTPUT);
  pinMode(enablePinW, OUTPUT);
  digitalWrite(enablePinX, LOW);
  digitalWrite(enablePinY, LOW);
  digitalWrite(enablePinW, LOW);

  //pinMode(readPinYmin, INPUT);
  
  //position to origin
  while(digitalRead(readPinYmax)==1) yStepper.step(-1);
  while(digitalRead(readPinWmin)==1) wStepper.step(-1);
  while(digitalRead(readPinXmin)==1) xStepper.step(1);
    
  //moving source out
  while(digitalRead(readPinYmax)==1) yStepper.step(-1);
  xStepper.step(-stepsX_chip1);
  wStepper.step(stepsW);
  delay(5000);
  xStepper.step(-stepsX_chip2);
  delay(5000);
  wStepper.step(-stepsW_chipshift);
  delay(1000);
  xStepper.step(-stepsX_chip3);
  delay(5000);
  xStepper.step(-stepsX_chip4);
  delay(5000);
//   step one revolution in the other direction:
  //Serial.println("counterclockwise");
  while(digitalRead(readPinWmin)==1) wStepper.step(-1);
  while(digitalRead(readPinXmin)==1) xStepper.step(1);
  while(digitalRead(readPinYmin)==1) yStepper.step(1);
}

void loop() {

}
