# c64-tiny
This is a Commodore 64 program (not sure what it will be yet) for the Hackclub Say Cheese thing (https://saycheese.hackclub.com/)

## Resources
- New cc65 documentation (https://cc65.github.io/doc/)
- C64 emulator online (https://stigc.dk/c64/basic/)
- C64 KERNAL API (https://www.pagetable.com/c64ref/kernal/)
- 6502 Instruction set (https://www.masswerk.at/6502/6502_instruction_set.html)

## Dependencies
- `cc65` (http://cc65.org/ or https://cc65.github.io/)
- Some Commodore 64 emulator (I use `vice-jz` on linux)
- `qrencode` (for generating the qr code, not required)
- On Ubuntu, all of these can be installed with apt (`sudo apt install cc65 vice-jz qrencode`)

## Build and run
- Build: `make` which compiles, assembles, and links it with `cl65`. This makes the `main` file which can be loaded into a c64 emulator
- Run: `make run` (probably not how im supposed to do it, but it works) or use your own emulator
    - It normally runs `vice-jz.x64 -autostart main`
- Generate qr code: `make qr.png`
