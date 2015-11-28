#include <iostream>
#include <vector>
#include "../Interpolation/direct_fit.h"
#include "direct_fit.h"
#include "../Interpolation/newton.h"
#include "newton.h"

using std::vector;
using std::cout;
using std::endl;

template<typename T> void direct_fit() {
  vector<T> x = {3.1, 3.5, 3.9};
  vector<T> fx = {1/3.1, 1/3.5, 1/3.9};

  Interpolation::DirectFit<T> xinv_directfit(x, fx);
  vector<T> coeffs = xinv_directfit.coeffs(3.44, 2);

  Integration::DirectFit<T> xinv_integration(coeffs);
  T i = xinv_integration.integrate(3.1, 3.9);
  cout << "Direct Fit: " << i << endl;
}

template<typename T> void newton() {
  vector<T> x = {3.1, 3.3, 3.5, 3.7, 3.9};
  vector<T> fx = {1/3.1, 1/3.3, 1/3.5, 1/3.7, 1/3.9};

  Interpolation::ForwardDifference<T> xinv_poly(x, fx, 0.2);
  xinv_poly.fit(3.5, 2);
  Integration::Trapezoid<T> xinv_integration(xinv_poly);
  T i = xinv_integration.integrate(3.1, 3.9);
  cout << "Trapezoid: " << i << endl;
}

int main() {
  cout.precision(15);
  direct_fit<double>();
  newton<double>();
}
