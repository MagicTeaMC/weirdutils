#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 65536

static char buffer[BUFFER_SIZE];

int main(int argc, char **argv) {
    int fd, i;
    ssize_t bytes_read;
    
    if (argc < 2) {
        while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0) {
            write(1, buffer, bytes_read);
        }
        return 0;
    }
    
    for (i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        if (fd == -1) return 1;
        
        while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
            write(1, buffer, bytes_read);
        }
        
        close(fd);
    }
    
    return 0;
}