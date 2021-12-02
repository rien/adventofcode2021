#include "../lib/io.c"

int main() {
    unsigned int curr    = 0;
    unsigned int incs    = 0;
    unsigned int widx    = 0;
    unsigned int wndw[3] = {~0u, ~0u, ~0u};

    while (read_uint(&curr)) {
        /* compare with measurement leaving window */
        if (wndw[widx] < curr) {
            incs += 1;
        }

        /* update window */
        wndw[widx] = curr;
        widx       = (widx + 1) % 3;
    };

    return write_uint(incs);
}
