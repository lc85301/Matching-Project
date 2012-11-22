//********************************************
// File: line_operator.h
// Description: This header file define some operator in microwave
// each take a "complex number" and
// "electric length(beta)"
// return the complex gamma
//  1. Tline(): rotate the complex
//  2. OpenStub(): Y = jtan(betaL)
//  3. ShortStub(): Y = 1/jtan(betaL)
//  use by above 3 function, function as their name indicate:
//  get a complex and return another complex
//  !!!!!assume Z0 = 50
//  4. GammaToY():
//  5. GammaToZ():
//  6. YToGamma():
//  7. ZToGamma():
//********************************************

#ifndef LINE_OPERATOR_H_
#define LINE_OPERATOR_H_

#include <complex>

complex<double> Tline(complex<double> &in, double length);
complex<double> OpenStub(complex<double> &in, double length);
complex<double> ShortStub(complex<double> &in, double length);
complex<double> GammaToY(complex<double> &in);
complex<double> GammaToZ(complex<double> &in);
complex<double> YToGamma(complex<double> &in);
complex<double> ZToGamma(complex<double> &in);

#endif

