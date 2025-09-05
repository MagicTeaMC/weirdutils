#include <unistd.h>

#define PATH_MAX 4096

static char path_buffer[PATH_MAX];

int main(void) {
    if (getcwd(path_buffer, PATH_MAX)) {
        char *p = path_buffer;
        while (*p) p++;
        write(1, path_buffer, p - path_buffer);
        write(1, "\n", 1);
        return 0;
    }
    
    return 1;
}