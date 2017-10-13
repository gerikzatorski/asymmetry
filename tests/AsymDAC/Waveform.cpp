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

/** Waveform constructor */
Waveform::Waveform(void) {
}

/** 
    Initializes Waveform objects.
    @param f Wave frequency
*/
void Waveform::init(int f) {
  _A = 1;
  _f = f;
  _T = 1 / _f;
  _phase_offset = 0;
}

/** Create lookup table */
void Waveform::compute(void) {
  for (int i = 0; i < N_UPDATES; i++) {
    updates[i] = (float) 1 * sin( 2 * PI * _f * i * _update_rate + 0 );
  }
}

/** 
    Calculate update values dynamically
    @param t The time to evaluate waveform at
    @return The waveform update value at time t
*/
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

// Graphs a single Waveform.
void Waveform::graph(void) {
  double n = (double)N_UPDATES;
  vector<double> x(n),y(n); 

  for(int i=0; i<n; ++i) {
    double t = i/n;
    x.at(i) = t;
    y.at(i) = calcUpdate(t);
  }
  
  plt::plot(x, y, "r-");
  plt::show();
  
}

double Waveform::getPeriod(void) { return _T; }
int Waveform::getAmplitude(void) { return _A; }
int Waveform::getFrequency(void) { return _f; }
double Waveform::getOffset(void) { return _phase_offset; }
