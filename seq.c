#include <unistd.h>

static char num_buf[32];

static inline void write_num(int n) {
    char *p = num_buf + 31;
    *p = '\0';
    
    if (n == 0) {
        *--p = '0';
    } else {
        while (n > 0) {
            *--p = '0' + (n % 10);
            n /= 10;
        }
    }
    
    while (*p) {
        write(1, p, 1);
        p++;
    }
}

static int parse_int(const char *s) {
    int result = 0;
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }
    return result;
}

int main(int argc, char **argv) {
    int start = 1, end = 10, step = 1;
    
    if (argc == 2) {
        end = parse_int(argv[1]);
    } else if (argc == 3) {
        start = parse_int(argv[1]);
        end = parse_int(argv[2]);
    } else if (argc == 4) {
        start = parse_int(argv[1]);
        step = parse_int(argv[2]);
        end = parse_int(argv[3]);
    }
    
    for (int i = start; i <= end; i += step) {
        write_num(i);
        write(1, "\n", 1);
    }
    
    return 0;
}