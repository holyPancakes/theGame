
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

void clearArea(int x, int y, int w, int h);

int main() {
	int x_menu=0,y_menu=0;
	char keypress;
	int i=0, textSpeed = NORMAL;
	set_graphics(VGA_320X200X256);
	//erase(1,1,770,220);

	write_text(".the Game",45,130,DARK_BLUE,1);
	write_text("Play",40,150,WHITE,0);
	write_text("Settings",40,170,WHITE,0);
	write_text("Credits",150,150,WHITE,0);
	write_text("Quit",150,170,WHITE,0);
	write_text(">",30+x_menu*110,150+y_menu*20,WHITE,0);
	//for (i = 0; i < 256; i++) {
	//	write_text("Y",i*4,130,i,9);
	//
	//}
	do{
		keypress = (char)getch();
		char* text = "In the year 2016, a man named _____";
		char sub[256];
		for ( i = 0 ; i < strlen(text) ; i++) {
			memcpy( sub, &text[0], i );
			sub[strlen(text)] = '\0';
			write_text(sub,45,100,WHITE,1);
			delay(5);
		}

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
		write_text(">",30+x_menu*110,150+y_menu*20,WHITE,0);
	}while(keypress!='q');


	set_graphics(VGA_TEXT80X25X16);
	clrscr();
	return 0;
}

void writeText(char* text, , , ,){

}

void clearArea(int x, int y, int w, int h) {
   int i,j;
   for ( i = y ; i <= (y+h) ; i++ ) {
      for (j=x;j<=(x+w);j++){
         write_pixel(j,i,0x0000);
      }
   }
}
