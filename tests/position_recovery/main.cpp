// #include "Waveform.h"
// #include <iostream>
// #include "matplotlibcpp.h"

// using namespace std;

// void graphWave(asymmetry::Waveform *wave) {
//   namespace plt = matplotlibcpp;
  
//   double n = (double) wave->getN();
//   vector<double> x(n+1),y(n+1); 

//   for(int i=0; i<n; ++i) {
//     double t = i/n;
//     x.at(i) = wave->getTime(i);
//     y.at(i) = wave->getUpdate(i);
//   }

//   x.at(n) = wave->getPeriod();
//   y.at(n) = wave->getUpdate(0);
    
//   plt::plot(x, y, "r-");
//   // plt::plot(y, "b-");
//   plt::show(); 
// }

// // void Waveform::graphApprox(double f_int) {
// //   double T_int = 1.0 / f_int;
  
// //   double n = (double) _T / T_int;
// //   vector<double> x(n+1),y(n+1); 
  
// //   int i = 0;
// //   double t = 0;

// //   while (t < _T) {
// //     x.at(i) = i * T_int;
// //     y.at(i) = approx(t);
// //     i++;
// //     t = i * T_int;
// //   }

// //   x.at(n) = _T;
// //   y.at(n) = _updates[0];

// //   plt::plot(x, y, "r-");
// //   plt::show();
// // }

// int main() 
// {
//   asymmetry::Waveform waveform(3);
//   asymmetry::SineWave sinewave(3);
//   asymmetry::TriangleWave trianglewave(1);

//   // test sinewaves
//   sinewave.setSkew(0.7);
//   sinewave.compute();
//   asymmetry::SineWave *pwave;
//   pwave = &sinewave;

//   // test trianglewaves
//   // trianglewave.setSkew(2.0);
//   // trianglewave.compute();
//   // asymmetry::TriangleWave *pwave;
//   // pwave = &trianglewave;

//   // DEBUGGING
//   // cout << waveform.getPeriod() << endl;
//   // cout << sinewave.getPeriod() << endl;
  
//   graphWave(pwave);
  
//   return 0;
// } 
