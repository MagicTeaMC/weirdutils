#include <unistd.h>

static inline void write_str(const char *s) {
    const char *p = s;
    while (*p) p++;
    write(1, s, p - s);
}

int main(int argc, char **argv) {
    const char *path, *p, *start;
    
    if (argc < 2) return 1;
    
    path = argv[1];
    p = path;
    while (*p) p++;
    
    while (p > path && *(p-1) == '/') p--;
    
    start = p;
    while (start > path && *(start-1) != '/') start--;
    
    if (start < p) {
        char c = *p;
        *(char*)p = '\0';
        write_str(start);
        *(char*)p = c;
    }
    
    write(1, "\n", 1);
    return 0;
}