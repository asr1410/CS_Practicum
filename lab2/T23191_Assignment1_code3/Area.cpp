#include <bits/stdc++.h>
using namespace std;

class Area
{
private:
public:
    Area(){};
    double getArea(double length, double breadth)
    {
        return length * breadth;
    }
};
class Circle : public Area
{
private:
public:
    Circle(){};
    double getArea(double radius)
    {
        return M_PI * radius * radius;
    }
};
class Triangle : public Area
{
private:
public:
    Triangle(){};
    double getArea(double sideOne, double sideTwo, double sideThree)
    {
        double halfPerimeter = (sideOne + sideTwo + sideThree) / 2;
        return sqrt(halfPerimeter * (halfPerimeter - sideOne) * (halfPerimeter - sideTwo) * (halfPerimeter - sideThree));
    }
};
class Solution
{
private:
public:
    Solution(){};
    void rectangleArea(double var1, double var2)
    {
        Area a;
        cout << "Area of Rectangle : " << a.getArea(var1, var2) << endl;
    }
    void circleArea(double var1)
    {
        Circle c;
        cout << "Area of Circle : " << c.getArea(var1) << endl;
    }
    void triangleArea(int var1, int var2, int var3)
    {
        Triangle t;
        cout << "Area of Triangle : " << t.getArea(var1, var2, var3) << endl;
    }
};

int main()
{
    Solution s;
    double var1, var2, var3;
    cout << "Enter Length and Breadth of Rectangle : ";
    cin >> var1 >> var2;
    s.rectangleArea(var1, var2);
    cout << "Enter radius of Circle : ";
    cin >> var1;
    s.circleArea(var1);
    cout << "Enter sides of Triangle: ";
    cin >> var1 >> var2 >> var3;
    s.triangleArea(var1, var2, var3);
    return 0;
}