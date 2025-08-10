# Interface Segregation Principle (ISP)

> "Clients should not be forced to depend on interfaces they do not use."

---

## What is ISP?
The **Interface Segregation Principle** states that no class should be forced to implement methods it does not need.  
Large, “fat” interfaces should be split into smaller, more specific ones so that implementing classes only need to care about the methods relevant to them.

---

## Example Scenario
We have a `Worker` interface with methods:
- `work()`
- `eat()`
- `sleep()`

If we make **all workers** implement this interface, we might end up with classes that have to provide meaningless implementations for methods they don’t need (e.g., a robot worker that doesn’t eat or sleep).

---

## Bad Example – Violating ISP
See [`bad_example.cpp`](./bad_example.cpp)

**How it works:**
- We define a single `IWorker` interface with `work()`, `eat()`, and `sleep()` methods.
- `HumanWorker` implements all methods normally.
- `RobotWorker` is forced to implement `eat()` and `sleep()` even though they don’t apply.

**The problem:**
- Classes are forced to depend on methods they don't use.
- Unused methods can cause confusion, bugs, and unnecessary coupling.

---

## Good Example – Following ISP
See [`good_example.cpp`](./good_example.cpp)

**How it works:**
- We break the large interface into smaller, more specific ones:
  - `IWorkable` → `work()`
  - `IEatable` → `eat()`
  - `ISleepable` → `sleep()`
- `HumanWorker` implements all three.
- `RobotWorker` only implements `IWorkable`.

**The benefit:**
- Classes only depend on methods they actually need.
- Reduces unnecessary dependencies and keeps code cleaner.

---

## Key Takeaways
1. Avoid large, multi-purpose interfaces.  
2. Split interfaces into smaller, role-specific ones.  
3. Classes should only implement what they truly use.

---