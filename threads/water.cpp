#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore>

#include <mutex>
#include <atomic>

std::counting_semaphore<2> sem_hydrogen(0);
std::binary_semaphore sem_molecule(0);

std::atomic<uint32_t> atoms = 0u;

static void make_molecule(void) {
    printf("\rMade %u water atoms!\n", ++atoms);
    sem_molecule.release(2);
}

/**
 * @brief
 * @param
 */
static void hydrogen_generator(void) {
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 4000u));
        printf("\rmade 1 hydrogen\n");
        sem_hydrogen.release();
        sem_molecule.acquire();
    }
}

/**
 * @brief
 * @param
 */
static void oxygen_generator(void) {
    while (1) {
        int count = 2;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000u));
        printf("\rmade 1 oxygen\n");
        while (count--) { sem_hydrogen.acquire(); }
        make_molecule();
    }
}

int main() {
    std::thread thread_h1(hydrogen_generator);
    std::thread thread_h2(hydrogen_generator);
    std::thread thread_o1(oxygen_generator);

    while (atoms < 10u) {}
    return 0;
}