
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

int row, col;
int flip;

void writeTextAnimation(char* text, int x, int y, int color, int maxWidth, int size);
void clearArea(int x, int y, int w, int h);
void playGame();
void credits();
void settings();
void quit();


int main() {
	int x_menu=0,y_menu=0;
	char keypress;
	int i=0, textSpeed = NORMAL;
	set_graphics(VGA_320X200X256);
	//clrscr();

	write_text(".the Game",45,130,DARK_BLUE,1);
	write_text("Play",40,150,WHITE,0);
	write_text("Settings",40,170,WHITE,0);
	write_text("Credits",150,150,WHITE,0);
	write_text("Quit",150,170,WHITE,0);
	write_text(">",30+x_menu*110,150+y_menu*20,WHITE,0);

	do{
		keypress = (char)getch();
		//char* text = "In the year 2016, a man named _____";


		clearArea(30,150,5,30);
		clearArea(140,150,5,30);

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
			playGame();
		}
		else if(keypress==okay && x_menu==0 && y_menu==1 ){
			credits();
		}
		else if(keypress==okay && x_menu==0 && y_menu==0 ){
			settings();
		}
		else if(keypress==okay && x_menu==0 && y_menu==0 ){
			quit();
		}
		write_text(">",30+x_menu*110,150+y_menu*20,WHITE,0);
	}while(keypress!='q');


	set_graphics(VGA_TEXT80X25X16);
	clrscr();
	return 0;
}

void writeTextAnimation(char* text, int x, int y, int color, int maxWidth, int size){
	char sub[256];
	int i;
	for ( i = 0 ; i < strlen(text) ; i++) {
		memset( sub, '\0', sizeof(sub) );
		memcpy( sub, &text[(i/maxWidth)*maxWidth], i%maxWidth );
		sub[strlen(text)%maxWidth] = '\0';
		write_text(sub,45,50+(i/maxWidth)*10,WHITE,size);
		delay(5);
		//if(i%maxWidth == (maxWidth-1)){
        //    write_text(">",45+maxWidth, 80 , WHITE, 0);
        //    getch();
        //    clearArea(0,0,440,220);        
		//}
	}
}

void playGame(){
	clearArea(0,0,440,220);
	writeTextAnimation("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", 20, 5, WHITE, 30, 0);
	//Insert Intro here
}

void credits(){
	//Insert Intro here
}

void settings(){
	//Insert Intro here
}

void quit(){
	//Insert Intro here
}

void clearArea(int x, int y, int w, int h) {
   int i,j;
   for ( i = y ; i <= (y+h) ; i++ ) {
      for (j=x;j<=(x+w);j++){
         write_pixel(j,i,0x0000);
      }
   }
}
