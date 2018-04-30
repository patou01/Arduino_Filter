#include "Filter.h"
#include <Ultrasonic.h>

#define INPUT_LENGTH 400
#define SQUARE_FREQ 10
#define SINE_FREQ_LO 100
#define SINE_FREQ_HI 0

#define DIGITS 3

#define TRIG_PIN 5
#define ECHO_PIN 6

#define BAUD 1000000

Filter filt(10, 00, 10); 
Ultrasonic hc04(TRIG_PIN, ECHO_PIN);

float testInput[INPUT_LENGTH];
float curInput;
int inputCounter = 0;
float dt;
float startMillis;

void setup() {
  // put your setup code here, to run once:

  makeSquareInput();
  makeSineInput();

  Serial.begin(BAUD);
  while(!Serial)
    ;
 // Serial.println(loPass.getLoPassAlpha());
 // Serial.println(filt.getHiPassAlpha());
  
  //while(1)
 //   ;
 startMillis = millis();
 
}

void loop() {
  // put your main code here, to run repeatedly:
  hc04.measure();
  curInput = hc04.get_cm();
  dt = millis() - startMillis;
  dt /= 1000.0;
  curInput = 2*sin(dt*2*PI*SINE_FREQ_LO) + 0.5*sin(dt*2*PI*SINE_FREQ_HI);
  filt.addData(curInput);
  //Serial.print(inputCounter);
  Serial.print(dt, DIGITS); Serial.print(" ");
//  Serial.print(curInput*0.5,DIGITS); Serial.print(" ");
//    Serial.print(curInput*0.7,DIGITS); Serial.print(" ");
  Serial.print(curInput,DIGITS); Serial.print(" ");
  Serial.println(filt.getValue(),DIGITS);
  
 // Serial.print(" , ");
 // Serial.println(filt.getValue());
  inputCounter++;
 // delay(10);
}

void makeSquareInput()
{
  for(int i = 0; i < INPUT_LENGTH; i++)
  {
    if(i % SQUARE_FREQ < SQUARE_FREQ/2)
    {
      testInput[i] = 0;
    }
    else
      testInput[i] = 5;
  }
}

void makeSineInput()
{
  for(int i = 0; i < INPUT_LENGTH; i++)
  {
    testInput[i] = sin(i*2*PI*SINE_FREQ_LO) + sin(i*2*PI*SINE_FREQ_HI);
  }
}

