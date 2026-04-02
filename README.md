# 🧮 Event-Driven Calculator using SDL2 (C++)

A fully functional **GUI calculator** built from scratch using **SDL2** and **SDL_ttf** in C++.
This project demonstrates event-driven programming, custom UI rendering, and real-time input handling without using any high-level GUI frameworks.

---

## 📌 Features

* 🖱️ Mouse-based interaction (click & hover)
* 🎨 Custom UI rendering using SDL2
* 🔢 Supports basic arithmetic operations:

  * Addition (+)
  * Subtraction (-)
  * Multiplication (*)
  * Division (/)
* 🧠 Real-time expression evaluation
* 🖋️ Text rendering using SDL_ttf
* ⚡ Smooth event-driven update loop

---

## 🧱 Tech Stack

* Language: **C++**
* Graphics/UI: **SDL2**
* Text Rendering: **SDL_ttf**

---

## 🏗️ Architecture

### 🔹 Components

* **Button System**

  * Stores position, value, state (hover/click)
* **Screen Buffer**

  * Handles input, operators, and result display
* **Event Loop**

  * Processes mouse movement and clicks
* **Rendering Pipeline**

  * Draws buttons, text, and screen dynamically

---

## ⚙️ How It Works

1. Buttons are initialized with positions and values
2. Mouse events detect:

   * Hover (for UI feedback)
   * Click (for input)
3. Input is stored in a buffer
4. Operator selection triggers:

   * Storage of first operand
5. On `=`:

   * Expression is evaluated
6. Result is displayed on screen

---

## ▶️ How to Run

### 🔧 Requirements

* SDL2
* SDL2_ttf
* C++ Compiler (GCC / MinGW / MSVC)

---

### 🛠️ Compile (Example)

```bash id="cmp1"
g++ main.cpp -lSDL2 -lSDL2_ttf -o calculator
```

---

### ▶️ Run

```bash id="run1"
./calculator
```

---

## 📁 Required Files

* `Arial.ttf` → Font file (must be in project directory)
* `data.txt` → Button labels (16 characters)

Example `data.txt`:

```
7 8 9 +
4 5 6 -
1 2 3 *
C 0 = /
```

---

## 🎮 Controls

* Click buttons using mouse
* Hover highlights buttons
* `C` → Clear screen
* `=` → Evaluate expression

---

## ⚠️ Limitations

* Only supports basic arithmetic (no advanced operations)
* Single-operation evaluation (no full expression parsing)
* Font path must be correct (`Arial.ttf`)
* No keyboard input support
* No error handling for invalid operations (e.g., divide by zero)

---

## 🚀 Future Improvements

* Add keyboard input support
* Implement full expression parser (BODMAS)
* Improve UI styling (animations, themes)
* Add scientific calculator features
* Handle edge cases (division by zero, large inputs)
* Make layout responsive

---

## 🧠 What I Learned

* Event-driven programming with SDL
* GUI rendering without frameworks
* Handling user input via mouse events
* Managing UI state (hover, click)
* Implementing calculator logic manually
* Text rendering with SDL_ttf

---

## 🎯 Conclusion

This project demonstrates how low-level libraries like SDL2 can be used to build interactive GUI applications from scratch.
It highlights core concepts of event handling, rendering, and state management in real-time systems.

---

## 📜 License

MIT License
