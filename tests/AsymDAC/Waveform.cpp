#include "Waveform.h"
#include <math.h>

#define PI 3.141592

Waveform::Waveform(void) {
}

void Waveform::init(void) {
  _A = 1;
  _f = 1 / 2 * PI;
  _T = 1 / _f;
  _phase_offset = 0;
}

// create lookup table
void Waveform::compute(void) {
  for (int i = 0; i < N_UPDATES; i++) {
    updates[i] = (float) 1 * sin( 2 * PI * 1 * t + 0 );
  }
}

float Waveform::calcUpdate(float t) {
  return (float) 1 * sin( 2 * PI * 1 * t + 0 );
}

void Waveform::graph(void) {
}
