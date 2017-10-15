#include <memory>

char const* some_api();

int main()
{
  auto* p = some_api();

  // free(p);
  // delete p;
  // delete [] p;
}


#include <cstring>

char const* some_api() {
  return strstr("Hello, world!", "orl");
}
