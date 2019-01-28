/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: std::any exercise
 */ 

#include <cstdlib>
#include <string>
#include <any>
#include <map>
#include <iostream>
#include <cassert>


int main(){
  std::any a_double {5e-3};
  std::any other_double {-1e-1};
  std::any fourth_french {L"Quatrième"};
  std::any fourth {"fourth"};
  std::any nothing; 

  std::multimap<std::string, std::any> mm {
    {"first key", "1st value"},
    {"second key", 2},
    {"third key", a_double},
    {"third key", other_double},
    {"4th key", true},
    {"4th key", fourth_french},
    {"5th key", L"cinquième"},
    {"4th key", fourth},
    {"no key", nothing},
  };

  for (const auto &[key, val]: mm){
    std::cout << key << " = ";
    if (! val.has_value()) {
      std::cout << "No value";
    }else if (val.type() == typeid(int)){
      std::cout << std::any_cast<int>(val) << " ( int )"; 
    } else if (val.type() == typeid(double)){
      std::cout << std::any_cast<double>(val) << " ( double )"; 
    }else if (val.type() == typeid(bool)){
      std::cout << std::boolalpha << std::any_cast<bool>(val) << " ( bool )"; 
    }else if (val.type() == typeid(const wchar_t*)){
      std::wcout << std::any_cast<const wchar_t*>(val) << " ( const wchar_t* )"; 
    }else if (val.type() == typeid(const char*)){
      std::cout << std::any_cast<const char*>(val) << " ( const char* )"; 
    }else{
       try{
        std::cout << std::any_cast<std::string>(val); 
       } catch (std::bad_any_cast& e){
         std::cout << e.what();
       }
    }    

    std::cout << std::endl;
  }
  
  
  double* double_ptr = std::any_cast<double>(&a_double);
  std::cout << "Double #1 - from pointer: "<< *double_ptr << std::endl;
  
  a_double.reset();
  assert(!a_double.has_value());
  
  a_double = std::string {"An uninteresting C++ string"};

  //dangling pointer
  std::cout << "Double #2 - from pointer: "<< *double_ptr << std::endl;

  nothing = a_double;
  assert(nothing.type() == typeid(std::string));
  std::cout << "nothing value ='" <<std::any_cast<std::string>(nothing) 
            << "' ( std::string )" << std::endl; 

  nothing.reset();

  if (nothing.type() == typeid(std::string)){
    std::cout << "nothing value ='" << std::any_cast<std::string>(nothing) 
              << "' ( std::string )" << std::endl; 
  }
  nothing = nullptr;
  assert(nothing.type() == typeid(std::nullptr_t));

  return (EXIT_SUCCESS);
}