#include <iostream>
#include <cstdlib>
#include <string>
#include <type_traits>
/* check a template parameter value */
template <typename T, size_t L>
struct Record { // struct is just a class with all members public
  static_assert(L >= 1, "Length must be a scalar >= 1");
  T vector[L];
};

int main(){
  Record<std::string, 0> failed_rec; // This fails at compile time
  Record<int, 10> ok_rec;            // This is OK.
  // Next two might fail or not at compile time depending on your machine
  static_assert(sizeof(int) == 4, "int type must be of size 4");
  static_assert(sizeof(int* ) == 8, "int* pointer type must be of size 8");

  return (EXIT_SUCCESS);
}