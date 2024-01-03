#include <cstdio>
#include <ctime>
#include <iostream>
#include <cstring>

#include <pthread.h>
#include <unistd.h>

#include <logging.h>
LOG_TAG(pthreads_c);

#define MS_TO_NS(x) (static_cast<uint64_t>(x * 1000000u))

/**
 * @brief Thread configuration
 */
typedef struct thread_param {
    uint64_t period_ms;
    char* name[20u];
} thread_param_s;

/**
 * @brief Thread instance
 * @param args
 * @return
 */
void* thread_ping(void* args) {
    thread_param_s* conf = (thread_param_s*) args;

    while (1) {
        timespec tv = {
            .tv_sec = (time_t) (conf->period_ms / 1000u),
            .tv_nsec = (long) MS_TO_NS(conf->period_ms) % 1000u,
        };
        nanosleep(&tv, NULL);
        LOG_INFO("Ping %s", conf->name);
    }
}

int main(int argc, char** argv) {
    LOG_PASS("Hello Main %d", getpid());
    /* run two threads for 60 seconds */
    pthread_t handler[2u]{};

    thread_param_s time_1{};
    strncpy((char*) time_1.name, "Thread 1", sizeof("Thread 1"));
    time_1.period_ms = 4000u;
    pthread_create(&handler[0u], NULL, thread_ping, &time_1);

    thread_param_s time_2{};
    strncpy((char*) time_2.name, "Thread 2", sizeof("Thread 2"));
    time_2.period_ms = 2000u;
    pthread_create(&handler[1u], NULL, thread_ping, &time_2);

    sleep(60u);

    pthread_join(handler[0u], NULL);
    pthread_join(handler[1u], NULL);

    return 0;
}