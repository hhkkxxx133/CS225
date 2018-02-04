#include <algorithm>
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

int main()
{
	PNG image("in.png");

	size_t w = image.width();
	size_t h = image.height();

	size_t i,j;
	RGBAPixel pixel;

	for ( i = 0 ; i < h/2 ; ++i )
	{
		for ( j = 0; j < w ; ++j )
		{
			pixel = *(image.operator()(j,i)) ;
			*(image.operator()(j,i)) = *(image.operator()(w-1-j,h-1-i)) ;
			*(image.operator()(w-1-j,h-1-i)) = pixel ;	
		}
	}

	if ( h%2 != 0)
	{
		i = h/2 ;
		for ( j=0 ; j < w/2 ; ++j )
		{
			pixel = *(image.operator()(j,i)) ;
			*(image.operator()(j,i)) = *(image.operator()(w-1-j,i)) ;
			*(image.operator()(w-1-j,i)) = pixel ;
		}
	}

	image.writeToFile("out.png");

	return 0;
}