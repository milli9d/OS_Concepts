#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>
#include <memory>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include <unistd.h>

#define TOKEN_LIMIT 10u
static volatile uint64_t _tokens = 0u;
static std::mutex _token_mutex{};
static std::condition_variable token_available{};
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
            std::unique_lock<std::mutex> token_lock(_token_mutex);
            if (_tokens < TOKEN_LIMIT) {
                printf("Added new token %lu\n", ++_tokens);
                token_available.notify_all();
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
            std::unique_lock<std::mutex> token_lock(_token_mutex);
            while (!_tokens) { token_available.wait(token_lock); }
            printf("Removed a token %lu\n", --_tokens);
        }
    }

  public:
    /**
     * @brief
     */
    consumer() : _thread(std::make_shared<std::thread>(this->_run)) {}
};

int main() {
    consumer cons[16u];
    producer my_prod;

    while (!done) { std::this_thread::sleep_for(std::chrono::milliseconds(100u)); }
    return 0;
}
