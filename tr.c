#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 8192

static char buffer[BUFFER_SIZE];

int main(int argc, char **argv) {
    int fd;
    ssize_t bytes_read;
    char from_char, to_char;
    char *p;
    
    if (argc < 3) return 1;
    
    from_char = argv[1][0];
    to_char = argv[2][0];
    
    if (argc > 3) {
        fd = open(argv[3], O_RDONLY);
        if (fd == -1) return 1;
    } else {
        fd = 0;
    }
    
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        p = buffer;
        
        while (p < buffer + bytes_read) {
            if (*p == from_char) {
                *p = to_char;
            }
            p++;
        }
        
        write(1, buffer, bytes_read);
    }
    
    if (fd != 0) close(fd);
    return 0;
}