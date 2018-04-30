# Arduino_Filter

This is a class that allows to easily filter data with a digital RC low-pass followed by a digital RC high-pass.
It is not the most efficient yet due to the floating points, once this has been benchmarked I will see if it requires modifications.


# Use

```Filter(int loFreq, int hiFreq, int dt)```
Where loFreq and hiFreq are frequencies in Hz. The filter will cut at those frequencies. if hiFreq = 0, then the filter is a low-pass.

dt is the expected time between 2 samples in ms.


```addData(float data)```
Use this method to give a new datapoint to the filter, it then proceeds to calculate the filtered value at this point.

```getValue()```
Returns the filtered output.
