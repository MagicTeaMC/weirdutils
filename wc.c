#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    
    FILE *f = fopen(argv[1], "r");
    if (!f) return 1;
    
    char buf[8192];
    int lines = 0;
    size_t n;
    
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        for (size_t i = 0; i < n; i++) {
            if (buf[i] == '\n') lines++;
        }
    }
    
    fclose(f);
    printf("%d\n", lines);
    return 0;
}