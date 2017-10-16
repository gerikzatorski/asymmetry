#include "Waveform.h"

#define ledPin 13
#define outPin A21		// DAC pins are A21 and A22
#define INT_FREQ 40

double interrupt_callback_time = (double) (1 / INT_FREQ);

// use volatile for shared variables
volatile unsigned int step = 0; // increment on interrupts
volatile double debug;

// Objects
IntervalTimer myTimer; // init Teensy timer
asymmetry::ASinewave wave;

void setup() {
  analogWriteResolution(12); // 12bit = 4096 levels (max is 13 bit)

  pinMode(ledPin, OUTPUT);
  pinMode(outPin, OUTPUT);

  wave.init(40);
  wave.compute();
  
  Serial.begin(115200);
  Serial.println("serial on");
  
  myTimer.begin(play_level, (int) interrupt_callback_time * 1000000);
}

// play value on analog out pin
void play_level(void) { 
  /* double time = step * (double)(interrupt_callback_time); */
  /* if (time > wave.getPeriod()) { */
  /*   time = time - wave.getPeriod(); */
  /* } */

  if (step >= 1000) {
    step = 0;
  }
  double val = wave.getUpdate(step);
  analogWrite(outPin, val);
  Serial.println("testing good");
  step++;
}

void loop() {

  double debugCopy;

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.
  noInterrupts();
  debugCopy = debug;
  interrupts();

  /* Serial.println(debugCopy, 5); */
}

double waveKlatzky(double wavept) {
  long delta = -0.5;
  double omega1 = PI + PI/2 * delta;

  if (wavept < omega1) return -cos(wavept * PI/omega1);
  else {
    double omega2 = PI - PI/2 * (1 - delta);
    return -cos(wavept * PI/omega2);
  }
}
