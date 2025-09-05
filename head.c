#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 8192

static char buffer[BUFFER_SIZE];

int main(int argc, char **argv) {
    int fd, lines_to_show = 10;
    ssize_t bytes_read;
    char *p, *end;
    
    if (argc > 1) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) return 1;
    } else {
        fd = 0;
    }
    
    while (lines_to_show > 0 && (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        p = buffer;
        end = buffer + bytes_read;
        
        while (p < end && lines_to_show > 0) {
            if (*p == '\n') {
                lines_to_show--;
            }
            write(1, p, 1);
            p++;
        }
    }
    
    if (fd != 0) close(fd);
    return 0;
}