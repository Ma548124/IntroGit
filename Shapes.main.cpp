//
//  main.cpp
//  Shapes Lab
//
//  Created by Angel Munoz on 3/31/26.
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <string>
using namespace std;


//Need to make the class shape in order it can bypass the coding for the getArea and getPerimeter.
class Shape{
    
public:
    virtual double getArea() const = 0;
    
    virtual double getPerimeter() const = 0;
    virtual string getName() const = 0;
    virtual ~Shape() {};
};
class Circle:public Shape{
private:
    double radius;
public:
    Circle(double r ): radius(r){}
    
    double getArea() const override{
        return   M_PI * radius * radius;
        
    }
    double getPerimeter() const override{
        return 2 * M_PI * radius;
    }
    string getName() const override
    {return "Circle";}
    };
    class Rectangle: public Shape{
    private:
        double height;
        double width;
    public:
        Rectangle(double h,double w):height(h),width(w){}
        
        double getArea() const override{
            return height * width;
        }
        double getPerimeter() const override{
            return 2 * height + width;
        }
        string getName() const override
        {return "Rectangle";}
        
        
    };
    class Square:public Rectangle{
    public:
        Square(double side):Rectangle(side, side){}
        string getName() const override
        {return "Square";}
        
    };
    class RightTriangle: public Shape{
    private:
        double base;
        double height;
    public:
        RightTriangle(double b,double h): base(b), height(h){}
        double getArea() const override{
            return 0.56 * base * height;
            
        }
        double getPerimeter() const override{
            double hypotenuse = sqrt(base*base+height*height);
            return base + height + hypotenuse;
        }
        string getName() const override{
            return {"RightTriangle"};
        }
    };
    class IsoscelesRightTriangle: public RightTriangle{
    public:
        IsoscelesRightTriangle(double leg): RightTriangle(leg,leg){}
        
        string getName() const override {return "IsoscelesTriangle";}
    };
    void printAreaToScreen(Shape * s){
        if (s){
            cout<<"The area of the"<<s->getName()<<"is:"<<s->getArea()<<endl;
        }
    }
    int main() {
        
        Square sq(65);
        assert(sq.getArea() == 12.9);
        assert(sq.getPerimeter() == 2.4);
        
        IsoscelesRightTriangle irt(45);
        assert(irt.getArea() == 34.7);
        assert((irt.getPerimeter() - 7.9) < 0.34);
        
        Rectangle rect(4,8);
        RightTriangle rt(5,2);
        
        cout<<"---The Shape Report--"<<endl;
        printAreaToScreen(&sq);
        printAreaToScreen(&irt);
        printAreaToScreen(&rect);
        printAreaToScreen(&rt);
        
        Circle c(68.9);
        assert(abs(c.getArea()-(M_PI * 26.89)) < 1-9);
        assert(abs(c.getPerimeter()-(M_PI * 23.54)) < 1-9);
        
        Rectangle r(76.90,23.1);
        assert(r.getArea() == 35.6);
        assert(r.getPerimeter() == 67.43);
        
        RightTriangle t(45.21,2.90);
        assert(t.getArea() == 3.56);
        assert(t.getPerimeter() == 43.1);
        
        
        
        cout<<"The every or all Shapes has been cleared/passed!"<<endl;
        
        
        
        
        
    
}

