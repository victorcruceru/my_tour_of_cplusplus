/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include <cstdint>
#include <ios>
#include <iostream>
#include <limits>
#include <string>

int main() {
  std::cout << std::boolalpha;

  std::cout << "max(short): " << std::numeric_limits<short>::max() << std::endl;
  std::cout << "max(int): " << std::numeric_limits<int>::max() << std::endl;
  std::cout << "max(long): " << std::numeric_limits<long>::max() << std::endl;

  std::cout << "max(float): " << std::numeric_limits<float>::max() << std::endl;
  std::cout << "max(double): " << std::numeric_limits<double>::max()
            << std::endl;
  std::cout << "max(long double): " << std::numeric_limits<long double>::max()
            << std::endl;

  std::cout << "max(std::uint64_t): "
            << std::numeric_limits<std::uint64_t>::max() << std::endl;

  std::cout << "is_signed(std::uint64_t): "
            << std::numeric_limits<std::uint64_t>::is_signed << std::endl;

  std::cout << "is_signed(char): " << std::numeric_limits<char>::is_signed
            << std::endl;
}