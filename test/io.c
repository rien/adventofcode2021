
int read(char* buffer, long size) {
    asm ("\
    movq $1, %%rax;\
    movq $1, %%rdi;\
    syscall;\
    ":: "S" (buffer), "d" (size) :);
}

int main() {
    //syscall(1, 1, "Hello World!\n", 13);
    read("Hello ASM!\n", 9);
}

