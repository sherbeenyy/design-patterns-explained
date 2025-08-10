# Open/Closed Principle (OCP)

> "Software entities should be open for extension, but closed for modification."

---

## What is OCP?
The **Open/Closed Principle** means your code should be:
- **Open for extension** → You can add new behavior without touching old code.
- **Closed for modification** → You shouldn’t have to change already working code just to add new features.

---

## Example Scenario
We want to build a small program that draws different shapes:  
- Initially, we have a `Circle` and a `Square`.  
- Later, we may want to add more shapes, like a `Triangle`.

The question is: How should we design our code so that adding new shapes is easy and safe?

---

## Bad Example – Violating OCP
See [`bad_example.cpp`](./bad_example.cpp)

**How it works:**
- We have a `Shape` class with a `ShapeType` enum (CIRCLE, SQUARE).
- We have `Circle` and `Square` classes storing their type.
- In `drawShapes()`, we check the type with `if`/`else` and decide how to draw.

**The problem:**
- If we add a `Triangle`, we must edit the `drawShapes()` function and add a new `if` branch.
- This means modifying existing, tested code every time we add something new.
- The function grows larger and harder to maintain.

---

## Good Example – Following OCP
See [`good_example.cpp`](./good_example.cpp)

**How it works:**
- We have an abstract `Shape` class with a `draw()` method.
- Each shape (`Circle`, `Square`, `Triangle`) implements its own `draw()` method.
- `drawShapes()` just calls `draw()` on each shape — no `if` statements needed.

**The benefit:**
- Adding a new shape (e.g., `Triangle`) means only creating a new class.
- No changes to old code → fewer bugs, easier to maintain.
- Code is cleaner and more flexible.

---

## Key Takeaways
1. If you see a big `if`/`switch` checking types, you might be violating OCP.  
2. Use abstraction so new functionality is added by writing new code, not modifying old code.  
3. Following OCP helps keep your code safe, clean, and easy to extend.

---
