#include <iostream>
#include "direct_fit.h"

int main() {
  vector<float> x; 
  vector<float> fx;
  float start = 3.4;
  int points = 3;
  int deg = 2;

  x.push_back(3.35);
  fx.push_back(1.0/3.35);
  for(int i = 0; i < points; i++) {
    float _x = start+i*0.1;
    x.push_back(_x);
    fx.push_back(1.0/_x);
  }
  
  DirectFit xinv = DirectFit(x, fx);
  function<float (float)> fit_f = xinv.fit(3.44, deg);
  cout << fit_f(3.44) << endl;
}
