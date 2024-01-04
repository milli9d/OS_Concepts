#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>
#include <memory>
#include <algorithm>
#include <mutex>
#include <atomic>

#include <unistd.h>

#define TOKEN_LIMIT 10000u
std::atomic<uint64_t> _tokens(0u);

bool done{};

class producer {
  private:
    std::shared_ptr<std::thread> _thread;

    /**
     * @brief
     * @param
     */
    static void _run(void) {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100u));
            uint64_t tokens = _tokens; // load
            if (tokens < TOKEN_LIMIT) {
                printf("Added new token %lu\n", ++tokens);
                _tokens = tokens; // store
            }
        }
    }

  public:
    /**
     * @brief
     */
    producer() : _thread(std::make_shared<std::thread>(this->_run)) {}
};

class consumer {
  private:
    std::shared_ptr<std::thread> _thread;

    /**
     * @brief
     * @param
     */
    static void _run(void) {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50u));
            uint64_t tokens = _tokens; // load
            if (tokens) {
                printf("Removed a token %lu\n", --tokens);
                _tokens = tokens; // store
            }
        }
    }

  public:
    /**
     * @brief
     */
    consumer() : _thread(std::make_shared<std::thread>(this->_run)) {}
};

int main() {
    producer my_prod[16u];
    consumer cons_1[8u];

    std::this_thread::sleep_for(std::chrono::milliseconds(5000u));
    return 0;
}
