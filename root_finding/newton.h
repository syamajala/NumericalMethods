using namespace std;

class Newton {
 private:
  double initial_guess;
  double e;
 public:
  Newton(double initial_guess, double e);
  virtual double f(double x) = 0;
  virtual double df(double x) = 0;
  double iterate();
};
