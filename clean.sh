#!/bin/bash

BINARIES=(wc ls cp mv rm cat echo touch chmod chown pwd head tail stat du df mkdir rmdir basename dirname grep sort uniq cut tr cmp tac rev uname whoami sleep seq yes true false sync)

echo "Cleaning binaries..."
for bin in "${BINARIES[@]}"; do
    if [ -f "$bin" ]; then
        echo "  Removing $bin"
        rm "$bin"
    fi
done

if [ -f testfile ]; then
    echo "  Removing testfile"
    rm testfile
fi

echo "Clean complete."