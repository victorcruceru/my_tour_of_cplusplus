/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

template <typename T>
class __CustomAllocator {
  public:
    using value_type  = T;
    using propagate_on_container_move_assignment  =  std::true_type;
    using is_always_equal  =  std::true_type;
    using size_type	= std::size_t;
    using difference_type =	std::ptrdiff_t;

    __CustomAllocator() noexcept {}  // not required, unless used

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

class AllocHelper{
  private:
    inline static std::size_t new_count {0};
    inline static std::size_t delete_count {0};
    inline static std::int64_t total_bytes {0};
    inline static std::map<void*, std::size_t, std::less<void* >, 
            __CustomAllocator<std::pair<const void*, std::size_t>>> addr_map;
    inline static bool do_trace {false};
  public:
    inline static void set_tracing(bool do_trace = true){
      AllocHelper::do_trace = do_trace;
    }  

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

    static void* allocate_h(std::size_t sz, const char* msg){
      if (AllocHelper::do_trace){
        std::printf ("Allocating %zu bytes, %s\n",  sz, msg);
      }

      void* x = std::malloc(sz);
      if (x != nullptr){
        AllocHelper::addr_map[x] = sz;
        AllocHelper::total_bytes += sz;
        new_count++;        
      }
      return (x);
    }

    static void deallocate_h(void* ptr, const char* msg){
      if (AllocHelper::do_trace){
        std::printf("Deallocating  address 0x%x, %s\n", ptr, msg);
      }
      std::map<void*, std::size_t>::iterator m_it =  
                                    AllocHelper::addr_map.find(ptr);
      if (m_it != AllocHelper::addr_map.end()){                              
        AllocHelper::total_bytes -= m_it->second;
        AllocHelper::delete_count++;
        AllocHelper::addr_map.erase(m_it);
        std::free(ptr);
      } else {
        std::printf ("Address 0x%x  not recorded,  %s\n", ptr, msg);        
      }
    }
};

// overloading global new operator
inline void* operator new(std::size_t sz){
  std::printf("operator new size  %zu\n", sz);    
  return AllocHelper::allocate_h(sz, "::new");
}

// overloading global new[] operator
inline void* operator new[](std::size_t sz){
  std::printf("operator new[] size  %zu\n", sz);
  return AllocHelper::allocate_h(sz, "::new[]");
}

// overloading  global delete operator
inline void operator delete (void* ptr) noexcept{
  std::printf( "operator delete for addr 0x%x\n", ptr);    
  return AllocHelper::deallocate_h(ptr, "::delete");
}

// overloading  global delete operator
inline void operator delete (void* ptr, std::size_t sz) noexcept{
  std::printf( "operator delete for addr 0x%x, size %zu\n", ptr, sz);    
  return AllocHelper::deallocate_h(ptr, "::delete");
}

// overloading  global delete operator
inline void operator delete[](void* ptr) noexcept{
  std::printf( "operator delete[] for addr. %x\n", ptr);    
  return AllocHelper::deallocate_h(ptr, "::delete[]");
}

// overloading  global delete operator
inline void operator delete[](void* ptr, std::size_t sz) noexcept{
  std::printf( "operator delete[] for addr 0x%x, size %zu\n", ptr, sz);      
  return AllocHelper::deallocate_h(ptr, "::delete[]");
}