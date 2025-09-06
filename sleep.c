#include <unistd.h>

static int parse_int(const char *s) {
    int result = 0;
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }
    return result;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    
    int seconds = parse_int(argv[1]);
    sleep(seconds);
    
    return 0;
}