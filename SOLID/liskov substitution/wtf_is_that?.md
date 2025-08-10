# Liskov Substitution Principle (LSP)

> "Objects of a superclass should be replaceable with objects of its subclasses without breaking the application."

---

## What is LSP?
The **Liskov Substitution Principle** states that if you have a base class and a subclass, you should be able to use the subclass anywhere the base class is expected without the program behaving incorrectly.  

If a subclass changes the expected behavior of the base class, it violates LSP.

---

## Example Scenario
We have a `Bird` class with a method `fly()`.  
We create two subclasses:  
- `Sparrow` → can fly.  
- `Penguin` → cannot fly.  

The problem is: If our code expects every `Bird` to fly, but `Penguin` breaks that assumption, we violate LSP.

---

## Bad Example – Violating LSP
See [`bad_example.cpp`](./bad_example.cpp)

**How it works:**
- `Bird` has a `fly()` method.  
- Both `Sparrow` and `Penguin` inherit from `Bird`.  
- The `Penguin` class overrides `fly()` to throw an error or print "I can't fly".

**The problem:**
- Anywhere in the code where we expect a `Bird` to fly will break when we pass in a `Penguin`.
- This makes the subclass incompatible with the base class’s expected behavior.

---

## Good Example – Following LSP
See [`good_example.cpp`](./good_example.cpp)

**How it works:**
- We separate flying birds and non-flying birds into different hierarchies:
  - `Bird` → common bird behavior (eat, lay eggs).
  - `FlyingBird` → adds `fly()` method.
  - `Sparrow` inherits from `FlyingBird`.
  - `Penguin` inherits from `Bird` but not from `FlyingBird`.

**The benefit:**
- No broken expectations only `FlyingBird` types are expected to fly.
- `Penguin` can still be used anywhere a `Bird` is expected without causing errors.

---

## Key Takeaways
1. Subclasses should honor the contracts of their base classes.  
2. Avoid creating subclasses that remove or break expected behaviors.  
3. Redesign hierarchies to group similar behaviors and keep them consistent.

---
