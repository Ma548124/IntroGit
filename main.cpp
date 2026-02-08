//
//  main.cpp
//  I Get The Point!
//
//  Created by Angel Munoz on 2/3/26.
//

#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

class Point {
private:
    double x, y;

public:
    // Constructor
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    // Getters (optional, for testing)
    double getX() const { return x; }
    double getY() const { return y; }

    // Overloaded operators

    // Distance: p1 - p2 returns distance
    friend double operator-(const Point& p1, const Point& p2) {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        return sqrt(dx * dx + dy * dy);
    }

    // Equality: p1 == p2
    friend bool operator==(const Point& p1, const Point& p2) {
        return p1.x == p2.x && p1.y == p2.y;
    }

    // Inequality: p1 != p2
    friend bool operator!=(const Point& p1, const Point& p2) {
        return !(p1 == p2);
    }

    // Midpoint: p1 / p2 returns midpoint
    friend Point operator/(const Point& p1, const Point& p2) {
        return Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
    }

    // Output streaming: cout << p
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    // Input streaming: cin >> p, expects (x, y)
    friend istream& operator>>(istream& is, Point& p) {
        char ch;
        is >> ch; // Read '('
        if (ch != '(') {
            is.setstate(ios::failbit);
            return is;
        }
        is >> p.x;
        is >> ch; // Read ','
        if (ch != ',') {
            is.setstate(ios::failbit);
            return is;
        }
        is >> p.y;
        is >> ch; // Read ')'
        if (ch != ')') {
            is.setstate(ios::failbit);
            return is;
        }
        return is;
    }

    // Prefix ++: ++p increments x
    Point& operator++() {
        ++x;
        return *this;
    }

    // Postfix ++: p++ increments y
    Point operator++(int) {
        Point temp = *this;
        ++y;
        return temp;
    }

    // Prefix --: --p decrements x
    Point& operator--() {
        --x;
        return *this;
    }

    // Postfix --: p-- decrements y
    Point operator--(int) {
        Point temp = *this;
        --y;
        return temp;
    }

    // Subscript: p[0] for x, p[1] for y
    double& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        throw out_of_range("Index must be 0 or 1");
    }

    const double& operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        throw out_of_range("Index must be 0 or 1");
    }
};

// Example usage (for testing)
int main() {
    Point p1(5.16, 13.567);
    Point p2(2.98, 8.24);

    // Distance
    cout << "Distance: " << p1 - p2 << endl;

    // Equality
    cout << "Equal: " << (p1 == p2) << endl;
    cout << "Not equal: " << (p1 != p2) << endl;

    // Midpoint
    Point mid = p1 / p2;
    cout << "Midpoint: " << mid << endl;

    // Output
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;

    // Increment/Decrement
    ++p1; // x++
    cout << "After ++p1: " << p1 << endl;
    p1++; // y++
    cout << "After p1++: " << p1 << endl;
    --p1; // x--
    cout << "After --p1: " << p1 << endl;
    p1--; // y--
    cout << "After p1--: " << p1 << endl;

    // Subscript
    cout << "p1[0]: " << p1[0] << endl;
    cout << "p1[1]: " << p1[1] << endl;
    p1[0] = 10.0;
    cout << "After p1[0] = 10: " << p1 << endl;

    // Input
    Point p3;
    cout << "Enter a point in the form that will be (x, y): ";
    cin >> p3;
    cout << "You entered this equation: " << p3 << endl;

    return 0;
}
