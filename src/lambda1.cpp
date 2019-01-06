#include <cstdlib>
#include <iostream>
#include <functional>

int main(){
  // capture nothing
  auto is_positive = [] (int n) { 
    return (n >= 0);
  };
  std::cout<< std::boolalpha << is_positive(7) <<std::endl;

  // capture all local names by values 
  auto zero = 0;
  auto is_positive2 = [=] (int n) { 
    return (n >= zero);
  };
  std::cout<< std::boolalpha << is_positive2(-2) <<std::endl;
  
  // capture only zero name by value
  auto is_positive3 = [zero] (int n) { 
    return (n >= zero);
  };
  std::cout<< std::boolalpha << is_positive3(-2) <<std::endl;

  // capture only zero name by reference
  auto is_positive4 = [&zero] (int n) { 
    return (n >= zero);
  };
  std::cout<< std::boolalpha << is_positive4(-0) <<std::endl;

  // recursive Fibonacci lambda function
  std::function <uint64_t(uint64_t)> fib = [&fib] (uint64_t n) { 
    return n < 2 ? 1 : fib(n - 1) + fib(n - 2);
  };

  std::cout<< fib(10) <<std::endl;

  return(EXIT_SUCCESS);
}