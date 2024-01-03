#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>
#include <memory>
#include <algorithm>
#include <mutex>

#include <unistd.h>

#define TOKEN_LIMIT 10000u
static volatile uint64_t _tokens = 0u;
static std::mutex _token_mutex{};
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
            if (_tokens < TOKEN_LIMIT) {
                _token_mutex.lock();
                printf("Added new token %lu\n", ++_tokens);
                _token_mutex.unlock();
            } else {
                done = true;
                break;
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
            if (_tokens) {
                _token_mutex.lock();
                printf("Removed a token %lu\n", --_tokens);
                _token_mutex.unlock();
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
    producer my_prod;
    consumer cons_1;

    while (!done) { std::this_thread::sleep_for(std::chrono::milliseconds(100u)); }
    return 0;
}
