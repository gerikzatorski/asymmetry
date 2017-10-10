#ifndef _WAVEFORM_H
#define _WAVEFORM_H

#define PI 3.141592
#define N_SAMPLES 1000
#define OUTPIN 9

/* 
/* Assuming amplitude of 1
/* 
*/

// can still make subclasses
namespace Waves {
  class Waveform {

  /* public: */
    Waveform::Waveform(int);
    Waveform::init(void);
    Waveform::compute(void);
    Waveform::graph(void);

  private:
    int _pin;
    
    double samples[N_SAMPLES];

    // Wave Characteristics
    int _A;			// Amplitude
    int _f;			// Wave pattern frequency (Hz)
    int _T;			// period (s)
    int _phase_offset;		// phase offset (deg with 360 max)
  };

}; // Waves namespace

#endif // _WAVEFORM_H
