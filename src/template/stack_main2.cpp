#include "stack_string_specialization.h"
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
/* 
 Inspied by an example from the book:
 C++ Templates 
 The Complete Guide 
 Second Edition 
 */

#include <iostream>
#include <utility>
#include <cstdlib>


int main(){


  Stack<std::string>  stack_of_strings;
  const char* strings[] = {"one", "two", "three", "four", "five"};
  for (const auto& s: strings){
    stack_of_strings.push(s);
  }

  std::cout << stack_of_strings.height() << "\n"; // prints 5

  // next does not compile, because there is no operator <<
  // for Stack<std::string>
#if 0
    std::cout << stack_of_strings << "\n"; 
#endif  

  Stack<std::pair<int,std::string>> stack_of_pairs;
  auto idx = 0;
  for (const auto& s: strings){
    stack_of_pairs.push(std::make_pair(idx, s));
    idx++;
  }
  
  std::cout << stack_of_pairs.height() << "\n"; // prints 5 as well
  
  // Next does not compile because std::pair
  // does not have a << operator
#if 0
  std::cout << stack_of_pairs << "\n";
#endif
  
  while(!stack_of_pairs.empty()){
    const auto& x = stack_of_pairs.top();
    std::cout << x.first << ", " << x.second << "\n";
    stack_of_pairs.pop();
  }
// prints: 
// 4, five
// 3, four
// 2, three
// 1, two
// 0, one

  return (EXIT_SUCCESS);
}
