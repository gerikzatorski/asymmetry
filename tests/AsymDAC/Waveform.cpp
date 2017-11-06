// Class that represents a waveform pattern.
// "samples" the wave function to create a lookup table.
//
// @author Gerik Zatorski
// @version 0.0
//
// ######################################################################

#include "Waveform.h"
#include <math.h>
// #include "matplotlibcpp.h"
// #include <iostream>

#define PI 3.141592
#define E 2.71828182845904523536

using namespace std;

namespace asymmetry {

// ######################################################################
// # Waveform Class
// ######################################################################

Waveform::Waveform(int f)
  : _n(MAX_UPDATES),
    _A(1),
    _f(f)
{
  _T = 1.0 / _f;
  _update_rate = (double) _T / _n;

  for (int i = 0; i < _n; ++i) {
    _times[i] = (double) i * _update_rate;
  }
}

Waveform::Waveform(int size, double *t, double *u) {
  _n = size;
  
  for (int i =0; i < _n; ++i) {
    _times[i] = t[i];
    _updates[i] = u[i];
  }
}

double Waveform::getUpdate(int i) {
  return _updates[i];
}

double Waveform::approx(double t) {
  double dt = t;

  // ensure dt is within waveform domain
  if (t >= _T) {
    double ttot = t / _T;
    double tfract, tint;
    tfract = modf(ttot, &tint);
    dt = tfract * _T;
  }

  int i = 0;
  while (dt > _times[i] && i < _n) {
    i++;
  }

  int i0 = i-1;
  int i1 = i;
  if (i >= _n) {
    i0 = i-1;
    i1 = 0;
  }
  return _updates[i0] + (dt - _times[i0]) * (_updates[i1] - _updates[i0]) / _update_rate;
}

void Waveform::graph(void) {
  // namespace plt = matplotlibcpp;
  // using namespace std;

  // double n = (double)_n;
  // vector<double> x(n+1),y(n+1); 

  // for(int i=0; i<n; ++i) {
  //   double t = i/n;
  //   x.at(i) = _times[i];
  //   y.at(i) = _updates[i];
  // }

  // x.at(_n) = _T;
  // y.at(_n) = _updates[0];
    
  // plt::plot(x, y, "r-");
  // plt::show(); 
}

void Waveform::graphApprox(double f_int) {
  // namespace plt = matplotlibcpp;
  // using namespace std;

  // double T_int = 1.0 / f_int;
  
  // double n = (double) _T / T_int;
  // vector<double> x(n+1),y(n+1); 
  
  // int i = 0;
  // double t = 0;

  // while (t < _T) {
  //   x.at(i) = i * T_int;
  //   y.at(i) = approx(t);
  //   i++;
  //   t = i * T_int;
  // }

  // x.at(n) = _T;
  // y.at(n) = _updates[0];

  // plt::plot(x, y, "r-");
  // plt::show();
}

// Getters
int Waveform::getN(void) {return _n; }
int Waveform::getAmplitude(void) { return _A; }
int Waveform::getFrequency(void) { return _f; }
double Waveform::getPeriod(void) { return _T; }

void Waveform::setFrequency(int f) {
  for (int i = 0; i < _n; ++i) {
    _times[i] = _times[i] * f / _f;
  }
  _f = f;
  _T = 1.0 / f;
  _update_rate = (double) _T / _n;
}

void Waveform::rms(void) {
  // double tot = 0;
  // for (int i = 0; i < _n; ++i) {
  //   tot += _updates[i] * _updates[i];
  // }
  // return sqrt(tot/_n);
}

// ######################################################################
// # SineWave Class
// ######################################################################

/** Constructor */
SineWave::SineWave(int f) : Waveform(f) {
  // _K = 0.0; // no skew
}

void SineWave::compute(void) {
  // option 1:
  // double x = 0;
  // for (int i = 0; i < _n; ++i) {
  //   x = (double) i / _n * 2 * PI;
  //   _updates[i] = cos( x + pow( sin( x / 2 ), 2) );
  // }

  // option 2 : simple skew
  double x = 0;
  for (int i = 0; i < _n; ++i) {
    x = (double) i / _n * 2 * PI;
    _updates[i] = sin( x + _K * sin(x));
  }
}

double SineWave::getSkew(void) {
  return _K;
}

void SineWave::setSkew(double K) {
  _K = K;
}

// ######################################################################
// # TriangleWave Class
// ######################################################################

/** Constructor */
TriangleWave::TriangleWave(int f) : Waveform(f) {
  // _m = 2.0; // no skew
}

void TriangleWave::compute(void) {
  double x = 0;
  double L = _T / 2;
  for (int i = 0; i < _n; ++i) {
    x = (double) i / _n * _T;
    if (x <= L/_m) {
      _updates[i] = _m * x / L;
    } else if (x <= 2 * L - L/_m) {
      _updates[i] = 1 - _m / ((_m-1) * L) * (x - L/_m);
    } else {
      _updates[i] = _m / L * (x - 2 * L);
    }
  }
}

double TriangleWave::getSkew(void) {
  return _m;
}

void TriangleWave::setSkew(double m) {
  _m = m;
}

} // namespace asymmetry
