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