#include<iostream>
using namespace std;
const float PI = 3.141593;
const float FENCE_PRICE = 35;
const float CONCRETE_PRICE = 20;
class Circle {
public:
	Circle(float r);
	float circumference();
	float area();
private:
	float radius;
};
int main()
{
	float radius;
	cout << "Enter the radius of the pool: ";
	cin >> radius;
	Circle pool(radius);
	Circle poolrim(radius+3);
	auto fencecost = poolrim.circumference() * FENCE_PRICE;
	auto concretecost = (poolrim.area() - pool.area()) * CONCRETE_PRICE;
	cout << fencecost << endl<< concretecost << endl;
	return 0;
}
Circle::Circle(float r)
{
	radius = r;
}
float Circle::circumference()
{
	return 2 * PI * radius;
}
float Circle::area()
{
	return PI * radius * radius;
}
