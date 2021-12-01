#include "lib.c"

int main() {
             char lchr = 48;
        long int  retn =  0;
    unsigned int  incs =  0;
    unsigned int  curr =  0;
    unsigned int  prev = ~0u;

    do {

        /* read input until newline */
        do {
            curr = curr*10 + (unsigned int) ( lchr - 48);
            retn = read(STDIN_FILENO, &lchr, 1);
        } while(lchr != '\n' && retn > 0);

        /* compare with previous measurement */
        if (prev < curr) {
            incs += 1;
        }

        prev = curr;
        curr = 0;
        lchr = 48;
    } while(retn > 0);

    return writeuint(incs);
}
