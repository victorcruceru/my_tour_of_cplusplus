/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#include "track_new_delete.hpp"
#include <cstdlib>
#include <string>
int main(){
  AllocHelper::set_tracing(false);
  char* x1 = ::new char;
  double* x2 = ::new double;
  std::uint64_t* x3 = ::new std::uint64_t[10];

  std::cout << "::new counter = " << AllocHelper::get_new_count() 
            << ", ::delete counter = " << AllocHelper::get_delete_count() 
            << ", total bytes allocated = " << AllocHelper::get_total_bytes() 
            << std::endl;
  
  ::delete x1;
  ::delete x2;
  std::cout << "::new counter = " << AllocHelper::get_new_count() 
            << ", ::delete counter = " << AllocHelper::get_delete_count() 
            << ", total bytes allocated = " << AllocHelper::get_total_bytes() 
            << std::endl;

  return (EXIT_SUCCESS);
}