#include <vector>
#include <cmath>
#include "newton_systems.h"
#include "radians.h"

static constexpr double r1 = 10.0;
static constexpr double r2 = 6.0;
static constexpr double r3 = 8.0;
static constexpr double r4 = 4.0;
static const double theta_4 = deg_to_rad<double>(220.0);

template <class R>
class Systems_Link : public NonlinearSystems::NewtonSystems<R> {
public:
  Systems_Link(vector<R> initial_guesses, vector<R> e) :
    NonlinearSystems::NewtonSystems<R>(initial_guesses, e) {};

  vector<R> f(vector<R> &x) {
    vector<R> fx = {
      r2*cos(x[0]) + r3*cos(x[1]) + r4*cos(theta_4) - r1,
      r2*sin(x[0]) + r3*sin(x[1]) + r4*sin(theta_4)
    };
    return fx;
  };

  // Must be in column major format
  vector<vector<R>> df(vector<R>& x) {
    vector<vector<R>> dfx = {
      { -r2*sin(x[0]),  r2*cos(x[0])},
      {  -r3*sin(x[1]), r3*cos(x[1]) }
    };
    return dfx;
  };
};

int main() {
  vector<double> initial_guesses = { deg_to_rad<double>(30.0),
                                     deg_to_rad<double>(0.0) };
  vector<double> e(2, 0.000001);
  Systems_Link<double> slink(initial_guesses, e);
  vector<double> r = slink.iterate();

  cout.precision(15);
  for(auto &x : r)
    cout << rad_to_deg<double>(x) << " ";
  cout << endl;
  return 0;
}

