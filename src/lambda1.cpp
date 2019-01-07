/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: Basic attempts to use lambda functions.
 * The most interesting item is the recursive ( impractical! ) Fibonacci 
 * function.
 */
 
#include <cstdlib>
#include <iostream>
#include <functional>

int main(){
  // capture nothing
  auto is_positive = [] (int n) { 
    return (n >= 0);
  };
  std::cout << std::boolalpha << is_positive(7) << std::endl;

  // capture all local names by values 
  auto zero = 0;
  auto is_positive2 = [=] (int n) { 
    return (n >= zero);
  };
  std::cout << std::boolalpha << is_positive2(-2) << std::endl;
  
  // capture only zero name by value
  auto is_positive3 = [zero] (int n) { 
    return (n >= zero);
  };
  std::cout << std::boolalpha << is_positive3(-2) << std::endl;

  // capture only zero name by reference
  auto is_positive4 = [&zero] (int n) { 
    return (n >= zero);
  };
  std::cout << std::boolalpha << is_positive4(-0) << std::endl;

  // recursive Fibonacci lambda function
  std::function <uint64_t(uint64_t)> fib = [&fib] (uint64_t n) { 
    return (n == 0 ? 0 : ( n == 1 ? 1 : fib(n - 1) + fib(n - 2)));
  };

  std::cout<< fib(17) <<std::endl;

  return(EXIT_SUCCESS);
}