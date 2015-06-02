#include <iostream>
#include "direct_fit.h"
#include "lagrange.h"

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
  
  DirectFit xinv_directfit = DirectFit(x, fx);
  function<float (float)> fit_f = xinv_directfit.fit(3.44, deg);
  cout << "Direct Fit: " << fit_f(3.44) << endl;

  Lagrange xinv_lagrange = Lagrange(x, fx);
  function<float (float)> fit_f1 = xinv_lagrange.fit(3.44, deg);
  cout << "Lagrange: " << fit_f1(3.44) << endl;
}
