#ifndef _WAVEFORM_H
#define _WAVEFORM_H

#define N_UPDATES 1000

// can still make subclasses
namespace asymmetry {

  class Waveform
  {
  public:
    // @brief Constructor
    Waveform(void);
    
    // @brief Initializes Waveform objects.
    // @param f Wave frequency
    void init(int f);

    // @brief Create lookup table
    void compute(void);

    // Calculate update values dynamically
    // @param t The time to evaluate waveform at
    // @return The waveform update value at time t
    double calcUpdate(double);

    // @brief Graphs a single Waveform.
    void graph(void);
    
    int getAmplitude(void);
    int getFrequency(void);
    double getPeriod(void);
    double getOffset(void);
  
  protected:
    int _pin;
    int _A;			// Amplitude
    int _f;			// Wave pattern frequency (Hz)
    double _T;			// period (s)
    double _phase_offset;	// phase offset (deg with 360 max)

    double _update_rate;	// sampling rate of signals
    double _updates[N_UPDATES];	// for precalculating lookup table
    double _times[N_UPDATES];

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
}

#endif // _WAVEFORM_H
