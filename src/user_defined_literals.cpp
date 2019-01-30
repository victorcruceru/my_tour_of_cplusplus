/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: User defined literals
 */ 

#include <cstdlib>
#include <string>
#include <any>
#include <map>
#include <iostream>
#include <cassert>

// Converts inches to cm
constexpr
long double operator""_in(long double inches){
   return (inches * 2.54);
}


int main(){
  // C++14 - std::string literals are hidden into the namespace 
  // std::string_literals
  using namespace std::string_literals;
  std::cout << "mumu"s << std::endl;
  std::wcout << L"Édith Piaf"s << std::endl;
  
  // built in binary numeric literals
  std::cout << 0b1111 + 0b00001010 << std::endl;

  //custom made literal
  std::cout << 20.1 << " in = " << 20.1_in << " cm." << std::endl;
  std::cout <<  " 9.9 in - 10.11 in  = " << 9.9_in  - 10.11_in << " cm." 
            << std::endl;
            
  return (EXIT_SUCCESS);
}