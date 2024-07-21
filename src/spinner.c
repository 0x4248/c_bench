#include <stdio.h>
#include <unistd.h>

/**
 * spinner - A function that prints a spinner to the terminal
 *
 * @message: The message to print before the spinner
 *
 * @returns: void
 */
void *spinner(void *message) {
    const char *animation[] = {"-", "\\", "|", "/"};
    while (1) {
        for (int i = 0; i < 4; i++) {
            printf("\r%s [%s]", message, animation[i]);
            fflush(stdout);
            usleep(100000);
        }
    }
}