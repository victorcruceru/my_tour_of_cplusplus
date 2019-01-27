/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include <string>
#include <optional>
#include <iostream>
#include <map>
#include <cstdlib>

struct SmallKey {
  std::uint8_t k1 = 0;
  std::uint32_t k2 = 0;
};

bool operator < (const SmallKey& key1, const SmallKey& key2){
  return (key1.k1 < key2.k1) or (key1.k1 == key2.k1 and key1.k2 < key2.k2);
};


struct HugeKey {
  SmallKey sk = {0, 0};
  std::string hk[1024] = {};
};


bool operator<(const HugeKey& huge_k, const SmallKey& small_k) { 
  return (huge_k.sk < small_k); 
}
bool operator<(const SmallKey& small_k, const HugeKey& huge_k) { 
  return (small_k < huge_k.sk); 
}
bool operator<(const HugeKey& hk1, const HugeKey& hk2) { 
  return (hk1.sk < hk2.sk); 
}

static
std::optional <std::string> 
get_first_value(const std::map<HugeKey, std::string, std::less<>>& hm, 
                const SmallKey& sk){
  auto result = hm.find(sk);
  if (result != hm.end()) {
    return (result->second);
  } 
  return (std::nullopt);
}


int main(){
  std::map<HugeKey, std::string, std::less<>> h_map = {
    { {{100, 7}, {}}, "item99" },
    { {{100, 7}, {"abc", "lorem ipsum", "xyz"}}, "item1" },
    { {{253, 7000}, {"abc", "lorem ipsum", "xyz", "capital"}}, "item2" },
    { {{254, 99999}, {}}, "item3" },
  };

  for ( const auto& item: (SmallKey[]){ 
                                {1, 1}, 
                                {100, 7},
                                {9, 9},
                                {254, 99999} 
                              } ){
    std::cout << "Searching for combo key ["<< static_cast<uint32_t>(item.k1) 
              <<", "  << item.k2 << "]: ";
    if (auto x = get_first_value(h_map, item); x){
      std::cout << "First item found: " << *x << std::endl;
    }else{
      std::cout <<"No items found." << std::endl;
    }
  }
  return (EXIT_SUCCESS);
}

