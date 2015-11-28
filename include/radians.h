#ifndef RADIANS_H
#define RADIANS_H

#include <cmath>

using namespace std;

template<typename T>
T rad_to_deg(T x) {
  return x*(180.0/M_PI);
}

template<typename T>
const T deg_to_rad(T x) {
  return x*(M_PI/180.0);
}

#endif
