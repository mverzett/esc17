---
title: Short introduction to Valgrind
layout: main
---

[Valgrind](http://valgrind.org/) is an instrumentation framework
for dynamic analysis tools. At this school we use the tools for checking
memory management bugs, but it includes many other tools such as for
finding threading bugs and analysing cache access patterns. This
exercise will introduce you to the basic mechanics of using Valgrind;
later exercises will go into more detail.

Build [`memerror.cc`]({{site.exercises_repo}}/hands-on/basic/memerror.cc):

    [studentNM@esc-XY ~]$ cd esc16/hands-on/basic
    [studentNM@esc-XY basic]$ g++ -g -o memerror memerror.cc

Run the test program under valgrind:

    [studentNM@esc-XY basic]$ valgrind ./memerror

Re-build the executable without using the `-g` option and check the
consequences in the valgrind output.

The compiler can sometimes warn us about problems in our code:

    [studentNM@esc-XY basic]$ g++ -g -Wall -Wextra -o memerror memerror.cc

Sanitizers can also help:

    [studentNM@esc-XY basic]$ g++ -fsanitize=address -g -Wall -Wextra -o memerror memerror.cc
    [studentNM@esc-XY basic]$ ./memerror
