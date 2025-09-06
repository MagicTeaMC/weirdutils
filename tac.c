#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 65536

static char buffer[BUFFER_SIZE];

int main(int argc, char **argv) {
    int fd;
    struct stat st;
    off_t file_size, pos;
    ssize_t bytes_read;
    char *line_end, *line_start;
    
    if (argc > 1) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) return 1;
    } else {
        fd = 0;
    }
    
    if (fstat(fd, &st) == -1) {
        if (fd != 0) close(fd);
        return 1;
    }
    
    file_size = st.st_size;
    if (file_size == 0) {
        if (fd != 0) close(fd);
        return 0;
    }
    
    pos = file_size;
    
    while (pos > 0) {
        off_t read_size = (pos > BUFFER_SIZE) ? BUFFER_SIZE : pos;
        pos -= read_size;
        
        lseek(fd, pos, SEEK_SET);
        bytes_read = read(fd, buffer, read_size);
        
        line_end = buffer + bytes_read;
        
        for (char *p = buffer + bytes_read - 1; p >= buffer; p--) {
            if (*p == '\n' || p == buffer) {
                line_start = (p == buffer) ? p : p + 1;
                
                if (line_start < line_end) {
                    write(1, line_start, line_end - line_start);
                    if (*(line_end - 1) != '\n') {
                        write(1, "\n", 1);
                    }
                }
                
                line_end = p;
            }
        }
    }
    
    if (fd != 0) close(fd);
    return 0;
}