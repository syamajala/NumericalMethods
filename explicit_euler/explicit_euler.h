#include <vector>
#include <cstdarg>

using namespace std;

class ExplicitEuler {
 protected:
  double initial_condition;
  double step_size;
  int steps;
  vector<double> y_n;
  vector<double> f_n;
 public:
  ExplicitEuler(double initial_condition, double step_size, int steps);
  virtual double f_nplusone(double t_n, double T_n) = 0;
  double y_nplusone(double y_n, double f_n);  
  void iterate();
  void print_table();
};
