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
#pragma once
#include "stack_1.h"
#include <deque>
#include <string>
#include <cassert>
#include <iostream>

// Stack<std::string> is a full specialization of Stack<T>
// For T = std::string this specialization is used
// For the rest of T's the generic version Stack<T> will be instantiated and 
// used
template <>
class Stack<std::string> {
  private:
    std::deque<std::string> _elements;

  public:
    void push(std::string const&);
    void pop(void);
    std::string const& top() const;
    std::size_t height() const{
      std::cout << "DEBUG: " << __func__ << "\n";
      return _elements.size();
    }
    bool empty() const {
      return _elements.empty();
    }
};

void Stack<std::string>::push(std::string const& e){
  std::cout <<"DEBUG: " << __func__ << "\n";
  _elements.push_back(e);
}


void Stack<std::string>::pop(void){
  std::cout << "DEBUG: " << __func__ << "\n";
  assert(!_elements.empty());
  _elements.pop_back();
}
// get the top element without removing it
std::string const& Stack<std::string>::top() const{
  std::cout << "DEBUG: " << __func__ << "\n";
  assert(!_elements.empty());
   return _elements.back();      // returns a copy of last element    
}