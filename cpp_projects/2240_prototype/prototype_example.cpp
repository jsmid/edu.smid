/*
    Prototype Design Pattern Example in C++

    Purpose:
    The Prototype pattern is used to create new objects by copying an existing object, known as the prototype.
    This pattern is useful when the cost of creating a new object is expensive or complex.
    Instead of creating new instances from scratch, you clone a prototype.
    It also helps when you want to avoid subclassing for object creation.

    In this example, we demonstrate how to clone shapes (Circle and Rectangle) using the Prototype pattern.
*/

#include <iostream>
#include <string>

// Prototype interface
class Shape {
public:
    virtual ~Shape() {}
    virtual Shape* clone() const = 0;
    virtual void draw() const = 0;
};

// Concrete Prototype 1
class Circle : public Shape {
private:
    int radius;
public:
    Circle(int r) : radius(r) {}
    Circle(const Circle& other) : radius(other.radius) {}
    Shape* clone() const {
        return new Circle(*this);
    }
    void draw() const {
        std::cout << "Drawing a Circle with radius " << radius << std::endl;
    }
};

// Concrete Prototype 2
class Rectangle : public Shape {
private:
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {}
    Rectangle(const Rectangle& other) : width(other.width), height(other.height) {}
    Shape* clone() const {
        return new Rectangle(*this);
    }
    void draw() const {
        std::cout << "Drawing a Rectangle of size " << width << "x" << height << std::endl;
    }
};

int main() {
    // Create original objects
    Shape* circle1 = new Circle(10);
    Shape* rect1 = new Rectangle(5, 8);

    // Clone the objects
    Shape* circle2 = circle1->clone();
    Shape* rect2 = rect1->clone();

    // Draw originals and clones
    std::cout << "Originals:" << std::endl;
    circle1->draw();
    rect1->draw();

    std::cout << "Clones:" << std::endl;
    circle2->draw();
    rect2->draw();

    // Clean up
    delete circle1;
    delete rect1;
    delete circle2;
    delete rect2;

    return 0;
}