#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 65536
#define MAX_LINES 10000

static char buffer[BUFFER_SIZE];
static char *lines[MAX_LINES];

static int compare_strings(const char *a, const char *b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return *a - *b;
}

static void quicksort(char **arr, int low, int high) {
    if (low < high) {
        char *pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (compare_strings(arr[j], pivot) < 0) {
                i++;
                char *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        
        char *temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        
        int pi = i + 1;
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main(int argc, char **argv) {
    int fd, line_count = 0;
    ssize_t bytes_read;
    char *p, *line_start;
    
    if (argc > 1) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) return 1;
    } else {
        fd = 0;
    }
    
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0) {
        if (fd != 0) close(fd);
        return 0;
    }
    
    line_start = buffer;
    p = buffer;
    
    while (p < buffer + bytes_read && line_count < MAX_LINES) {
        if (*p == '\n') {
            *p = '\0';
            lines[line_count++] = line_start;
            line_start = p + 1;
        }
        p++;
    }
    
    quicksort(lines, 0, line_count - 1);
    
    for (int i = 0; i < line_count; i++) {
        write(1, lines[i], __builtin_strlen(lines[i]));
        write(1, "\n", 1);
    }
    
    if (fd != 0) close(fd);
    return 0;
}