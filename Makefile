OUT_FILE := main

CC_FLAGS := -t c64 -O
CA_FLAGS := -t c64
LD_FLAGS := -t c64

all:
	cl65 -O -t c64 main.c

main.s: main.c
	cc65 $(CC_FLAGS) main.c

main.o: main.s
	ca65 $(CA_FLAGS) main.s

main: main.o
	ld65 -o $(OUT_FILE) $(LD_FLAGS) main.o c64.lib
	@stat -c "%s bytes" $(OUT_FILE)

uri:
	echo "data:application/octet-stream;base64,"$$(base64 main -w0) > uri.txt

qr: uri
	qrencode -o qr.png $$(cat uri.txt)

run:
	vice-jz.x64 -autostart $(OUT_FILE)

clean:
	rm main
	rm main.o
	rm main.s
	rm uri.txt
	rm qr.png