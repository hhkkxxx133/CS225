#include <cstdint>

#include "image.h"
#include "png.h"

void Image::flipleft()
{
	size_t h = height();
	size_t w = width();

 	RGBAPixel* temp = new RGBAPixel();

	for (size_t y = 0; y < h ; ++y )
	{
		for (size_t x = 0; x < w/2; ++x)
		{
			*temp = *( operator()(x,y) );
			*( operator()(x,y) ) = *( operator()(w-x-1 , y) );
			*( operator()(w-x-1 , y) ) = *temp;

		}
	}

	delete temp;
	temp = NULL;
}

void Image::adjustbrightness(int r, int g, int b)
{
	size_t h = height();
	size_t w = width();

	//RGBAPixel * pixel = new RGBAPixel();

	for (size_t y = 0; y < h ; ++y )
	{
		for (size_t x = 0; x < w; ++x)
		{

			//pixel  = operator()(x,y);

			if (operator()(x,y)->red + r > 255)
				operator()(x,y)->red = 255 ;
			else if (operator()(x,y)->red + r < 0)
				operator()(x,y)->red = 0 ;
			else
				operator()(x,y)->red = operator()(x,y)->red + r ;


			if (operator()(x,y)->green + g > 255)
				operator()(x,y)->green = 255 ;
			else if (operator()(x,y)->green + g < 0)
				operator()(x,y)->green = 0 ;
			else
				operator()(x,y)->green = operator()(x,y)->green + g ;


			if (operator()(x,y)->blue + b > 255)
				operator()(x,y)->blue = 255 ;
			else if (operator()(x,y)->blue + b < 0)
				operator()(x,y)->blue = 0 ;
			else
				operator()(x,y)->blue = operator()(x,y)->blue + b ;
		}
	}

}

void Image::invertcolors()
{

	size_t h = height();
	size_t w = width();

	//RGBAPixel * pixel = new RGBAPixel();

	for (size_t y = 0; y < h ; ++y )
	{
		for (size_t x = 0; x < w; ++x)
		{

			//pixel  = operator()(x,y);

			operator()(x,y)->red = 255 - operator()(x,y)->red ;
			operator()(x,y)->green = 255 - operator()(x,y)->green ;
			operator()(x,y)->blue = 255 - operator()(x,y)->blue ;
		}
	}
}
