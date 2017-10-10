#define DACout A21 // DAC pins are A21 and A22

float Fs = 5000; // frequency of interrupt
float t = 0;

int ledPin = 13;

volatile unsigned int level = 0; // use volatile for shared variables
volatile unsigned long time = 0;

// Objects
IntervalTimer myTimer; // init Teensy timer
Waveform wavePattern;

void setup() {

  analogWriteResolution(12); // 12bit = 4096 levels (max is 13 bit)

  pinMode(ledPin, OUTPUT);
  pinMode(DACout, OUTPUT);

  Serial.begin(115200);
  Serial.println("serial on");

  wavePattern.init();
  wavePattern.compute();
  wavePattern.graph();

  int interrupt_callback_time = (1 / Fs) * 1000000; // microseconds
  myTimer.begin(play_level, (int)interrupt_callback_time);
}

// play value on analog out pin
void play_level(void) {
  time = millis();
  
}

void loop() {
  unsigned long debug;

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.
  noInterrupts();
  debug = time;
  interrupts();
  /* Serial.println(debug); */
  
  delay(100);
}


// based of step/ramp waveform in Culbertson et al (2016)
/* int t1 = 0; */
/* int t2 = 0; */
/* void culbert_wave(void) { */
/*   if (t <= t1) { */
/*     level = max_level; */
/*   } else if (t <= t2) { */
/*     level = max_level - (2 / (t2 - t1)) * (t - t1); */
/*   } else { */
/*     level = 0; */
/*   } */
/* } */
