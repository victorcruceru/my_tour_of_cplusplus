/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: How to unpack a tuple
 */ 
#include <cstdlib>
#include <iostream>   // std::cout
#include <string> 
#include <tuple>
#include <ctime>
#include <chrono>
#include <cstdlib>

static
std::tuple<std::string, std::chrono::system_clock::time_point, int32_t> 
get_stock(const std::string& s_symbol){
  return std::make_tuple(s_symbol,  
                  std::chrono::system_clock::now() + std::chrono::hours(24),
                  std::rand()); 
  
}

int main(int argc, char** argv){
  std::srand(std::time(nullptr)); 
  for (int n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}){
    // unpacking the tuple returned by local function get_stock
    const auto [name, valid_time, price] = get_stock("AMZN" + 
                                                     std::to_string(n));
    std::cout<<name<<", "<< std::chrono::system_clock::to_time_t(valid_time) 
             << ", " << price << std::endl;
  }
  return(EXIT_SUCCESS);
}  

 
