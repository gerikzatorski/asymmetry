/**
   Class that represents a waveform pattern.

   @author Gerik Zatorski
   @version 0.0
*/

#include "matplotlibcpp.h"
#include "Waveform.h"
#include <iostream>

#define PI 3.141592

namespace plt = matplotlibcpp;
using namespace std;

namespace asymmetry {

// ######################################################################
// # Waveform Class
// ######################################################################

Waveform::Waveform(void) {
}

void Waveform::init(int f) {
  _A = 1;
  _f = f;
  _T = 1.0 / _f;
  _phase_offset = 0.0;

  _update_rate = (double) _T / N_UPDATES;
}

void Waveform::compute(void) {
  for (int i = 0; i < N_UPDATES; i++) {
    _updates[i] = (double) 4.0;
    _times[i] = (double) i * _update_rate;
  }
}

double Waveform::calcUpdate(double t) {
  if (t > _T) {
    throw "t is outside domain of waveform function.";
  }
  
  // basic sine wave
  return (double) 1 * sin( 2 * PI * _f * t + 0 );

  // klatzky wave
  long delta = -0.5;
  float omega1 = PI + PI/2 * delta;
  float wavePct = t / _T; // need "modulus" of float
}

void Waveform::graph(void) {
  double n = (double)N_UPDATES;
  vector<double> x(n),y(n); 

  using namespace std;
  
  for(int i=0; i<n; ++i) {
    double t = i/n;
    x.at(i) = _times[i];
    y.at(i) = _updates[i];
    cout << "DEBUG : " << i << endl;
    
  }
  
  plt::plot(x, y, "r-");
  plt::show();
  
}

int Waveform::getAmplitude(void) { return _A; }
int Waveform::getFrequency(void) { return _f; }
double Waveform::getPeriod(void) { return _T; }
double Waveform::getOffset(void) { return _phase_offset; }


// ######################################################################
// # Sinewave Class
// ######################################################################

/** Constructor */
Sinewave::Sinewave(void) {
}

/** Destructor */
Sinewave::~Sinewave(void) {
}

void Sinewave::compute(void) {
  using namespace std;
  for (int i = 0; i < N_UPDATES; i++) {
    _updates[i] = (double) 1 * sin( 2 * PI * _f * i * _update_rate + 0 );
    _times[i] = (double) i * _update_rate;
  }
}

// ######################################################################
// # ASinewave Class
// ######################################################################

ASinewave::ASinewave(void) {
}

ASinewave::~ASinewave(void) {
}

void ASinewave::compute(void) {
  for (int i = 0; i < N_UPDATES; i++) {
    _updates[i] = (double) 1 * sin( 2 * PI * _f * i * _update_rate + 0 );
  }
}

} // namespace asymmetry
