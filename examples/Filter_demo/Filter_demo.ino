#include <Filter.h>
#include <Ultrasonic.h>

#define LO_FREQ 0
#define HI_FREQ 10
#define SAMP_TIME 10

#define TRIG_PIN 5
#define ECHO_PIN 6


#define DIGITS 3
#define BAUD 115200

Filter filt(LO_FREQ, HI_FREQ, SAMP_TIME); 
Ultrasonic hc04(TRIG_PIN, ECHO_PIN);


float curInput;
float dt;
float startMillis;

void setup() {
  Serial.begin(BAUD);
  while(!Serial)
    ;

 startMillis = millis();
 
}

void loop() {
  hc04.measure();
  curInput = hc04.get_cm();
  dt = millis() - startMillis;
  dt /= 1000.0;
  filt.addData(curInput);

  Serial.print(dt, DIGITS); Serial.print(" ");
  Serial.print(curInput,DIGITS); Serial.print(" ");
  Serial.println(filt.getValue(),DIGITS);
  
  delay(SAMP_TIME-2); // saying 2ms for the rest of the loop, give or take a ms
}

