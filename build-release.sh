#!/bin/bash

SOURCES=(wc.c ls.c cp.c mv.c rm.c cat.c echo.c touch.c chmod.c chown.c pwd.c head.c tail.c stat.c du.c df.c)

echo "Building optimized release versions..."
for src in "${SOURCES[@]}"; do
    if [ -f "$src" ]; then
        target="${src%.c}"
        echo "  $src -> $target"
        gcc -O3 -march=native -flto -s -o "$target" "$src"
    fi
done
echo "Release build complete."