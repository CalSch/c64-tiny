all:
	cl65 -O -t c64 main.c

run:
	vice-jz.x64 -autostart main
