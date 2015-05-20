#include <cmath>
#include "iterative.h"

Iterative::Iterative(double a, double b, double e) : a(a), b(b), e(e) {};

double Iterative::iterate_bisection() {
  double c = (this->a+this->b)/2.0;
  while(abs(b - a) >= e) {
    if(f(a)*f(c) < 0)
      b = c;
    else if (f(a)*f(c) > 0)
      a = c;
    else if (f(a)*f(c) == 0)
      break;
    c = (a+b)/2.0;
  }

  return c;
}

double Iterative::iterate_false_position() {
  double dg = 0.0;
  double c = 0.0;
  double fa = 0.0;
  double fb = 0.0;
  double fc = 0.0;
    
  while (abs(b-a) >= e) {
      fb = f(b);
      fa = f(a);
      dg = (fb - fa)/(b-a);
      c = b - fb/dg;
      fc = f(c);

      if(fa*fc < 0)
	b = c;
      else if (fa*fc > 0)
	a = c;
      else if (fa*fc == 0)
	break;      
    }

    return c;
}

double Iterative::iterate_secant() {
  double t = 0.0;
  double x_i = this->a;
  double x_ip1 = this->b;

  double dg_xi = (f(x_ip1) - f(x_i))/(x_ip1-x_i);
  t = x_ip1;
  x_ip1 = x_i - (f(x_i)/dg_xi);
  x_i = t;
  
  while(abs(x_ip1 - x_i) >= e) {
    dg_xi = (f(x_ip1) - f(x_i))/(x_ip1-x_i);
    t = x_ip1;
    x_ip1 = x_i - (f(x_i)/dg_xi);
    x_i = t;
  }

  return x_ip1;
}
