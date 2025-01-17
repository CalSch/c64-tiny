void poke(int addr,int value) {
	*(unsigned char*) addr = value;
}
void printChar(int x,int y, char c) {
	int addr = 0x400 + x + y * 40;
	*(unsigned char*) addr = c;
}

void printBinary(int x,int y,int n,int bits) {
	int i;
	for (i=0;i<bits;++i) {
		int value = (n>>i)&1;
		printChar(x-i+bits-1,y,value?'1':'0');
	}
}
void clearScreen() {
	int n=0x400;
	while (n<0x400+40*25) {
		
		++n;
	}
}

int main() {
	int n;
	*(unsigned char*) 0x400 = 0x5E;
	printBinary(0,1,10,8);

	while (1) {
		int w=2000;
		while (w)
			--w;
		*(unsigned char*) 0x401 = n;
		// printBinary(0,2,
		++n;
	}
	return 0;
}
