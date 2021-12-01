#include "lib.c"

int main(int _argc, char* _argv[]) {
             char lchr = 48;
             int  retn =  0;
    unsigned int  curr =  0;
    unsigned int  incs =  0;
    unsigned int  widx =  0;
    unsigned int  wndw[3] = { -1, -1, -1};

    do {

        // read input until newline
        do {
            curr = curr*10 + (lchr - 48);
            retn = read(STDIN_FILENO, &lchr, 1);
        } while(lchr != '\n' && retn > 0);

        // compare with measurement leaving window
        if (wndw[widx] < curr) {
            incs += 1;
        }

        // update window
        wndw[widx] = curr;
        widx = (widx + 1) % 3;

        curr = 0;
        lchr = 48;
    } while(retn > 0);

    return writeuint(incs);
}
