/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: This exercise tries to accomplish a few things:
 * - inline variables (including data members) in header files
 * - replacing new/ delete operators in order to track their usage
 *   via a std::map
 * - a custom allocator to use in the above mentioned std::map to avoid the 
 *   default one based on new/ delete operators (to avoid recursion).
 */ 
#pragma once  // not exactly portable across compiler
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

// Custom allocator based on standard free/ malloc
// This will be used as an allocator for a std::map used in turn to track new/
// delete operator calls. 
// Do not use std. cout/ cerr  here as they may use global new/ delete ops
// (risk of recursion - again).
// Most of the code is boiler -plate code, except for allocate/ deallocate
template <typename T>
class __CustomAllocator {
  public:
    using value_type  = T;
    using propagate_on_container_move_assignment  =  std::true_type;
    using is_always_equal  =  std::true_type;
    using size_type	= std::size_t;
    using difference_type =	std::ptrdiff_t;

    __CustomAllocator() noexcept {}  

    template <class U> 
    __CustomAllocator(__CustomAllocator<U> const&) noexcept {}

    value_type*  
    allocate(std::size_t n)
    {
        //std::cout << "DEBUG: Called custom allocate, " << __FILE__ << ":" 
        //          << __LINE__<< " size = " << n << std::endl;
        return static_cast<value_type*>(std::malloc(n*sizeof(value_type)));

    }

    void
    deallocate(value_type* p, std::size_t) noexcept  
    {
        //std::cout << "DEBUG: Called custom deallocate, "<< __FILE__ << ":" 
        //         << __LINE__<< " addr = " << std::hex << p << std::endl;
        std::free(p);
    }
};

template <typename T, typename U>
bool
operator==(__CustomAllocator<T> const&, __CustomAllocator<U> const&) noexcept{
    return true;
}

template <typename T, typename U>
bool
operator!=(__CustomAllocator<T> const& x, __CustomAllocator<U> const& y) 
        noexcept{
    return !(x == y);
}

// A helper class to collect statistics about new/ delete calls, memory usage,
// memory addresses used.
class AllocHelper{
  private:
    
    inline static std::size_t new_count {0}; // how many times new was called
    inline static std::size_t delete_count {0}; // counter for delete calls
    inline static std::int64_t total_bytes {0}; // number of bytes in use
    // map (address => size) of allocations in use
    inline static std::map<void*, std::size_t, std::less<void* >, 
            __CustomAllocator<std::pair<const void*, std::size_t>>> addr_map;
    inline static bool do_trace {false}; // enable/ disable tracing
  public:

    inline static void set_tracing(bool do_trace = true){
      AllocHelper::do_trace = do_trace;
    }  
     
    // Below are some getters  
    static std::size_t get_new_count(void){
      return (AllocHelper::new_count);
    }
    static std::size_t get_delete_count(void){
      return (AllocHelper::delete_count);
    }    

    static std::size_t get_total_bytes(void){
      return (AllocHelper::total_bytes);
    }    

    static std::size_t get_leaks_count(void){
      return (AllocHelper::addr_map.size());
    } 
    
    // Dump on stdout the allocated memory locations and the corresponding size
    static void dump_used(void){
      std::printf("INFO: Used memory map:\n");
      for (auto const& [key, val]: AllocHelper::addr_map){
        std::printf("\tINFO: memory addr. %p size %zu\n", key, val);
      }
    }
    // Allocation helper. Second parameter is used as a message for debugging
    // Use standard C printf as C++ iostream operators may use new/ delete 
    // (recursion risk)
    static void* allocate_h(std::size_t sz, const char* msg){
      if (AllocHelper::do_trace){
        std::printf ("DEBUG: %s: Allocating %zu bytes\n", msg, sz);
      }

      void* x = std::malloc(sz);
      if (x != nullptr){
        AllocHelper::addr_map[x] = sz;
        AllocHelper::total_bytes += sz;
        new_count++;        
      }
      return (x);
    }

    // Deallocation helper. Second parameter is used as a message for debugging
    static void deallocate_h(void* ptr, const char* msg){
      if (AllocHelper::do_trace){
        std::printf("DEBUG: %s: Deallocating  address 0x%p\n", msg, ptr);
      }
      std::map<void*, std::size_t>::iterator m_it =  
                                    AllocHelper::addr_map.find(ptr);
      if (m_it != AllocHelper::addr_map.end()){                              
        AllocHelper::total_bytes -= m_it->second;
        AllocHelper::delete_count++;
        AllocHelper::addr_map.erase(m_it);
        std::free(ptr);
      } else {
        std::printf ("DEBUG: %s: Address 0x%p not recorded.\n", msg, ptr);        
      }
    }
};

// replacing (overloading) global new operator
inline void* operator new(std::size_t sz){
  //std::printf("operator new size  %zu\n", sz);    
  return AllocHelper::allocate_h(sz, "::new");
}

// replacing (overloading) global new[] operator
inline void* operator new[](std::size_t sz){
  //std::printf("operator new[] size  %zu\n", sz);
  return AllocHelper::allocate_h(sz, "::new[]");
}

// replacing (overloading)  global delete operator
inline void operator delete (void* ptr) noexcept{
  //std::printf( "operator delete for addr 0x%p\n", ptr);    
  return AllocHelper::deallocate_h(ptr, "::delete");
}

// replacing (overloading)  global delete operator
// NOTE - This one is called when deleting simple pointers:
// X *ptr = new X;
// delete ptr;
inline void operator delete (void* ptr, std::size_t sz) noexcept{
  //std::printf( "operator delete for addr 0x%p, size %zu\n", ptr, sz);    
  return AllocHelper::deallocate_h(ptr, "::delete");
}

// replacing (overloading) global delete[] operator
// NOTE - This one is called for arrays:
// X* arr = new X[10];
// delete arr; 
inline void operator delete[](void* ptr) noexcept{
  //std::printf( "operator delete[] for addr. %p\n", ptr);    
  return AllocHelper::deallocate_h(ptr, "::delete[]");
}

// replacing (overloading) global delete operator
inline void operator delete[](void* ptr, std::size_t sz) noexcept{
  //std::printf( "operator delete[] for addr 0x%p, size %zu\n", ptr, sz);      
  return AllocHelper::deallocate_h(ptr, "::delete[]");
}