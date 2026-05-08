# Contact-List / Contact Management System

Academic group project for CSE333 (Spring 2026). Single-file C++17 console app using an AVL tree.

## Build & Run

```powershell
# Compile all cpp files in src/
g++ -std=c++17 src/main.cpp src/Avl.cpp -o src/contacts

# Run
.\src\contacts.exe
```

MSYS2/MinGW (`D:\msys2\ucrt64\bin\g++.exe`) is the dev toolchain for Windows.

## Structure

All source files are flat in `src/`:
- `Contact.h` — data struct (name, phone, email, address)
- `AvlTree.h` / `Avl.cpp` — AVL tree with rotations (LL, RR, LR, RL)
- `main.cpp` — menu loop entrypoint

No tests, no linter, no CI, no package manager.
