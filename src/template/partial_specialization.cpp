/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#include "partial_specialization.h"
#include <string>
int main(){
  Cls<double, char, 7> double_char_7;
  // DEBUG: void Cls<T1, T2, 7>::cls_method() [with T1 = double; T2 = char]
  double_char_7.cls_method(); 
 
  // Next is ambigous, two partial specialization matches
#if 0  
  Cls<int, char, 7> cls_int_char_7;
  cls_int_char_7.cls_method();
#endif  

  Cls<int, char, 100> cls_int_char_100;
  // DEBUG: void Cls<int, T, I>::cls_method() [with T = char; long unsigned int I = 100]
  cls_int_char_100.cls_method();

  // Next is ambigous, two partial specialization matches
#if 0
  Cls<int, int, 777> cls_int_int_777;
  cls_int_int_777.cls_method();
#endif

  Cls<std::string, std::string, 777> cls_str_str_777;
  //DEBUG: void Cls<T, T, I>::cls_method() [with T = std::__cxx11::basic_string<char>; long unsigned int I = 777]
  cls_str_str_777.cls_method();


  return(EXIT_SUCCESS);
}