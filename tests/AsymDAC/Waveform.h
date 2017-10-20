#ifndef _WAVEFORM_H
#define _WAVEFORM_H

#define N_UPDATES 100

// can still make subclasses
namespace asymmetry {

  class Waveform
  {
  public:
    // Constructor
    Waveform(void);
    
    // Initializes Waveform objects.
    // @param f Wave frequency
    void init(int f);

    // Compute lookup tables for signal values and times
    void compute(void);

    // @param i iteration within N_UPDATES
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
    int getAmplitude(void);
    int getFrequency(void);
    double getPeriod(void);
    double getOffset(void);

    // Setters
    void setFrequency(int f);
    
  protected:
    int _pin;
    int _A;			// Amplitude
    int _f;			// Wave pattern frequency (Hz)
    double _T;			// period (s)
    double _phase_offset;	// phase offset (deg with 360 max)

    double _update_rate;	// sampling rate of signals
    double _updates[N_UPDATES];	// for precalculating lookup table
    double _times[N_UPDATES];   // array of times corresponding to update values

  };

  class Sinewave : public Waveform
  {
  public:
    Sinewave(void);
    ~Sinewave(void);
    void compute(void);
  };

  class ASinewave : public Waveform
  {
  public:
    ASinewave(void);
    ~ASinewave(void);
    void compute(void);
  };

  class ATrianglewave : public Waveform
  {
  public:
    ATrianglewave(void);
    ~ATrianglewave(void);
    void compute(void);
    double getSkew(void);
    void setSkew(double m);
  private:
    double _m;
  };

}

#endif // _WAVEFORM_H
