#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

static char num_buf[32];
static char path_buf[4096];

static inline void write_str(const char *s) {
    const char *p = s;
    while (*p) p++;
    write(1, s, p - s);
}

static inline void write_num(long n) {
    char *p = num_buf + 31;
    *p = '\0';
    
    if (n == 0) {
        *--p = '0';
    } else {
        while (n > 0) {
            *--p = '0' + (n % 10);
            n /= 10;
        }
    }
    
    write_str(p);
}

static long get_size(const char *path) {
    struct stat st;
    DIR *dir;
    struct dirent *entry;
    long total = 0;
    char *p;
    
    if (stat(path, &st) == -1) return 0;
    
    if (S_ISREG(st.st_mode)) {
        return (st.st_size + 1023) / 1024;
    }
    
    if (!S_ISDIR(st.st_mode)) return 0;
    
    dir = opendir(path);
    if (!dir) return 0;
    
    p = path_buf;
    while (*path) *p++ = *path++;
    if (p > path_buf && *(p-1) != '/') *p++ = '/';
    
    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.') continue;
        
        char *q = p;
        char *name = entry->d_name;
        while (*name) *q++ = *name++;
        *q = '\0';
        
        total += get_size(path_buf);
    }
    
    closedir(dir);
    return total;
}

int main(int argc, char **argv) {
    const char *path = (argc > 1) ? argv[1] : ".";
    long size = get_size(path);
    
    write_num(size);
    write(1, "\t", 1);
    write_str(path);
    write(1, "\n", 1);
    
    return 0;
}