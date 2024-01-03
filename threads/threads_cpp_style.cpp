/**
 * @file threads_cpp_style.cpp
 * @author Milind Singh (milind345@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cstdio>
#include <cstdint>

#include <iostream>
#include <memory>
#include <array>
#include <thread>
#include <sstream>
#include <thread>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <vector>

#include <unistd.h>

#include <logging.h>
LOG_TAG(threads_cpp);

#define NUM_OF_THREADS 16u

/**
 * @brief Burn CPU on a polling while loop
 */
void cpu_burner() {
    std::stringstream os{};
    os << std::this_thread::get_id();
    LOG_INFO("CPU burner PID = %d , TID = %s", getpid(), os.str().c_str());
    while (true) { usleep(100); }
}

/**
 * @brief CPP-style generator helper function for new threads
 * @return
 */
std::shared_ptr<std::thread> generate_thread() {
    return std::make_shared<std::thread>(cpu_burner);
}

int main(void) {
    /* create n number of threads */
    std::array<std::shared_ptr<std::thread>, NUM_OF_THREADS> threads{};
    std::generate(threads.begin(), threads.end(), generate_thread);

    std::this_thread::sleep_for(std::chrono::seconds(60u));
    return 0;
}