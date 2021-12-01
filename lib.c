#include <unistd.h>

#define true 1
#define false 0

#define IBUF_SIZE 4096

/**
 * Read the next integer and store it in *pointer.
 *
 * Returns `true` if an integer has been read.
 * Returns `false` if stdin is empty (and no integer has been read).
 */
int read_next_int(unsigned int* pointer) {
    static long int left;
    static long int bidx = IBUF_SIZE;
    static char buff[IBUF_SIZE];

    char nxt;
    unsigned int val = 0;

    while (true) {

        /* fill buffer if required, ensures at least 1 char */
        if (bidx >= left) {
            left = read(STDIN_FILENO, &buff, IBUF_SIZE);
            bidx = 0;
            /* there are no more bytes to read */
            if (left == 0) {
                return false;
            }
        }

        /* consume a single character */
        nxt = buff[bidx];
        bidx += 1;

        if (nxt != '\n') {
            val = val*10 + (unsigned int) (nxt - 48);
        } else {
            *pointer = val;
            return true;
        }
    }
}

int writeuint(unsigned int result) {
    char out = (char) (result % 10) + 48;
    result /= 10;
    return (result > 0 ? writeuint(result) : 0) |
            ((int) write(STDOUT_FILENO, &out, 1) & ~1);
}
