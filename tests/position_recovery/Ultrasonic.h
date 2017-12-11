#include "Arduino.h"

class Ultrasonic
{
 public:
  Ultrasonic(void);
  void pins(int trigPin, int echoPin);
  void DistanceMeasure(void);
  long microsecondsToCentimeters(void);
  long microsecondsToMillimeters(void);
  long microsecondsToInches(void);
 private:
  int _trigPin;
  int _echoPin;
  long duration;// the Pulse time received;
};

Ultrasonic::Ultrasonic(void)
{
}

void Ultrasonic::pins(int trigPin, int echoPin)
{
  _trigPin = trigPin;
  _echoPin = echoPin;

  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

/*Begin the detection and get the pulse back signal*/
void Ultrasonic::DistanceMeasure(void)
{
  pinMode(_trigPin, OUTPUT);
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(_trigPin,LOW);
  pinMode(_echoPin,INPUT);
  duration = pulseIn(_echoPin,HIGH);
}

/*The measured distance from the range 0 to 400 Centimeters*/
long Ultrasonic::microsecondsToCentimeters(void)
{
    return duration/29/2;
}

long Ultrasonic::microsecondsToMillimeters(void)
{
  return duration/29/2/10;
}

/*The measured distance from the range 0 to 157 Inches*/
long Ultrasonic::microsecondsToInches(void)
{
    return duration/74/2;
}
