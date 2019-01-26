/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: Trying the replaced new/ deleted operators
 */

#include <cstdlib>
#include <string>
#include "track_new_delete.hpp"

// Dummy class used to check replaced new/ delete on a real class instance 
struct Dummy {
  uint32_t d1 = 0;
  uint64_t d2 = 0;
  Dummy(void){
    std::cout << "INFO: Dummy Constructor invoked" << std::endl;
  }
  ~Dummy(void){
    std::cout << "INFO Dummy Destructor invoked" << std::endl;
  } 

};
int main(){
  AllocHelper::set_tracing(true);
  char* x1 = ::new char;
  double* x2 = ::new double;
  std::uint64_t* x3 = ::new std::uint64_t[10];
  Dummy* d = new Dummy;
  Dummy* d_array = new Dummy[2];

  std::cout << "::new counter = " << AllocHelper::get_new_count() 
            << ", ::delete counter = " << AllocHelper::get_delete_count() 
            << ", total bytes allocated = " << AllocHelper::get_total_bytes() 
            << std::endl;
  
  AllocHelper::dump_used();

  ::delete x1;
  ::delete x2;
  ::delete [] x3;
  //::delete d;  commented to generate a "leak"
  ::delete [] d_array;

  std::cout << "::new counter = " << AllocHelper::get_new_count() 
            << ", ::delete counter = " << AllocHelper::get_delete_count() 
            << ", total bytes allocated = " << AllocHelper::get_total_bytes() 
            << std::endl;
  std::cout << "Number of *leaks* = " << AllocHelper::get_leaks_count() 
            << std::endl;
  AllocHelper::dump_used();
  return (EXIT_SUCCESS);
}