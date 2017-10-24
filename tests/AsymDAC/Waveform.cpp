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

Waveform::Waveform(void) {
}

void Waveform::init(int f) {
  _A = 1;
  _f = f;
  _T = 1.0 / _f;
  _phase_offset = 0.0;
  _update_rate = (double) _T / N_UPDATES;

  for (int i = 0; i < N_UPDATES; ++i) {
    _times[i] = (double) i * _update_rate;
  }

}

void Waveform::compute(void) {
  // handled by sub classes (TODO: virtual void?)
}
 
double Waveform::getUpdate(int i) {
  return _updates[i];
}

double Waveform::approx(double t) {
  using namespace std;
  
  double dt = t;

  // ensure dt is within waveform domain
  if (t >= _T) {
    double ttot = t / _T;
    double tfract, tint;
    tfract = modf(ttot, &tint);
    dt = tfract * _T;
  }

  int i = 0;
  while (dt > _times[i] && i < N_UPDATES) {
    i++;
  }

  int i0 = i-1;
  int i1 = i;


  if (i >= N_UPDATES) {
    i0 = i-1;
    i1 = 0;
  }

  return _updates[i0] + (dt - _times[i0]) * (_updates[i1] - _updates[i0]) / _update_rate;
}

void Waveform::graph(void) {
  // namespace plt = matplotlibcpp;
  // using namespace std;

  // double n = (double)N_UPDATES;
  // vector<double> x(n+1),y(n+1); 

  // for(int i=0; i<n; ++i) {
  //   double t = i/n;
  //   x.at(i) = _times[i];
  //   y.at(i) = _updates[i];
  // }

  // x.at(N_UPDATES) = _T;
  // y.at(N_UPDATES) = _updates[0];
    
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
int Waveform::getAmplitude(void) { return _A; }
int Waveform::getFrequency(void) { return _f; }
double Waveform::getPeriod(void) { return _T; }
double Waveform::getOffset(void) { return _phase_offset; }

void Waveform::setFrequency(int f) {
  for (int i = 0; i < N_UPDATES; ++i) {
    _times[i] = _times[i] * f / _f;
  }
  _f = f;
  _T = 1.0 / _f;
  _update_rate = (double) _T / N_UPDATES;
}


// ######################################################################
// # SineWave Class
// ######################################################################

/** Constructor */
SineWave::SineWave(void) {
  _K = 0.0; // no skew
}

/** Destructor */
SineWave::~SineWave(void) {
}

void SineWave::compute(void) {
  // option 1:
  // double x = 0;
  // for (int i = 0; i < N_UPDATES; ++i) {
  //   x = (double) i / N_UPDATES * 2 * PI;
  //   _updates[i] = cos( x + pow( sin( x / 2 ), 2) );
  // }

  // option 2 : simple skew
  double x = 0;
  for (int i = 0; i < N_UPDATES; ++i) {
    x = (double) i / N_UPDATES * 2 * PI;
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
// # ATrianglewave Class
// ######################################################################

TriangleWave::TriangleWave(void) {
  _m = 2.0; // no skew
}

TriangleWave::~TriangleWave(void) {
}

void TriangleWave::compute(void) {
  double x = 0;
  double m = _m; // determines skew
  double L = _T / 2;
  for (int i = 0; i < N_UPDATES; ++i) {
    x = (double) i / N_UPDATES * _T;
    if (x <= L/m) {
      _updates[i] = m * x / L;
    } else if (x <= 2 * L - L/m) {
      _updates[i] = 1 - m / ((m-1) * L) * (x - L/m);
    } else {
      _updates[i] = m / L * (x - 2 * L);
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
