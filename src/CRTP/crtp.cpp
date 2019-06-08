#include <iostream>
#include <cstdlib>
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: CRTP  =  Curiously Recurring Template Pattern
 * This is inheritance at compile time:
 *  - Base is templatized on Derived, hence at compile time
 *    Base knows each derived type
 *  - The trick is done into the do_stuff method of the base class
 *    where this pointer is casted to Derived type
 */

template <typename Derived>
class Base {
public:
  /* This will be "overridden" at compile time*/  
  void pseudo_virtual_method(void){
    std::cout << "*Base* implementation" << std::endl;
  }
  void do_stuff(void){
    static_cast<Derived* >(this)->pseudo_virtual_method();
  }
};

class Derived_1: public Base<Derived_1>{
  public:
    void pseudo_virtual_method(void){
      std::cout << "*Derived_1* implementation" << std::endl;
    }    
};

class Derived_2: public Base<Derived_2>{
  public:
    void pseudo_virtual_method(void){
      std::cout << "*Derived_2* implementation" << std::endl;
    }    
};

class Derived_empty: public Base<Derived_empty>
{
 // pseudo_virtual_method is not "overridden" here - hence the Base version 
 // will be called.
};

int main(){
    Derived_1 d1;
    d1.do_stuff();

    Derived_2 d2;
    d2.do_stuff();

    Derived_empty de;
    de.do_stuff();

    return (EXIT_SUCCESS);    
}
