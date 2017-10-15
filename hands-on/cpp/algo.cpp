#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>

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

  // alternative way to fill the vector (but less efficient, why?)
  // std::vector<int> v(SIZE);
  // std::generate_n(std::begin(v), SIZE, [&]() { return uniform_dist(e); });

  // sum all the elements of the vector
  // use std::accumulate

  // multiply all the elements of the vector
  // use std::accumulate

  // sort the vector in ascending order
  // use std::sort

  // sort the vector in descending order
  // use std::sort

  // move the even numbers at the beginning of the vector
  // use std::partition

  // move the three central elements to the beginning of the vector
  // use std::rotate

  // find the first element that is multiple of 3 or 7
  // use std::find_if

  // erase from the vector the multiples of 3 or 7
  // use std::remove_if followed by vector::erase

};
