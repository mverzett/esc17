---
title: Use of function objects and algorithms
layout: main
category: cpp
---

The goal of this exercise is to get some confidence with the C++
entities that are _callable_: functions, functors and lambdas. You
will use them to customize the behaviour of some of the algorithms
provided by the C++ standard library.

The test program
[`algo.cpp`]({{site.exercises_repo}}/hands-on/cpp/algo.cpp)
generates and prints a vector of randomly-chosen integer numbers.

Build it and run it a few times to verify that it works as
expected:

    [studentNM@esc-XY ~]$ cd esc17/hands-on/cpp
    [studentNM@esc-XY basic]$ g++ -O3 -Wall -Wextra -o algo algo.cpp
    [studentNM@esc-XY basic]$ ./algo
    [studentNM@esc-XY basic]$ ./algo

Then extend the program in order to:

* sum all the elements of the vector
* multiply all the elements of the vector
* sort the vector in ascending and descending order
* move the even numbers at the beginning
* move the three central numbers at the beginning
* find the first element that satisfies a certain predicate
* erase from the vector the elements that satisfy that predicate

The source code contains some hints about what algorithms can be used
to implement the requested functionality. 
[cppreference.com](http://en.cppreference.com/w/) is an excellent source of
documentation for the algorithms (and C++ in general).
