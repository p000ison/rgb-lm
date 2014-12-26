#include <stdio.h>
#include <unistd.h>
#include <lm.h>

int main() {
    printf("Starting\n");
    lm_gpio_init();
    lm_gpio_init_output(lm_io_bits_new());

    lmLedMatrix *matrix = lm_matrix_new(32, 32, 6);
    lm_matrix_clear(matrix);

    lmThread *thread = lm_thread_new(matrix);
    lm_thread_start(thread);


    uint32_t continuum = 0;
    while (1) {
        usleep(5 * 1000);
        continuum += 1;
        continuum %= 3 * 255;
        int r = 0, g = 0, b = 0;
        if (continuum <= 255) {
            int c = continuum;
            b = 255 - c;
            r = c;
        } else if (continuum > 255 && continuum <= 511) {
            int c = continuum - 256;
            r = 255 - c;
            g = c;
        } else {
            int c = continuum - 512;
            g = 255 - c;
            b = c;
        }
        lm_matrix_fill(matrix, r, g, b);
    }

    lm_thread_wait(thread);
    return 0;
}
