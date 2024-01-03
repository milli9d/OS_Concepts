# Shell for interaction with console

# glob all source files
file(GLOB shell_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# add library
add_library(os_shell SHARED ${shell_srcs})
target_include_directories(fib_threads
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# add library alias
add_library(CPP::os_shell ALIAS os_shell)

# add runnable target
add_executable(_os_shell_tb ${CMAKE_CURRENT_SOURCE_DIR}/os_shell_tb.cpp)

target_link_libraries(_threads_tb
    PRIVATE CPP::os_shell
)

add_custom_target(os_shell_tb COMMAND _os_shell_tb)