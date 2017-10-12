#include "Waveform.h"

#define PI 3.141592

#define ledPin 13
#define outPin A21		// DAC pins are A21 and A22
#define INT_FREQ 100.0

float interrupt_callback_time = (1 / INT_FREQ) * 1000000; // microseconds


// use volatile for shared variables
volatile unsigned int step = 0; // increment on interrupts
volatile float debug;

// Objects
IntervalTimer myTimer; // init Teensy timer
Waveform wave;

void setup() {
  analogWriteResolution(12); // 12bit = 4096 levels (max is 13 bit)

  pinMode(ledPin, OUTPUT);
  pinMode(outPin, OUTPUT);

  wave.init();
  
  Serial.begin(115200);
  Serial.println("serial on");
  
  myTimer.begin(play_level, (int) interrupt_callback_time);
}

// play value on analog out pin
void play_level(void) {
  float time = step * (float)(interrupt_callback_time / 1000000);
  debug = wave.calcUpdate(time);
  step++;
}

void loop() {

  /* float test = 1.0 /90.0; */
  /* Serial.println(test); */
  
  float debugCopy;

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.

  noInterrupts();
  debugCopy = debug;
  interrupts();

  Serial.println(debugCopy, 5);
}


float waveSine(float wavept) {
  return 1 * sin( 2 * 3.141592 * 40 * wavept + 0 );  
}

float waveKlatzky(float wavept) {
  long delta = -0.5;
  float omega1 = PI + PI/2 * delta;

  if (wavept < omega1) return -cos(wavept * PI/omega1);
  else {
    float omega2 = PI - PI/2 * (1 - delta);
    return -cos(wavept * PI/omega2);
  }
}
