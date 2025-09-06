#!/bin/bash

SOURCES=(wc.c ls.c cp.c mv.c rm.c cat.c echo.c touch.c chmod.c chown.c pwd.c head.c tail.c stat.c du.c df.c mkdir.c rmdir.c basename.c dirname.c grep.c sort.c uniq.c cut.c tr.c cmp.c tac.c rev.c uname.c whoami.c sleep.c seq.c yes.c true.c false.c sync.c)

echo "Building development versions..."
for src in "${SOURCES[@]}"; do
    if [ -f "$src" ]; then
        target="${src%.c}"
        echo "  $src -> $target"
        gcc -g -O0 -Wall -Wextra -o "$target" "$src"
    fi
done
echo "Development build complete."