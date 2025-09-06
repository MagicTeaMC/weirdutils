#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 8192

static char buffer[BUFFER_SIZE];

int main(int argc, char **argv) {
    int fd;
    ssize_t bytes_read;
    char *line_start, *line_end, *p;
    
    if (argc > 1) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) return 1;
    } else {
        fd = 0;
    }
    
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        line_start = buffer;
        p = buffer;
        
        while (p < buffer + bytes_read) {
            if (*p == '\n') {
                line_end = p - 1;
                
                while (line_end >= line_start) {
                    write(1, line_end, 1);
                    line_end--;
                }
                
                write(1, "\n", 1);
                line_start = p + 1;
            }
            p++;
        }
    }
    
    if (fd != 0) close(fd);
    return 0;
}