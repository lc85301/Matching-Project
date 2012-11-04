#ifndef __COMPLEX__H__
#define __COMPLEX__H__

#define PI pi

class Complex {
public:
	friend ostream& operator<<(ostream&, const Complex&);
	Complex (double r=0, double i=0);

	double distance() const;
	double abs() const;
	Complex conj() const;
	//basic function for operator + and +=
	//modify lhs directly and no residual copy
	void add(const Complex& lhs, const Complex& rhs);
	void sub(const Complex& lhs, const Complex& rhs);
	void mul(const Complex& lhs, const Complex& rhs);
	void div(const Complex& lhs, const Complex& rhs);

	//overload comparison operator
	bool operator==(const Complex &rhs) const;
	bool operator!=(const Complex &rhs) const;
	//overload return-by-value operator
	Complex operator+(const Complex &rhs) const;
	Complex operator-(const Complex &rhs) const;
	Complex operator*(const Complex &rhs) const;
	Complex operator/(const Complex &rhs) const;
	//overload assignment operator
	void operator+=(const Complex &rhs);
	void operator-=(const Complex &rhs);
	void operator*=(const Complex &rhs);
	void operator/=(const Complex &rhs);

	double real;
	double imag;
};

inline Complex Complex::operator+(const Complex &rhs) const
{
	Complex ans;
	ans.add(*this, rhs);
	return ans;
}
inline Complex Complex::operator-(const Complex &rhs) const
{
	Complex ans;
	ans.sub(*this, rhs);
	return ans;
}
inline Complex Complex::operator*(const Complex& rhs) const{
	Complex ans;
	ans.mul(*this, rhs);
	return ans; 
}
inline Complex Complex::operator/(const Complex& rhs) const{
	Complex ans;
	ans.div(*this, rhs);
	return ans;
}
inline void Complex::operator+=(const Complex &rhs)
{
	add(*this, rhs);
}
inline void Complex::operator-=(const Complex &rhs)
{
	sub(*this, rhs);
}
inline void Complex::operator*=(const Complex& rhs)
{
	mul(*this, rhs);
}
inline void Complex::operator/=(const Complex& rhs){
	div(*this, rhs);
}

#endif /* end of include guard: __COMPLEX__H__ */
