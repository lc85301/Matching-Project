//********************************************
// File: line_operator.cpp
// Description: This cpp file define some operator in microwave
// each take a "complex number" and
// "fratio (freq/Centralfreq)", "electric length(beta)"
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

#include <complex>
#include <math.h>
using namespace std;

complex<double> Tline(complex<double> &in, double fratio, double length);
complex<double> OpenStub(complex<double> &in, double fratio, double length);
complex<double> ShortStub(complex<double> &in, double fratio, double length);
complex<double> GammaToY(complex<double> &in);
complex<double> GammaToZ(complex<double> &in);
complex<double> YToGamma(complex<double> &in);
complex<double> ZToGamma(complex<double> &in);

complex<double> Tline(complex<double> &in, double fratio, double length){
	double rotate_phase = (-1)*2*fratio*length*M_PI/180;
	double newangle = arg(in) + rotate_phase;
	while (newangle < 0) { newangle += 2*M_PI; }
	while (newangle > 2*M_PI) { newangle -= 2*M_PI; }
	return complex<double>(polar(abs(in), newangle));
}
complex<double> OpenStub(complex<double> &in, double fratio, double length){
	double openy = tan(fratio*length*M_PI/180);
	complex<double> y(GammaToY(in));
	imag(y) = imag(y) + openy;
	return YToGamma(y);
}
complex<double> ShortStub(complex<double> &in, double fratio, double length){
	double openy = 1/tan(fratio*length*M_PI/180);
	complex<double> y(GammaToY(in));
	imag(y) = imag(y) - openy;
	return YToGamma(y);
}
//return (1-gamma)/(1+gamma)/50
complex<double> GammaToY(complex<double> &in){
	return -1.0*(in-1.0)/(in+1.0);
}
////return 50*(1+gamma)/(1-gamma)
complex<double> GammaToZ(complex<double> &in){
	return -1.0*(in+1.0)/(in-1.0);
}
//return -1*(y-1)/(y+1)
complex<double> YToGamma(complex<double> &in){
	return -1.0*(in-1.0)/(in+1.0);
}
//return (z-1)/(z+1)
complex<double> ZToGamma(complex<double> &in){
	return (in-1.0)/(in+1.0);
}
