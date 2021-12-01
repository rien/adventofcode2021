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
int read_uint(unsigned int* pointer) {
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

/**
 * Write an integer to stdout
 */
int write_uint(unsigned int result) {
    long unsigned int idx = 9;
    long int ret;
    char out[10];
    while (result > 0) {
        out[idx] = (char) (result % 10) + 48;
        result /= 10;
        idx -= 1;
    }
    ret = write(STDOUT_FILENO, &out[idx + 1] , 9 - idx);
    return ret > 0 ? 0 : (int) ret;
}
