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