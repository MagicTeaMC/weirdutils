#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

static int parse_int(const char *s) {
    int result = 0;
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }
    return result;
}

int main(int argc, char **argv) {
    uid_t uid;
    gid_t gid;
    int i;
    
    if (argc < 3) return 1;
    
    uid = parse_int(argv[1]);
    gid = parse_int(argv[2]);
    
    for (i = 3; i < argc; i++) {
        if (chown(argv[i], uid, gid) != 0) {
            return 1;
        }
    }
    
    return 0;
}