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

class AllocHelper{
  private:
    inline static std::size_t new_count {0};
    inline static std::size_t delete_count {0};
    inline static std::int64_t total_bytes {0};
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


};