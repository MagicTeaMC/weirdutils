#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int i;
    
    if (argc < 2) return 1;
    
    for (i = 1; i < argc; i++) {
        if (mkdir(argv[i], 0755) != 0) {
            return 1;
        }
    }
    
    return 0;
}