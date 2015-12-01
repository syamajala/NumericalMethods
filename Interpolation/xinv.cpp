#include <iostream>
#include "direct_fit.hpp"
#include "lagrange.hpp"
#include "neville.hpp"
#include "divided_difference.hpp"
#include "newton.hpp"

using std::cout;
using std::endl;
using std::function;

int main() {
  vector<double> x;
  vector<double> fx;
  double start = 3.4;
  int points = 3;
  int deg = 2;

  x.push_back(3.35);
  fx.push_back(1.0/3.35);
  for(int i = 0; i < points; i++) {
    double _x = start+i*0.1;
    x.push_back(_x);
    fx.push_back(1.0/_x);
  }
  cout.precision(15);
  Interpolation::DirectFit<double> xinv_directfit(x, fx);
  function<double (double)> fit_f = xinv_directfit.fit(3.44, deg);
  cout << "Direct Fit: " << fit_f(3.44) << endl;

  Interpolation::Lagrange<double> xinv_lagrange(x, fx);
  function<double (double)> fit_f1 = xinv_lagrange.fit(3.44, deg);
  cout << "Lagrange: " << fit_f1(3.44) << endl;

  Interpolation::Neville<double> xinv_neville(x, fx);
  function<double (double)> fit_f2 = xinv_neville.fit(3.44, deg);
  cout << "Neville: " << fit_f2(3.44) << endl;

  Interpolation::DividedDifference<double> xinv_difference(x, fx);
  function<double (double)> fit_f3 = xinv_difference.fit(3.44, deg);
  cout << "Divided Difference: " << fit_f3(3.44) << endl;

  x.clear();
  fx.clear();

  start = 3.1;
  points = 9;
  double step = 0.1;
  for(int i = 0; i < points; i++) {
    x.push_back(start+i*step);
    fx.push_back(1/x.back());
  }

  Interpolation::ForwardDifference<double> xinv_forward(x, fx, step);
  function<double (double)> fit_f4 = xinv_forward.fit(3.44, deg);
  cout << "Forward Difference: " << fit_f4(3.44) << endl;

  Interpolation::BackwardDifference<double> xinv_backward(x, fx, step);
  function<double (double)> fit_f5 = xinv_backward.fit(3.44, deg);
  cout << "Backward Difference: " << fit_f5(3.44) << endl;
}
