/*
    Bridge Design Pattern Example in C++

    Purpose:
    The Bridge pattern decouples an abstraction from its implementation so that the two can vary independently.
    It is useful when you want to avoid a permanent binding between an abstraction and its implementation,
    or when both the abstractions and their implementations should be extensible by subclassing.
    The Bridge pattern is often used to separate platform-independent code from platform-specific code.

    In this example, we have a Shape abstraction that uses a Drawing implementation.
    Different shapes (like Circle and Square) can use different drawing APIs (like DrawingAPI1 and DrawingAPI2)
    without being tightly coupled to any specific drawing implementation.
*/

#include <iostream>
#include <string>

// Implementor interface
class DrawingAPI {
public:
    virtual void drawCircle(double x, double y, double radius) const = 0;
    virtual void drawRectangle(double x, double y, double width, double height) const = 0;
    // Add more shape methods as needed
    virtual ~DrawingAPI() {}
};

// Concrete Implementor 1
class DrawingAPI1 : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) const override {
        std::cout << "[API1] Drawing circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }
    void drawRectangle(double x, double y, double width, double height) const override {
        std::cout << "[API1] Drawing rectangle at (" << x << ", " << y << ") with width " << width << " and height " << height << std::endl;
    }
};

// Concrete Implementor 2
class DrawingAPI2 : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) const override {
        std::cout << "[API2] Drawing circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }
    void drawRectangle(double x, double y, double width, double height) const override {
        std::cout << "[API2] Drawing rectangle at (" << x << ", " << y << ") with width " << width << " and height " << height << std::endl;
    }
};

// Abstraction
class Shape {
protected:
    const DrawingAPI& drawingAPI;
public:
    Shape(const DrawingAPI& api) : drawingAPI(api) {}
    virtual void draw() const = 0;
    virtual ~Shape() {}
};

// Refined Abstraction
class Circle : public Shape {
    double x, y, radius;
public:
    Circle(double x, double y, double radius, const DrawingAPI& api)
        : Shape(api), x(x), y(y), radius(radius) {}
    void draw() const override {
        drawingAPI.drawCircle(x, y, radius);
    }
};

class Rectangle : public Shape {
    double x, y, width, height;
public:
    Rectangle(double x, double y, double width, double height, const DrawingAPI& api)
        : Shape(api), x(x), y(y), width(width), height(height) {}
    void draw() const override {
        drawingAPI.drawRectangle(x, y, width, height);
    }
};

int main() {
    DrawingAPI1 api1;
    DrawingAPI2 api2;

    Circle circle1(1, 2, 3, api1);
    Circle circle2(4, 5, 6, api2);

    circle1.draw(); // Uses API1
    circle2.draw(); // Uses API2
    Rectangle rect1(0, 0, 10, 20, api1);
    Rectangle rect2(5, 5, 15, 25, api2);

    rect1.draw(); // Uses API1
    rect2.draw(); // Uses API2
    
    return 0;
}