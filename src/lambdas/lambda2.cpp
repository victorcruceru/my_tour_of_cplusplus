/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: A lambda function used for std::sort
 */ 
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <iostream>

int main(){
  std::vector<std::pair<int, std::string>>  v {
    {1, "one"}, {2, "two"}, {7,"seven"}, {1, "uno"}, {2, "due"}
  };
  std::sort(v.begin(), v.end(), 
   [](const std::pair<int, std::string>& a, 
      const std::pair<int, std::string>& b){
     if (a.first == b.first) {
       return a.second <= b.second;
     } else {
       return a.first < b.first;
     }  
   });

  for (const auto& x: v){
    std::cout << "[" << x.first << ", " << x.second << "]" << std::endl;
  }
  return (EXIT_SUCCESS);
}