#include <stdio.h>
#include <windows.h>
#include<time.h>
#include<stdlib.h>
#include <conio.h>
#define WIDTH 64
#define HEIGHT 26
void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void hidecursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
}
void draw_boundary() {
    int x, y;
    for (x = 0; x < WIDTH; x++) {
        gotoxy(x, 0);          printf("#");
        gotoxy(x, HEIGHT);    printf("#");
    }
    for (y = 1; y < HEIGHT; y++) {
        gotoxy(0, y);          printf("#");
        gotoxy(WIDTH-1, y);    printf("#");
    }
}
int main() {
	srand((unsigned) time(NULL));
	draw_boundary();
	int map[WIDTH+2][HEIGHT+2]={0};
	int len=3;
	int n=14;
    hidecursor();
    int x1[n];
    int y1[n];
    for(int i=0;i<n;i++){
		do{
			x1[i]=rand()%62+1;
			y1[i]=rand()%25+1;
		}while(map[x1[i]][y1[i]]!=0);
		map[x1[i]][y1[i]]=33464;
		gotoxy(x1[i],y1[i]);printf("X");
	}
    int x = 10, y = 10;
    int fwd=3;
    while (1) {
    	for(int i=0;i<64;i++){
			for(int j=0;j<26;j++){
				if(map[i][j]>0&&map[i][j]<11451){
					map[i][j]--;
					if(map[i][j]==0){
						gotoxy(i,j); printf(" ");
					}
				}
			}
		}
        if (_kbhit()) {
            char ch = _getch();
            if(ch=='w'){
            	if(map[x][y-1]==0||map[x][y-1]==33464)
				fwd=0;
			}
			if(ch=='a'){
				if(map[x-1][y]==0||map[x-1][y]==33464)
				fwd=1;
			}
			if(ch=='s'){
				if(map[x][y+1]==0||map[x][y+1]==33464)
				fwd=2;
			}
			if(ch=='d'){
				if(map[x+1][y]==0||map[x+1][y]==33464)
				fwd=3;
			}
        }
        switch(fwd){
			case 0:
				y--;
			break;
			case 1:
				x--;
			break;
			case 2:
				y++;
			break;
			case 3:
				x++;
			break;
		}
		if(x<=0||y<=0||x>=WIDTH-1||y>=HEIGHT){gotoxy(1,HEIGHT+1);break;}
		if(map[x][y]==0)map[x][y]=len;
		else if(map[x][y]==33464){
			for(int i=0;i<64;i++){
				for(int j=0;j<26;j++){
					if(map[i][j]>0&&map[i][j]<11451){
						map[i][j]++;
						}
					}
				}
			len++;map[x][y]=len;
			int xx=x,yy=y;
			int t=0;
			while(map[xx][yy]!=0&&t<10000){
				xx=rand()%62+1;
				yy=rand()%25+1;
				t++;
			}
			if(t-10000){
				map[xx][yy]=33464;
				gotoxy(xx,yy);printf("X");
			}
		}
		else{gotoxy(1,HEIGHT+1);break;}
		gotoxy(x, y); printf("O");
        Sleep(120);
    }
    printf("Game over");
    gotoxy(1,HEIGHT+2);
    printf("Score:%d     ",len-3);
    int speed=len/5;
    if(speed<2)speed=2;
    if(speed>30)speed=30;
    Sleep(2500/speed);
}
