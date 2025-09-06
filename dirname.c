#include <unistd.h>

static inline void write_str(const char *s) {
    const char *p = s;
    while (*p) p++;
    write(1, s, p - s);
}

int main(int argc, char **argv) {
    const char *path, *p;
    
    if (argc < 2) {
        write_str(".\n");
        return 0;
    }
    
    path = argv[1];
    p = path;
    while (*p) p++;
    
    while (p > path && *(p-1) == '/') p--;
    while (p > path && *(p-1) != '/') p--;
    while (p > path && *(p-1) == '/') p--;
    
    if (p == path) {
        write_str(".\n");
    } else {
        char c = *p;
        *(char*)p = '\0';
        write_str(path);
        *(char*)p = c;
        write(1, "\n", 1);
    }
    
    return 0;
}