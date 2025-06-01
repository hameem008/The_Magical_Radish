# 🥕 The_Magical_Radish

**The_Magical_Radish** is a simple yet fun 2D game developed using the [`iGraphics.h`](https://github.com/IUT-ACM/iGraphics) library in C. In this game, a magical radish leads a determined donkey on a chase! The radish teleports to wherever you click, and the donkey dashes toward it, creating a playful and entertaining experience.

---

## 🎮 Gameplay

- You control the **magical radish** by clicking anywhere on the screen.
- The **donkey** will run toward the last clicked location.
- The game continues infinitely as you lead the donkey around the screen.
- there is a demo video of the gameplay

---

## 📷 Preview

<!-- You can include screenshots or GIFs here -->
*Coming soon!*

---

## ⚙️ How to Run

### Prerequisites
- A C compiler (e.g., GCC or Code::Blocks)
- The `iGraphics.h` library  
  [Download iGraphics](https://github.com/IUT-ACM/iGraphics)

### Compilation

1. Make sure you have `iGraphics.h` and its required dependencies properly placed.
2. Compile the game source code. If using **GCC**, a typical compile command may look like:

```bash
gcc main.cpp -o The_Magical_Radish -lglut -lGL -lGLU
