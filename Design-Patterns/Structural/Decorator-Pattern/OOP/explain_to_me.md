/*
# Decorator Pattern

## Wrapping an object to add new features (like putting a gift in a box, then gift-wrapping the box)

## What Are We Building?

We're building the backend for our blog application. We have an API endpoint `/posts/{id}` that needs to return a JSON object for a blog post.

However, the JSON response must be dynamic and change based on the user's role:

* **A normal user** gets the basic post data (ID, title, content).
* **The post's author** gets the basic data **plus** view statistics.
* **An editor** gets the basic data **plus** moderation information.
* **A developer** gets all the above **plus** debugging metrics.

The tricky part?

A single user can have multiple roles (e.g., an editor who is also the author). We need to be able to generate a response that combines the features for **any combination of roles**, and we want to be able to **add new roles and data types in the future** without rewriting the entire system.

This is where the **Decorator Pattern** provides a flexible and scalable solution.

## Overview

The **Decorator Pattern** is a structural design pattern that lets you attach new behaviors to objects dynamically by placing these objects inside special "wrapper" objects that contain the behaviors.

In short:

> Instead of creating a massive inheritance tree with a separate class for every possible feature combination, you start with a base object and "wrap" it with layers of functionality at runtime.

## Why Not Just Use Inheritance?

The most intuitive approach is to create subclasses for each variation. This works for one or two options, but it quickly leads to a **"class explosion"**:

* You'd need `BlogPostResponse`, `AuthorResponse`, `EditorResponse`, `AuthorEditorResponse`, `DebuggerResponse`, `AuthorDebuggerResponse`, `EditorDebuggerResponse`, `AuthorEditorDebuggerResponse`...
* You end up with **8 classes for just 3 roles**. Add a fourth role, and you'd need **16 classes**. This is completely unscalable.
* This approach is **rigid**. All combinations must be known at compile-time.
* It violates the **Open/Closed Principle**. Adding a new "Subscriber" role requires you to create many new combination classes.

## Why The Decorator Pattern Is Better

With the Decorator Pattern:

* **Objects are composed dynamically**. You can mix and match wrappers at runtime to create any combination you need.
* **Code is decoupled**. The base object doesn't know about the decorators, and decorators can be used with any object that follows the same interface.
* **It follows the Single Responsibility Principle (SRP)**. Each decorator has one job: to add one specific piece of functionality.
* **It's easy to extend**. Need to add subscriber-only data? You create *one* new `SubscriberDataDecorator` class. Nothing else needs to change.

## Diagram

This diagram shows how a base `BlogPostResponse` object is wrapped first by the `AuthorStatsDecorator` and then by the `EditorModerationDecorator` to build up the final object.

## Understanding the Code

### 1. [bad_api_response.cpp](./bad_api_response.cpp) - Bad Example (Inheritance)

**Code explanation:**

* This file uses a separate, hard-coded class for each combination of user roles (e.g., `BlogPostAuthorResponse`, `BlogPostAuthorEditorResponse`).
* The `handleApiRequest()` function becomes a giant, complex `if/else if` block to figure out which specific class to create.
* Adding a new role would require creating many new classes and making this `if/else` block even more complicated.

**Why this is bad:**

1.  **Class Explosion**: The number of classes grows exponentially with each new feature.
2.  **Rigidity**: All combinations are fixed at compile time.
3.  **High Maintenance**: A simple change (like adding a field to the author data) might require you to update multiple classes (`BlogPostAuthorResponse`, `BlogPostAuthorEditorResponse`, etc.).
4.  **Violates OCP**: The system is not closed for modification. Adding a feature requires changing existing creation logic.

### 2. The Good Example (Decorator Approach from our chat)

**Code explanation:**

* We have a single concrete component: `BlogPostResponse`.
* We have small, reusable wrapper classes: `AuthorStatsDecorator`, `EditorModerationDecorator`, and `DebugProfilingDecorator`.
* Each decorator takes an `ApiResponse` object in its constructor and *wraps* it, adding its own data when `generate()` is called.
* The client code (`handleApiRequest`) is now super simple. It starts with a base response and conditionally stacks decorators on top of it:

    ```cpp
    // Client code is simple and dynamic:
    unique_ptr<ApiResponse> response = make_unique<BlogPostResponse>(101);
    
    if (isAuthor) {
        response = make_unique<AuthorStatsDecorator>(move(response));
    }
    if (isEditor) {
        response = make_unique<EditorModerationDecorator>(move(response));
    }
    ```

**Why this is good:**

1.  **Flexible & Dynamic**: We can create any combination of features at runtime.
2.  **Scalable**: Adding a new role requires adding only *one* new decorator class. The client logic barely changes.
3.  **Follows SRP & OCP**: Each decorator has a single responsibility, and the system is open for extension but closed for modification.
4.  **Clean and Robust**: The creation logic is simple, readable, and less prone to errors.

## Key Differences Summary

| Feature              | Without Decorator (Inheritance) | With Decorator Pattern     |
| -------------------- | ------------------------------- | -------------------------- |
| Flexibility        | Low (fixed at compile-time)   | High (dynamic at runtime)  |
| Scalability        | Poor (class explosion)        | Excellent                  |
| Adding a New Feature | Requires many new classes     | Requires *one* new class   |
| Guiding Principle    | Inheritance                     | Composition over Inheritance |
| Code Complexity      | High (in creation logic)      | Low (in small, focused classes) |

## Analogy

Think of ordering a sandwich at a deli.

* **Without Decorator (Inheritance):** The menu has a fixed list of every possible sandwich: "Ham & Cheese," "Turkey & Swiss," "Ham, Cheese & Lettuce," etc. If you want a combination that's not on the menu (like Turkey, Ham, and Provolone), you can't order it.
* **With Decorator:** You start with your base component (`Bread`). Then, you tell the sandwich maker to wrap it with `HamDecorator`, then wrap that with `CheeseDecorator`, and finally wrap that with `LettuceDecorator`. You can build your exact, custom sandwich dynamically by stacking "ingredient" wrappers.

*/
