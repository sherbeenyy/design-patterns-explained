#include <iostream>
#include <vector>

class Shape {
public:
    virtual void draw() const = 0; // pure virtual function making the class abstract
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Circle\n";
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Square\n";
    }
};

// adding a new shape requires creating a new class only
class Triangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Triangle\n";
    }
};

void drawShapes(const std::vector<Shape*>& shapes) {
    for (auto shape : shapes) {
        shape->draw(); // no type checking needed
    }
}

int main() {
    std::vector<Shape*> shapes = { new Circle(), new Square(), new Triangle() };
    drawShapes(shapes);

    for (auto s : shapes) delete s; // just deleting pointers to clean up the memory
    return 0;
}
