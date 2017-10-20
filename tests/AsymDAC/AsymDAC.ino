#include "Waveform.h"

#define ledPin 13
#define outPin A21		// DAC pins are A21 and A22
#define INT_FREQ 1000

double interrupt_callback_time = (double) (1.0 / INT_FREQ);

// use volatile for shared variables
volatile unsigned int step = 0; // increment on interrupts
volatile double time = 0; // increment on interrupts
volatile double debug;

// Objects
IntervalTimer myTimer; // init Teensy timer
asymmetry::ATrianglewave wave;

void setup() {
  analogWriteResolution(12); // 12bit = 4096 levels (max is 13 bit)

  pinMode(ledPin, OUTPUT);
  pinMode(outPin, OUTPUT);

  wave.init(20);
  wave.compute();
  
  Serial.begin(115200);
  Serial.println("serial on");
  
  myTimer.begin(play_level, (int)(interrupt_callback_time * 1000000));
}

// play value on analog out pin
void play_level(void) { 

  // toggle wave skew value
  if (step >= INT_FREQ * 2) {
    if (wave.getSkew() == 2.0) {
      wave.setSkew(8.0);
      wave.compute();
      debug = 8.0;
    } else {
      wave.setSkew(2.0);
      wave.compute();
      debug = 2.0;
    }
    step = 0;
  }
  
  if (time >= wave.getPeriod()) {
    time = time - wave.getPeriod();
  }

  double val = wave.approx(time) * 2000 + 2000; // help with dc offset
  analogWrite(outPin, val);

  debug = val;
  
  time = time + interrupt_callback_time;
  step++;
}

void loop() {

  double debugCopy;
  double timeCopy;

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.
  noInterrupts();
  debugCopy = debug;
  timeCopy = time;
  interrupts();

  /* Serial.print(timeCopy); */
  /* Serial.print("\t"); */
  Serial.println(debugCopy);
  
  delay(4);
}
