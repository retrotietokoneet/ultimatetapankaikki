#include < math.h > 
#include < conio.h > 
#include < stdlib.h > 
#include < stdio.h > 
#include < i86.h > 
#include < string.h > 
#include "defines.h"
#include "globvar.h"

int get_dist( int x1, int y1, int x2, int y2 ) 
{
	int xs, ys, dist;
	xs = x1 - x2;
	ys = y1 - y2;
	dist = sqrt( ( xs*xs ) + ( ys*ys ) );
	return( dist );
}

int get_pan( int x1, int x2)
{	
	int pan;
 	int diff;
 	// stereo effect
  	diff=  - ( x1 - x2 ); 
  	if (diff!=0){
  	pan = diff  / 2;
  	if ( pan <  - 63 ) pan =  - 63;
   	if ( pan > 63 ) pan = 63;
	} else pan=0;
	return(pan);
}

int get_volume( int x1, int y1, int x2 , int y2)
{ 
 float dist;
 int shit;
  dist=get_dist(x1,y1,x2,y2);
  if (dist<500){
  dist/=200;
  if (dist<1) dist=1;
  shit=(int)(EFFECT_VOLUME/(float)dist);  
  } else shit=0;
  return(shit);
}

int get_angle( int x, int y, int x2, int y2 ) 
{
	int s1, s2, ang;
	float jako;
	s1 = x - x2;
	s2 = y - y2;
	if ( s1!= 0 ) 
	{
		jako = ( float ) ( s2 ) / ( float ) ( s1 );
		ang = atan( jako ) *360 / 2 / pi;
		if ( x > x2 ) ang = ang + 180;
	}
	if ( s1 == 0 ) 
	{
		if ( y < y2 ) ang = 90;
		if ( y > y2 ) ang = 270;
	}
	return( ang );
}

void pre_count() 
{
	int a;
	for ( a = 0;a < 360;a ++ ) 
	{
		sini[a]= sin( ( float ) a / 360*2*pi );
		cosi[a]= cos( ( float ) a / 360*2*pi );
	}
}

void randomize() 
{
	union REGS regs;
	regs.h.ah = 0x2c;
	int386( 0x21, &regs, &regs );
	srand( regs.h.dl + regs.h.dh*100 + regs.h.cl*6000 + regs.h.ch*36000 );
}

char *c_2_c( int aika ) 
{
	int min, sec;
	char text[10], text2[10], *t;
	min = aika / 60;
	sec = aika % 60;
	itoa( min, text, 10 );
	itoa( sec, text2, 10 );
	strcat( text, ":");
	if ( sec < 10 ) strcat( text, "0");
	strcat( text, text2 );
	t = strdup( text );
	return( t );
}

