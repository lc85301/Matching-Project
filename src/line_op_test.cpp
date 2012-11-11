#include <iostream>
#include <cmath>
#include <complex>
using namespace std;
#include "line_operator.cpp"
int main(int argc, const char *argv[])
{
	complex<double> a(0.5,0.5), b, c;
	//gamma = 0.707<45
	cout << ShortStub(a,1,30) << endl;
	return 0;
}
