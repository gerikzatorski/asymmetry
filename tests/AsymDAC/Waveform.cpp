#include "matplotlibcpp.h"
#include <cmath>
#include "Waveform.h"
// #include <math.h>
#include <iostream>

#define PI 3.141592

namespace plt = matplotlibcpp;
using namespace std;

Waveform::Waveform(void) {
  
}

void Waveform::init(int f) {
  _A = 1;
  _f = f;
  _T = 1 / _f;
  _phase_offset = 0;
}

// create lookup table
void Waveform::compute(void) {
  for (int i = 0; i < N_UPDATES; i++) {
    updates[i] = (float) 1 * sin( 2 * PI * _f * i * _update_rate + 0 );
  }
}

double Waveform::calcUpdate(double t) {
  if (t > _T) {
    throw "t is outside domain of waveform function.";
  }
  
  // basic sine wave
  return (double) 1 * sin( 2 * PI * _f * t + 0 );

  // klatzky wave
  // long delta = -0.5;
  // float omega1 = PI + PI/2 * delta;
  // float wavePct = t / _T; // need "modulus" of float
  
}

void Waveform::graph(void) {
  // Prepare data.
  double n = (double)N_UPDATES; // number of data points
  vector<double> x(n),y(n); 
  for(int i=0; i<n; ++i) {
    double t = i/n;
    x.at(i) = t;
    // y.at(i) = t * i;
    y.at(i) = calcUpdate(t);
    
    cout << i << " " << t << endl;
  }

  // plot() takes an arbitrary number of (x,y,format)-triples. 
  // x must be iterable (that is, anything providing begin(x) and end(x)),
  // y must either be callable (providing operator() const) or iterable. 
  plt::plot(x, y, "r-");


  // show plots
  plt::show();
}

void Waveform::print(void) {
  cout << "Print Waveform..." << endl;
}

double Waveform::getPeriod(void) { return _T; }
int Waveform::getAmplitude(void) { return _A; }
int Waveform::getFrequency(void) { return _f; }
double Waveform::getOffset(void) { return _phase_offset; }
