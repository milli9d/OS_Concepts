# Fibonacci Sequence threads example

# glob all source files
file(GLOB threads_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# add library
add_library(fib_threads SHARED ${threads_srcs})
target_include_directories(fib_threads
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# add library alias
add_library(CPP::fib_threads ALIAS fib_threads)

# add runnable target
add_executable(_threads_tb ${CMAKE_CURRENT_SOURCE_DIR}/threads_tb.cpp)

target_link_libraries(_threads_tb
    PRIVATE CPP::fib_threads
)

add_custom_target(threads_tb COMMAND _threads_tb)