#include "lib.c"

int main() {
             char lchr = 48;
        long int  retn =  0;
    unsigned int  curr =  0;
    unsigned int  incs =  0;
    unsigned int  widx =  0;
    unsigned int  wndw[3] = { ~0u, ~0u, ~0u};

    do {

        /* read input until newline */
        do {
            curr = curr*10 + (unsigned int) ( lchr - 48);
            retn = read(STDIN_FILENO, &lchr, 1);
        } while(lchr != '\n' && retn > 0);

        /* compare with measurement leaving window */
        if (wndw[widx] < curr) {
            incs += 1;
        }

        /* update window */
        wndw[widx] = curr;
        widx = (widx + 1) % 3;

        curr = 0;
        lchr = 48;
    } while(retn > 0);

    return writeuint(incs);
}
