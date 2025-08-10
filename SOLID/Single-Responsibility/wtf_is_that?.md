# Single Responsibility Principle (SRP)

> "A class should have only one reason to change."

---

## What is SRP?
The **Single Responsibility Principle** states that each class should focus on a single responsibility or job.  
If a class has more than one reason to change, it is doing too much and should be split into separate classes.

---

## Example Scenario
We want to create a simple system for invoices:  
- Store invoice details (customer name, amount).  
- Print the invoice.  
- Save the invoice to a file.

The question is: Should one class handle all of these tasks, or should we split responsibilities?

---

## Bad Example – Violating SRP
See [`bad_example.cpp`](./bad_example.cpp)

**How it works:**
- The `Invoice` class:
  - Stores invoice details.
  - Prints the invoice.
  - Saves the invoice to a file.

**The problem:**
- The class has multiple responsibilities:
  1. Managing invoice data.
  2. Printing invoices.
  3. Saving invoices to a file.
- If file storage changes (e.g., new format or database), we must modify the `Invoice` class even if invoice data handling hasn’t changed.
- If printing changes (e.g., new layout), we must also modify the `Invoice` class again.
- This makes the class harder to maintain and more prone to bugs.

---

## Good Example – Following SRP
See [`good_example.cpp`](./good_example.cpp)

**How it works:**
- `Invoice` stores only invoice data.
- `InvoicePrinter` is responsible for printing.
- `InvoiceFileSaver` is responsible for saving to a file.

**The benefit:**
- Each class has one clear responsibility.
- Changes to printing or saving do not affect invoice data handling.
- Code is easier to test, extend, and maintain.

---

## Key Takeaways
1. A class should only have one reason to change.  
2. Separate unrelated responsibilities into different classes or modules.  
3. SRP improves maintainability, reduces bugs, and makes code easier to test.

---
