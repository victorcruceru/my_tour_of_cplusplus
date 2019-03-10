set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(locks1  locks1.cpp)
target_link_libraries (locks1 ${CMAKE_THREAD_LIBS_INIT})