#!/bin/bash

SOURCES=(wc.c ls.c cp.c mv.c rm.c cat.c echo.c touch.c chmod.c chown.c pwd.c head.c tail.c stat.c du.c df.c)

echo "Building development versions..."
for src in "${SOURCES[@]}"; do
    if [ -f "$src" ]; then
        target="${src%.c}"
        echo "  $src -> $target"
        gcc -g -O0 -Wall -Wextra -o "$target" "$src"
    fi
done
echo "Development build complete."