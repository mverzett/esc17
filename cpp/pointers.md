---
title: Smart pointers
layout: main
category: cpp
---

The goal of this exercise is to get some confidence with the smart
pointers provide by the C++ standard library: `unique_ptr` and
`shared_ptr`.

Open the test program
[`dir.cpp`]({{site.exercises_repo}}/hands-on/cpp/dir.cpp)
and complete the existing code to:

* create a smart pointer managing a DIR resource obtained with the
  `opendir()` function call
* associate a deleter to that smart pointer
* implement a function to read the names of the files in that
  directory
* check if the deleter is called at the right moment
* hide the creation of the smart pointer behind a factory function

You can experiment with both kinds of smart pointers and with the type
of the function arguments.

The commands to build and run the exercise are:

    [studentNM@esc-XY ~]$ cd esc16/hands-on/cpp
    [studentNM@esc-XY cpp]$ g++ -o dir dir.cpp
    [studentNM@esc-XY cpp]$ ./dir /tmp
