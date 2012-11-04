#include <iostream>
#include <cmath>
using namespace std;

#include "complex.h"

Complex::Complex(double r, double i):
	real(r),imag(i){};
ostream& operator<<(ostream& out, const Complex& c){
	out << "(" << c.real << "," << c.imag << "j)";
	return out;
}

double Complex::distance() const{ return (real*real + imag*imag); }
double Complex::abs() const{ return sqrt(real*real + imag*imag); }
Complex Complex::conj() const{ return Complex(real, -1*imag); }

void Complex::add(const Complex &lhs, const Complex &rhs)
{
	real = lhs.real + rhs.real;
	imag = lhs.imag + rhs.imag;
}
void Complex::sub(const Complex &lhs, const Complex &rhs)
{
	real = lhs.real - rhs.real;
	imag = lhs.imag - rhs.imag;
}
void Complex::mul(const Complex &lhs, const Complex &rhs)
{
	real = lhs.real * rhs.real - lhs.imag * rhs.imag;
	imag = lhs.real * rhs.imag + lhs.imag * rhs.real;
}
void Complex::div(const Complex &lhs, const Complex &rhs)
{
	double denominant = rhs.distance();
	if (denominant == 0) {
		real = imag = 0;
		return;
	}
	real = (lhs.real * rhs.real + lhs.imag * rhs.imag) / denominant;
	imag = (lhs.imag * rhs.real - lhs.real * rhs.imag) / denominant;
}
bool Complex::operator==(const Complex &rhs) const{
	return (this->real == rhs.real && this->imag == rhs.imag);
}
bool Complex::operator!=(const Complex &rhs) const{
	return !(*this == rhs);
}
