#include <limits>
#include <cmath>

using namespace std;

typedef numeric_limits<double> dbl;

double rad_to_deg(double x) {
  return x*(180.0/M_PI);
}

const double deg_to_rad(double x) {
  return x*(M_PI/180.0);
}


