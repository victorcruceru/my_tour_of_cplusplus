/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: compile time "if constexpr"
 * Inspired 
 */
#include <type_traits>
#include <iostream>

template <typename T>
std::string convert_to_string(const T& t){
  if constexpr (std::is_arithmetic<T>::value) {
    return (std::to_string(t));
  } else if constexpr (std::is_same_v<T, std::string>){
    return (t);
  } else {
    return (std::string(t));
  }

}

int main(){
  std::cout << convert_to_string(-3.7) << std::endl;
  std::cout << convert_to_string(1107) << std::endl;
  std::cout << convert_to_string("A string literal") << std::endl;
  std::cout << convert_to_string(false) << std::endl;
  std::cout << convert_to_string('c') << std::endl;
  std::cout << convert_to_string(std::string("c")) << std::endl;
  enum class En {} e;
  // Next two will fail to instantiate the template properly...
  //std::cout << convert_to_string(e) << std::endl;
  //std::cout << convert_to_string(L"A string literal") << std::endl;
}