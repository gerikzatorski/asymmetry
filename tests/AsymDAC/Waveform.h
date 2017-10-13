#ifndef _WAVEFORM_H
#define _WAVEFORM_H

#define N_UPDATES 1000

// can still make subclasses
class Waveform
{
 public:
  Waveform(void);
  void init(int f);
  void compute(void);
  double calcUpdate(double);
  void graph(void);
  void print(void);

  int getAmplitude(void);
  int getFrequency(void);
  double getPeriod(void);
  double getOffset(void);
  
 private:
  int _pin;
  int _A;			// Amplitude
  int _f;			// Wave pattern frequency (Hz)
  double _T;			// period (s)
  double _phase_offset;		// phase offset (deg with 360 max)

  int _update_rate;		// sampling rate of signals
  double updates[N_UPDATES];	// for precalculating lookup table

};


#endif // _WAVEFORM_H
