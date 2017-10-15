---
title: Profiling using perf
layout: main
category: Architecture
---

``perf`` is a tool to profile a process using ``Hardware Performance Counters``. Each counter counts
Events in the CPU such as cycles, executed instructions, load from a given level of the memory caches,
branches...

{% highlight bash %}
perf list
{% endhighlight %}
lists the event that are predefined inside the tool.


the easiest way to use perf is to profile the whole application (say ./a.out) using a default set of events
{% highlight bash %}
perf stat -d ./a.out
{% endhighlight %}

One can choose a set of events and list them on the command line as in

[`doPerf`]({{site.exercises_repo}}/hands-on/architecture/doPerf)

For large applications more details can be obtained running ``perf record``  that will produce a file containing all sampled events and their location in the application.
``perf report`` can be used to display the detailed profile

a wrapper defining more user-friedly name for INTEL counters can be downloaded
{% highlight bash %}
cd;git clone https://github.com/andikleen/pmu-tools.git
{% endhighlight %}
in your home directory
and executed in place of `perf` as
 {% highlight bash %}
~/pmu-tools/ocperf.py
{% endhighlight %}
try
{% highlight bash %}
~/pmu-tools/ocperf.py list
{% endhighlight %}
to have a list of ALL available counters (and their meaning)

for an example see
[`doOCPerf`]({{site.exercises_repo}}/hands-on/architecture/doOCPerf)


Excercise 1
-----------

Exchange the order of the loops in the matrix multiplication

Use [matmul.cpp]({{site.exercises_repo}}/hands-on/architecture/matmul.cpp)

Compile
{% highlight bash %}
c++62 -O2 -fopt-info-vec -march=native
{% endhighlight %}
Measure. What's happening?
{% highlight bash %}
perf stat -d ./a.out
{% endhighlight %}

Recompile with<br>
-O3  (aggressive optimization and vectorization)<br>
-Ofast (allow reordering of math operation)<br>
Add -ffunroll-loops (force loop unrolling)

Change the product in a division


Excercise 2
-----------

Compare Horner Method with Estrin

Use [PolyTest.cpp]({{site.exercises_repo}}/hands-on/architecture/PolyTest.cpp)

compile, measure performance and eventually change compiler options as in Exercise 1

try also [pipeline.cpp]({{site.exercises_repo}}/hands-on/architecture/pipeline.cpp)

Excercise 3
-----------

Branch predictor in OO code

Use [Virtual.cpp]({{site.exercises_repo}}/hands-on/architecture/Virtual.cpp)

compile, measure performance and eventually change compiler options as in Exercise 1

Measure in various conditions
   * Remove “random_shuffle”
   * Increase number of Derived Classes
   * Try to change the order in the vector of pointers
   * Try to see if using an _ad-hoc_ type identification makes a difference
   * Compare with a SOA
   * Try “AnyOf”



Excercise 4
-----------

Different form of “Braching” in conditional code

Use [Branch.cpp]({{site.exercises_repo}}/hands-on/architecture/Branch.cpp)

compile, measure performance and eventually change compiler options as in Exercise 1

Measure in various conditions
   * Remove “random_shuffle”
   * change the way the conditions are expressed

