#include <iostream>
#include <cstdlib>
#include <string>
#include <tuple>


std::tuple<std::string, size_t> ShiftTuple(const std::tuple<int, std::string, 
                                           size_t>& tu) {
  return std::make_tuple(std::get<1>(tu), std::get<2>(tu));                                             

}

std::tuple<std::string, size_t> ShiftTuple2(const std::tuple<int, std::string, 
                                           size_t>& tu) {
  return std::tuple(std::get<1>(tu), std::get<2>(tu)); // requires C++ 17  
  // for older C++ versions we nedd to specify  template args because 
  // argument deduction for constructors does not work
  //return std::tuple<std::string, size_t>(std::get<1>(tu), std::get<2>(tu));                                        

}

int main(){
  std::string s;
  std::tie(s, std::ignore) = ShiftTuple({1, "tuple#1", 64});
  std::cout << s << std::endl;

  std::tie(s, std::ignore) = ShiftTuple({1, "tuple#2", 128});
  std::cout << s << std::endl;

  return (EXIT_SUCCESS);
}