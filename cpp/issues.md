---
title: Memory issues
layout: main
category: cpp
---

The goal of this exercise is to understand what are the main issues
when dealing with _owning_ raw pointers and how tools like `valgrind`
can help identify them.

Build and run, directly and through `valgrind`, the following small
programs in {{site.exercises_repo}}/hands-on/cpp:

* `non_owning_pointer.cpp`. Uncomment the lines containing calls to
  `free` or `delete` and see what the consequences are at run-time
* `array_too_small.cpp`
* `leak.cpp`. Comment the allocations and see what the consequences
  are at run-time
* `double_delete.cpp`
* `missed_delete.cpp`. Uncomment the lines about the `try`/`catch`
  block and position them in different places; see what the
  consequences are at run-time.

Try and fix the problems.

The commands to build and run the programs are:

    [studentNM@esc-XY ~]$ cd esc17/hands-on/cpp
    [studentNM@esc-XY cpp]$ g++ -o non_owning_pointer non_owning_pointer.cpp
    [studentNM@esc-XY cpp]$ ./non_owning_pointer
    [studentNM@esc-XY cpp]$ valgrind ./non_owning_pointer

Similarly for the other programs.
