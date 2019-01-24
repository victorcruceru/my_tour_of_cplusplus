/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include <cstdlib>
#include <string>
#include <iostream>

// overloading global new operator
 void* operator new(std::size_t sz){
  std::printf("operator new size  %zu\n", sz);    
  return std::malloc(sz);
}

// overloading global new[] operator
void* operator new[](std::size_t sz){
  std::printf("operator new[] size  %zu\n", sz);
  return std::malloc(sz);
}

// overloading  global delete operator
void operator delete (void* ptr) noexcept {
  std::printf( "operator delete for addr %x\n", ptr);    
  return std::free(ptr);
}

void operator delete (void* ptr, std::size_t sz) noexcept {
  std::printf( "operator delete2 for addr %x\n", ptr);    
  return std::free(ptr);
}

// overloading  global delete operator
void operator delete[](void* ptr) noexcept{
  std::printf( "operator delete[] for addr. %x\n", ptr);    
  return std::free(ptr);
}

void operator delete[] (void* ptr, std::size_t sz) noexcept {
  std::printf( "operator delete2[] for addr %x\n", ptr);    
  return std::free(ptr);
}

int main(){
  char* x1 = new char;
  double* x2 = new double;
  std::uint64_t* x3 = new std::uint64_t[10];


  delete x1;
  delete x2;
  delete [] x3;


  return (EXIT_SUCCESS);
}