/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#include <iostream>

template <typename T1, typename T2, size_t I>
struct Cls {
  void cls_method(void); 
};

template <typename T1, typename T2, size_t I>
void Cls<T1, T2, I>::cls_method(void){
  std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << "\n";
}


// Partial specialization where T1 is the same as T2
template <typename T, size_t I>
struct Cls <T, T, I> {
  void cls_method(void); 
};


template <typename T, size_t I>
void Cls<T, T, I>::cls_method(void){
  std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << "\n";
}

// Partial specialization of Cls<T1, T2, I>
// where I is 7
template <typename T1, typename T2>
struct Cls<T1, T2, 7> {
  void cls_method(void); 
};

template <typename T1, typename T2>
void Cls<T1, T2, 7>::cls_method(void){
  std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << "\n";
}

// Partial specialization of Cls<T1, T2, I>
// where I is 7
template <typename T, size_t I>
struct Cls<int, T, I> {
  void cls_method(void); 
};

template <typename T, size_t I>
void Cls<int, T, I>::cls_method(void){
  std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << "\n";
}
