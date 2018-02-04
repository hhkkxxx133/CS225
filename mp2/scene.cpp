#include <cstdint>
#include <iostream>
using namespace std;

#include "scene.h"

void Scene::_copy(Scene const & other)
{
	_max = other._max;
	_layer = new Image*[_max];
	_xcoord = new int[_max];
	_ycoord = new int[_max];

	for (int i = 0; i < _max; ++i)
	{	
		_xcoord[i] =  other._xcoord[i];
		_ycoord[i] =  other._ycoord[i];

		if (other._layer[i] != NULL){

			_layer[i] = new Image;
			//*(_layer[i]) = *(other._layer[i]) ;
			//_layer[i]->operator=(*(other._layer[i]));
			_layer[i]->resize( other._layer[i]->width(), other._layer[i]->height() );

			for ( size_t y = 0 ; y<other._layer[i]->height() ; ++y){
				for ( size_t x = 0 ; x<other._layer[i]->width() ; ++x){
					*( _layer[i]->operator()(x,y) ) = *( other._layer[i]->operator()(x,y) );
				}
			}
		}
		else _layer[i] = NULL;		

	}

}

void Scene::_clear()
{
	for( int i=0 ; i<_max ; ++i ){
		if (_layer[i] != NULL){
			delete _layer[i];
			_layer[i] = NULL;
		}
	}

	delete [] _layer;
	_layer = NULL;

	delete [] _xcoord;
	_xcoord = NULL;

	delete [] _ycoord;
	_ycoord = NULL;
}

Scene::Scene(int max)
{
	_max = max;
	_layer= new Image*[_max];

	_xcoord = new int[_max];
	_ycoord = new int[_max];

	for( int i=0 ; i < _max ; ++i )
	{
		_layer[i] = NULL;
		_xcoord[i] =  0;
		_ycoord[i] =  0;
	}
}

Scene::~Scene()
{
	_clear();
}

Scene::Scene(const Scene & source)
{
	_copy(source);
}

const Scene & Scene::operator=(const Scene & source)
{
	if ( this != &source)
	{
		_clear();
		_copy(source);		
	}

	return *this;
}

void Scene::changemaxlayers(int newmax)
{
	if (newmax<_max)
	{
		for ( int k=newmax; k < _max ; ++k)
		{
			if(_layer[k] != NULL){
				cout << "invalid newmax" << endl;
				return;}
		}
	}

	Image** temp = new Image*[newmax];
	int * xtemp = new int [newmax];
	int * ytemp = new int [newmax];

 	int min = newmax;
 	if (_max < min) min = _max;

	for(int i = 0; i<min; ++i)
	{
		if (_layer[i] != NULL)
		{	
			temp[i] = new Image;
			xtemp[i] = _xcoord[i];
			ytemp[i] = _ycoord[i];
			temp[i]->resize(_layer[i]->width(), _layer[i]->height());

			for ( size_t y = 0 ; y< _layer[i]->height() ; ++y)
			{
				for ( size_t x = 0 ; x< _layer[i]->width() ; ++x)
				{
					*( temp[i]->operator()(x,y) ) = *( _layer[i]->operator()(x,y) );
				}
			}
		}
		else {
			temp[i] = NULL;
			xtemp[i] = 0;
			ytemp[i] = 0; }

	}

	if (min != newmax)
	{
		for(int j = min;j<newmax;++j)
		{
			temp[j] = NULL;
			xtemp[j] = 0;
			ytemp[j] = 0;
		}
	}

	for(int i= 0;i<_max;++i)
	{
		delete _layer[i];
		_layer[i]=NULL;
	}
	delete [] _layer;
	_layer = temp;

	delete [] _xcoord;
	_xcoord = xtemp;

	delete [] _ycoord;
	_ycoord = ytemp;

	_max = newmax;
	
	return;
}

void Scene::addpicture(const char * FileName, int index, int x, int y)
{
	if( index >= _max || index < 0 )
	{
		cout<<"index out of bounds"<<endl;
		return;
	}
	else
	{
		_layer[index] = new Image;
		_layer[index]->readFromFile(FileName);
		_xcoord[index] = x;
		_ycoord[index] = y;
	}
}

void Scene::changelayer(int index, int newindex)
{
	if ( index >= _max || index < 0 || newindex >= _max || newindex < 0 )
	{
		cout<<"invalid index"<<endl;
		return;
	}
	else if (index == newindex)
		return;
	else
	{

		if ( _layer[newindex] != NULL)
		{
			delete _layer[newindex];
			_layer[newindex] = NULL;
		}

		_layer[newindex] = _layer[index];
		_xcoord[newindex] = _xcoord[index];
		_ycoord[newindex] = _ycoord[index];

		_layer[index] = NULL;

	}

	return;
}

void Scene::translate(int index, int xcoord, int ycoord)
{
	if( index >= _max || index < 0 || getpicture(index) == NULL )
	{
		cout<<"invalid index"<<endl;
		return;
	}
	else
	{
		_xcoord[index] = xcoord;
		_ycoord[index] = ycoord;
	}

}

void Scene::deletepicture(int index)
{
	if( index >= _max || index < 0 || getpicture(index) == NULL)
	{
		cout<<"invalid index"<<endl;
		return;
	}
	else
	{
		delete _layer[index];
		_layer[index] = NULL;
	}
}

Image * Scene::getpicture(int index) const
{
	if( index >= _max || index < 0 )
	{
		return NULL;
	}
	else
	{
		return _layer[index];
	}	
}

Image Scene::drawscene() const
{
	size_t width = 0;
	size_t height = 0;

	for (int i = 0; i < _max ; ++i)
	{
		if (_layer[i] != NULL)
		{
			if ( _xcoord[i] + _layer[i]->width() > width )
				width = _xcoord[i] + _layer[i]->width();

			if ( _ycoord[i] + _layer[i]->height() > height )
				height = _ycoord[i] + _layer[i]->height();
		}

	}	

	Image temp;
	temp.resize(width,height);

	for (int j = 0 ; j<_max ; ++j )
	{
		if ( _layer[j] != NULL )
		{
			for (size_t y = _ycoord[j] ; y < _ycoord[j]+_layer[j]->height() ; ++y )
			{
				for (size_t x = _xcoord[j]; x < _xcoord[j]+_layer[j]->width() ; ++x )
				{
					*( temp.operator()(x,y) ) = *( _layer[j]->operator()(x-_xcoord[j],y-_ycoord[j]) );
				}
			}
		}
	}

	return temp;

}