#ifndef BINOMIAL
#define BINOMIAL

template<typename T>
T factorial(T n) {
  return (n == 1 || n <= 0) ? 1 : factorial(n-1) * n;
}

template<typename T>
T binomial_coefficient(T s, int i) {
  T r = s;
  for(int t = 1; t <= i-1; t++)
    r *= s-t;
  return r/factorial(i);
}

template<typename T>
T nonstandard_binomial_coefficient(T s, int i) {
  T r = s;
  for(int t = 1; t <= i-1; t++)
    r *= s+t;
  return r/factorial(i);
}

#endif
