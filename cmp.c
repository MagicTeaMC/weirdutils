#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 8192

static char buffer1[BUFFER_SIZE];
static char buffer2[BUFFER_SIZE];

int main(int argc, char **argv) {
    int fd1, fd2;
    ssize_t bytes1, bytes2;
    int i;
    
    if (argc != 3) return 1;
    
    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) return 1;
    
    fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1) {
        close(fd1);
        return 1;
    }
    
    while ((bytes1 = read(fd1, buffer1, BUFFER_SIZE)) > 0 &&
           (bytes2 = read(fd2, buffer2, BUFFER_SIZE)) > 0) {
        
        if (bytes1 != bytes2) {
            close(fd1);
            close(fd2);
            return 1;
        }
        
        for (i = 0; i < bytes1; i++) {
            if (buffer1[i] != buffer2[i]) {
                close(fd1);
                close(fd2);
                return 1;
            }
        }
    }
    
    if (bytes1 != bytes2) {
        close(fd1);
        close(fd2);
        return 1;
    }
    
    close(fd1);
    close(fd2);
    return 0;
}