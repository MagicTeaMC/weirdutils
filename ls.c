#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

static char buffer[BUFFER_SIZE];
static char *buf_ptr = buffer;
static char *buf_end = buffer;

static inline void flush_buffer(void) {
    if (buf_ptr > buffer) {
        write(1, buffer, buf_ptr - buffer);
        buf_ptr = buffer;
    }
}

static inline void write_char(char c) {
    if (buf_ptr >= buf_end) {
        buf_end = buffer + BUFFER_SIZE;
        flush_buffer();
    }
    *buf_ptr++ = c;
}

static inline void write_str(const char *s) {
    while (*s) {
        write_char(*s++);
    }
}

int main(int argc, char **argv) {
    DIR *dir;
    struct dirent *entry;
    const char *path = (argc > 1) ? argv[1] : ".";
    
    buf_end = buffer + BUFFER_SIZE;
    
    dir = opendir(path);
    if (!dir) return 1;
    
    while ((entry = readdir(dir))) {
        if (entry->d_name[0] != '.') {
            write_str(entry->d_name);
            write_char(' ');
        }
    }
    
    closedir(dir);
    flush_buffer();
    return 0;
}