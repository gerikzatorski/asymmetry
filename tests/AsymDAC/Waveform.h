#ifndef _WAVEFORM_H
#define _WAVEFORM_H

#define N_UPDATES 1000

/* 
 * Assuming amplitude of 1
 * 
*/

// can still make subclasses
class Waveform
{
 public:
  Waveform(void);
  void init(void);
  void compute(void);
  float calcUpdate(float);
  void graph(void);

 private:
  int _pin;
  float updates[N_UPDATES];
  int _A;			// Amplitude
  int _f;			// Wave pattern frequency (Hz)
  int _T;			// period (s)
  int _phase_offset;		// phase offset (deg with 360 max)
  int _sampling_rate;		// sampling rate of signals
};


#endif // _WAVEFORM_H
