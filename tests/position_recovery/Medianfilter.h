/* #ifndef MEDIANFILTER_H */
/* #define MEDIANFILTER_H */

class Fuckingfilter {
 public:
  Fuckingfilter(void);
  void add(long);
  long getAvg(void);
    
 private:
  int num;
  int _index;
  long _total;
  long _history[5];

};

Fuckingfilter::Fuckingfilter(void)
{
  num = 5;
  for (int i = 0; i < num; ++i) {
    _history[i] = 0;
  }
  _index = 0;
  _total = 0;
}

void Fuckingfilter::add(long val)
{
  _total = _total - _history[_index] + val;
  _history[_index] = val;
  _index++;
  // if index > num
}

long Fuckingfilter::getAvg(void)
{
  return _total / num;
}

/* #endif */
