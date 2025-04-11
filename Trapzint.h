#pragma once
#ifndef _TRAPZINT_H
#define _TRAPZINT_H
class Function {
public:
	virtual double operator ()(double x)const = 0;
	virtual ~Function() {}
};
class MyFunction :public Function {
public:
	virtual double operator()(double x)const;
};
class Intergration {
public:
	virtual double operator()(double a, double b, double eps)const = 0;
	virtual ~Intergration() {}
};
class Trapz :public Intergration {
public:
	Trapz(const Function& f) :f(f) {}
	virtual double operator()(double a, double b, double eps)const;
private:
	const Function& f;
};
#endif
