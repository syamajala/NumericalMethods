#include <math.h>
#include "explicit_euler.h"

using namespace std;

class Radiation: public ExplicitEuler {
protected:
  static constexpr double alpha = 4.0*10.0e-13;
  static constexpr double T_a4 = pow(250.0, 4);
public:
  Radiation(double initial_condition, double step_size, double steps) :
    ExplicitEuler(initial_condition, step_size, steps) {
    f_n.push_back(-1*(this->alpha)*(pow(initial_condition, 4) - T_a4));
    y_n.push_back(initial_condition);
  };

  double f_nplusone(double t_n, double T_n) {
    return -(this->alpha)*(pow(T_n, 4) - T_a4);
  }
};

int main() {
  double initial_condition = 2500.0;
  double del_t = 2.0;

  Radiation r = Radiation(initial_condition, del_t, 5);
  r.iterate();
  r.print_table();
  return 0;
}
