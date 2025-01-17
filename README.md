# c64-tiny
this is a thing for the saycheese thing (https://saycheese.hackclub.com/)

## dependencies
- cc65 (http://cc65.org/)
- some commodore 64 emulator (I use vice-jz on linux)
- on ubuntu, both can be installed with apt (`sudo apt install cc65 vice-jz`)

## build and run
- build: `make` which compiles, assembles, and links it with cl65. This makes the `main` file which can be loaded into a c64 emulator
- run: `make run` (probably not how im supposed to do it, but it works) or use your own emulator
    - it runs `vice-jz.x64 -autostart main`
