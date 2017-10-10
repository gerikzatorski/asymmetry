#include "Waveform.h"

Waveform::Waveform(int pin) {
  _pin = OUTPIN;
}

Waveform::init(void) {
  pinMode(_pin, OUTPUT);
  
  _A = 1;
  _f = 40;
  _T = 1 / _f;
  _phase_offset = 0;
}

Waveform::compute(void) {
  
  double step = _T / N_SAMPLES;

  for (int i = 0; i < N_SAMPLES; ++i) {
    samples[i] = A * sin( 2 * PI * _f * i * step + _phase_offset );
  }
}

Waveform::graph(void) {
  for (int i = 0; i < N_SAMPLES; ++i) {
    Serial.println(samples[i]);
    delay(5);
  }
}
