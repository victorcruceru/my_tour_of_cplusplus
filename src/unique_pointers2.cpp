/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: A PIMPL or d-pointer, compiler firewall pattern 
 * (https://cpppatterns.com/patterns/pimpl.html) using std::unique_ptr.
 */

#include "p_impl.hpp"
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <iostream>

int main(){
  RandomGenerator rg;
  for (int i = 1; i < 500; ++i){
    std::cout << "Random integer# " << i << " = " 
              << rg.get_random_integer() << std::endl;
  }

  return (EXIT_SUCCESS);
}