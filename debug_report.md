# Debug Report

**Author:** Samuel G. Berning
**Date:** 2026-01-28
**Project:** C++ Debugging Assignment 4

---

## 1. Compilation

Compiled the program with debugger

```bash
g++ -std=c++17 -O0 -g -Wall -Wextra -Wpedantic debug_starter.cpp -o debug_starter
[ debug_starter input_small.txt ] 
N=5
Mean=30
Max=-2113833498 // garbage value ( 50 )
Count(>50)=0
[ debug_starter input_trigger.txt ] 
N=8
Mean=4 // int division ( 4.5 )
Max=1213066870 // garbage value ( 8 )
Count(>50)=0
```
## 2. Compile program with GDB

```(gdb)
breakpoints:
	Breakpoint 1 at 0x2659: line 16. (mean_BUG)
	Breakpoint 2 at 0x27cb: line 32. (maxPtr_BUG)
	Breakpoint 3 at 0x2761: line 24. (countAbove_BUG)

transcripts:
	Breakpoint 1, mean_BUG(&v) {...}
		print v
		$1 = std::vector len 8, cap 8 = {1, 2, 3, 4, 5, 6, 7, 8}
		17	long long sum = 0; // sum is int initialized
		18	for (int x : v) sum += x; // sum is still int
		19	return (v.empty() ? 0.0 : (sum / v.size())); // returnValue is int if !v.empty()

	Breakpoint 2, maxPtr_BUG(&v) {...}
		print v
		%5 = std::vector len 8, cap 8 = {1, 2, 3, 4, 5, 6, 7, 8}
		print p
		%6 = (int *) 0x5c52a4e8cca0
		next
		35	delete p;
		$7 = (int *) 0x5c52ddc9df2b0 // dangling pointer
		next
		36	return p;
		print *p;
		%8 = 431217951 // garbage value
	
	Breakpoint 3, countAbove_BUG() {...}
		print v
		%9 = std::vector len 8, cap 8 = {1, 2, 3, 4, 5, 6, 7, 8}
		...
		for (size_t i = 0; i <= v.size(); i++) { }
			if (v[i] > threshold) cnt++;
		print i
		%10 = 8
		next
		for (size_t i = 0; i <= v.size(); i++) { }
		// out of range
		next
		return cnt;
```
## 3. Compile program with ASan

```(bash)
g++ -std=c++17 -O0 -g -Wall -Wextra -Wpedantic -fsanitize=address debug_starter.cpp -o debug_starter_asan
./debug_starter_asan input_trigger.txt

	#0 0x627edb6f3463 in main /workspaces/assignment4-debugging-MetthiousGh/debug_starter.cpp:51
	//51	if (pMax) std::cout << "Max=" << *pMax << "\n"; this statment is where the error occured.
	#0 0x799fe89935e8 in operator delete(void*, unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:164
	// The error was detected by the asan delete function prior to the statement in debug_starter.cpp line 51
	#1 0x627edb6f2db1 in maxPtr_BUG(std::vector<int, std::allocator<int> > const&) /workspaces/assignment4-debugging-MetthiousGh/debug_starter.cpp:34
	//34	int* p = new int(*std::max_element(v.begin(), v.end())); error with int pointer in function maxPtr_BUG() in debug_starter.cpp
	SUMMARY: AddressSanitizer: heap-use-after-free /workspaces/assignment4-debugging-MetthiousGh/debug_starter.cpp:51 in main
	Shadow bytes around the buggy address:
	0x501fffffff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	=>0x502000000000: fa fa fd fa fa fa fd fa fa fa fd fd fa fa[fd]fa
	//int, *pMax, left dangling in shadow memory leading to undenfined behavior.
```
## 4. Fixes to debug_starter.cpp

```fixes
	19:	- return (v.empty()) ? 0.0 : (sum / v.size());
	19:	+ return (v.empty()) ? 0.0 : (static_cast<double>(sum) / v.size());
	motive: "sum static_cast into double to enable float division"

	25: - for (size_t i = 0; i <= v.size(); i++) {
	25: + for (size_t i = 0; i < v.size(); i++) {
	motive: "i limited to less than v.size() to avoid OBOE"

	35: - delete p;
	51: + delete pMax;
	motive: "pointer deletion postponed to avoid UB"
```

## 5. Resolved outputs from standard and trigger inputs

```
	[Output of input_small.txt]
N=5
Mean=30
Max=50
Count(>50)=0

	[Output of input_trigger.txt]
N=8
Mean=4.5
Max=8
Count(>50)=0
```
