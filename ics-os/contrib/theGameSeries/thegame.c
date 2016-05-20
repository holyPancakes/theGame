
#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

#define okay 'z'
#define back 'x'
#define up_key (char)151
#define down_key (char)152
#define left_key (char)150
#define right_key (char)153

#define SKY_BLUE 3
#define GREEN 2
#define YELLOW 54
#define PALE_YELLOW 62
#define ROYAL_BLUE 1
#define DARK_BLUE 8
#define GRAY 56
#define WHITE 63

#define SLOW 10
#define NORMAL 5
#define FAST 3

#define CHARACTERPIXELSIZE 6400
#define TILEPIZELSIZE 1600

typedef struct monster{
	char *name;
	int hp;
	int max_hp;
	int atk;
	int mag;
	int def;
	int agi;
	int crt;
	int cash;
}Monster;

typedef struct player{
	char *name;
	int hp;
	int max_hp;
	int mp;
	int max_mp;
	int atk;
	int mag;
	int def;
	int agi;
	int crt;
	int cash;
}Player;

typedef struct maptile{
	int x;
	int y;
	int type;
	boolean walkable;
}Tile;

typedef struct map{
	Tile tiles[14][6];
}Map;

int mm = 1;//currently in main_menu;
int bm1 = 0;//battle screen menu;
int bm2 = 0;// ability screen menu;

int row, col;
int flip;
char keypress;
Monster jcarter,jackie,piggy,emo,lazertron,glucose,eboy,kekman;
Player me;
Map map1, map2;
int alive = 1;

void writeTextAnimation(char* text, int x, int y, int color, int maxWidth, int size);
void clearArea(int x, int y, int w, int h);
void playGame();
void credits();
void settings();
void quit();
void menu();
void playIntro();

void drawBattleBox(Player x, Monster y);

Player initializeplayer();
Player monsterAttack(Monster y, Player x);
Monster playerAttack(Player y, Monster x);
Monster playerBash(Player y, Monster x);
Monster playerCram(Player y, Monster x);
Player playerExcessiveAbsence(Player y);
Monster playerKek(Player y, Monster x);

Monster initializejcarter(){
	Monster x;
	x.name = "Jay Carter";
	x.hp = 150;
	x.atk = 22;
	x.mag = 10;
	x.def = 23;
	x.agi = 7;
	x.crt = 3;
	return x;
}

Monster initializejackie(){
	Monster x;
	x.name = "Jackie Chan";
	x.hp = 175;
	x.atk = 60;
	x.mag = 38;
	x.def = 25;
	x.agi = 20;
	x.crt = 7;
	x.cash = 2000;
	return x;
}

Monster initializepiggy(){
	Monster x;
	x.name = "Piggy";
	x.hp = 30;
	x.atk = 6;
	x.mag = 0;
	x.def = 3;
	x.agi = 1;
	x.crt = 0;
	x.cash = 35;
	return x;
}
Monster initializeemo(){
	Monster x;
	x.name = "EMO-man";
	x.hp = 999;
	x.atk = 999;
	x.mag = 999;
	x.def = 999;
	x.agi = 999;
	x.crt = 999;
	x.cash = 0;
	return x;
}
Monster initializelazertron(){
	Monster x;
	x.name = "Lazertron";
	x.hp = 50;
	x.atk = 15;
	x.mag = 2;
	x.def = 13;
	x.agi = 7;
	x.crt = 0;
	x.cash = 70;
	return x;
}
Monster initializeglucose(){
	Monster x;
	x.name = "Anemone X-22";
	x.hp = 66;
	x.atk = 2;
	x.mag = 20;
	x.def = 13;
	x.agi = 5;
	x.crt = 0;
	x.cash = 100;
	return x;
}

Monster initializeeboy(){
	Monster x;
	x.name = "Energy Boy";
	x.hp = 10;
	x.atk = 2;
	x.mag = 0;
	x.def = 3;
	x.agi = 1;
	x.crt = 0;
	x.cash = 0;
	return x;
}
Monster initializekekman(){
	Monster x;
	x.name = "The Kekman";
	x.hp = 120;
	x.atk = 20;
	x.mag = 12;
	x.def = 13;
	x.agi = 6;
	x.crt = 3;
	x.cash = 1250;
	return x;
}

Player initializeplayer(){
	Player x;
	x.name = "You";
	x.hp = 50;
	x.mp = 40;
	x.atk = 18;
	x.mag = 15;
	x.def = 12;
	x.agi = 9;
	x.crt = 0;
	x.cash = 0;
	return x;
}


Player monsterAttack(Monster y,Player x){
	int dmg;
	dmg = (y.atk) + (y.mag/2) - (x.def/3);

	if(dmg <= 0){
		dmg = 1;
	}

	x.hp -= dmg;
	printf("%s dealt %d damage!\n", y.name,dmg);
	if(x.hp < 0){
		x.hp = 0;
	}
	return x;
}

Monster playerAttack(Player y, Monster x){
	int dmg;
	dmg = y.atk - (x.def/3);

	if(dmg <= 0){
		dmg = 1;
	}

	x.hp -= dmg;
	printf("%s dealt %d damage!\n", y.name,dmg);
	if(x.hp < 0){
		x.hp = 0;
	}
	return x;
}

Tile initializeTile(int xPos, int yPos){
	Tile newTile;
	newTile.x=xPos;
	newTile.y=yPos;
}

void encounterMonster(Player x, Monster y, int num){
	alive++;
	switch(num){
		case 1: y = initializepiggy(); break;
		case 2: y = initializelazertron(); break;
		case 3: y = initializeglucose(); break;
		case 4: y = initializekekman(); break;
		default: y = initializepiggy();
	}

	if(y.agi > x.agi){
		x = monsterAttack(y,x);
		if(x.hp == 0){
			printf("Game over\n");
			/*GameOver function*/
			alive--;
		}
	}

	while(1){
		/*player choice*/
		y = playerAttack(x,y);
		if(y.hp == 0){
			printf("yas!\n");
			x.cash += y.cash;
			break;
		}
		x = monsterAttack(y,x);
		if(x.hp == 0){
			printf("game over\n");
			alive = 0;
			break;
		}
	}
}

void encounterEmo(Player x, Monster y){
	printf("Emo kills self\n");
	x.cash += 1000;
}

void encounterEboy(Player x, Monster y){
	/* Stuff */
	printf("Eboy restores your MP!\n");
	x.mp += 20;
	if(x.mp < x.max_mp){
		x.mp = x.max_mp;
	}
}

/*Encounter Randomizer*/
int encounterRoll(){
	int randy = rand()%100 + 1;
	return randy;
}

/*Monster Encounter*/
void encountery(int x){
	int num;
	if(x >= 1 && x<= 35){
		num = 1;
		encounterMonster(me,piggy,num);
	}else if(x>40 && x<= 70){
		num = 2;
		encounterMonster(me,glucose,num);
	}else if(x > 70 && x<= 90){
		num = 3;
		encounterMonster(me,lazertron,num);
	}else if(x > 90 && x<= 98){
		encounterEmo(me,emo);
	}else if(x > 35 && x<=40){
		encounterEboy(me,eboy);
	}else{
		num = 4;
		encounterMonster(me,kekman,num);
	}
}

void gameOver(){
	/*ayun*/
}


int main() {
	int x_menu=0,y_menu=0;
	int i=0, textSpeed = NORMAL;
	set_graphics(VGA_320X200X256);
	//clrscr();

	write_text("Press Z to continue",50,100,WHITE,1);
	while(keypress != okay){
		keypress = (char)getch();
	}
	clearArea(0,0,440,220);

	write_text(".the Game",45,130,DARK_BLUE,1);
	write_text("Play",40,150,WHITE,0);
	write_text("Kelp",40,170,WHITE,0);
	write_text("Credits",150,150,WHITE,0);
	write_text("Quit",150,170,WHITE,0);
	write_text(">",30+x_menu*110,150+y_menu*20,WHITE,0);

	do{
		keypress = (char)getch();

		clearArea(30,150,5,30);
		clearArea(140,150,5,30);
		if(mm == 1){
			if(keypress==up_key){
				i = (i+1)%63;
				if(y_menu==1){
					y_menu=0;
				}
			}
			else if(keypress==down_key){
				i = (i-1)%63;
				if(y_menu==0){
					y_menu=1;
				}
			}
			else if(keypress==left_key){
				if(x_menu==1){
					x_menu=0;
				}
			}
			else if(keypress==right_key){
				if(x_menu==0){
					x_menu=1;
				}
			}
			else if(keypress==okay && x_menu==0 && y_menu==0 ){
				mm = 0;
				playGame();
			}
			else if(keypress==okay && x_menu==1 && y_menu==0 ){
				credits();
			}
			else if(keypress==okay && x_menu==0 && y_menu==1 ){
				settings();
			}
			else if(keypress==okay && x_menu==1 && y_menu==1 ){
				quit();
			}
			write_text(">",30+x_menu*110,150+y_menu*20,WHITE,0);
		}

	}while(keypress!='q');


	set_graphics(VGA_TEXT80X25X16);
	clrscr();
	return 0;
}

void writeTextAnimation(char* text, int x, int y, int color, int maxWidth, int size){
	char sub[256];
	int i;
	for ( i = 0 ; i < strlen(text)+1 ; i++) {
		memset( sub, '\0', sizeof(sub) );
		memcpy( sub, &text[(i/maxWidth)*maxWidth], i%maxWidth );
		sub[strlen(text)%maxWidth] = '\0';
		write_text(sub,x,y+(i/maxWidth)*10,WHITE,size);
		delay(1);
		//if(i%maxWidth == (maxWidth-1)){
        //    write_text(">",45+maxWidth, 80 , WHITE, 0);
        //    getch();
        //    clearArea(0,0,440,220);
		//}
	}
}

void playGame(){
	clearArea(0,0,440,220);
	//playIntro();
	//writeTextAnimation("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", 20, 5, WHITE, 30, 0);
	//Insert Intro here
	//map1 here
	drawBattleBox(me,piggy);
	delay(10);
	//map2 here
	//credits();
}

void credits(){
	//Insert Intro here
	clearArea(0,0,440,220);
	writeTextAnimation("The Game \n Project",20,20,DARK_BLUE,28,1);
	delay(SLOW*10);
	writeTextAnimation("Created by:",30,45,WHITE,29,0);
	writeTextAnimation("Maru Baul and Aron Vibar",30,55,WHITE,30,0);
	clearArea(0,0,440,220);
	keypress = 'q';
}

void settings(){
	//Insert Intro here
	write_text("Z - Confirm",30,35,WHITE,1);
	write_text("x - Back",30,55,WHITE,1);
	write_text("Arrow Keys - Movement",30,75,WHITE,1);
	write_text("Q - Quit Game",30,95,WHITE,1);
}

void quit(){
	clearArea(0,0,440,220);
	write_text("Bye.",140,180,WHITE,1);
	keypress = 'q';
}

void clearArea(int x, int y, int w, int h) {
   int i,j;
   for ( i = y ; i <= (y+h) ; i++ ) {
      for (j=x;j<=(x+w);j++){
         write_pixel(j,i,0x0000);
      }
   }
}

void playIntro(){
    char* title = "THE GAME \n PROJECT";

    writeTextAnimation("One day, in the year XX16",30,45,WHITE,29,0);
    delay(NORMAL);
    writeTextAnimation("In a galaxy not really far away",30,55,WHITE,40,0);
    clearArea(0,0,440,220);
    writeTextAnimation("You'll finally finish",30,45,WHITE,49,0);
	delay(NORMAL);
    writeTextAnimation("Your game project in CMSC 125",30,55,WHITE,30,0);
    delay(NORMAL);
    clearArea(0,0,440,220);
    writeTextAnimation("But then a portal opened",30,55,WHITE,30,0);
    delay(NORMAL);
    clearArea(0,0,440,220);
    writeTextAnimation("And you got into a world",30,45,WHITE,35,0);
    delay(NORMAL);
    writeTextAnimation("where random people show up",30,55,WHITE,30,0);
    delay(NORMAL);
    clearArea(0,0,440,220);
    writeTextAnimation("You must now go home",30,45,WHITE,35,0);
    delay(NORMAL);
    writeTextAnimation("with the help of Jackie Chan",30,55,WHITE,30,0);
    delay(NORMAL);
    clearArea(0,0,440,220);
    writeTextAnimation("And finish...",30,45,WHITE,29,0);
    delay(NORMAL);
    clearArea(0,0,440,220);
    delay(NORMAL);
    writeTextAnimation(title,40,50,DARK_BLUE,28,1);
    clearArea(0,0,440,220);
}

void drawBattleBox(Player x, Monster y){
	int i,j;

	x = initializeplayer();
	y = initializepiggy();

	write_text(x.name,25,110,WHITE,0);
	write_text("HP: ",40,120,WHITE,0); //HP VALUE AT 42  "/MAXHP" GOES AT +25
	write_text("MP: ",40,131,WHITE,0); //SAME DITO

	write_text(y.name,175,110,WHITE,0);
	write_text("HP: ",190,125,WHITE,0);

	for(i=145;i<219;i++){
		for(j=1;j<320;j++){
			if(i == 145 || j == 1 || i == 199 || j == 218 || j == 319){
				write_pixel(j,i,WHITE);
			}

		}
	}

	for(i = 5 ; i<=40;i++){
		for(j=1;j<320;j++){
			if(i == 5 || i == 40 || j == 1 || j == 319){
				write_pixel(j,i,WHITE);
			}
		}
	}

	write_text("FIGHT",248,155,WHITE,0);
	write_text("ITEM", 248,175,WHITE,0);
}
