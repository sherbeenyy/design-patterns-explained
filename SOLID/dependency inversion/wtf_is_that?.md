# Dependency Inversion Principle (DIP)

> "High-level modules should not depend on low-level modules. Both should depend on abstractions."

---

## What is DIP?
The **Dependency Inversion Principle** is about decoupling high-level logic from low-level implementations.  
Instead of high-level modules depending directly on concrete classes, they should depend on abstract interfaces.  
This makes systems more flexible, easier to test, and easier to change.

---

## Example Scenario
We have a `Keyboard` and a `Computer`.  
If `Computer` directly creates and uses a specific `Keyboard` class, replacing it with another type of input device (e.g., a `TouchScreen`) requires modifying the `Computer` class.

---

## Bad Example – Violating DIP
See [`bad_example.cpp`](./bad_example.cpp)

**How it works:**
- `Computer` creates and uses a concrete `Keyboard` directly.
- If we want to use another input device, we have to change `Computer`’s code.

**The problem:**
- Tight coupling between `Computer` and `Keyboard`.
- Replacing dependencies requires editing the high-level class.

---

## Good Example – Following DIP
See [`good_example.cpp`](./good_example.cpp)

**How it works:**
- We create an abstract `IInputDevice` interface.
- `Keyboard` and `TouchScreen` both implement `IInputDevice`.
- `Computer` depends on `IInputDevice` instead of a specific class.
- We inject the dependency from the outside (constructor injection).

**The benefit:**
- `Computer` works with any `IInputDevice` implementation.
- No need to change `Computer` when adding new devices.

---

## Key Takeaways
1. Depend on abstractions, not concretions.  
2. Pass dependencies into classes (dependency injection).  
3. Improves flexibility and testability.

---