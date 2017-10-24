#include "Waveform.h"
#include <iostream>

using namespace std;

int main() 
{
  double a[5] = {0,1,2,3,4};
  double b[5] = {0,2,4,6,8};

  double *pa = a;
  double *pb = b;

  // asymmetry::Waveform wave(5, a[], b[]);
  asymmetry::Waveform wave(5, pa, pb);

  wave.compute();

  // cout << wave.approx(0.5) << endl;
  // cout << wave.approx(1.9) << endl;

  wave.graph();
  
  return 0;
} 
