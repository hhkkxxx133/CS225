/* Your code here! */
#include "maze.h"


SquareMaze::SquareMaze()
{
	_width = _height = _size = 0;
}

void SquareMaze::makeMaze(int width, int height)
{
	_width = width;
	_height = height;
	_size = width * height;

	visited = new bool*[_height];

	for (int i = 0; i < _height; ++i){
		visited[i] = new bool[_width];
		for (int j = 0; j < _width; ++j){
			visited[i][j] = false;
		}
	}

	_cells.addelements(_size);

	for (int i=0 ; i<_size ; ++i){
		_downwall.push_back(true);
		_rightwall.push_back(true);
	}

	srand(time(NULL));

	vector<int> randx;
	vector<int> randy;
	
	for (int i=0; i<_width; ++i){
		randx.push_back(i);
	}
	random_shuffle(randx.begin(), randx.end());

	for (int j=0; j<_height; ++j){
		randy.push_back(j);
	}
	random_shuffle(randy.begin(), randy.end());

	for (int j=0 ; j<_height ; ++j){
		for (int i=0 ; i<_width ; ++i){
			int currx = randx[i];
			int curry = randy[j];

			if (rand()%2) {
				if (currx!=_width-1){
				if ( _rightwall[curry*_width + currx] == true && _cells.find(curry*_width + currx) != _cells.find(curry*_width + currx+1)){
					_cells.setunion(curry*_width + currx, curry*_width + currx+1);
					_rightwall[curry*_width + currx] = false;
				}
			}
			}
			else {
				if(curry!=_height-1){
				if (_downwall[curry*_width + currx] == true &&_cells.find(curry*_width + currx) != _cells.find((curry+1)*_width + currx)){
					_cells.setunion(curry*_width + currx, (curry+1)*_width + currx);
					_downwall[curry*_width + currx] = false;
				}
			}
			}
		}
	}


}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
	if ( dir==0 && (x+1)<_width ) {//rightward step
		return (_rightwall[ y * _width + x ] == false);
	}
	else if ( dir==1 && (y+1)<_height ) {//downward step
		return (_downwall[ y * _width + x ] == false);
	}
	else if ( dir==2 && x>0 ) {//leftward step
		return (_rightwall[ y * _width + x-1 ] == false);
	}
	else if ( dir==3 && y>0 ) {//upward step
		return (_downwall[ (y-1) * _width + x ] == false);
	}

	return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	if (dir==0 && (x+1)<_width) {
		_rightwall[y*_width+x] = exists;
	}

	if (dir==1 && (y+1)<_height) {
		_downwall[y*_width+x] = exists;
	}
}

vector<int> SquareMaze::solveMaze()
{
	vector<int> solution;
	vector<vector<int> > paths;
	vector<int> end_x;

	solve(0, 0, solution, paths, end_x);

	int sol = 0;
	for (int i = 0; i < (int)paths.size(); ++i){
		if (paths[sol].size() < paths[i].size() ){
			sol = i;
		}
		else if (paths[sol].size() == paths[i].size()){
			sol = end_x[sol] < end_x[i] ? sol : i;
		}
	}

	for (int i = 0; i < _height; ++i){
		for (int j = 0; j < _width; ++j){
			visited[i][j] = false;
		}
	}

	//cout << sol << ", " << paths.size() << endl;
	if (paths.size() == 0){
		return vector<int>();
	}
	solution = paths[sol];
	return solution;	
}


void SquareMaze::solve(int x, int y, vector<int> path, vector<vector<int>> & paths, vector<int> & end_x)
{
	visited[y][x] = true;
//if find path to last row
	if ( y == _height -1 ){//&& _downwall[y*_width + x] ) {
		paths.push_back(path);
		end_x.push_back(x);
		return;
	}
//if dead end
//travel right
	if ( canTravel(x, y, 0) && visited[y][x+1]==false){
		path.push_back(0);
		//visited[y][x+1]=true;
		//setWall(x, y, 0, true);
		solve(x+1, y, path, paths, end_x);
		path.pop_back();
		//setWall(x, y, 0, false);
	}
	
//travlel down
	if ( canTravel(x, y, 1) && visited[y+1][x]==false){
		path.push_back(1);
		//visited[y+1][x]=true;
		//setWall(x, y, 1, true);
		solve(x, y+1, path, paths, end_x);
		path.pop_back();
		//setWall(x, y, 1, false);
	}
	
//travel left
	if ( canTravel(x, y, 2) && visited[y][x-1]==false){
		path.push_back(2);
		//visited[y][x-1]=true;
		//setWall(x-1, y, 0, true);
		solve(x-1, y, path, paths, end_x);
		path.pop_back();
		//setWall(x-1, y, 0, false);
	}
//travel up
	if ( canTravel(x, y, 3) && visited[y-1][x]==false){
		path.push_back(3);
		//visited[y-1][x]=true;
		//setWall(x, y-1, 1, true);
		solve(x, y-1, path, paths, end_x);
		path.pop_back();
		//setWall(x, y-1, 1, false);
	}

	return;
}

PNG* SquareMaze::drawMaze() const
{
	PNG * image = new PNG(_width*10+1, _height*10+1);

	for (size_t j=0; j<image->height();++j){
		image->operator()(0,j)->red = 0;
		image->operator()(0,j)->green = 0;
		image->operator()(0,j)->blue = 0;
	}

	for (size_t i=10; i<image->width();++i){			
		image->operator()(i,0)->red = 0;
		image->operator()(i,0)->green = 0;
		image->operator()(i,0)->blue = 0;
	}

	for (int y=0; y<_height; ++y){
		for (int x=0; x<_width; ++x){
			if (_rightwall[y*_width+x]){
				for (int k=0;k<=10;++k){
					image->operator()((x+1)*10,y*10+k)->red = 0;
					image->operator()((x+1)*10,y*10+k)->green = 0;
					image->operator()((x+1)*10,y*10+k)->blue = 0;
				}
			}

			if (_downwall[y*_width+x]){
				for (int k=0;k<=10;++k){
					image->operator()(x*10+k,(y+1)*10)->red = 0;
					image->operator()(x*10+k,(y+1)*10)->green = 0;
					image->operator()(x*10+k,(y+1)*10)->blue = 0;
				}
			}
		}
	}

	return image;
}

PNG* SquareMaze::drawMazeWithSolution()
{	
	
	PNG * image = drawMaze();
	vector<int> sol = solveMaze();

	int x=5;
	int y=5;

	for (auto it=sol.begin(); it!=sol.end(); ++it){
		if (*it==0){
			for (int i=0;i<11;++i){
				image->operator()(x,y)->red = 255;
				image->operator()(x,y)->green = 0;
				image->operator()(x,y)->blue = 0;
				x++;
			}
			x = x-1;
		}
		else if (*it==1){
			for (int i=0;i<11;++i){
				image->operator()(x,y)->red = 255;
				image->operator()(x,y)->green = 0;
				image->operator()(x,y)->blue = 0;
				y++;
			}
			y = y-1;
		}
		else if (*it==2){
			for (int i=0;i<11;++i){
				image->operator()(x,y)->red = 255;
				image->operator()(x,y)->green = 0;
				image->operator()(x,y)->blue = 0;
				x--;
			}
			x = x+1;
		}
		else if (*it==3){
			for (int i=0;i<11;++i){
				image->operator()(x,y)->red = 255;
				image->operator()(x,y)->green = 0;
				image->operator()(x,y)->blue = 0;
				y--;
			}
			y = y+1;
		}
	}

	x = x/10;
	for (int k=1; k<=9; ++k){
		image->operator()(x*10+k, _height*10)->red = 255;
		image->operator()(x*10+k, _height*10)->green = 255;
		image->operator()(x*10+k, _height*10)->blue = 255;
	}

	return image;
}