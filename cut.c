#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 8192

static char buffer[BUFFER_SIZE];

static int parse_int(const char *s) {
    int result = 0;
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }
    return result;
}

int main(int argc, char **argv) {
    int fd, field_num = 1;
    ssize_t bytes_read;
    char *line_start, *p, *field_start;
    int current_field;
    
    if (argc < 2) return 1;
    
    if (argv[1][0] == '-' && argv[1][1] == 'f') {
        field_num = parse_int(&argv[1][2]);
        if (argc > 2) {
            fd = open(argv[2], O_RDONLY);
            if (fd == -1) return 1;
        } else {
            fd = 0;
        }
    } else {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) return 1;
    }
    
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        line_start = buffer;
        p = buffer;
        
        while (p < buffer + bytes_read) {
            if (*p == '\n') {
                *p = '\0';
                
                field_start = line_start;
                current_field = 1;
                char *q = line_start;
                
                while (*q && current_field < field_num) {
                    if (*q == '\t') {
                        current_field++;
                        field_start = q + 1;
                    }
                    q++;
                }
                
                if (current_field == field_num) {
                    char *field_end = field_start;
                    while (*field_end && *field_end != '\t') {
                        field_end++;
                    }
                    write(1, field_start, field_end - field_start);
                }
                
                write(1, "\n", 1);
                *p = '\n';
                line_start = p + 1;
            }
            p++;
        }
    }
    
    if (fd != 0) close(fd);
    return 0;
}