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
}