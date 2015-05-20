using namespace std;

class Iterative {
 protected:
  double a;
  double b;
  double e;

 public:
  Iterative(double a, double b, double e);
  virtual double f(double x) = 0;
  double iterate_bisection();
  double iterate_false_position();
};
