# Design Patterns & SOLID Principles Learning Repository

## Overview

Welcome to my **Design Patterns & SOLID Principles Learning Repository**  
This repository serves as a structured documentation of the design patterns and SOLID principles I have learned and implemented, complete with explanations and practical C++ examples.

It covers **SOLID principles** and popular **design patterns** with detailed explanations and C++ code examples, illustrating both good and bad practices.

---

## How to Use This Repo

### 1. Start with the `SOLID` Folder

The `SOLID` folder contains the core principles of good software design:

- For **each principle**, you’ll find:
  - A markdown file named `wtf_is_that?.md` (e.g., `Single_Responsibility/wtf_is_that?.md`) with **short notes and a brief explanation** of the principle.
  - Two C++ files:
    - `bad_example.cpp` : the wrong way
    - `good_example.cpp` : the correct way (so your future self doesn’t hate you).

**How to study:**

1. Read the `wtf_is_that?.md` to get the theory.
2. Look at `bad_example.cpp` to see the typical rookie mistakes.
3. Check `good_example.cpp` to learn how to apply the principle properly.
4. Compile and run the code to see the difference. (Instructions below)

---

### 2. Move on to the `design_patterns` Folder

This folder covers **behavioral**, **structural**, and **creational** design patterns:

- An explanation file: `explain_to_me.md`  
  This file contains:

  - Why the pattern exists.
  - When you should (and shouldn’t) use it.
  - A step-by-step walkthrough of the example code.

- Two `.cpp` files for each pattern:
  - `without_example.cpp` : shows the "bad" naive approach.
  - `with_example.cpp` : shows the proper pattern applied.

**How to study:**

1. Read the **"what we are building"** section in `explain_to_me.md`.
2. Compare `without_example.cpp` with the "without" explanation to understand the baseline.
3. Study `with_example.cpp` with the "with" explanation to see how the pattern improves the design.
4. Run both versions and notice how much nicer the "with" version is. (Unless you enjoy debugging pain.)

---

## How to Compile & Run the Code

Before you run anything:

- Make sure you have **g++ compiler** installed.  
  On Windows: "fuck windows"
  - Install **MinGW** or **MSYS2** and add it to PATH.
  - Open a terminal (cmd or PowerShell) and type:
    ```sh
    g++ --version
    ```
    If it prints a version, you’re good to go. If not, go download g++
- On Linux/Mac:  
  Usually g++ comes pre-installed. Check with:
  ```sh
  g++ --version
  ```

**To run a `.cpp` file:**

1. Open your terminal.
2. Navigate to the folder containing the `.cpp` file:
   ```sh
   cd path/to/folder
   ```
3. Compile the file:
   ```sh
   g++ with_example.cpp -o a.exe
   ```
4. Run the compiled program:
   ```sh
   ./a.exe
   ```
   > بس executable اهم حاجة يبقى linux و windows ممكن تشغلها بـ `a.exe` عادي.

---

## Final Note

This repository represents my structured approach to studying and documenting software design principles and patterns.  
Each concept is accompanied by clear explanations and practical C++ examples to bridge the gap between theory and real-world implementation.

My objective is to create a resource that is both educational and reusable, for myself and for others who wish to strengthen their understanding of maintainable, scalable, and well-structured software design.

---

Good luck all !  
Ahmed Hesham Elsherbeeny
