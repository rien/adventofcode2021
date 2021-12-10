#include "../lib/io.c"
#include "../lib/sort.c"

#define MAX_LINE_LENGTH 109
#define MAX_LINE_COUNT 110


unsigned long long int score_incomplete() {
    unsigned char stack[MAX_LINE_LENGTH + 1];
    stack[0] = '0'; // sentinel value
    int i = 0;
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
                // fall through
            case '}':
                // fall through
            case ']':
                // fall through
            case ')':
                if (current_char() != stack[i]) {
                    skip_line();
                    return 0;
                }
                i -= 1;
                break;
            default:
                write_string("Oh no! Oopsie: ");
                write_char(current_char());
                write_char('\n');
                return 0;
        }
    }
    unsigned long long int score = 0;
    while(i > 0) {
        score *= 5;
        switch(stack[i]) {
            case '>':
                score += 1;
                // fall through
            case '}':
                score += 1;
                // fall through
            case ']':
                score += 1;
                // fall through
            case ')':
                score += 1;
        }
        i -= 1;
    }
    return score;
}

int main() {
    unsigned long long int scores[MAX_LINE_COUNT];
    int i = 0;
    while(input_left()) {
        scores[i] = score_incomplete();
        if(scores[i]) {
            i += 1;
        }
    }
    insertion_sort(scores, i);
    return write_uint(scores[i / 2]);
}
