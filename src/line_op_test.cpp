#include <iostream>
#include <cmath>
#include <complex>
using namespace std;
#include "line_operator.cpp"
int main(int argc, const char *argv[])
{
	complex<double> a(-0.226, -0.621), b, c;
	cout << a  << endl;
	cout << Tline(a, 60);
	return 0;
}
