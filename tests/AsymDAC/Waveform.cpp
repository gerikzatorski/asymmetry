/**
   Class that represents a waveform pattern.

   @author Gerik Zatorski
   @version 0.0
*/

#include "matplotlibcpp.h"
#include "Waveform.h"
#include <iostream>

#define PI 3.141592
#define E 2.71828182845904523536

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

  for (int i = 0; i < N_UPDATES; i++) {
    _times[i] = (double) i * _update_rate;
  }

}

void Waveform::compute(void) {
  throw "Calling compute on Waveform parent class";
}

double Waveform::calcUpdate(double t) {
  if (t > _T) {
    throw "t is outside domain of waveform function.";
  }
  
  // basic sine wave by default
  return (double) 1 * sin( 2 * PI * _f * t + 0 );
}

void Waveform::graph(void) {
  double n = (double)N_UPDATES;
  vector<double> x(n),y(n); 

  using namespace std;
  
  for(int i=0; i<n; ++i) {
    double t = i/n;
    x.at(i) = _times[i];
    y.at(i) = _updates[i];
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

  // option 1:
  // double x = 0;
  // for (int i = 0; i < N_UPDATES; ++i) {
  //   x = (double) i / N_UPDATES * 2 * PI;
  //   cout << x << endl;
  //   _updates[i] = cos( x + pow(sin( x / 2 ),2) );
  // }

  // option 2
  // double x = 0;
  // for (int i = 0; i < N_UPDATES; ++i) {
  //   x = (double) i / N_UPDATES * PI;
  //   cout << x << endl;
  //   _updates[i] = 2 * pow(cos( x ),2) * pow(E,sin(2*x)) / 1.7866 - 1;
  // }

  // option 3 : pure skew
  double x = 0;
  double K = 0.5;
  for (int i = 0; i < N_UPDATES; ++i) {
    x = (double) i / N_UPDATES * 2 * PI;
    cout << x << endl;
    _updates[i] = sin( x + K * sin(x));
  }

}

} // namespace asymmetry
