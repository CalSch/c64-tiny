
#define POKE(addr,value) *(unsigned char*) addr = value;
#define PEEK(addr) (*(unsigned char*)(addr))

// convert direction into change in x
#define DIR2DX(dir) (dir&1 ? (dir==1 ? 1 : -1) : 0)
// convert direction into change in y
#define DIR2DY(dir) (dir&1 ? 0 : (dir==0 ? -1 : 1))

int DIR2OPPOSITE[] = {2,3,0,1};

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
		POKE(n,' ');
		++n;
	}
}

void wait(int n) {
	while (n) --n;
}


int key;
int gameState=0; // 0=playing, 1=player 1 won, 2=player 2 won
int gameTime=0;


typedef struct Player {
	int id;
	int x;
	int y;
	int d; // direction, 0=up, 1=right, 2=down, 3=left
	char c; // player's onscreen character
	int test; // unused maybe (for testing)
	char input[10]; // input queue
	int inputSize; // current input queue size
} Player;

void playerAddInput(Player* p, int d) {
	p->input[p->inputSize] = d;
	++p->inputSize;
}
void playerProcessInput(Player* p) {
	int d;
	int i=0;
	if (p->inputSize == 0) return;
	d=p->input[p->inputSize-1]; // get direction
	--p->inputSize;
	// now move queue back
	for (i=0;i<p->inputSize;i++) {
		p->input[i]=p->input[i+1];
	}

	p->d = d; // set player direction
}
void updatePlayer(Player* p) {
	char c;
	playerProcessInput(p);
	p->x += DIR2DX(p->d);
	p->y += DIR2DY(p->d);
	c = PEEK(0x400 + p->x + p->y*40); // test screen for what character is there
	if (c != ' ') { // if the next position isnt blank, the player loses
		gameState=p->id ? 1 : 2;
		return;
	}
	printChar(p->x,p->y,p->c); // draw player
}

void getKey() {
	__asm__("jsr $ffe4"); // run a kernal routine to take a key off of the system queue (not the player queue), the key is stored in A
	__asm__("sta %v",key); // load A (the key) into `key`
}

Player p1;
Player p2;

int main() {
	int frame;
	p1.id=0;
	p1.x=4;
	p1.y=4;
	p1.d=2; // down
	p1.c='1';

	p2.id=1;
	p2.x=40-4;
	p2.y=25-4;
	p2.d=0; // up
	p2.c='2';
	clearScreen();

	while (1) {
		wait(3000);
		// keyboard input
		getKey();
		while (key) { // repeat until system queue is empty
			switch (key) {
				case 'w':
					playerAddInput(&p1,0);
					break;
				case 'd':
					playerAddInput(&p1,1);
					break;
				case 's':
					playerAddInput(&p1,2);
					break;
				case 'a':
					playerAddInput(&p1,3);
					break;
				case 'i':
					playerAddInput(&p2,0);
					break;
				case 'l':
					playerAddInput(&p2,1);
					break;
				case 'k':
					playerAddInput(&p2,2);
					break;
				case 'j':
					playerAddInput(&p2,3);
					break;
			}
			getKey();
		}
		
		if (gameState == 0) {
			updatePlayer(&p1);
			updatePlayer(&p2);

			printBinary(0,0,p1.inputSize,8);
			printBinary(0,1,p2.inputSize,8);
			// printChar(0,2,p1.test);
			++gameTime;
		} else {
			clearScreen();
			printChar(0,0,'l');
			printChar(0,1,gameState == 1 ? '1' : '2');
			printBinary(0,2,gameTime,8);
		}

		++frame;
	}
	return 0;
}
