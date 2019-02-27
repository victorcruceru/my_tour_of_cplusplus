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

#pragma once
#include <memory>


class RandomGenerator{
  public:
    RandomGenerator();
    virtual ~RandomGenerator();

    RandomGenerator(const RandomGenerator&) = delete;
    RandomGenerator& operator=(const RandomGenerator&) = delete;
    
    unsigned int get_random_integer(void);
  private:
    class RGImpl;
    std::unique_ptr<RGImpl> rg_impl_p; /* pointer to implemenation 
      defined elsewhere to avoid rebuilding the files including this header*/
};