#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 8192

static char buffer[BUFFER_SIZE];

static int match_pattern(const char *line, const char *pattern) {
    const char *l = line;
    
    const char *p = pattern;
    
    while (*l) {
        const char *l_start = l;
        const char *p_curr = p;
        
        while (*l_start && *p_curr && *l_start == *p_curr) {
            l_start++;
            p_curr++;
        }
        
        if (*p_curr == '\0') return 1;
        l++;
    }
    
    return 0;
}

int main(int argc, char **argv) {
    int fd;
    ssize_t bytes_read;
    char *pattern, *line_start, *p;
    
    if (argc < 2) return 1;
    
    pattern = argv[1];
    
    if (argc > 2) {
        fd = open(argv[2], O_RDONLY);
        if (fd == -1) return 1;
    } else {
        fd = 0;
    }
    
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        line_start = buffer;
        p = buffer;
        
        while (p < buffer + bytes_read) {
            if (*p == '\n') {
                *p = '\0';
                if (match_pattern(line_start, pattern)) {
                    write(1, line_start, p - line_start);
                    write(1, "\n", 1);
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