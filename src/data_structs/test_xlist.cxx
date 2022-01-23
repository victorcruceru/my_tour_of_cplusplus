/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#include "xlist.hxx"
#include <cstdlib>
#include <iostream>
#include <string>
int main() {
  X::List<int> intlist{};
  intlist.push_back(7);
  intlist.push_back(10);
  intlist.push_back(777);
  intlist.push_back(9);

  for (auto &r : intlist) {
    std::cout << r << '\n';
  }
  intlist.pop_back();

  std::cout << '\n';
  for (auto &r : intlist) {
    std::cout << r << '\n';
  }

  intlist.pop_front();

  std::cout << '\n';
  for (auto &r : intlist) {
    std::cout << r << '\n';
  }
  
  intlist.erase(intlist.begin(), intlist.end());

  std::cout << "After erase1 \n";
  for (auto &r : intlist) {
    std::cout << r << '\n';
  }

  intlist.erase(intlist.begin(), intlist.end());

  std::cout << "After erase2 \n";
  for (auto &r : intlist) {
    std::cout << r << '\n';
  }

  std::cout << "==== initilizer list==== \n";
  X::List<std::string> strlist{"seven", "ten", "seven hundred seventy seven", 
                               "nine"};
 
  for (auto &r : strlist) {
    std::cout << r << '\n';
  }

  strlist.pop_back();

  std::cout << '\n';
  for (auto &r : strlist) {
    std::cout << r << '\n';
  }

  strlist.pop_front();

  std::cout << '\n';
  for (auto &r : strlist) {
    std::cout << r << '\n';
  }
  
  strlist.erase(strlist.begin(), strlist.end());

  std::cout << "After erase1 \n";
  for (auto &r : strlist) {
    std::cout << r << '\n';
  }

  strlist.erase(strlist.begin(), strlist.end());

  std::cout << "After erase2 \n";
  for (auto &r : strlist) {
    std::cout << r << '\n';
  }
  for (auto &r : strlist) {
    std::cout << r << '\n';
  }
  
  return (EXIT_SUCCESS);
}