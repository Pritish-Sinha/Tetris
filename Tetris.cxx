#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#define Yr 18
#define Xr 12
#define totalshapes 7
char shape[totalshapes][16];
char cshape[16];
struct range{
	int minx,maxx,miny,maxy;
};
struct range shaperange()
{
	int i,j;
	struct range z;
	z.minx=4; z.miny=4;
	z.maxx=0; z.maxy=0;
	int k;
	char tempo[4][4];
	for( i=0;i<4;i++){
		for( j=0;j<4;j++){
			if(i==0)
			k=j;
			else if(i==1)
			k=j+4;
			else if(i==2)
			k=j+8;
			else if(i==3)
			k=j+12;
			tempo[i][j]=cshape[k];
		}
	}
	for( i=0;i<4;i++){
		for( j=0;j<4;j++){
			if(tempo[i][j]=='X'&&j<=z.minx)
			z.minx=j;
		}
	}
	for( i=0;i<4;i++){
		for( j=0;j<4;j++){
			if(tempo[i][j]=='X'&&j>=z.maxx)
			z.maxx=j;
		}
	}
	for( i=0;i<4;i++){
		for( j=0;j<4;j++){
			if(tempo[i][j]=='X'&&i<=z.miny)
			z.miny=i;
		}
	}
	for( i=0;i<4;i++){
		for( j=0;j<4;j++){
			if(tempo[i][j]=='X'&&i>=z.maxy)
			z.maxy=i;
		}
	}
	return(z);
}
int g4status=1,cx=4,cy=0,score=0,r,rnext=100;
void initialise();
void screen();
void layerdetect();
void initiatetrack();
void starttemp();
int genshape();
void rotate90();
void rotate270();
void down();
void right();
void fall();
void left();
char trackbound[Yr][Xr];
char temp[Yr][Xr];
char fallen[Yr][Xr];

void takeinput()
{
	char input;
	re_enter:
	gotoxy(29,3);
	input=getch();
	if (input == 'l')
	{
		rotate90();
	}
	else if (input == 's')
	{
		down();
	}
	else if(input=='d')
	{
		right();
	}
	else if(input=='a')
	{
		left();
	}
	else if(input=='k')
	{
		rotate270();
	}
	else if(input==' ')
	{
		fall();
	}
	else if(input=='Z')
	{
		exit(0);
	}
	else
	goto re_enter;
	
}
void main()
{
	clrscr();
	initialise();
	r = genshape();
	screen();
	while(g4status==1||g4status==2){
		
		if(g4status==2)
		{
			layerdetect();
			cx=4;
			cy=0;
			g4status=1;
			r = genshape();
			if(g4status!=0)
			screen();
		}
	gotoxy(34,5);
	cout<<"             ";
	gotoxy(30, 5);
	cout << "SCORE :  "<<score;
	if(g4status!=0)
	takeinput();
	}
	if(g4status==0)
	{getch(); getch(); clrscr(); cout<<"\n\n\tYOU LOSE at "<<score; }
	
	gotoxy(30, 24);
	getch();
}
int genshape()
{
	int i,j;
	gen : 
	srand(time(NULL));
	if(rnext==100)
	r = rand() % (totalshapes - 1 + 1) + 0;
	else
	r=rnext;
	if(rnext==100&&(r==2||r==3))
	goto gen;
	rnext=rand() % (totalshapes- 1 + 1) + 0;
	if(rnext==r)
	goto gen;
	
	strncpy(cshape,shape[r],16);
	shaperange();
	starttemp();
	for ( i = 0; i < Yr; i++)
	{
		for ( j = 0; j < Xr; j++)
		{if((temp[i][j]=='X'&&fallen[i][j]=='X')||(temp[i][j]=='X'&&trackbound[i][j]=='1'))
		{g4status=0;
		break;}
	}
	}
	
	int k;
	char tempo[4][4];
	for( i=0;i<4;i++){
		for( j=0;j<4;j++){
			if(i==0)
			k=j;
			else if(i==1)
			k=j+4;
			else if(i==2)
			k=j+8;
			else if(i==3)
			k=j+12;
			tempo[i][j]=shape[rnext][k];
		}
	}
	gotoxy(29,8);
	cout<<"NEXT SHAPE";
	for(int h=0;h<4;h++){
		for(int k=0;k<4;k++){
			gotoxy(29+k,9+h);
			if(tempo[h][k]=='0')
			cout<<" ";
			else{
				textcolor(14);
			cout<<tempo[h][k];
			textcolor(15);
			}
		}
	}
	return r;
}
void screen()
{
	starttemp();
	initiatetrack();
	for(int i=0;i<Yr;i++){
		for(int j=0;j<Xr;j++){
			gotoxy(j+3,i+3);
			if(fallen[i][j]=='X'){
				textcolor(2);
			cout<<fallen[i][j];
			textcolor(15);
			}
			else if(temp[i][j]=='0')
			cout<<" ";
			else
			cout<<temp[i][j];
			/*gotoxy(j+3,i+3);
			if(trackbound[i][j]=='1')
			cout<<1;*/
		}
	}
	
}
void rotate90()
{
	char tempshape[16];
	int error=0,i,j;
	char tempo[4][4];
	
	for( i =0;i<4;i++){
		for( j=0;j<4;j++){
			tempo[i][j]=cshape[i*4+j];
		}
	}
	
	if (r == 4)
	{
		cshape[1] = tempo[1][0];
		cshape[4] = tempo[2][1];
		cshape[6] = tempo[0][1];
		cshape[9] = tempo[1][2];
	}
	else{
	for( i =0;i<4;i++){
		for( j=0;j<4;j++){
		cshape[i*4+j]=tempo[4-1-j][i];
		}
	}}
	
	struct range s;
	s=shaperange();
	starttemp();
	
	strncpy(tempshape,cshape,16);
	
	for( i =0;i<4;i++){
		for( j=0;j<4;j++){
			tempo[i][j]=cshape[i*4+j];
		}
	}
	if (r == 4)
	{
		cshape[1] = tempo[1][2];
		cshape[4] = tempo[0][1];
		cshape[6] = tempo[2][1];
		cshape[9] = tempo[1][0];
	}
	else{
	for( i =0;i<4;i++){
		for( j=0;j<4;j++){
		cshape[i*4+j]=tempo[j][4-1-i];
		}
	}}
	
	for ( i = 0; i < Yr; i++)
	{
		for ( j = 0; j < Xr; j++)
		{
		if(temp[i][j]=='X'&&fallen[i][j]=='X')
			{
			error=1;
			break;
			}
			else if(cx+s.maxx>=Xr||
			cx+s.minx<0)
			{
			error=1;
			break;
			}
		}
	}
	if(error==1)
	{
		struct range s;
		s=shaperange();
		takeinput();
	}
	else
	{
		strncpy(cshape,tempshape,16);
		screen();
	}
	
}
void rotate270()
{
	char tempshape[16];
	int error=0,i,j;
	char tempo[4][4];
	
	for( i =0;i<4;i++){
		for( j=0;j<4;j++){
			tempo[i][j]=cshape[i*4+j];
		}
	}
	
	if (r == 4)
	{
		cshape[1] = tempo[1][2];
		cshape[4] = tempo[0][1];
		cshape[6] = tempo[2][1];
		cshape[9] = tempo[1][0];
	}
	else{
	for( i =0;i<4;i++){
		for( j=0;j<4;j++){
		cshape[i*4+j]=tempo[j][4-1-i];
		}
	}}
	
	struct range s;
	s=shaperange();
	starttemp();
	
	strncpy(tempshape,cshape,16);
	
	for(i =0;i<4;i++){
		for( j=0;j<4;j++){
			tempo[i][j]=cshape[i*4+j];
		}
	}
	if (r == 4)
	{
		cshape[1] = tempo[1][0];
		cshape[4] = tempo[2][1];
		cshape[6] = tempo[0][1];
		cshape[9] = tempo[1][2];
	}
	else{
	for(i =0;i<4;i++){
		for( j=0;j<4;j++){
		cshape[i*4+j]=tempo[4-1-j][i];
		}
	}}
	
	for ( i = 0; i < Yr; i++)
	{
		for (j = 0; j < Xr; j++)
		{
		if(temp[i][j]=='X'&&fallen[i][j]=='X')
			{
			error=1;
			break;
			}
			else if(cx+s.maxx>=Xr||
			cx+s.minx<0)
			{
			error=1;
			break;
			}
		}
	}
	if(error==1)
	{
		struct range s;
		s=shaperange();
		takeinput();
	}
	else
	{
		strncpy(cshape,tempshape,16);
		screen();
	}	
}
void right()
{
	int error=0,i,j;
	++cx;
	struct range s;
	s=shaperange();
	starttemp();
	for (i = 0; i < Yr; i++)
	{
		for ( j = 0; j < Xr; j++)
		{
			if(temp[i][j]=='X'&&fallen[i][j]=='X')
			{
			error=1;
			break;
			}
			else if(cx+s.maxx>=Xr)
			{
			error=1;
			break;
			}
		}
	}
	if(error==1)
	{
		--cx;
		takeinput();
	}
	else
	screen();
}
void left()
{
	int error=0,i,j;
	--cx;
	struct range s;
	s=shaperange();
	starttemp();
	for ( i = 0; i < Yr; i++)
	{
		for (j = 0; j < Xr; j++)
		{if(temp[i][j]=='X'&&fallen[i][j]=='X')
		{
		error=1;
		break;
		}
		else if(cx+s.minx<0)
		{
		error=1;
		break;
		}
		}
	}
	if(error==1)
	{
		++cx;
		takeinput();
	}
	else
	screen();	
}
void down()
{
	int error=0,i,j;
	struct range s;
	s=shaperange();
	starttemp();
	for ( i = 0; i < Yr; i++)
	{
		for ( j = 0; j < Xr; j++)
		{
			if(temp[i][j]=='X'&&
			trackbound[i][j]=='1')
			{ g4status=2;
			error=1;
			break;}
		}
	}
	if(error==0){
	++cy;
	struct range s;
	s=shaperange();
	starttemp();

	for ( i = 0; i < Yr; i++)
	{
		for ( j = 0; j < Xr; j++)
		{
			if(temp[i][j]=='X'&&
			trackbound[i][j]=='1')
			{ g4status=2;
			break;}
		}
	}
	}
	screen();
}
void fall()
{
	while(g4status!=2){
		++cy;
		struct range s;
		s=shaperange();
		starttemp();
		
		for (int i = 0; i < Yr; i++)
		{
			for (int j = 0; j < Xr; j++)
			{
				if(temp[i][j]=='X'&&
				trackbound[i][j]=='1')
				{ g4status=2;
				break;}
			}
		}
	}
	screen();
}
void layerdetect()
{
	char tempo[Yr][Xr];
	int count,row[Yr],index=-1,i,j;
	for( i=0;i<Yr;i++)
	{
		count=0;
		for( j=0;j<Xr;j++)
		{
			if(fallen[i][j]=='X')
			++count;
		}
		if(count==Xr)
		{++index; row[index]=i;}
	}
	if(index<0)
	goto end;
	for( int a=0;a<=index;a++){
		score+=25*a+100;
		
		for ( i = 0; i < Yr; i++){
			for ( j = 0; j < Xr; j++){
				if(trackbound[i][j]=='1')
				trackbound[i][j]='0';
			}
		}
		for ( i = 0; i < Yr; i++){
			for ( j = 0; j < Xr; j++)
			tempo[i][j]=fallen[i][j];
		}
		
		for (i = row[index]; i>=0; i--){
			for (j = 0; j < Xr; j++){
				if(fallen[i][j]=='X')
				fallen[i][j]='0';
			}
		}
		
		for ( i = row[index]; i>0; i--){
			for ( j = 0; j < Xr; j++)
			fallen[i][j]=tempo[i-1][j];
		}
		
		for (i = 0; i < Yr; i++){
			for (j = 0; j < Xr; j++){
				if(fallen[i][j]=='X')
				trackbound[i-1][j]='1';
			}
		}
		for ( i = 0; i < Yr; i++){
			for ( j = 0; j < Xr; j++){
				if(i==Yr-1)
				trackbound[i][j]='1';	
			}
		}
	}	
	
	end : 
	for( i=0;i<Yr;i++){
		for( j=0;j<Xr;j++){
			gotoxy(j+3,i+3);
			if(fallen[i][j]=='X')
			cout<<fallen[i][j];
			/*gotoxy(j+3,i+3);
			if(trackbound[i][j]=='1')
			cout<<1;*/
		}
	}
}

void initiatetrack()
{
	for (int i = 0; i < Yr; i++)
	{
		for (int j = 0; j < Xr; j++)
		{
			if(g4status==2)
			{if(temp[i][j]=='X')
			{fallen[i][j]='X';
			trackbound[i-1][j]='1';}
			}
		}
	}
}
void starttemp()
{
	int w,i,j,k;
	w=cx-4;
	for (int i = 0; i < Yr; i++)
	{
		for (int j = 0; j < Xr; j++)
		temp[i][j]='0';
	}
	for(  i=cy;i<cy+4;i++)
	{
		for( j=cx;j<cx+4;j++)
		{
			if(i==cy)
			k=j-4-w;
			else if(i==1+cy)
			k=j-w;
			else if(i==2+cy)
			k=j+4-w;
			else if(i==3+cy)
			k=j+8-w; 
		if(cshape[k]=='X')
			temp[i][j]=cshape[k];
		}
	}
	
}
void initialise()
{
	gotoxy(20,15);
	cout<<"DOWN  : s";
	gotoxy(20,16);
	cout<<"LEFT  : a";
	gotoxy(20,17);
	cout<<"RIGHT : d";
	gotoxy(20,18);
	cout<<"ROTATE CLOCKWISE : l";
	gotoxy(20,19);
	cout<<"ROTATE ANTI-CLOFKWISE : k";
	gotoxy(20,20);
	cout<<"DIRECT FALL DOWN : (space key)";
	gotoxy(20,22);
	cout<<"EXIT : Z";
	for (int i = 0; i < Yr; i++)
	{
		for (int j = 0; j < Xr; j++)
		{
			fallen[i][j]='0';
			if(i==Yr-1)
			trackbound[i][j]='1';
			else
			trackbound[i][j]='0';
			
		}
	}
	
	strcpy(shape[0],"00X000X000X000X0");
	
	strcpy(shape[1],"00000XX00XX00000");

	strcpy(shape[2],"00000XX0XX000000");
	
	strcpy(shape[3],"0000XX000XX00000");

	strcpy(shape[4],"0000XXX00X000000");
	
	strcpy(shape[5],"00000X000X000XX0");

	strcpy(shape[6],"000000X000X00XX0");
	
	for (int i = 2; i < Yr + 3; i++)
	{
		gotoxy(2, i);
		cout << "|";
		gotoxy(Xr + 3, i);
		cout << "|";
	}
	for (int i = 3; i < Xr + 3; i++)
	{
		gotoxy(i, Yr + 3);
		cout << "T";
	}
	for (int i = 3; i < Xr + 3; i++)
	{
		gotoxy(i, 2);
		cout << "_";
	}
}