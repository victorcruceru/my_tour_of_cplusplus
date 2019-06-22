/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#include "cmp.h"
#include <iostream>

class CmpDerived: public CmpBase<CmpDerived>{
  private:
    int v_;
  public:
    CmpDerived(int v = 0): v_{v}{

    }

    friend 
    bool operator==(const CmpDerived& lhs, const CmpDerived& rhs) {
      std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << "\n";
      return lhs.v_ == rhs.v_;
    }    

    friend 
    bool operator>(const CmpDerived& lhs, const CmpDerived& rhs) {
      std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << "\n";
      return lhs.v_ > rhs.v_;
    }     
};

int main(){
  CmpDerived d1{1}, d2{7};
  std::cout << std::boolalpha <<  (d1 == d2) << '\n';
  std::cout << std::boolalpha <<  (d1 != d2) << '\n';
  std::cout << std::boolalpha <<  (d1 <= d2) << '\n';
  std::cout << std::boolalpha <<  (d1 < d2) << '\n';
  return (EXIT_SUCCESS);
}