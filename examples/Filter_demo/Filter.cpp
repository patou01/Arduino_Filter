#include "Filter.h"

    float prevData;
    float data;
    float output;
    float loAlpha;
    float hiAlpha;
    
Filter::Filter()
{
  prevData = 0;
  data = 0;
  output = 0;
  loAlpha = 0;
  hiAlpha = 0;
}


Filter::Filter(int loFreq, int hiFreq, int dt) // set hiFreq = 0 and loFreq > 0 for high-pass
{
  prevData = 0;
  data = 0;
  output = 0;
  loPassAlpha = 2*PI*dt*1e-3*hiFreq/(2*PI*dt*1e-3*hiFreq + 1);
  hiPassAlpha = 1/(2*PI*dt*1e-3*loFreq+1);
}


void Filter::setLoFreq(int freq)
{
  hiPassAlpha = 0;
}


void Filter::setHiFreq(int freq)
{
  //loPassAlpha = 2*PI*dt*1e-3*freq/(2*PI*dt*1e-3*freq + 1);
}


float Filter::getValue()
{
  return output;
}


int Filter::getIntValue()
{
  return (int)(output);
}


void Filter::addData(float data_)
{
  prevData = data;
  data = data_;
  prevOutput = output;
  
  // low pass
  output = loPassAlpha*data + (1-loPassAlpha)*output;

  // high pass
  if(hiPassAlpha > 0.001)
    output = hiPassAlpha*output + hiPassAlpha*(data - prevData);
}

float Filter::getLoPassAlpha()
{
  return loPassAlpha;
}

float Filter::getHiPassAlpha()
{
  return hiPassAlpha;
}

