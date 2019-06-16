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

#include <vector>
#include <iostream>
#include <cassert>

template <typename T>
class Stack{
  private:
    // keep stack items in a vector
    // top of the stack is the back of the vector
    std::vector<T> _elements;

  public:
    void push(T const& e){
      _elements.push_back(e);
    }

    void pop(){               // remove the top element from stack
      assert(!_elements.empty());
      _elements.pop_back();
    }

    T const& top() const{      // return top element without removal
      assert(!_elements.empty());
      return _elements.back();   
    }

    bool empty() const {
      return _elements.empty();
    }

    std::size_t height() const;

    // friend (non-member) function declaration
    template<typename P>
    friend std::ostream& operator<< (std::ostream&, Stack<P> const&);    
};

// outside of the class member fuction definition
template <typename T>
std::size_t Stack<T>::height() const {
  return _elements.size();
} 


// friend (non-member) function definition
template<typename P>
std::ostream& operator<< (std::ostream& os, Stack<P> const& s){
  for(const auto& v: s._elements){
    os << v << ' ';
  }
  return (os);
}    