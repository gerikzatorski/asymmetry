#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#define SIZE_HIST 5

class MedianFilter
{
 public:
  MedianFilter(void);
  void add(double);
  double getAvg(void);
    
 private:
  int num = SIZE_HIST;
  int _index;
  double _total;
  double _history[SIZE_HIST];
};

MedianFilter::MedianFilter(void)
{
  num = 5;
  for (int i = 0; i < num; ++i) {
    _history[i] = 0;
  }
  _index = 0;
  _total = 0.0;
}

void MedianFilter::add(double val)
{
  _total = _total - _history[_index] + val;
  _history[_index] = val;
  _index++;
  if (_index == num) {
    _index = 0;
  }
}

double MedianFilter::getAvg(void)
{
  return double(_total / num);
}

#endif
