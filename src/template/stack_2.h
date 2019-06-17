/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#pragma once
#include <array>
#include <cassert>
#include <optional>

template <typename T, std::size_t Maxsize> 
class Stack {
  private:
    std::array<T, Maxsize> _elements; // elements kept in a std::array, 
                                      //top is on the right side 
    std::size_t _elements_count;      // current number of elements in the stack

  public:
    Stack();
    bool push(const T&);
    bool pop(void); // remoe the top element or return false
    std::optional<T> top() const; 

    bool empty(void) const {
      return (_elements_count == 0);
    }

    std::size_t size() const {
      return (_elements_count);
    }

    template<typename P, std::size_t M>
    friend std::ostream& operator<< (std::ostream&, Stack<P, M> const&);    

};

template<typename T, std::size_t Maxsize>
Stack<T,Maxsize>::Stack (): _elements_count{0} {
}

template<typename T, std::size_t Maxsize>
bool Stack<T, Maxsize>::push(const T& e){
  if (_elements_count >= Maxsize){
    return (false);
  }
  _elements[_elements_count] = e;
  _elements_count++;
  return (true);
}

template<typename T, std::size_t Maxsize>
bool Stack<T, Maxsize>::pop(void){
  if (empty()){
    return (false);
  }
  --_elements_count;
  return(true);
}

template<typename T, std::size_t Maxsize>
std::optional<T>  Stack<T, Maxsize>::top() const{
  if (_elements_count >= 1){
    return std::optional<T>{_elements[_elements_count - 1]};
  }
  return std::nullopt;
}


template<typename P, std::size_t M>
std::ostream& operator<< (std::ostream& os, Stack<P, M> const& s){

  for(std::size_t i = 0; i< s._elements_count; i++){
    os <<  s._elements[i] << ' ';
  }

  return (os);
}    