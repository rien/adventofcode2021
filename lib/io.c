#include <unistd.h>

#define true 1
#define false 0

# define assert(X) \
if(!(X)) { \
    write_string("Assertion failed at "); \
    write_string(__FILE__); \
    write_char(':'); \
    write_uint(__LINE__); \
    write_string(" -> "); \
    write_string(#X); \
    write_char('\n'); \
}

# define write_string(X) { char arr[] = X; write_char_array(arr, sizeof(arr) - 1); }

#define IBUF_SIZE 12288

static long int left = -1;
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
 * This will return the amount of bytes left in the input buffer.
 * Will return 0 if the input is empty.
 */
static inline long int input_left() {
    return left;
}

/**
 * Write an integer to stdout
 */
static inline int write_uint(unsigned long long int result) {
    long unsigned int idx = 20;
    long int ret;
    char out[22];
    out[21] = '\n';
    while (result > 0) {
        out[idx] = (char) ((result % 10) + 48);
        result /= 10;
        idx -= 1;
    }
    ret = write(STDOUT_FILENO, &out[idx + 1], 21 - idx);
    return ret > 0 ? 0 : (int) ret;
}

/**
 * Write a character to stdout
 */
static inline int write_char(unsigned char chr) {
    long int ret = write(STDOUT_FILENO, &chr, 1);
    return ret > 0 ? 0 : (int) ret;
}

static inline int write_int(long long int result) {
    if(result < 0) {
        write_char('-');
        result *= -1;
    }
    return write_uint((unsigned long long) result);
}

/**
 * Write a string to stdout
 */
static inline int write_char_array(char* ptr, unsigned int size) {
    long int ret = write(STDOUT_FILENO, ptr, size);
    return ret > 0 ? 0 : (int) ret;
}

/**
 * The current character from stdout.
 * Undefined if there hasn't been a call to read_char() yet.
 */
static inline unsigned char current_char() { return buff[bidx]; }

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
            val = val * 10 + (unsigned int)nxt;
        } else {
            *pointer = val;
            return true;
        }
    }
    return false;
}

/**
 * Read characters up until the next whitespace.
 * Assigns the first character of the consumed characters to the pointer.
 *
 * Returns how many characters have been read or 0 (false) if there were no
 * characters left to read.
 */
static inline int read_until_space(unsigned char* pointer) {
    unsigned char nxt;
    int i = 0;
    if (read_char()) {
        i += 1;
        nxt = current_char();
        // 'whitespace', exit
        if (nxt <= 32) {
            return true;
        }
        // assign to pointer
        *pointer = nxt;
    }
    while (read_char()) {
        i += 1;
        nxt = current_char();
        // 'whitespace', exit
        if (nxt <= 32) {
            return true;
        }
    }
    return i;
}

static inline void skip_input(unsigned int count) {
    while (count && read_char()) {
        count -= 1;
    }
}

static inline void skip_line() {
    while(read_char() && current_char() != '\n') {}
}
