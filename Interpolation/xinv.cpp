#include <iostream>
#include "direct_fit.h"
#include "lagrange.h"
#include "neville.h"
#include "divided_difference.h"

using namespace std;

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

  DirectFit<float> xinv_directfit(x, fx);
  function<float (float)> fit_f = xinv_directfit.fit(3.44, deg);
  cout << "Direct Fit: " << fit_f(3.44) << endl;

  Lagrange<float> xinv_lagrange(x, fx);
  function<float (float)> fit_f1 = xinv_lagrange.fit(3.44, deg);
  cout << "Lagrange: " << fit_f1(3.44) << endl;

  Neville<float> xinv_neville(x, fx);
  function<float (float)> fit_f2 = xinv_neville.fit(3.44, deg);
  cout << "Neville: " << fit_f2(3.44) << endl;

  DividedDifference<float> xinv_difference(x, fx);
  function<float (float)> fit_f3 = xinv_difference.fit(3.44, deg);
  cout << "Divided Difference: " << fit_f3(3.44) << endl;

  // ForwardDifference<float> xinv_forward(x, fx, 0.1);
  // function<float (float)> fit_f4 = xinv_forward.fit(3.44, deg);
}
