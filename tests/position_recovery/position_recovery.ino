#include "Waveform.h"
#include "Ultrasonic.h"
#include "Filter.h"

#define ledPin 13
#define avdPin A21		// DAC pins are A21 and A22
#define buttonPin 23

#define INT_FREQ 1000

#define MIN_RANGE 0
#define MAX_RANGE 100

double spring_center;
double spring_range = 50.0;
double spring_min;
double spring_max;

double wave_frequency = 40;
double interrupt_callback_time = (double) (1.0 / INT_FREQ);

volatile double wavetime = 0;
volatile double debug;
volatile unsigned int step = 0;
volatile double k = 0.5;

Ultrasonic ultrasonic;
MedianFilter filter;
IntervalTimer myTimer; // init Teensy timer

asymmetry::SineWave waveform(wave_frequency);
asymmetry::SineWave *pwave;

void setup() {
  Serial.begin(9600);
  analogWriteResolution(12); // 12bit = 4096 levels (max is 13 bit)

  // Pin Setup
  pinMode(buttonPin, INPUT_PULLUP);
  /* digitalWrite(buttonPin, LOW); */
  pinMode(avdPin, OUTPUT);
  ultrasonic.pins(6,5);

  // Waveform setup
  waveform.setSkew(k);
  pwave = &waveform;

  // Timer Setup
  myTimer.begin(play_level, (int)(interrupt_callback_time * 1000000));

  // "Spring" Setup
  randomSeed(analogRead(0));
  spring_center = random(25, 75);
  /* spring_center = 50.0; */
  spring_min = spring_center - spring_range/2;
  spring_max = spring_center + spring_range/2;
}

// play value on analog out pin
void play_level(void) { 
  if (wavetime >= pwave->getPeriod()) {
    wavetime = wavetime - pwave->getPeriod();
  }

  double val = pwave->calculate(wavetime) * 2048 + 2048; // help with dc offset
  analogWrite(avdPin, val);

  debug = val;
  wavetime = wavetime + interrupt_callback_time;
  step++;
}

void loop() {
  // transfer variables from interrupts
  /* double debugCopy; */
  /* double wavetimeCopy; */
  /* noInterrupts(); */
  /* debugCopy = debug; */
  /* wavetimeCopy = wavetime; */
  /* interrupts(); */

  double raw_dist;
  ultrasonic.DistanceMeasure();
  raw_dist = ultrasonic.microsecondsToCentimeters();
  
  filter.add(raw_dist);
  
  double dist = filter.getAvg();
  if (dist < spring_min) dist = spring_min;
  if (dist > spring_max) dist = spring_max;
  
  k = map(dist, spring_min, spring_max, 0.0, 1.0);
  waveform.setSkew(k);

  if (digitalRead(buttonPin) == HIGH) {

  Serial.print(spring_min);
  Serial.print('\t');
  Serial.print(spring_center);
  Serial.print('\t');
  Serial.print(spring_max);

  Serial.print("\t | \t");
  
  Serial.print(raw_dist);
  Serial.print('\t');
  Serial.print(dist);
  Serial.print('\t');
  Serial.println(k);
    
  }

  /** DEBUGGING **/

  delay(4);
}

