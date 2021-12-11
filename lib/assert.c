# define assert(X) \
if(!(X)) { \
    write_string("Assertion failed at "); \
    write_string(__FILE__); \
    write_char(':'); \
    write_uint(__LINE__); \
    write_string(" -> "); \
    write_string(#X); \
    write_char('\n'); \
}
