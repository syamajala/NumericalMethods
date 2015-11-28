#include <iostream>
#include <vector>
#include "direct_fit.h"

using std::vector;
using std::cout;
using std::endl;

template <typename _T> void univariate() {
  vector<_T> T = { 800.0, 1000.0, 1200.0 };
  vector<_T> P = { 1150.0, 1200.0, 1250.0 };

  vector<_T> R0 = { 1380.4, 1500.2, 1614.5 };
  vector<_T> R1 = { 1377.7, 1499.0, 1613.6 };
  vector<_T> R2 = { 1375.2, 1497.1, 1612.6 };

  Interpolation::DirectFit<_T> T_1100_P_1150(T, R0);
  function<_T (_T)> T_1100_P_1150_fit = T_1100_P_1150.fit(1150, 2);
  _T f_1150_1100 = T_1100_P_1150_fit(1100);

  Interpolation::DirectFit<_T> T_1100_P_1200(T, R1);
  function<_T (_T)> T_1100_P_1200_fit = T_1100_P_1200.fit(1150, 2);
  _T f_1150_1200 = T_1100_P_1200_fit(1100);

  Interpolation::DirectFit<_T> T_1100_P_1250(T, R2);
  function<_T (_T)> T_1100_P_1250_fit = T_1100_P_1250.fit(1150, 2);
  _T f_1150_1250 = T_1100_P_1250_fit(1100);

  vector<_T> T_1100 = { f_1150_1100, f_1150_1200, f_1150_1250 };
  Interpolation::DirectFit<_T> T_1100_P_1225(P, T_1100);
  function<_T (_T)> f_1100_1225 = T_1100_P_1225.fit(1, 2);

  cout << f_1100_1225(1225) << endl;
}

int main() {
  univariate<double>();
}
