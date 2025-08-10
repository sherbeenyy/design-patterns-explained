#include <iostream>
#include <vector>

enum ShapeType {
    CIRCLE,
    SQUARE
};

class Shape {
public:
    ShapeType type;
    Shape(ShapeType t) : type(t) {}
};

class Circle : public Shape {
public:
    Circle() : Shape(CIRCLE) {}
};

class Square : public Shape {
public:
    Square() : Shape(SQUARE) {}
};

void drawShapes(const std::vector<Shape*>& shapes) {
    for (auto shape : shapes) {
        if (shape->type == CIRCLE) {
            std::cout << "Drawing Circle\n";
        } 
        else if (shape->type == SQUARE) {
            std::cout << "Drawing Square\n";
        }
        // adding a new shape? you must edit this function
        // so imagine adding 20 different shapes wtf ?
    }
}

int main() {
    std::vector<Shape*> shapes = { new Circle(), new Square() };
    drawShapes(shapes);

    for (auto s : shapes) delete s; // just deleting pointers to clean up the memory
    return 0;
}
