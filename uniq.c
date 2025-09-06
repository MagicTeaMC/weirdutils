#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 8192

static char buffer[BUFFER_SIZE];
static char prev_line[1024];

static int strings_equal(const char *a, const char *b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return (*a == *b);
}

static void copy_string(char *dest, const char *src, int len) {
    int i;
    for (i = 0; i < len; i++) {
        dest[i] = src[i];
    }
    dest[len] = '\0';
}

int main(int argc, char **argv) {
    int fd;
    ssize_t bytes_read;
    char *line_start, *p;
    int first_line = 1;
    
    if (argc > 1) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) return 1;
    } else {
        fd = 0;
    }
    
    prev_line[0] = '\0';
    
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        line_start = buffer;
        p = buffer;
        
        while (p < buffer + bytes_read) {
            if (*p == '\n') {
                *p = '\0';
                
                if (first_line || !strings_equal(line_start, prev_line)) {
                    write(1, line_start, p - line_start);
                    write(1, "\n", 1);
                    copy_string(prev_line, line_start, p - line_start);
                    first_line = 0;
                }
                
                *p = '\n';
                line_start = p + 1;
            }
            p++;
        }
    }
    
    if (fd != 0) close(fd);
    return 0;
}