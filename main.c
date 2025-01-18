
typedef unsigned char byte;

#define POKE(addr,value) *(byte*) addr = value;
#define PEEK(addr) (*(byte*)(addr))

// convert direction into change in x
#define DIR2DX(dir) (dir&1 ? (dir==1 ? 1 : -1) : 0)
// convert direction into change in y
#define DIR2DY(dir) (dir&1 ? 0 : (dir==0 ? -1 : 1))

#define BG_CHAR 0xe9

// byte DIR2OPPOSITE[] = {2,3,0,1};

#define XY2ADDR(x,y) (0x400+x+y*40)
// int XY2ADDR(char x, char y) {
// 	return (0x400+x+y*40);
// }

// Old title:
// char tronText1[] = "#####  ###    ###   #  #     #  # ";
// char tronText2[] = "  #    #  #  #   #  ## #          ";
// char tronText3[] = "  #    ###   #   #  # ##    #    #";
// char tronText4[] = "  #    #  #   ###   #  #     #### ";
// New title
// char tronText1[] = "### # ##  # #  ### ##   #  ##   # ";
// char tronText2[] = " #  # # # # #   #  # # # # # #  # ";
// char tronText3[] = " #  # # #  #    #  ##  # # # #    ";
// char tronText4[] = " #  # # #  #    #  # #  #  # #  # ";

void printChar(byte x, byte y, char c) {
	POKE(XY2ADDR(x,y),c);
}

// void printBinary(byte x, byte y, int n, byte bits) {
// 	byte i;
// 	for (i=0;i<bits;++i) {
// 		byte value = (n>>i)&1;
// 		printChar(x-i+bits-1,y,value?'1':'0');
// 	}
// }
void printDecimal(byte x, byte y, int n, byte digits) {
	byte i;
	for (i=digits;i--;) {
		int value = n%10;
		printChar(x+i,y,'0'+value);
		n/=10;
	}
}
void printString(char* str, byte x, byte y) {
	byte i=-1;
	while (str[++i]) {
		printChar(x+i,y,str[i]);
		// ++i;
	}
}
void fillScreen(char c) {
	int n=0x400;
	while (n<0x400+40*25) {
		POKE(n,c);
		// if (w) wait(w);
		++n;
	}
}
#define clearScreen() fillScreen(' ')

void sayPrintSpace() {
	printString("press space",(40-11)/2,10);
}

char key;
byte gameState=3; // 0=playing, 1=player 1 won, 2=player 2 won, 3=main menu
// int gameTime=0;


typedef struct Player {
	byte id;
	byte x;
	byte y;
	byte d; // direction, 0=up, 1=right, 2=down, 3=left
	char c; // player's onscreen character
	// byte test; // unused maybe (for testing)
	byte input[10]; // input queue
	byte inputSize; // current input queue size
	byte score;
} Player;

void playerAddInput(Player* p, byte d) {
	// if (DIR2OPPOSITE[d]==p->d) return;
	p->input[p->inputSize] = d;
	++p->inputSize;
}
void playerProcessInput(Player* p) {
	byte d;
	byte i;
	if (p->inputSize == 0) return;
	d=p->input[p->inputSize-1]; // get direction
	--p->inputSize;
	// now move queue back
	for (i=0;i<p->inputSize;++i) {
		p->input[i]=p->input[i+1];
	}

	p->d = d; // set player direction
}
void updatePlayer(Player* p) {
	// char c;
	playerProcessInput(p);
	p->x += DIR2DX(p->d);
	p->y += DIR2DY(p->d);
	// c = ; // test screen for what character is there
	if (PEEK(XY2ADDR(p->x,p->y)) != BG_CHAR || p->x>=40 || p->y>=25) { // if the next position isnt blank or the player is OOB, the player loses
		gameState=p->id ? 1 : 2;
		--p->score;
		// clearScreen();
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

void resetGame() {
	p1.id=0;
	p1.x=4;
	p1.y=4;
	p1.d=2; // down
	p1.c=0xa0;

	p2.id=1;
	p2.x=40-4;
	p2.y=25-4;
	p2.d=0; // up
	p2.c=0x20;
	fillScreen(BG_CHAR);
}

void onMainMenu() {
	int i;
	// clearScreen();
	// for (i=0;i<40-2;++i) {
	// 	printChar(i+1,8,0xa0);
	// 	printChar(i+1,1,0xa0);
	// }
	// printString(tronText1,3,3);
	// printString(tronText2,3,4);
	// printString(tronText3,3,5);
	// printString(tronText4,3,6);
	// printString("tron!",1,1);
	sayPrintSpace();
	// printString("player 1",4,13);
	// printString("player 2",40-8-4,13);
	// printString("w/a/s/d",4,14);
	// printString("i/j/k/l",40-8-4,14);
	while (1) {
		getKey();
		if (key==' ') break;
	}
	gameState = 0;
	resetGame();
}

void gameTick() {
	getKey();
	while (key) { // repeat until system queue is empty
		byte d;
		switch (key) {
			case 'w':
				d=0;
				goto P1;
			case 'd':
				d=1;
				goto P1;
			case 's':
				d=2;
				goto P1;
			case 'a':
				d=3;
				goto P1;
			case 'i':
				d=0;
				goto P2;
			case 'l':
				d=1;
				goto P2;
			case 'k':
				d=2;
				goto P2;
			case 'j':
				d=3;
				goto P2;
		}
		goto end;
		P1:
		playerAddInput(&p1,d);
		goto end;
		P2:
		playerAddInput(&p2,d);
		end:
		getKey();
	}
	
	updatePlayer(&p1);
	updatePlayer(&p2);

	// printBinary(0,0,p1.inputSize,8);
	// printBinary(0,1,p2.inputSize,8);
	// printChar(0,2,p1.test);
	// ++gameTime;
}

void onLose() {
	++p1.score;
	++p2.score;
	clearScreen();
	printString("game over!",(40-10)/2,1);
	printString("winner p#",1,3);
	printChar(9,3,gameState == 1 ? '1' : '2');
	printDecimal(22,3,p1.score,3);
	printDecimal(29,3,p2.score,3);

	sayPrintSpace();

	while (1) {
		getKey();
		if (key==' ') { // wait for space key
			break;
		}
	}
	resetGame();
	gameState=0;
}

int main() {
	// int frame;
	clearScreen();
	onMainMenu();
	while (1) {
		int n=2500;
		while (n) --n;
		// keyboard input
		
		// if (gameState == 3) {
		// 	onMainMenu();
		// } else if (gameState == 0) {
		// 	gameTick();
		// } else if (gameState==1 || gameState == 2) {
		// 	onLose();
		// }
		if (gameState) onLose();
		else gameTick();

		// ++frame;
	}
	return 0;
}
