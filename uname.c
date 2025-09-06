#include <sys/utsname.h>
#include <unistd.h>

static inline void write_str(const char *s) {
    const char *p = s;
    while (*p) p++;
    write(1, s, p - s);
}

int main(int argc, char **argv) {
    struct utsname info;
    
    if (uname(&info) != 0) return 1;
    
    if (argc == 1) {
        write_str(info.sysname);
        write(1, "\n", 1);
        return 0;
    }
    
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'a':
                    write_str(info.sysname);
                    write(1, " ", 1);
                    write_str(info.nodename);
                    write(1, " ", 1);
                    write_str(info.release);
                    write(1, " ", 1);
                    write_str(info.version);
                    write(1, " ", 1);
                    write_str(info.machine);
                    break;
                case 's':
                    write_str(info.sysname);
                    break;
                case 'n':
                    write_str(info.nodename);
                    break;
                case 'r':
                    write_str(info.release);
                    break;
                case 'm':
                    write_str(info.machine);
                    break;
            }
            if (i < argc - 1) write(1, " ", 1);
        }
    }
    
    write(1, "\n", 1);
    return 0;
}