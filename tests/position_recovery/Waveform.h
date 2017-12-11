#ifndef _WAVEFORM_H
#define _WAVEFORM_H

#define MAX_UPDATES 10 // per waveform cycle

// can still make subclasses
namespace asymmetry {

  class Waveform
  {
  public:
    // Simple Constructor
    // @param f Wave frequency
    Waveform(int f);

    // Custom Wave Constructor
    Waveform(int size, double *t, double *u);
    
    // @param i index value
    // @return The signal value at i
    double getUpdate(int i);

    // @param i index value
    // @return The time at i
    double getTime(int i);

    // Linear interpolate the waveform value using precomputed tables
    // @param t The time to evaluate waveform at
    // @return The approximate wave value at time t
    double approx(double t);
    
    // Getters
    int getN(void);
    int getAmplitude(void);
    int getFrequency(void);
    double getPeriod(void);

    // Setters
    void setFrequency(int f);
    
  protected:
    int _n;			// Number of updates
    int _A;			// Amplitude
    int _f;			// Wave pattern frequency (Hz)
    double _T;			// period (s)

    double _update_rate;	  // sampling rate of signals
    double _updates[MAX_UPDATES]; // for precalculating lookup table
    double _times[MAX_UPDATES];   // array of times corresponding to update values
  };

  class SineWave : public Waveform
  {
  public:
    SineWave(int f);
    void compute(void);
    double calculate(double);
    double getSkew(void);
    void setSkew(double omega1);
  private:
    double _omega1; // skew factor
  };

  class TriangleWave : public Waveform
  {
  public:
    TriangleWave(int f);
    void compute(void);
    double getSkew(void);
    void setSkew(double m);
  private:
    double _m;
  };

}

#endif // _WAVEFORM_H
