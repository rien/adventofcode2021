#include "../lib/io.c"

int main() {
    unsigned int incs = 0;
    unsigned int curr = 0;
    unsigned int prev = ~0u;

    while (read_uint(&curr)) {
        if (prev < curr) {
            incs += 1;
        }
        prev = curr;
    }

    return write_uint(incs);
}
