#include <unistd.h>

static inline void write_str(const char *s) {
    const char *p = s;
    while (*p) p++;
    write(1, s, p - s);
}

int main(int argc, char **argv) {
    int i;
    
    for (i = 1; i < argc; i++) {
        write_str(argv[i]);
        if (i < argc - 1) {
            write(1, " ", 1);
        }
    }
    
    write(1, "\n", 1);
    return 0;
}