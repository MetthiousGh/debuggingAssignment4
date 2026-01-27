[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/CwXN8Ksa)
# Assignment 4: Debugging with GDB and AddressSanitizer (ASan)

This repository contains **intentionally buggy C++ code** for practicing
debugging using **GDB** and **AddressSanitizer (ASan)**.

You will diagnose, explain, and fix bugs using professional debugging tools
inside the **VS Code + Docker dev container** environment.

---

## Files in This Repository

- `debug_starter.cpp`  
  Starter C++ program with intentional bugs (DO NOT rewrite from scratch).

- `input_small.txt`  
  Small input file for basic testing.

- `input_trigger.txt`  
  Input file designed to trigger memory bugs.

- `debug_report.md`  
  Template for your debugging report (you must complete this).

---

## Build and Run (Debug Build)

Compile with warnings and debug symbols:

```bash
g++ -std=c++17 -O0 -g -Wall -Wextra -Wpedantic debug_starter.cpp -o debug_starter
```

Run with the provided inputs:

```bash
./debug_starter input_small.txt
./debug_starter input_trigger.txt
```

Observe incorrect output, crashes, or inconsistent behavior.

---

## Run with GDB

Start the debugger:

```bash
gdb ./debug_starter
```

Inside GDB, run the program:

```text
(gdb) run input_trigger.txt
```

You are expected to use at least:
- `break` (or `b`)
- `run`
- `next` or `step`
- `print`

Include relevant GDB output in `debug_report.md`.

---

## Build and Run with AddressSanitizer (ASan)

Recompile using ASan:

```bash
g++ -std=c++17 -O0 -g -Wall -Wextra -Wpedantic -fsanitize=address debug_starter.cpp -o debug_starter_asan
```

Run with the triggering input:

```bash
./debug_starter_asan input_trigger.txt
```

ASan should report **memory errors**.  
Copy relevant parts of the ASan report into `debug_report.md` and explain them.

---

## After Fixing Bugs

After fixing all bugs:

- The program should run correctly on both input files
- The ASan build should run **without any errors**
- Your fixes should be minimal and well-reasoned

---

## What to Submit

Your repository must contain:

- `debug_starter.cpp` (fixed version)
- `debug_report.md` (completed report)

Submit **only the GitHub repository URL** on Canvas.

---

## Academic Integrity

You may discuss ideas and debugging strategies with others, but:
- Your code changes must be your own
- Your report must be written in your own words
- Do not copy another student’s fixes or report

---

Good luck, and debug like a professional!

