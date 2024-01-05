#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

static sem_t h_sem;
static sem_t water_sem;

#define N_HYDROGEN_THREADS 2

/**
 * @brief
 */
static void make_water() {
    printf("Made water\n");
    int count = N_HYDROGEN_THREADS;
    while (count--) { sem_post(&water_sem); }
}

/**
 * @brief
 * @param args
 * @return
 */
static void* h_gen(void* args) {
    printf("Hydrogen!\n");
    sem_post(&h_sem);
    sem_wait(&water_sem);
    return NULL;
}

/**
 * @brief
 * @param args
 * @return
 */
static void* o_gen(void* args) {
    printf("Oxygen!\n");
    int count = N_HYDROGEN_THREADS;
    while (count--) { sem_wait(&h_sem); }
    make_water();
    return NULL;
}

/**
 * @brief
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv) {
    sem_init(&h_sem, 0, 0u);
    pthread_t h1, h2, o1;

    pthread_create(&h1, NULL, h_gen, NULL);
    pthread_create(&h2, NULL, h_gen, NULL);
    pthread_create(&o1, NULL, o_gen, NULL);

    pthread_join(o1, NULL);
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);

    return 0;
}