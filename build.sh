#!/bin/sh

gcc -Iinclude src/main.c src/editor.c -o bin/melon -lncurses
