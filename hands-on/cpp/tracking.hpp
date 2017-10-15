#include <iostream>

struct Tracking
{
  Tracking()
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }
  Tracking(Tracking const&)
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }
  Tracking& operator=(Tracking const&)
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return *this;
  }
  Tracking(Tracking&&)
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }
  Tracking& operator=(Tracking&&)
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return *this;
  }
  ~Tracking()
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }

  int k = 0;
};
