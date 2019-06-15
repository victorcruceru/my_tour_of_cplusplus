/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
/* 
 Inspied by an example from the book:
 C++ Templates 
 The Complete Guide 
 Second Edition 
 */

#include <iostream>
#include <cstdlib>
#include "stack_1.h"

int main(){
  Stack<double>       stack_of_doubles;
  Stack<std::string>  stack_of_strings;

  stack_of_doubles.push(7.7777);
  stack_of_doubles.push(-7.07);

  std::cout << "Stack of doubles:\n";

  while(!stack_of_doubles.empty()){
    stack_of_strings.push(std::to_string(stack_of_doubles.top()));
    std::cout<< stack_of_doubles.top() << '\n';
    stack_of_doubles.pop();
  }
  
  
  std::cout << "Height of the Stack of strings = " << stack_of_strings.height() 
            << '\n'; 
  
  std::cout << "\nStack of strings:\n";
  while(!stack_of_strings.empty()){
    std::cout<< stack_of_strings.top() << '\n';
    stack_of_strings.pop();
  }


  Stack<Stack<int>> intStackStack;
  std::cout << "\nStack of Stacks of ints:\n";
  for (auto i: {0,1,2,3,4,5}){
    Stack<int> si;
    for (auto j = 0; j < i+1; j++ ){
      si.push(j);
    }
    intStackStack.push(si);
  }

  
  while(!intStackStack.empty()){
    std::cout<< intStackStack.top().height() << '\n';
    intStackStack.pop();
  }  

  

  return (EXIT_SUCCESS);
}