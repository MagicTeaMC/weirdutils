#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static char num_buf[32];

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

int main(int argc, char **argv) {
    struct stat st;
    
    if (argc != 2) return 1;
    
    if (stat(argv[1], &st) == -1) return 1;
    
    write_str("Size: ");
    write_num(st.st_size);
    write_str("\nMode: ");
    write_num(st.st_mode & 0777);
    write_str("\nUID: ");
    write_num(st.st_uid);
    write_str("\nGID: ");
    write_num(st.st_gid);
    write_str("\nLinks: ");
    write_num(st.st_nlink);
    write_str("\n");
    
    return 0;
}