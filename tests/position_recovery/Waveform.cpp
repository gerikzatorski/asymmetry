// Class that represents a waveform pattern.
// "samples" the wave function to create a lookup table.
//
// @author Gerik Zatorski
// @version 0.0
//
// ######################################################################

#include "Waveform.h"
#include <math.h>

#define PI 3.141592
#define E 2.71828182845904523536

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

double Waveform::getTime(int i) {
  return _times[i];
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

// ######################################################################
// # SineWave Class
// ######################################################################

/** Constructor */
SineWave::SineWave(int f)
  : Waveform(f) {
  // _omega1 = 0.5; // no skew
}

void SineWave::compute(void) {
  double omega1 = _omega1;
  double omega2 = 1 - omega1;
  for (int i = 0; i < _n; ++i) {
    double x = (double) i / _n;
    if (x <= omega1/2) {
      _updates[i] = sin(x * PI/omega1);
    } else if (x <= omega2 + omega1/2) {
      _updates[i] = sin(x * PI/omega2 + PI/2 * (1 - omega1/omega2));
    } else {
      _updates[i] = sin(x * PI/omega1 + PI * (1 - omega2/omega1));
    }
  }
}

double SineWave::calculate(double x) {
  // x is on the scale of 0-1
  x = x / _T;
  double omega1 = _omega1;
  double omega2 = 1 - omega1;
  if (x <= omega1/2) {
    return sin(x * PI/omega1);
  } else if (x <= omega2 + omega1/2) {
    return sin(x * PI/omega2 + PI/2 * (1 - omega1/omega2));
  } else {
    return sin(x * PI/omega1 + PI * (1 - omega2/omega1));
  }
}

double SineWave::getSkew(void) {
  return _omega1;
}

void SineWave::setSkew(double omega1) {
  _omega1 = omega1;
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
