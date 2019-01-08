/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: Attempt to define ostream << insertion operator for any 
 * std::tuple.  Definition is template recursive, to print tuple of size N use 
 * a template for tuple size N-1, for N > 1. 
 * The recursion stops at the trivial tuple of size 1
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <tuple>

// Generic Print Helper for any tuple T of size N
template <typename T, std::size_t N>
struct TuplePrinterHelper {
    static_assert(N >= 1, "size must be at least 1");
    static void print(std::ostream& os, const T& tuple) 
    {
        TuplePrinterHelper<T, N - 1>::print(os, tuple);
        os << ", " << std::get<N - 1>(tuple);
    }
};

// Print Helper for any tuple of size 1
template <typename T>
struct TuplePrinterHelper<T, 1> {
    static void print(std::ostream& os, const T& tuple) {
        os << std::get<0>(tuple);
    }  
};


// definition for ostream insertion operator
template <typename... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& tuple){
    os << "{";
    TuplePrinterHelper<decltype(tuple), sizeof...(T)>::print(os, tuple);
    return os << "}";
}


int main (){
  std::tuple<uint16_t, uint32_t, uint64_t> t1 {1, 2, 3};
  std::cout << t1 << std::endl;

  std::pair<std::string, float> p2 {"tuple#2", 0.0001};
  auto t2 = std::tuple{p2}; 
  std::cout << t2 << std::endl;
 
  std::tuple<std::tuple<uint32_t, uint32_t>, std::string, std::string, double> 
                 t3 {{7, 100}, "tuple#3", "3#tuple", 0.1314};
  
  std::cerr << t3 << std::endl;
  return (EXIT_SUCCESS);
}