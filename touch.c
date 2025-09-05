#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>

int main(int argc, char **argv) {
    int i, fd;
    
    if (argc < 2) return 1;
    
    for (i = 1; i < argc; i++) {
        if (utime(argv[i], 0) == 0) {
            continue;
        }
        
        fd = open(argv[i], O_CREAT | O_WRONLY, 0644);
        if (fd != -1) {
            close(fd);
        }
    }
    
    return 0;
}