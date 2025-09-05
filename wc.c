#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 65536

static char buffer[BUFFER_SIZE];
static char num_buf[16];

static inline void write_num(int n) {
    char *p = num_buf + 15;
    *p = '\0';
    
    if (n == 0) {
        *--p = '0';
    } else {
        while (n > 0) {
            *--p = '0' + (n % 10);
            n /= 10;
        }
    }
    
    while (*p) {
        write(1, p, 1);
        p++;
    }
}

int main(int argc, char **argv) {
    int fd;
    ssize_t bytes_read;
    int lines = 0, words = 0, chars = 0;
    int in_word = 0;
    char *p, *end;
    
    if (argc < 2) {
        fd = 0;
    } else {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) return 1;
    }
    
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        chars += bytes_read;
        p = buffer;
        end = buffer + bytes_read;
        
        while (p < end) {
            if (*p == '\n') {
                lines++;
                if (in_word) {
                    words++;
                    in_word = 0;
                }
            } else if (*p == ' ' || *p == '\t') {
                if (in_word) {
                    words++;
                    in_word = 0;
                }
            } else {
                in_word = 1;
            }
            p++;
        }
    }
    
    if (in_word) words++;
    
    if (fd != 0) close(fd);
    
    write_num(lines);
    write(1, " ", 1);
    write_num(words);
    write(1, " ", 1);
    write_num(chars);
    write(1, "\n", 1);
    
    return 0;
}