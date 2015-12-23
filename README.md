C++11 implementation of numerical algorithms described in [Numerical Methods for
Engineers and Scientists](http://www.amazon.com/Numerical-Methods-Engineers-Scientists-Edition/dp/0824704436) by Hoffman.

Requires CMake, Armadillo and ANN.

Currently includes:

### Nonlinear systems
  * Bisection root finding method
  * False position root finding method
  * Newton's method
  * Secant method
  * Newton's method for systems

### Interpolation
  * Direct fit polynomial interpolation
  * Lagrange interpolation
  * Neville's algorithm
  * Divided difference
  * Newton forward difference
  * Newton backward difference

### Differentiation
  * Direct fit

### Integration
  * Direct fit
  * Trapezoid rule

### ODEs
  * Implicit Euler method
  * Explicit Euler method (for systems)
  * Modified midpoint method (for systems)
  * Modified Euler method (for systems)
  * Fourth order Runge Kutta (for systems)
  * Extrapolated modified midpoint method (for systems)
  * Adams-Bashforth-Moulton method (for systems)
