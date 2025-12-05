# 3D Lorenz Attractor Visualization

This project visualizes the Lorenz attractor in 3D using **C++** and **Raylib**.  
It draws a trail of points in space with a smoothly orbiting camera for a nice visual effect.

---

## Requirements

- [Raylib](https://www.raylib.com/) installed
- C++ compiler (tested with **g++ via MSYS2** on Windows)

---

## How to Compile

From your terminal or PowerShell, run:

```bash
g++ main.cpp -I"path/to/raylib/include" -L"path/to/raylib/lib" -lraylib -lopengl32 -lgdi32 -lwinmm -o app.exe
