#include <complex>
#include <cmath>
using namespace std;
#include "line_operator.h"

complex<double> Tline(complex<double> &in, double length){
	double rotate_phase = (-1)*2*length*M_PI/180;
	double newangle = arg(in) + rotate_phase;
	while (newangle < 0) { newangle += 2*M_PI; }
	while (newangle > 2*M_PI) { newangle -= 2*M_PI; }
	return complex<double>(polar(abs(in), newangle));
}
complex<double> OpenStub(complex<double> &in, double length){
	double openy = tan(length*M_PI/180);
	complex<double> y(GammaToY(in));
	imag(y) = imag(y) + openy;
	return YToGamma(y);
}
complex<double> ShortStub(complex<double> &in, double length){
	double openy = 1/tan(length*M_PI/180);
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
