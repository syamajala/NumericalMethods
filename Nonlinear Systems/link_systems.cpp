#include <vector>
#include <cmath>
#include "newton_systems.h"
#include "radians.h"

static constexpr double r1 = 10.0;
static constexpr double r2 = 6.0;
static constexpr double r3 = 8.0;
static constexpr double r4 = 4.0;

template <class R>
class Systems_Link : public NewtonSystems<R> {
public:
  Systems_Link(vector<R> initial_guesses, vector<R> e) :
    NewtonSystems<R>(initial_guesses, e) {};

  vector<R> f(vector<R> &x) {
    vector<R> fx = {
      r2*cos(x[0]) + r3*cos(x[1]) + r4*cos(x[2]) - r1,
      r2*sin(x[0]) + r3*sin(x[1]) + r4*sin(x[2])
    };
    return fx;
  };

  vector<vector<R>> df(vector<R>& x) {
    vector<vector<R>> dfx = {
      { -r2*sin(x[0]), -r3*sin(x[1]) },
      { r2*cos(x[0]), r3*cos(x[1]) }
    };
    return dfx;
  };
};

int main() {
  vector<double> initial_guesses = { deg_to_rad<double>(30.0),
                                     deg_to_rad<double>(0.0),
                                     deg_to_rad<double>(220.0) };
  vector<double> e(2, 0.000001);
  Systems_Link<double> slink(initial_guesses, e);
  slink.iterate();
  return 0;
}

