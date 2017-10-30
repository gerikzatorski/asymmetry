#ifndef _WAVEFORM_H
#define _WAVEFORM_H

#define MAX_UPDATES 1000 // sizes member arrays

#include <vector>

// can still make subclasses
namespace asymmetry {

  class Waveform
  {
  public:
    // Defaut Constructor
    Waveform(void);
    
    // Simple Constructor
    // @param f Wave frequency
    Waveform(int f);

    // Custom Wave Constructor
    Waveform(int size, double *t, double *u);
    
    // Compute lookup tables for signal values and times
    void compute(void);

    // @param i index value
    // @return The signal value at i
    double getUpdate(int i);

    // Linear interpolate the waveform value using precomputed tables
    // @param t The time to evaluate waveform at
    // @return The approximate wave value at time t
    double approx(double t);
    
    // Graphs a single Waveform using exact lookup table values
    void graph(void);

    // Graph a waveform with 
    void graphApprox(double f_int);

    // Getters
    int getN(void);
    int getAmplitude(void);
    int getFrequency(void);
    double getPeriod(void);
    double getOffset(void);

    // Setters
    void setFrequency(int f);
    
  protected:
    int _n;			// Number of updates
    int _pin;
    int _A;			// Amplitude
    int _f;			// Wave pattern frequency (Hz)
    double _T;			// period (s)
    double _phase_offset;	// phase offset (deg with 360 max)

    double _update_rate;	  // sampling rate of signals
    double _updates[MAX_UPDATES]; // for precalculating lookup table
    double _times[MAX_UPDATES];   // array of times corresponding to update values
  };

  class SineWave : public Waveform
  {
  public:
    SineWave(void);
    ~SineWave(void);
    void compute(void);
    double getSkew(void);
    void setSkew(double K);
  private:
    double _K; // skew factor
  };

  class TriangleWave : public Waveform
  {
  public:
    TriangleWave(void);
    TriangleWave(int f);
    ~TriangleWave(void);
    void compute(void);
    double getSkew(void);
    void setSkew(double m);
  private:
    double _m;
  };

}

#endif // _WAVEFORM_H
