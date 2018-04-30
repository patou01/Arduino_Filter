#ifndef FILTER_H
#define FILTER_H

#define PI 3.1415


class Filter
{

  public:
    Filter();
    Filter(int loFreq, int hiFreq, int dt); // set hiFreq = 0 and loFreq > 0 for high-pass
    void setLoFreq(int freq);
    void setHiFreq(int freq);
    float getValue();
    int getIntValue();
    void addData(float data_);
    float getLoPassAlpha();
    float getHiPassAlpha();
    
  private:
    float prevData;
    float data;
    float prevOutput;
    float output;
    float loPassAlpha;
    float hiPassAlpha;
    
};

#endif
