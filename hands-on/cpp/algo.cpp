#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include <chrono>

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& c)
{
  os << "{ ";
  std::copy(
      std::begin(c),
      std::end(c),
      std::ostream_iterator<T>{os, " "}
  );
  os << '}';

  return os;
}

int main()
{
  // define a pseudo-random number generator engine and seed it using an actual
  // random device
  std::random_device rd;
  std::mt19937 eng{rd()};

  int const MAX_N = 100;
  std::uniform_int_distribution<int> uniform_dist{1, MAX_N};

  // fill a vector with SIZE random numbers
  int const SIZE = 10;
  std::vector<int> v;
  v.reserve(SIZE);
  std::generate_n(std::back_inserter(v), SIZE, [&]() { return uniform_dist(eng); });

  std::cout << v << '\n';

  int const TSIZE = 10;
  int const TLOOP = 500;
  auto const start = std::chrono::high_resolution_clock::now();
  for(int test=0; test<TLOOP; test++) {
    std::vector<int> vv;
    vv.reserve(TSIZE);
    std::generate_n(std::back_inserter(vv), TSIZE, [&]() { return uniform_dist(eng); });    
  }
  auto const stop = std::chrono::high_resolution_clock::now();

  auto const cstart = std::chrono::high_resolution_clock::now();
  for(int test=0; test<TLOOP; test++) {
    std::vector<int> vv(TSIZE);
    std::generate_n(std::begin(vv), TSIZE, [&]() { return uniform_dist(eng); });    
  }
  auto const cstop = std::chrono::high_resolution_clock::now();
  std::cout << "Creation with back inserter: " << (stop - start).count() << std::endl
	    << "Creation with copy: " << (cstop - cstart).count() << std::endl;

  // alternative way to fill the vector (but less efficient, why?)
  // std::vector<int> v(SIZE); TODO
  // std::generate_n(std::begin(v), SIZE, [&]() { return uniform_dist(e); });

  // sum all the elements of the vector
  std::cout << "Sum: " << std::accumulate(v.begin(), v.end(), 0) << std::endl;

  // multiply all the elements of the vector
  // use std::accumulate
  std::cout << "Product: " << std::accumulate(v.begin(), v.end(), 1LL, std::multiplies<int>()) << std::endl;

  // sort the vector in ascending order
  // use std::sort
  std::sort(v.begin(), v.end());
  std::cout << "Sorted: " << v << std::endl;

  // sort the vector in descending order
  // use std::sort
  std::sort(v.begin(), v.end(), std::greater<int>());
  std::cout << "Descending sorted: " << v << std::endl;

  // move the even numbers at the beginning of the vector
  // use std::partition
  std::partition(v.begin(), v.end(), [](int i){return (i % 2) == 0;});
  std::cout << "Even at the beginning: " << v << std::endl;
  
  // move the three central elements to the beginning of the vector
  // use std::rotate
  std::sort(v.begin(), v.end());
  std::cout << "Sorted: " << v << std::endl;
  std::rotate(v.begin(), v.begin() + v.size()/2, v.end());
  std::cout << "Rotated: " << v << std::endl;
  
  // find the first element that is multiple of 3 or 7
  // use std::find_if
  auto mult3mult7 = [](int i){return ((i % 3) == 0 || (i % 7) == 0);};
  auto found = std::find_if(v.begin(), v.end(), mult3mult7);
  if(found == v.end()) {
    std::cout << "Element not found" << std::endl;
  } else {
    std::cout << "Found element: " << *found << std::endl;
  }

  // erase from the vector the multiples of 3 or 7
  // use std::remove_if followed by vector::erase
  std::cout << "Size before: " << v.size() << std::endl;
  auto returned = std::remove_if(v.begin(), v.end(), mult3mult7);
  v.erase(returned, v.end());
  std::cout << "Size after: " << v.size() << std::endl;  
  std::cout << "Removed: " << v << std::endl;
};
