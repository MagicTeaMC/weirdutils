#include <sys/statvfs.h>
#include <unistd.h>

static char num_buf[32];

static inline void write_str(const char *s) {
    const char *p = s;
    while (*p) p++;
    write(1, s, p - s);
}

static inline void write_num(unsigned long n) {
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

int main(int argc, char **argv) {
    struct statvfs st;
    const char *path = (argc > 1) ? argv[1] : ".";
    unsigned long total, free, used;
    
    if (statvfs(path, &st) == -1) return 1;
    
    total = (st.f_blocks * st.f_frsize) / 1024;
    free = (st.f_bavail * st.f_frsize) / 1024;
    used = total - free;
    
    write_str("Total: ");
    write_num(total);
    write_str("K\nUsed: ");
    write_num(used);
    write_str("K\nFree: ");
    write_num(free);
    write_str("K\nPath: ");
    write_str(path);
    write_str("\n");
    
    return 0;
}