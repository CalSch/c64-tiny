# c64-tiny (Tiny Tron!)
This is Tron for the Commodore 64 made for the Hackclub Say Cheese thing (https://saycheese.hackclub.com/) where you make a game/program that fits in a QR code.

## The QR Code
~~it will be here soon~~ It's here!  
![qr](https://github.com/user-attachments/assets/be54cd46-e6c9-4fec-9330-21ca81c5c8f4)


## How to play
1. Scan the QR code and put the data into a file
2. Load that file as a disk into a Commodore 64 emulator
3. Have fun

## Features
- The game (duh)
- Two players (no one player mode)
- A main menu with a cool title
- Score

## Resources
- New cc65 documentation (https://cc65.github.io/doc/)
- C64 emulator online (https://stigc.dk/c64/basic/)
- C64 KERNAL API (https://www.pagetable.com/c64ref/kernal/)
- 6502 Instruction set (https://www.masswerk.at/6502/6502_instruction_set.html)
- C64 character codes (https://sta.c64.org/cbm64scr.html)

## Dependencies
- `cc65` (http://cc65.org/ or https://cc65.github.io/)
- Some Commodore 64 emulator (I use `vice-jz` on linux)
- `qrencode` (for generating the qr code, not required)
- On Ubuntu, all of these can be installed with apt (`sudo apt install cc65 vice-jz qrencode`)

## Build and run
- Build: `make` which compiles, assembles, and links it with `cl65`. This makes the `main` file which can be loaded into a c64 emulator
    - Run `make main` to do it step-by-step if you want
- Run: `make run` (probably not how im supposed to do it, but it works) or use your own emulator
    - It normally runs `vice-jz.x64 -autostart main`
- Generate qr code: `make qr.png`
- Run `make clean` to remove generated files
