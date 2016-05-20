
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
	char *message;
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
	int pot;
}Player;

int mm = 1;//currently in main_menu;
int bm1 = 0;//battle screen menu;
int bm2 = 0;// ability screen menu;
int sm = 0;//shop screen menu;

int succ = 0; //successful skill

int row, col;
int flip;
char keypress;
Monster jcarter,jackie,piggy,emo,lazertron,glucose,eboy,kekman;
Player me;
int alive = 1;
int boss_turn = 0;

void writeTextAnimation(char* text, int x, int y, int color, int maxWidth, int size);
void clearArea(int x, int y, int w, int h);
void playGame();
void credits();
void settings();
void quit();
void menu();
void playIntro();

Player drawBattleBox(Player x, Monster y);
void gameOver();

Player initializeplayer();
Player monsterAttack(Monster y, Player x);
Monster playerAttack(Player y, Monster x);
Monster playerBash(Player y, Monster x);
Monster playerCram(Player y, Monster x);
Player playerExcessiveAbsence(Player y);
Monster playerKek(Player y, Monster x);

Player manaDown(Player x, int cost){
	x.mp -= cost;
	succ = 0;
	return x;
}

Player getCash(Player x, int rew){
	x.cash += rew;
	return x;
}

Player levelUp(Player x){
	x.max_hp += 150;
	x.max_mp += 80;
	x.hp = x.max_hp;
	x.mp = x.max_mp;
	x.atk += 12;
	x.mag += 8;
	x.def += 9;
	x.agi += 13;
	x.crt += 3;
	return x;
}

Monster initializejcarter(){
	Monster x;
	x.name = "Jay Carter";
	x.hp = 150;
	x.atk = 22;
	x.mag = 10;
	x.def = 23;
	x.agi = 7;
	x.crt = 3;
	x.message = "Jay Carter boxes in!";
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
	x.message = "You have been betrayed!";
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
	x.message = "Piggy struts in!";
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
	x.message = ". . .";
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
	x.message = "Lazertron, tinkering about!";
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
	x.message = "You feel the sweet air!";
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
	x.message = "You feel energized!";
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
	x.message = "KEK!";
	return x;
}

Player initializeplayer(){
	Player x;
	x.name = "You";
	x.hp = 999;
	x.max_hp = 999;
	x.mp = 120;
	x.max_mp = 120;
	x.atk = 28;
	x.mag = 15;
	x.def = 12;
	x.agi = 9;
	x.crt = 0;
	x.cash = 0;
	x.pot = 5;
	return x;
}

void updateStatusbar(char *message){
	clearArea(15,15,300,20);
	writeTextAnimation(message,15,15,WHITE,50,2);
}

Player monsterAttack(Monster y,Player x){
	int dmg;
	dmg = (y.atk) + (y.mag/2) - (x.def/3);

	if(dmg <= 0){
		dmg = 1;
	}

	x.hp -= dmg;
	updateStatusbar("Your opponent attacks!");
	if(x.hp < 0){
		x.hp = 0;
	}
	return x;
}

Player encounterMonster(Player x, Monster y, int num){
	switch(num){
		case 1: y = initializepiggy(); break;
		case 2: y = initializelazertron(); break;
		case 3: y = initializeglucose(); break;
		case 4: y = initializekekman(); break;
		default: return;
	}

	x = drawBattleBox(x,y);
	return x;
}

Player encounterEmo(Player x, Monster y){
	clearArea(0,0,440,220);
	/*draw emo*/
	writeTextAnimation(y.message,15,15,WHITE,30,0);
	delay(SLOW*2);
	clearArea(0,0,440,220);
	writeTextAnimation("You recieve 1000 CASH!",15,15,WHITE,40,0);
	clearArea(0,0,440,220);
	x.cash += 1000;
	return x;
}

Player encounterEboy(Player x, Monster y){
	clearArea(0,0,440,220);
	/*draw emo*/
	writeTextAnimation(y.message,15,15,WHITE,30,0);
	delay(SLOW*2);
	clearArea(0,0,440,220);
	writeTextAnimation("MP FULLY REPLENISHED",15,15,WHITE,40,0);
	clearArea(0,0,440,220);
	x.mp = x.max_mp;
	return x;
}

Player encounterJCarter(Player x, Monster y, Monster z){
	y = initializejcarter();
	z = initializejackie();

	x = drawBattleBox(x,y);

	clearArea(0,0,440,220);
	writeTextAnimation("The portal is near..,",30,30,WHITE,40,0);
	delay(SLOW);
	clearArea(0,0,440,220);
	writeTextAnimation("But . . .",30,30,WHITE,40,0);
	clearArea(0,0,440,220);
	x = drawBattleBox(x,z);
	return x;
}

/*Encounter Randomizer*/
int encounterRoll(){
	int randy = rand() % 150 + 1;
	return randy;
}

/*Monster Encounter*/
void encountery(int x){
	int num = 0;
	if(x >= 1 && x<= 45){
		num = 1;
		encounterMonster(me,piggy,num);
	}else if(x>45 && x<= 60){
		num = 2;
		encounterMonster(me,glucose,num);
	}else if(x > 60 && x<= 90){
		num = 3;
		encounterMonster(me,lazertron,num);
	}else if(x > 90 && x<= 98){
		encounterEmo(me,emo);
	}else if(x > 35 && x<=40){
		encounterEboy(me,eboy);
	}else if (x == 100){
		num = 4;
		encounterMonster(me,kekman,num);
	}
}


Player playerPotion(Player x){
	x.pot -= 1;
	updateStatusbar("You recovered 50 HP/MP!");
	x.hp += 50;
	x.mp += 50;
	if(x.hp > x.max_hp){
		x.hp = x.max_hp;
	}

	if(x.mp > x.max_mp){
		x.mp = x.max_mp;
	}

	return x;
}

void drawStatus(Player a, Monster b){
	/*INTEGER TO STRING PLEASE*/
	char str[10];

	clearArea(69,120,40,20);
	clearArea(219,125,40,17);
	clearArea(226,285,7,7);

	sprintf(str,"%d",a.hp);
	write_text(str,69,120,WHITE,0);
	write_text("/",92,120,WHITE,0);
	sprintf(str,"%d",a.max_hp);
	write_text(str,100,120,WHITE,0);

	sprintf(str,"%d",a.mp);
	write_text(str,69,129,WHITE,0);
	write_text("/",92,129,WHITE,0);
	sprintf(str,"%d",a.max_mp);
	write_text(str,100,129,WHITE,0);

	sprintf(str,"%d",b.hp);
	write_text(str,219,125,WHITE,0);

	sprintf(str,"%d",a.pot);
	write_text(str,236,200,WHITE,0);
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
	int g;
	int num;
	clearArea(0,0,440,220);
	playIntro();
	clearArea(0,0,440,220);
	me = initializeplayer();
	num = 1;
	encounterMonster(me,piggy,num);
	num = 2;
	encounterMonster(me,glucose,num);
	encounterEboy(me,eboy);
	num = 3;
	encounterMonster(me,lazertron,num);
	encounterEmo(me,emo);
	num = 4;
	encounterMonster(me,kekman,num);
	me = encounterJCarter(me,jcarter,jackie);
	credits();
}

void credits(){
	//Insert Intro here
	clearArea(0,0,440,220);
	writeTextAnimation("The Game \n Project",20,20,DARK_BLUE,28,1);
	delay(SLOW*10);
	writeTextAnimation("Created by:",30,45,WHITE,29,0);
	writeTextAnimation("Maru Baul and Aron Vibar",30,55,WHITE,30,0);
	clearArea(0,0,440,220);
	keypress = 'a';
	mm = 1;
	main();
}

void settings(){
	//Insert Intro here
	write_text("Z - Confirm",30,35,WHITE,1);
	write_text("X - Back",30,55,WHITE,1);
	write_text("Arrow Keys - Movement",30,75,WHITE,1);
	write_text("Q - Quit Game",30,95,WHITE,1);
}

void quit(){
	clearArea(0,0,440,220);
	write_text("Bye.",140,100,WHITE,1);
	delay(NORMAL);
	clearArea(0,0,440,220);
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

Player drawBattleBox(Player x, Monster y){
	int i,j;
	int num = 0;
	int xmen;
	int ymen;
	x = initializeplayer();
	bm1 = 1;

	write_text(x.name,25,110,WHITE,0);
	write_text("HP: ",40,120,WHITE,0); //HP VALUE AT 42  "/MAXHP" GOES AT +25
	write_text("MP: ",40,131,WHITE,0); //SAME DITO
	drawStatus(x,y);
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
	write_text("POTION", 248,175,WHITE,0);
	

	write_text("BASH     ",20,155,WHITE,3);
	write_text("EXAB 69MP",20,175,WHITE,3);
	write_text("CRAM 50MP",110,155,WHITE,3);
	write_text("KEK 100MP",110,175,WHITE,3);

	updateStatusbar(y.message);

	if(y.agi > x.agi){
		x = monsterAttack(y,x);
		delay(SLOW);
		drawStatus(x,y);
	}

	if(x.hp == 0){
		updateStatusbar("YOU DIED");
		delay(SLOW);
		bm1 = 0;
		gameOver();
	}

	while(1){
		here:;
		xmen = 0;
		ymen = 0;
		write_text(">",238,155,WHITE,0);
		while(bm1 == 1){
			keypress = (char)getch();
			if(keypress == up_key){
				clearArea(238,175,6,6);
				write_text(">",238,155,WHITE,0);
				num = 0;
			}else if(keypress == down_key){
				clearArea(238,155,6,6);
				write_text(">",238,175,WHITE,0);
				num = 1;
			}else if(keypress == okay){
				if(num == 0){
					bm1 = 0;
					bm2 = 1;	
				}else{
					if(x.pot <= 0){
						updateStatusbar("NO POTIONS!");
					}else{
						x = playerPotion(x);
						clearArea(238,175,6,6);
						drawStatus(x,y);
						keypress = 'a';
						num = 0;
						bm1 = 0;
						goto next;
					}
				}
				
			}
		}
		write_text(">",10,155,WHITE,0);
		heya:;
		while(bm2 == 1){
			keypress = (char)getch();
			if(keypress == up_key && xmen == 0){
				clearArea(10,175,6,6);
				clearArea(100,155,6,6);
				clearArea(100,175,6,6);
				write_text(">",10,155,WHITE,0);
				ymen = 0;
			}else if(keypress == up_key && xmen == 1){
				clearArea(10,175,6,6);
				clearArea(100,175,6,6);
				clearArea(10,155,6,6);
				write_text(">",100,155,WHITE,0);
				ymen = 0;
			}else if(keypress == down_key && xmen == 0){
				clearArea(10,155,6,6);
				clearArea(100,155,6,6);
				clearArea(100,175,6,6);
				write_text(">",10,175,WHITE,0);
				ymen = 1;
			}else if(keypress == down_key && xmen == 1){
				clearArea(10,155,6,6);
				clearArea(10,175,6,6);
				clearArea(100,155,6,6);
				write_text(">",100,175,WHITE,0);
				ymen = 1;
			}else if(keypress == left_key && ymen == 0){
				clearArea(10,175,6,6);
				clearArea(100,155,6,6);
				clearArea(100,175,6,6);
				write_text(">",10,155,WHITE,0);
				xmen = 0;
			}else if(keypress == left_key && ymen == 1){
				clearArea(10,155,6,6);
				clearArea(100,155,6,6);
				clearArea(100,175,6,6);
				write_text(">",10,175,WHITE,0);
				xmen = 0;
			}else if(keypress == right_key && ymen == 0){
				clearArea(10,155,6,6);
				clearArea(10,175,6,6);
				clearArea(100,175,6,6);
				write_text(">",100,155,WHITE,0);
				xmen = 1;
			}else if(keypress == right_key && ymen == 1){
				clearArea(10,155,6,6);
				clearArea(10,175,6,6);
				clearArea(100,155,6,6);
				write_text(">",100,175,WHITE,0);
				xmen = 1;
			}else if(keypress == okay){
				if(xmen == 0 && ymen == 0){
					y = playerBash(x,y);
					if(succ == 1){
						updateStatusbar("You Used BASH!");
					}
					clearArea(238,155,6,6);
					clearArea(10,155,6,6);
					clearArea(10,175,6,6);
					clearArea(100,155,6,6);
					clearArea(100,175,6,6);
					if(y.hp == 0){
						drawStatus(x,y);
						updateStatusbar("Your opponent died");
						delay(NORMAL);
						clearArea(0,0,440,220);
						bm2 = 0;
						keypress = 'a';
						x = getCash(x,y.cash);
						return x;
					}
					keypress = 'a';
					bm2 = 0;
				}else if(xmen == 1 && ymen == 0){
					y = playerCram(x,y);
					if(succ == 1){
						updateStatusbar("You Used CRAM!");
						x = manaDown(x,50);
					}else{
						bm2 = 0,
						bm1 = 1;
						goto heya;
					}
					clearArea(238,155,6,6);
					clearArea(10,155,6,6);
					clearArea(10,175,6,6);
					clearArea(100,155,6,6);
					clearArea(100,175,6,6);
					if(y.hp == 0){
						drawStatus(x,y);
						updateStatusbar("Your opponent died");
						delay(NORMAL);
						clearArea(0,0,440,220);
						bm2 = 0;
						keypress = 'a';
						x = getCash(x,y.cash);
						return x;
					}
					keypress = 'a';
					bm2 = 0;
				}else if(xmen == 0 && ymen == 1){
					x = playerExcessiveAbsence(x);
					if(succ == 1){
						updateStatusbar("You Recovered 50 percent HP!");
						x = manaDown(x,69);
					}
					clearArea(238,155,6,6);
					clearArea(10,155,6,6);
					clearArea(10,175,6,6);
					clearArea(100,155,6,6);
					clearArea(100,175,6,6);
					bm2 = 0;
					keypress = 'a';
				}else if(xmen == 1 && ymen == 1){
					y = playerKek(x,y);
					if(succ == 1){
						updateStatusbar("You Used KEK!");
						x = manaDown(x,100);
					}
					clearArea(238,155,6,6);
					clearArea(10,155,6,6);
					clearArea(10,175,6,6);
					clearArea(100,155,6,6);
					clearArea(100,175,6,6);
					if(y.hp == 0){
						drawStatus(x,y);
						updateStatusbar("Your opponent died");
						delay(NORMAL);
						clearArea(0,0,440,220);
						bm2 = 0;
						keypress = 'a';
						x = getCash(x,y.cash);
						return x;
					}
					keypress = 'a';
					bm2 = 0;
				}
			}else if(keypress == back){
				bm2 = 0;
				clearArea(10,155,6,6);
				clearArea(10,175,6,6);
				clearArea(100,155,6,6);
				clearArea(100,175,6,6);
				bm1 = 1;
				goto here;
			}
		}
		drawStatus(x,y);
		next:;
		delay(SLOW*3);
		x = monsterAttack(y,x);
		if(x.hp == 0){
			drawStatus(x,y);
			updateStatusbar("YOU DIED");
			gameOver();
		}
		bm1 = 1;
		drawStatus(x,y);
	}

	
}

Monster playerBash(Player y, Monster x){
	int dmg;

	dmg = (y.atk/2) + (y.mag/3) - (x.def/3);

	if(dmg <= 0){
		dmg = 1;
	}

	x.hp -= dmg;
	if(x.hp < 0){
		x.hp = 0;
	}

	succ = 1;

	return x;
}

Monster playerCram(Player y, Monster x){
	int dmg;
	if(y.mp < 50){
		updateStatusbar("Insufficient MP!");
		return x;
	}
	dmg = y.mag;
	if(dmg <= 0){
		dmg = 1;
	}
	x.hp -= dmg;
	if(x.hp < 0){
		x.hp = 0;
	}
	succ = 1;
	return x;
}

Player playerExcessiveAbsence(Player y){
	if(y.mp < 69){
		updateStatusbar("Insufficient MP!");
		return y;
	}

	updateStatusbar("You Used EXCESSIVE ABSENCES!");
	y.hp += (y.max_hp/2);
	if(y.hp > y.max_hp){
		y.hp = y.max_hp;
	}
	succ = 1;
	return y;
}

Monster playerKek(Player y, Monster x){
	int dmg;
	if(y.mp < 100){
		updateStatusbar("Insufficient MP!");
		return x;
	}
	dmg = y.mag + (2 * y.atk);
	if(dmg <= 0){
		dmg = 1;
	}
	x.hp -= dmg;
	if(x.hp < 0){
		x.hp = 0;
	}
	succ = 1;
	return x;
}

void gameOver(){
	clearArea(0,0,440,220);
	writeTextAnimation("GAME OVER",150,150,WHITE,30,2);
	mm = 1;
	bm1 = 0;
	bm2 = 0;
	keypress = 'a';
	main();
}