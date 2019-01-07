/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: Trying static_assert (compile time check) in various
 * scenarios like template parameters and basic types.
 */
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
  //Record<std::string, 0> failed_rec; // This fails at compile time
  Record<int, 10> ok_rec;            // This is OK.
  // Next two might fail or not at compile time depending on your machine
  static_assert(sizeof(int) == 4, "int type must be of size 4");
  static_assert(sizeof(int* ) == 8, "int* pointer type must be of size 8");

  return (EXIT_SUCCESS);
}