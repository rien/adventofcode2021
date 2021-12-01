#include <unistd.h>

#define true 1
#define false 0

#define IBUF_SIZE 12288

static long int left;
static long int bidx = IBUF_SIZE;
static unsigned char buff[IBUF_SIZE];

static inline long int read_char() {
    bidx += 1;
    /* fill buffer if required, ensures at least 1 char */
    if (bidx >= left) {
        left = read(STDIN_FILENO, &buff, IBUF_SIZE);
        bidx = 0;
    }
    return left;
}

/**
 * The current character from stdout.
 * Undefined if there hasn't been a call to read_char() yet.
 */
static inline unsigned char current_char() {
    return buff[bidx];
}

/**
 * Read the next integer and store it in *pointer.
 * After this function has been performed, the current_char() will be the first
 * non-digit character from stdout.
 *
 * Returns `true` if an integer has been read.
 * Returns `false` if stdin is empty (and no integer has been read).
 */
static inline int read_uint(unsigned int* pointer) {

    unsigned char nxt;
    unsigned int val = 0;

    while (read_char()) {
        nxt = current_char() - 48;
        if (nxt < 10) {
            val = val*10 + (unsigned int) nxt;
        } else {
            *pointer = val;
            return true;
        }
    }
    return false;
}

/**
 * Write an integer to stdout
 */
static inline int write_uint(unsigned int result) {
    long unsigned int idx = 9;
    long int ret;
    char out[10];
    while (result > 0) {
        out[idx] = (char) ((result % 10) + 48);
        result /= 10;
        idx -= 1;
    }
    ret = write(STDOUT_FILENO, &out[idx + 1] , 9 - idx);
    return ret > 0 ? 0 : (int) ret;
}
