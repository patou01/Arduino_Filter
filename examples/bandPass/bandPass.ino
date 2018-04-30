#include <Filter.h>

#define INPUT_LENGTH 400
#define SQUARE_FREQ 4

#define LOW_FREQ 1
#define HI_FREQ 2
#define SAMP_TIME 10 // ms

#define DIGITS 3
#define BAUD 115200

Filter filt(LOW_FREQ, HI_FREQ, SAMP_TIME); 

float testInput[INPUT_LENGTH];
float curInput;
int inputCounter = 0;
float dt;
float startMillis;

void setup() {
  makeSquareInput();

  Serial.begin(BAUD);
  while(!Serial)
    ;

 startMillis = millis();
 
}

void loop() {
  curInput = testInput[inputCounter];
  dt = millis() - startMillis;
  dt /= 1000.0;
  filt.addData(curInput);

  Serial.print(dt, DIGITS); Serial.print(" ");
  Serial.print(curInput,DIGITS); Serial.print(" ");
  Serial.println(filt.getValue(),DIGITS);

  inputCounter = (inputCounter+1) % INPUT_LENGTH;
  delay(SAMP_TIME-2); // saying 2ms for the rest of the loop, give or take a ms
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

