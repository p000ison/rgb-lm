#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"


lmLedMatrix *matrix_;

GHashTable *screens;
screen_t current_screen;

pthread_t screen_thread;
pthread_mutex_t screen_mutex;
pthread_cond_t screen_cond;

int running = 1;


static void *start(void *ptr) {

    struct timespec last_time;
    clock_gettime(CLOCK_REALTIME, &last_time);

    while (running) {
        struct timespec current;
        clock_gettime(CLOCK_REALTIME, &current);

        long int elapsed = current.tv_sec * 1000000000 + current.tv_nsec - last_time.tv_sec * 1000000000 + last_time.tv_nsec;

        pthread_mutex_lock(&screen_mutex);
        while (current_screen == NULL) {
            pthread_cond_wait(&screen_cond, &screen_mutex);
        }

        pthread_mutex_unlock(&screen_mutex);


        current_screen(elapsed / 1000000);

        struct timespec sleep, remaining;
        sleep.tv_sec = 0;
        sleep.tv_nsec = 16666666;

        nanosleep(&sleep, &remaining);
    }

    return NULL;
}


void init_screens(lmLedMatrix *matrix__) {
    screens = g_hash_table_new(g_str_hash, g_str_equal);
    pthread_create(&screen_thread, NULL, start, NULL);
    matrix_ = matrix__;
}

inline lmLedMatrix *get_matrix() {
    return matrix_;
}

inline screen_t get_current_screen() {
    return current_screen;
}

screen_t set_current_screen(lmLedMatrix *matrix, start_screen screen) {
    screen_t previous = get_current_screen();

    current_screen = screen;
    pthread_cond_signal(&screen_cond);

    return previous;
}

screen_t get_screen(const char *name) {
    return g_hash_table_lookup(screens, name);
}

int register_screen(const char *name, screen_t screen) {
    char *key = malloc(sizeof(char) * strlen(name));
    return g_hash_table_insert(screens, key, screen);
}


