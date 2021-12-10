#include "../lib/io.c"

#define MAX_LINE_LENGTH 109


long int check_syntax(unsigned int* total) {
    unsigned char stack[MAX_LINE_LENGTH + 1];
    stack[0] = '0'; // sentinel value
    int i = 0;
    unsigned int score = 0;
    while (read_char() != 0 && current_char() != '\n' && i >= 0) {
        switch (current_char()) {
            case '(':
                i += 1;
                stack[i] = ')';
                break;
            case '[':
                i += 1;
                stack[i] = ']';
                break;
            case '{':
                i += 1;
                stack[i] = '}';
                break;
            case '<':
                i += 1;
                stack[i] = '>';
                break;
            case '>':
                score += (25137 - 1197);
                // fall through
            case '}':
                score += (1197 - 57);
                // fall through
            case ']':
                score += (57 - 3);
                // fall through
            case ')':
                score += 3;
                if (current_char() != stack[i]) {
                    *total += score;
                    skip_line();
                    return input_left();
                }
                i -= 1;
                score = 0;
                break;
            default:
                write_string("Oh no! Oopsie: ");
                write_char(current_char());
                write_char('\n');
                return 0;
        }
    }
    return input_left();
}

int main() {
    unsigned int total = 0;
    while(check_syntax(&total)) {}
    return write_uint(total);
}
