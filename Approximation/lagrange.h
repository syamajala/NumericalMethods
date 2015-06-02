#include "fit.h"

using namespace std;

class Lagrange : public Fit {
 public:
 Lagrange(const vector<float> &x, const vector<float> &f) : Fit(x, f) {};
  function<float (float)> fit(const float point, const int deg);
};
