# Adapter Pattern

## Sometimes you need a translator

## What Are We Building?

Imagine you’re building a backend for an **e-commerce store**. Your application needs to process payments, but you want to support multiple providers, and they all speak different "languages":

* **Stripe** has its own API: `charge(cardDetails, amountInCents)`
* **PayPal** has a completely different API: `sendPayment(email, amountDollars)`

The tricky part?

You don’t want your `processOrder()` function to **know or care** about the specific details of Stripe or PayPal.

You also want to be able to **easily add new payment providers** without rewriting your core business logic every single time.

This is where the **Adapter Pattern** shines.

## Overview

The **Adapter Pattern** is a structural design pattern that allows objects with **incompatible interfaces** to collaborate. It acts as a wrapper or translator between two otherwise incompatible objects.

In short:

> Instead of writing messy `if/else` blocks to handle every different service, you **create an "adapter" for each one**. The rest of your application then communicates with the adapters through a single, standard interface.

## Diagram

## Why Not Just Use `if/else` Directly?

Handling each case with `if/else` works for one or two providers, but it quickly leads to **serious headaches**:

* Business logic (`processOrder`) is **tightly coupled** to every external service.
* Adding a new payment provider means **modifying every part** of the code that processes payments.
* Risk of **duplicating logic**, like converting dollars to cents, all over the codebase.
* The code becomes a complex, unmaintainable mess as more providers are added.

## Why The Adapter Pattern Is Better

With the Adapter Pattern:

* **Client code is decoupled** from the messy details of external services.
* **Translation logic is centralized** inside each adapter.
* **All services are used consistently** through a single interface.
* Adding new providers **does not require changing client code**.
* Supports the **Open/Closed Principle** from SOLID.

## Understanding the Code

### 1. [without_example.cpp](https://www.google.com/search?q=./without_adapter_example.cpp) - Bad Example

**Code explanation:**

* `processOrder()` uses an `if/else` chain to figure out which payment API to call.
* It contains specific, ugly logic for both Stripe (like currency conversion) and PayPal.
* Every time we add a new payment provider, we have to come back and make this function even bigger.

**Why this is bad:**

1.  **Tight coupling**: `processOrder` knows all the dirty secrets of every payment API.
2.  **Code duplication**: The logic to convert dollars to cents is stuck right in the client code.
3.  **Low scalability**: Adding more providers turns this function into a monster.
4.  **Violates OCP**: The function is never closed for modification.

### 2. [with_example.cpp](https://www.google.com/search?q=./with_example.cpp) - Adapter Pattern Approach

**Code explanation:**

* `IPaymentGateway` is the clean, standard interface our app uses.
* `StripeAPI` & `PayPalAPI` are the incompatible third-party services.
* `StripeAdapter` & `PayPalAdapter` are the translators.
* Client code (`processOrder()`) just makes one simple, clean call:
    ```
    gateway->pay(totalAmount);
    ```

**Why this is good:**

1.  **Decoupled client**: `processOrder` has no idea Stripe or PayPal even exist.
2.  **Centralized translation**: The `StripeAdapter` handles the currency conversion. No one else needs to worry about it.
3.  **Easily extensible**: Add a `SquareAdapter` without touching a single line of existing code.
4.  **Clean and readable**: The client code is simple and focuses on its job.
5.  **Supports OCP**: We can add new features without modifying old, working code.

## Key Differences Summary

| Feature                 | Without Adapter Pattern      | With Adapter Pattern                 |
| ----------------------- | ---------------------------- | ------------------------------------ |
| Client Code Logic       | Complex `if/else` chain      | Simple, direct call to one interface |
| Adding a New Provider   | Modify many existing files   | Add one new adapter class only       |
| Knowledge of Services   | Client knows every API       | Client knows only the target interface |
| Flexibility             | Low                          | High                                 |
| Follows OCP             | No                           | Yes                                  |

## Analogy

Think of it like a **travel power adapter**:

* **Without Adapter Pattern:** Your laptop has a US plug. You go to Europe and try to plug it into the wall. It doesn’t work. You'd have to rewire your laptop for every country you visit.
* **With Adapter Pattern:** You use a universal travel adapter. Your laptop always plugs into the same standard interface (the adapter), and the adapter handles the job of fitting into the wall socket.