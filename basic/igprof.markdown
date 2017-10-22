---
title: Short introduction to IgProf
layout: main
---

[IgProf](<http://igprof.org>) is both a performance profiler and a
memory allocation profiler. This exercise will introduce you to the
basic mechanics of using IgProf.

Basic profiling environment
---------------------------

To make sure you have technically everything set up right, let's first create a
profile for a simple run of the `ls` command.

    [studentNM@esc-XY ~]$ igprof -pp -z -o ls-test.gz -- ls -laFR /usr/lib >/dev/null
    [studentNM@esc-XY ~]$ igprof-analyse --sqlite -d -v -g ls-test.gz |
    > sqlite3 ~/public_html/cgi-bin/data/ls-test.sql3

View the report at `http://esc-gw.pd.infn.it:61100/~studentNM/cgi-bin/igprof-navigator.py/ls-test/`

Basic performance profile
-------------------------

This exercise will run the program from the previous exercise on `cputicks`
using igprof statistical performance profiler.

Run the test program under igprof performance profiler:

    [studentNM@esc-XY ~]$ cd esc17/hands-on/basic
    [studentNM@esc-XY basic]$ igprof -pp -z -o cputicks.gz ./cputicks 1000000

Generate a simple text profile output of run time:

    [studentNM@esc-XY basic]$ igprof-analyse -d -v -g cputicks.gz > cputicks.res
    [studentNM@esc-XY basic]$ less -SX cputicks.res
	Counter: PERF_TICKS

	----------------------------------------------------------------------
	Flat profile (cumulative >= 1%)

	% total      Total  Function
	  100.0       0.11  <spontaneous> [1]
	  100.0       0.11  _start [2]
	  100.0       0.11  __libc_start_main [3]
	  100.0       0.11  main [4]
	  100.0       0.11  pi(int) [5]
	...

Generate the same profile in a web-viewable database; then view the
profile at `http://esc-gw.pd.infn.it:61100/~studentNM/cgi-bin/igprof-navigator.py/cputicks/`:

    [studentNM@esc-XY basic]$ rm -f ~/public_html/cgi-bin/data/cputicks.sql3
    [studentNM@esc-XY basic]$ igprof-analyse --sqlite -d -v -g cputicks.gz |
    > sqlite3 ~/public_html/cgi-bin/data/cputicks.sql3
