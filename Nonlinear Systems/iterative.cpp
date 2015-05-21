#include <cmath>
#include "iterative.h"

Iterative::Iterative(double a, double b, double e) : a(a), b(b), e(e) {};

double Iterative::iterate_bisection() {
  double p = a;
  double q = b;
  double r = (this->a+this->b)/2.0;
  
  while(abs(q - p) >= e) {
    if(f(p)*f(r) < 0)
      q = r;
    else if (f(p)*f(r) > 0)
      p = r;
    else if (f(p)*f(r) == 0)
      break;
    r = (p+q)/2.0;
  }

  return r;
}

double Iterative::iterate_false_position() {
  double dg = 0.0;
  double p = a;
  double q = b;
  double r = 0.0;
  double fa = 0.0;
  double fb = 0.0;
  double fc = 0.0;
    
  while (abs(q - p) >= e) {
      fb = f(q);
      fa = f(p);
      dg = (fb - fa)/(q-p);
      r = q - fb/dg;
      fc = f(r);

      if(fa*fc < 0)
	q = r;
      else if (fa*fc > 0)
	p = r;
      else if (fa*fc == 0)
	break;      
    }

    return r;
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
