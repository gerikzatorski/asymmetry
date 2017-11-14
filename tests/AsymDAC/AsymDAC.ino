#include "Waveform.h"

#define ledPin 13
#define outPin A21		// DAC pins are A21 and A22
#define INT_FREQ 1000
#define potPin A13

int potVal = 0;
double interrupt_callback_time = (double) (1.0 / INT_FREQ);
double wave_frequency = 40;

// use volatile for shared variables
volatile unsigned int step = 0;
volatile double time = 0;
volatile double debug;

IntervalTimer myTimer; // init Teensy timer

/* asymmetry::TriangleWave wave1(wave_frequency); */
/* asymmetry::TriangleWave wave2(wave_frequency); */
/* asymmetry::TriangleWave *pwave; */

asymmetry::SineWave wave1(wave_frequency);
asymmetry::SineWave wave2(wave_frequency);
asymmetry::SineWave *pwave;

void setup() {
  analogWriteResolution(12); // 12bit = 4096 levels (max is 13 bit)

  pinMode(ledPin, OUTPUT);
  pinMode(outPin, OUTPUT);

  /* wave1.setSkew(2.0); */
  /* wave2.setSkew(8.0); */

  wave1.setSkew(0.5);
  wave2.setSkew(0.8);
  
  wave1.compute();
  wave2.compute();

  // start with wave1
  pwave = &wave1;
  
  Serial.begin(115200);
  Serial.println("serial on");
  
  myTimer.begin(play_level, (int)(interrupt_callback_time * 1000000));
}

// play value on analog out pin
void play_level(void) { 

  /* toggle waves */
  if (step >= INT_FREQ * 2) {
    if (pwave == &wave1) {
      pwave = &wave2;
      debug = 1;
    } else {
      pwave = &wave1;
      debug = 2;
    }
    step = 0;
  }
  
  if (time >= pwave->getPeriod()) {
    time = time - pwave->getPeriod();
  }

  double val = pwave->approx(time) * 2000 + 2000; // help with dc offset
  analogWrite(outPin, val);

  /* debug = val; */
  
  time = time + interrupt_callback_time;
  step++;
}

void loop() {
  double debugCopy;
  double timeCopy;

  /* potVal = analogRead(potPin) + 1; */
  /* double newF = potVal / 1024.0 * 100; */
  /* wave1.setFrequency(newF); */
  /* wave2.setFrequency(newF); */

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.
  noInterrupts();
  debugCopy = debug;
  /* timeCopy = time; */
  interrupts();

  /* Serial.print(timeCopy); */
  /* Serial.print("\t"); */
  Serial.println(debugCopy);
  /* Serial.println(newF); */

  delay(4);
}
