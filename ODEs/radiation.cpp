#include <iostream>
#include <math.h>
#include "explicit_euler.h"
#include "implicit_euler.h"

static constexpr double alpha = 4.0*10.0e-13;
static constexpr double T_a4 = pow(250.0, 4);

template <class E>
class ExplicitRadiation : public ExplicitEuler<E> {

public:
  ExplicitRadiation(E initial_condition, E step_size, int steps) :
    ExplicitEuler<E>(initial_condition, step_size, steps) {
    this->f_n.push_back(-1*alpha*(pow(initial_condition, 4) - T_a4));
    this->y_n.push_back(initial_condition);
  };

  E derivative(E t_n, E T_n) {
    return -alpha*(pow(T_n, 4) - T_a4);
  };
};

template <class E>
class ImplicitRadiation : public ImplicitEuler<E> {
  ImplicitRadiation(E initial_condition, E step_size, int steps) :
    ImplicitEuler<E>(initial_condition, step_size, steps) {
    
  };

  E derivative(E t_n, E T_n) {
    return 0.0;
  };
};

int main() {
  double initial_condition = 2500.0;
  double del_t = 2.0;

  ExplicitRadiation<double> r(initial_condition, del_t, 5);
  r.iterate();
  cout << r;
  return 0;
}

