#include <unistd.h>

int writeuint(unsigned int result) {
    char out = (char) (result % 10) + 48;
    result /= 10;
    return (result > 0 ? writeuint(result) : 0) |
            ((int) write(STDOUT_FILENO, &out, 1) & ~1);
}
