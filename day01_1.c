#include "lib.c"

int main() {
    unsigned int  incs =  0;
    unsigned int  curr =  0;
    unsigned int  prev = ~0u;

    while(read_next_int(&curr)) {
        if (prev < curr) {
            incs += 1;
        }
        prev = curr;
    }

    return writeuint(incs);
}
