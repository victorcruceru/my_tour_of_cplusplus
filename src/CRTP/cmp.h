/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#pragma once
#include <iostream>

template <typename Derived>
struct CmpBase {
  friend bool operator!=(const Derived& lhs, const Derived& rhs) {
    std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << "\n";
    return !(lhs == rhs);  // This will call operator== from Derived
  }  
  friend bool operator<=(const Derived& lhs, const Derived& rhs) {
    std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << "\n";
    return !(lhs > rhs);  // This will call operator> from Derived
  }   

  friend bool operator<(const Derived& lhs, const Derived& rhs) {
    std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << "\n";
    return (lhs <= rhs and lhs!= rhs); 
  }   
};


