#include <unistd.h>

int main(int argc, char **argv) {
    const char *msg = (argc > 1) ? argv[1] : "y";
    
    while (1) {
        const char *p = msg;
        while (*p) p++;
        write(1, msg, p - msg);
        write(1, "\n", 1);
    }
    
    return 0;
}