#include <unistd.h>
#include <pwd.h>

static inline void write_str(const char *s) {
    const char *p = s;
    while (*p) p++;
    write(1, s, p - s);
}

int main(void) {
    struct passwd *pwd = getpwuid(getuid());
    
    if (pwd && pwd->pw_name) {
        write_str(pwd->pw_name);
        write(1, "\n", 1);
        return 0;
    }
    
    return 1;
}