#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 65536

static char buffer[BUFFER_SIZE];

int main(int argc, char **argv) {
    int src_fd, dst_fd;
    ssize_t bytes_read, bytes_written;
    
    if (argc != 3) return 1;
    
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) return 1;
    
    dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        close(src_fd);
        return 1;
    }
    
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dst_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            close(src_fd);
            close(dst_fd);
            return 1;
        }
    }
    
    close(src_fd);
    close(dst_fd);
    return 0;
}