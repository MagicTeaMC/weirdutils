#include <sys/stat.h>
#include <unistd.h>

static int parse_octal(const char *s) {
    int result = 0;
    while (*s >= '0' && *s <= '7') {
        result = result * 8 + (*s - '0');
        s++;
    }
    return result;
}

int main(int argc, char **argv) {
    int mode, i;
    
    if (argc < 3) return 1;
    
    mode = parse_octal(argv[1]);
    
    for (i = 2; i < argc; i++) {
        if (chmod(argv[i], mode) != 0) {
            return 1;
        }
    }
    
    return 0;
}