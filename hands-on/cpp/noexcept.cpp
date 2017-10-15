#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <cstring>

#ifndef NOEXCEPT
#define NOEXCEPT
#endif

class String {
  char* s_; // nullptr or null-terminated
 public:
  String() noexcept : s_(nullptr) {}
  String(char const* s) {
    size_t size = strlen(s) + 1;
    s_ = new char[size];
    memcpy(s_, s, size);
  }
  ~String() { delete [] s_; }
  String(String const& other) {
    size_t size = strlen(other.s_) + 1;
    s_ = new char[size];
    memcpy(s_, other.s_, size);
  }
  String(String&& tmp) NOEXCEPT
      : s_(tmp.s_) {
    tmp.s_ = nullptr;
  }
  size_t size() const noexcept {
    return s_ ? strlen(s_) : 0;
  }
};

String get_string()
{
  return String{"Lorem ipsum dolor sit amet, consectetur adipiscing elit"};
}

std::chrono::duration<float> test()
{
  auto s = get_string();
  std::vector<String> v(10000000, s);
  auto start = std::chrono::high_resolution_clock::now();
  v.push_back(s);
  return std::chrono::high_resolution_clock::now() - start;
}

int main()
{
  auto d = test();
  std::cout << d.count() << " s\n";
}
