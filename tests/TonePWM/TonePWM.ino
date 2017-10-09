int pin = 35;
int freq = 6000;

void setup() {
}

void loop() {
  if (freq = 6000) {
    freq = 8000;
  }
  if (freq = 8000) {
    freq = 6000;
  }
  
  tone(pin, freq);       // Begin the tone
  delay(300);
  noTone(pin);                // manually stop it
}
