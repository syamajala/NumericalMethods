#ifndef FIT_H
#define FIT_H

#include <functional>
#include <vector>

using namespace std;

class Fit {
 protected:
  const vector<float> &x;
  const vector<float> &f;
 public:
 Fit(const vector<float> &x, const vector<float> &f) : x(x), f(f) {};
  virtual function<float (float)> fit(float point, int deg) = 0;
  vector<int> neighbors(const float point, const int deg);
};
#endif
