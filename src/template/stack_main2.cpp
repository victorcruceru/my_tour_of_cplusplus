/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#include "stack_2.h"
#include <iostream>
#include <string>

int main(){
  Stack<int,40> int40Stack;
  Stack<std::string,7> string7Stack;
  for (std:: size_t i = 0 ; i < 45 and int40Stack.push(i); i++){
  }
  std::cout << int40Stack << "\n";
  while (! int40Stack.empty()){
    int40Stack.pop();
  }
  std::cout << int40Stack << "\n";

  string7Stack.push("item0");
  string7Stack.push("item1");
  string7Stack.push("item2");

  std::cout << string7Stack  << "\n";

  while (! string7Stack.empty()){
    auto top_el = string7Stack.top();
    std::cout <<"Popping up: " << top_el.value_or("<empty stack>") << "\n";
    string7Stack.pop(); 
  }

  assert(string7Stack.empty());

  std::cout << "\n" << string7Stack.top().value_or("<empty stack>") << "\n";
  std::cout << string7Stack << "\n";
  return(EXIT_SUCCESS);
}