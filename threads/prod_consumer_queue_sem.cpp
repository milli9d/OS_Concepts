#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>
#include <memory>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include <unistd.h>

#define TOKEN_LIMIT   10u
#define NUM_PRODUCERS 1600u
#define NUM_CONSUMERS 1u

static std::mutex _token_mutex{};
static std::mutex _space_mutex{};

static std::condition_variable token_available{};
static std::condition_variable space_available{};

bool done{};

template<typename T, size_t S>
class queue {
  private:
    std::vector<T> _q{};
    size_t q_cap{ S };
    std::mutex q_mutex;

  public:
    queue(size_t sz) : q_cap(sz) {
        space_available.notify_all();
    }

    bool is_full() {
        return !(_q.size() < q_cap);
    }

    bool is_empty() {
        return _q.empty();
    }

    void enqueue(T val) {
        std::unique_lock<std::mutex> sem_lock(q_mutex);
        if (is_full()) {
            return;
        }
        /* enqueue */
        _q.insert(_q.begin(), val);
        token_available.notify_all();
    }

    T dequeue(void) {
        std::unique_lock<std::mutex> sem_lock(q_mutex);
        if (is_empty()) {
            return T();
        }
        /* dequeue */
        T ret = _q.back();
        _q.pop_back();
        space_available.notify_all();
        return ret;
    }
};

static queue<char, TOKEN_LIMIT> shared_q(TOKEN_LIMIT);
static const char* str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n"
                         "Phasellus vehicula eget enim at pellentesque.\n";

static char* ptr = (char*) &str[0u];

class producer {
  private:
    std::shared_ptr<std::thread> _thread;

    /**
     * @brief
     * @param
     */
    static void _run(void) {
        while (true) {
            /* Transmit input string */
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 250u));
            std::unique_lock<std::mutex> space_lock(_space_mutex);
            if (*ptr != '\0') {
                shared_q.enqueue(*(ptr++));
            } else {
                ptr = (char*) &str[0u];
            }
            /* when full , wait for another element */
            while (shared_q.is_full()) { space_available.wait(space_lock); }
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
            /* wait for element to arrive */
            std::unique_lock<std::mutex> token_lock(_token_mutex);
            while (shared_q.is_empty()) { token_available.wait(token_lock); }
            /* print out incoming element */
            char a = shared_q.dequeue();
            printf("%c", a);
            fflush(stdout);
        }
    }

  public:
    /**
     * @brief
     */
    consumer() : _thread(std::make_shared<std::thread>(this->_run)) {}
};

int main() {
    consumer cons[NUM_CONSUMERS];
    producer my_prod[NUM_PRODUCERS];
    while (!done) { std::this_thread::sleep_for(std::chrono::milliseconds(100u)); }
    return 0;
}
