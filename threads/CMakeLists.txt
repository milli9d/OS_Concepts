# build standalone executables for all files in this directory
project(threads)

file(GLOB threads_srcs "${CMAKE_CURRENT_SOURCE_DIR}/*.c*")

find_package(OpenMP REQUIRED)

foreach(filename ${threads_srcs})
    # extract filename
    get_filename_component(filename_we ${filename} NAME_WE)

    # add executable for current file
    add_executable(${filename_we} ${filename})

    # add include directories
    target_include_directories(${filename_we}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    # add pthreads
    target_link_libraries(${filename_we} 
        PRIVATE pthread
        PRIVATE logging
        PRIVATE OpenMP::OpenMP_CXX
        PRIVATE OpenMP::OpenMP_C
    )
endforeach()