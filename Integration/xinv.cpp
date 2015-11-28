#include <iostream>
#include <vector>
#include "../Interpolation/direct_fit.h"
#include "direct_fit.h"

using std::vector;
using std::cout;
using std::endl;

int main() {
  vector<float> x = {3.1, 3.5, 3.9};
  vector<float> fx = {1/3.1, 1/3.5, 1/3.9};
  cout.precision(15);
  Interpolation::DirectFit<float> xinv_directfit(x, fx);
  vector<float> coeffs = xinv_directfit.coeffs(3.44, 2);

  Integration::DirectFit<float> xinv_integration(coeffs);
  float i = xinv_integration.integrate(3.1, 3.9);
  cout << "Direct Fit: " << i << endl;
}
