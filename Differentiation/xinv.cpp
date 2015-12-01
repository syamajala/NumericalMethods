#include <iostream>
#include "direct_fit.hpp"
#include "../Interpolation/direct_fit.hpp"

using std::cout;
using std::endl;
using std::function;

int main() {
  vector<float> x = {3.4, 3.5, 3.6};
  vector<float> fx = {1/3.4, 1/3.5, 1/3.6};

  Interpolation::DirectFit<float> xinv_poly_directfit(x, fx);
  vector<float> coeffs = xinv_poly_directfit.coeffs(3.5, 2);
  Differentiation::DirectFit<float> xinv_deriv_directfit(coeffs);
  function<float (float)> fit_f1 = xinv_deriv_directfit.differentiate();
  cout << "Direct fit: " << fit_f1(3.5) << endl;
}
