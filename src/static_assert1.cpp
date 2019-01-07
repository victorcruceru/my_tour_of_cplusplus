/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: Trying static_assert (compile time check) in various
 * scenarios. These examples cover C++ type traits like std::is_copy_assignable
 * which are available at compile time as well.
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <type_traits>

// A is not copy assignable, because = operator is private
struct A { 
  int x;
private:
  A& operator= (const A& other){
    this->x = other.x;
    return (*this);
  }
};

// AA is copy assignable - it has a defaut = operator 
struct AA { 
  int x;
};

// B is not copy assignable, = operator is deleted.
struct B {
  B& operator= (const B& ) = delete;
};


int main(){
  // next will fail at *compile* time
  /*
  static_assert( std::is_copy_assignable<A>::value, 
                 "A must be copy assignable");
  */
  
  std::cout << "is A copy assignable ?: " << std::boolalpha << 
            std::is_copy_assignable<A>::value << std::endl;

  // next will pass at *compile* time
  static_assert( std::is_copy_assignable<AA>::value, 
                 "AA must be copy assignable");

  std::cout << "is AA copy assignable ?: " << std::boolalpha <<
            std::is_copy_assignable<AA>::value << std::endl;

  // failure at *compile* time as well
  /*
  static_assert( std::is_copy_assignable<B>::value, 
                 "B must be copy assignable");
  */
  std::cout << "is B copy assignable ?: " << std::boolalpha << 
            std::is_copy_assignable<B>::value << std::endl;

  return(EXIT_SUCCESS);
}