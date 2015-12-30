#include <iostream>
#include <vector>
#include <utility>
#include "ODEs/equilibrium.hpp"

using std::vector;
using std::pair;

template <class E>
class Heat : public ODEs::Equilibrium<E> {
public:
  Heat(pair<E, E> &start_end, vector<E> &ic, E step_size, int steps) :
    ODEs::Equilibrium<E>(start_end, ic, step_size, steps) {};

  E P(E x) {
    return 0;
  };

  E Q(E x) {
    return -16.0;
  };

  E F(E x) {
    return 0;
  };
};

int main() {
  pair<double, double> start_end(0.0, 1.0);
  vector<double> ic = {0.0, 100.0};
  double step_size = 0.125;
  int steps = 8;

  Heat<double> h(start_end, ic, step_size, steps);
  h.iterate();
  cout << h << endl;
}
