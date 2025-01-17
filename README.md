# c64-tiny
This is a Commodore 64 program (not sure what it will be yet) for the Hackclub Say Cheese thing (https://saycheese.hackclub.com/)

## Dependencies
- `cc65` (http://cc65.org/)
- Some Commodore 64 emulator (I use `vice-jz` on linux)
- `qrencode` (for generating the qr code, not required)
- On Ubuntu, all of these can be installed with apt (`sudo apt install cc65 vice-jz qrencode`)

## Build and run
- Build: `make` which compiles, assembles, and links it with `cl65`. This makes the `main` file which can be loaded into a c64 emulator
- Run: `make run` (probably not how im supposed to do it, but it works) or use your own emulator
    - It normally runs `vice-jz.x64 -autostart main`
- Generate qr code: `make qr.png`
