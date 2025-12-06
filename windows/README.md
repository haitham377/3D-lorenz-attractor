## Requirements

- [Raylib](https://www.raylib.com/) installed
- C++ compiler (tested with **g++ via MSYS2** on Windows)

---

## How to Compile

From your terminal or PowerShell, run:

```bash
g++ main.cpp -I"path/to/raylib/include" -L"path/to/raylib/lib" -lraylib -lopengl32 -lgdi32 -lwinmm -o app.exe
