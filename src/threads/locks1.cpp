/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: simple shared struct (between multiple threads) example
 */
#include <mutex>
#include <thread>
#include <random>
#include <chrono>
#include <cstdlib>
#include <iostream>

static 
int32_t get_a_random_number(int32_t low_limit = 0, int32_t hi_limit = 100){
  static std::mt19937_64 rng_dev(std::time(nullptr));
  static std::uniform_int_distribution<int32_t> uid(low_limit, hi_limit);
  return (uid(rng_dev));
}

struct BankAccount {
  double amount_;
  std::mutex m_;

  explicit BankAccount(double amount) : amount_{amount} {}

  BankAccount(const BankAccount &) = delete;
  BankAccount &operator=(const BankAccount &) = delete;

  void transferFrom(BankAccount &from, double amount) {
    std::unique_lock<std::mutex> lock_me(this->m_, std::defer_lock);
    std::unique_lock<std::mutex> lock_from(from.m_, std::defer_lock);
    std::lock(lock_me, lock_from);
    from.amount_ -= amount;
    this->amount_ += amount;
    std::cout << "Transferred " << amount << " from " << &from << " to "
              << this << std::endl;
    // RAII - both lock_me and lock_from are destroyed here and locks released
  }
};

static void transfer(BankAccount &from, BankAccount &to, double amount) {
  to.transferFrom(from, amount);
}

int main(void){
  BankAccount ba1 {static_cast<double>(get_a_random_number(1, 10000))};
  BankAccount ba2 {static_cast<double>(get_a_random_number(1, 10000))};
  std::thread t1(
    [](BankAccount& from_, BankAccount& to_, double a_){
      std::cout <<  std::this_thread::get_id() << " sleeping..." << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      transfer(from_, to_, a_);
      }, 
    std::ref(ba1), 
    std::ref(ba2), 
    static_cast<double>(get_a_random_number(7, 99)));

  std::thread t2(
    [](BankAccount& from_, BankAccount& to_, double a_){
      std::cout <<  std::this_thread::get_id() << " sleeping..." << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(2));
      transfer(from_, to_, a_);
      }, 
    std::ref(ba2), 
    std::ref(ba1), 
    static_cast<double>(get_a_random_number(100, 110)));

  t1.join();
  t2.join();  
  return (EXIT_SUCCESS);
}

