#include "../lib/io.c"

int main() {
    unsigned int hpos  = 0;
    unsigned int vpos  = 0;
    unsigned int units = 0;
    unsigned char next = 0;

    while (read_until_space(&next)) {
        if (next == 'f') {
            read_uint(&units);
            hpos += units;
        } else if (next == 'd') {
            read_uint(&units);
            vpos += units;
        } else if (next == 'u') {
            read_uint(&units);
            vpos -= units;
        } else {
            return 1;
        }
    }

    return write_uint(hpos * vpos);
}
