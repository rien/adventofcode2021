#include "lib.c"

int main(int _argc, char* _argv[]) {
             char lchr = 48;
             int  retn =  0;
    unsigned int  incs =  0;
    unsigned int  curr =  0;
    unsigned int  prev = -1;

    do {

        // read input until newline
        do {
            curr = curr*10 + (lchr - 48);
            retn = read(STDIN_FILENO, &lchr, 1);
        } while(lchr != '\n' && retn > 0);


        // compare with previous measurement
        if (prev < curr) {
            incs += 1;
        }

        prev = curr;
        curr = 0;
        lchr = 48;
    } while(retn > 0);

    return writeuint(incs);
}
