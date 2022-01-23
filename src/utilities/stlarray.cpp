/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#include <string>
#include <iostream>
#include <iterator>
#include <array>


int main() {
   
    std::array a4{3.7, 1.0, 4.0};

    std::cout << std::is_floating_point<decltype(a4)::value_type>::value <<'\n';
    

    for (const auto& e:a4){
        std::cout<<e<<" ";
    }
    std::cout<<"\n";

    std::copy(a4.cbegin(), a4.cend(),
            std::ostream_iterator<double>(std::cout, ";") ); 
    std::cout<<"\n";        
}