/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: A PIMPL or d-pointer, compiler firewall pattern 
 * (https://cpppatterns.com/patterns/pimpl.html) using std::unique_ptr.
 */

#include "p_impl.hpp"
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#if 0
/*
A simple implementation
*/
class RandomGenerator::RGImpl{
  private:
    bool initialized_m {false};

  public:

    RGImpl(){
      init();
      std::cout << "DEBUG: RGImpl constructed" << std::endl; 
    }


    ~RGImpl(){
      if (initialized_m){
        deinit();
        std::cout << "DEBUG: Default RGImpl destoyed" << std::endl; 
      } 
    }

    RGImpl(RGImpl&& other){
      std::cout << "DEBUG: RGImpl move constructed" << std::endl; 
      other.deinit();
      init();
    }

    RGImpl& operator=(RGImpl&& other){
      std::cout << "DEBUG: RGImpl move operator" << std::endl; 
      if (&other != this){
        other.deinit();
        init();
      }
      return (*this);
    }

    void init(){
      std::srand(std::time(nullptr)); 
      initialized_m = true;
      std::cout << "DEBUG: Default RGImpl initialized" << std::endl; 
    }

    void deinit(){
      initialized_m = false;
      std::cout << "DEBUG: Default RGImpl de-initialized" << std::endl; 
    }
    
    unsigned int generate_random_intger(void){
      return (std::rand());
    }
};
#else
/*
A more elaborate implementation
*/
class RandomGenerator::RGImpl{
  private:
    std::random_device random_device_m;
    std::uniform_int_distribution<unsigned int> random_dist_m;
    bool initialized_m {false};

  public:
    RGImpl(){
      init();
      std::cout << "DEBUG: Uniform RGImpl constructed" << std::endl; 
    }


    ~RGImpl(){
      if (initialized_m){
        deinit();
        std::cout << "DEBUG: Uniform RGImpl destoyed" << std::endl; 
      } 
    }

    RGImpl(RGImpl&& other){
      std::cout << "DEBUG: RGImpl move constructed" << std::endl; 
      other.deinit();
      init();
    }

    RGImpl& operator=(RGImpl&& other){
      std::cout << "DEBUG: RGImpl move operator" << std::endl; 
      if (&other != this){
        other.deinit();
        init();
      }
      return (*this);
    }

    void init(){
      random_dist_m = std::uniform_int_distribution<unsigned int>(0, RAND_MAX);
      initialized_m = true;
      std::cout << "DEBUG: Uniform RGImpl initialized" << std::endl; 
    }

    void deinit(){
      initialized_m = false;
      std::cout << "DEBUG: Uniform RGImpl de-initialized" << std::endl; 
    }
    
    int generate_random_intger(void){
      return (random_dist_m(random_device_m));
    }
};
#endif


RandomGenerator::RandomGenerator(void):rg_impl_p{new RGImpl}{
  std::cout << "DEBUG: RandomGenerator constructed." << std::endl; 
}

RandomGenerator::~RandomGenerator(void){
  std::cout << "DEBUG: RandomGenerator destructed." << std::endl; 
}

unsigned int RandomGenerator::get_random_integer(void){
  return (rg_impl_p->generate_random_intger());
}

