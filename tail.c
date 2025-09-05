#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 8192

static char buffer[BUFFER_SIZE];
static char line_starts[1024];

int main(int argc, char **argv) {
    int fd;
    struct stat st;
    ssize_t bytes_read;
    off_t file_size, pos;
    int newlines = 0, lines_to_show = 10;
    char *p;
    
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
    
    pos = file_size - BUFFER_SIZE;
    if (pos < 0) pos = 0;
    
    lseek(fd, pos, SEEK_SET);
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    
    p = buffer + bytes_read - 1;
    while (p >= buffer && newlines < lines_to_show) {
        if (*p == '\n') newlines++;
        p--;
    }
    p += 2;
    
    write(1, p, buffer + bytes_read - p);
    
    if (fd != 0) close(fd);
    return 0;
}