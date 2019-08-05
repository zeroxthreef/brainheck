# Brainheck
A very slightly optimized https://esolangs.org/wiki/Brainfuck interpreter with a few extensions.

## Extensions
* Extensions are enabled by the '@' character anywhere in the program. Probably best for it to be at the front.
* Pixel drawing (not optimized yet)
* Mouse, keyboard, and other events
* Sprites (not implemented)
* File IO (not implemented)
* TCP sockets (not implemented, but coming very soon)
* 3 channel music buffer/note+duration+volume queue (not implemented)
* Sound effect oscillator (not implemented)

## Using
Most of the extensions are created for easy use with c2bf (a C compiler that outputs code that brainheck can run). The file "c2bfapi.c" contains a bunch of functions that you can copy and paste at the top of any source file and use.

The "program_loop.c" file is an example of how to use the event commands and how I sorta structure programs with c2bf.

If you want to add more commands, node that if you provide no arguments, one extra character has to be written regardless.

Also, this is _by no means_ complete or clean code whatsoever. Just a few hours of messing around with stuff.

## License
Unlicense (pretty much international public domain)