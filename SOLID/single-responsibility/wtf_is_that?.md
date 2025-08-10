# Single Responsibility Principle (SRP)

> **One class = One responsibility**  
> A class should have **only one reason to change**.

---

## What is SRP?
The **Single Responsibility Principle** is the first principle of **SOLID**.  
It means that **each class should focus on doing one thing** and doing it well.  

If a class has more than one responsibility, changes in one area might unintentionally affect the others, making the code harder to maintain and more prone to bugs.

---

## Why is it important?
- **Easier maintenance** → You know exactly where to make changes.
- **Better readability** → Each class has a clear and simple purpose.
- **Fewer bugs** → Changes in one area won’t break unrelated features.
- **Improved reusability** → Classes can be reused without carrying unnecessary logic.

---

## Bad Example ( Violating SRP )
See [`bad_example.cpp`](./bad_example.cpp)

**What happens in this example:**
- The `Invoice` class **stores data**, **prints invoices**, and **saves them to a file**.
- If the printing format changes, you have to modify this class.
- If the file-saving method changes, you also have to modify this same class.
- This creates **multiple reasons for the class to change**, which violates SRP.
---

## Good Example ( Following SRP )
See [`good_example.cpp`](./good_example.cpp)

**What happens in this example:**
- The `Invoice` class **only stores and provides data**.
- A separate `InvoicePrinter` class handles printing.
- Another `InvoiceFileSaver` class handles saving invoices to files.
- Now, each class has **only one reason to change**.

**Why this is better:**
- If you change the printing format, you only modify `InvoicePrinter`.
- If you change the file-saving method, you only modify `InvoiceFileSaver`.
- The `Invoice` data class remains unaffected by these changes.
---

## Key Takeaways
1. **One class = One job**  
2. If a class changes for more than one reason → split it.  
3. SRP reduces **coupling** and increases **cohesion**.  
4. Makes your code **future-proof**.

---

