#!/bin/sh

# THIS FILE IS TEMPORARY

gcc -O3 -o brainheck brainheck.c -lSDL2
#gcc -Wall -O3 -o brainheck brainheck.c -lSDL2
#gcc -Wall -g -o brainheck brainheck.c -lSDL2
#x86_64-w64-mingw32-gcc -Wall -O3 -o brainheck.exe brainheck.c -L:LibSDL2.a -lmingw32 -lSDL2main -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc