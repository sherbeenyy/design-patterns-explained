# 🔓 Open/Closed Principle (OCP)

> **"Software entities should be open for extension, but closed for modification."**

---

## What is OCP?
The **Open/Closed Principle** says that your classes, modules, and functions should be **extensible without changing their existing source code**.

If you want to add new functionality, you should **add new code**, not change old code that’s already working.

---

## Why it matters
- **Keeps old code safe** → You don't break what already works.
- **Easy to add new features** → Just add new classes or methods.
- **Encourages clean design** → Fewer `if`/`switch` blocks.

---

## Bad Example – Violating OCP
See [`bad_example.cpp`](./bad_example.cpp)

**What's wrong here:**
- There is a `drawShapes()` function that checks `ShapeType` using `if`/`else`.
- If we add a new shape like a `Triangle`, we **must modify** `drawShapes()` to handle it.
- This means changing tested, working code whenever we add something new.

**Why it’s bad:**
- Risk of introducing new bugs in old logic.
- The function grows bigger and harder to maintain.
- Violates the "closed for modification" part of OCP.

---

## Good Example – Following OCP
See [`good_example.cpp`](./good_example.cpp)

**What's better here:**
- We define a `Shape` interface (abstract class) with a `draw()` method.
- Each shape (`Circle`, `Square`, `Triangle`) **implements** its own `draw()` method.
- Adding a new shape means **adding a new class**, not touching old code.

**Why it’s good:**
- Existing code remains unchanged when adding new features.
- No big `if`/`else` checks — the code is simpler.
- The program is easier to extend and maintain.

---

## Key Takeaways
1. **Don't** change old, working code just to add new features.  
2. Use **abstraction** (interfaces / abstract classes) so new things can be added easily.  
3. Replace `if`/`switch` on types with **polymorphism**.

---

