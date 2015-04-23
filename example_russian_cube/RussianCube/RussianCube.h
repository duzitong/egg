#pragma once

#include <math.h>
#include <stdlib.h>

class MyMatrix4
{
public:
	MyMatrix4()
	{
		set(0);
	}
	void set(int value)
	{
		e[0][0] = e[0][1] = e[0][2] = e[0][3] = 
		e[1][0] = e[1][1] = e[1][2] = e[1][3] = 
		e[2][0] = e[2][1] = e[2][2] = e[2][3] = 
		e[3][0] = e[3][1] = e[3][2] = e[3][3] = value;
	}
	int get(int i, int j)
	{
		return e[i][j];
	}
	void setColumn(int col, int value)
	{
		e[0][col] = e[1][col] = e[2][col] = e[3][col] = value;
	}
	void setRow(int row, int value)
	{
		e[row][0] = e[row][1] = e[row][2] = e[row][3] = value;
	}
	void set(int row, int col, int value)
	{
		e[row][col] = value;
	}
	void rotate90()
	{
		int n = 4;
		int f = floor((float)n/2);
		int c = ceil((float)n/2);

		for (int x = 0; x < f; ++x)
		  for (int y = 0; y < c; ++y)
		  {
			int temp = e[x][y];
			e[x][y] = e[y][n-1-x];
			e[y][n-1-x] = e[n-1-x][n-1-y];
			e[n-1-x][n-1-y] = e[n-1-y][x];
			e[n-1-y][x] = temp;
		  }
	}
private:
	int e[4][4];
};

class CubeElement
{
public:
	CubeElement(int i_, int j_, int type_) : i(i_),j(j_),type(type_){
		switch(type){
			case 0:
				{
					// I
					mat4.setColumn(1,1);
				}
				break;
			case 1:
				{
					// L
					mat4.setColumn(1,1);
					mat4.set(0,1,0);
					mat4.set(1,2,1);
				}
				break;
			case 2:
				{
					// L'
					mat4.setColumn(2,1);
					mat4.set(0,2,0);
					mat4.set(1,1,1);
				}
				break;
			case 3:
				{
					// Z
					mat4.set(2,0,1);
					mat4.set(2,1,1);
					mat4.set(1,1,1);
					mat4.set(1,2,1);
				}
				break;
			case 4:
				{
					// Z'
					mat4.set(1,1,1);
					mat4.set(1,2,1);
					mat4.set(2,2,1);
					mat4.set(2,3,1);
				}
				break;
			case 5:
				{
					// T
					mat4.set(2,0,1);
					mat4.set(2,1,1);
					mat4.set(2,2,1);
					mat4.set(1,1,1);
				}
				break;
			case 6:
				{
					// O
					mat4.set(1,1,1);
					mat4.set(1,2,1);
					mat4.set(2,1,1);
					mat4.set(2,2,1);
				}
				break;
			default:
				{}
		}
	}

	CubeElement(CubeElement &e)
	{
		this->i = e.getI();
		j = e.getJ();
		mat4 = e.getMat();
		type = e.getType();
	}

	void moveDown()
	{
		this->i--;
	}
	void rotate()
	{
		mat4.rotate90();
	}
	void moveLeft()
	{
		this->j--;
	}
	void moveRight()
	{
		this->j++;
	}
	void setI(int i_)
	{
		i = i_;
	}
	void setJ(int j_)
	{
		j = j_;
	}
	int getI()
	{
		return i;
	}
	int getJ()
	{
		return j;
	}
	int getType()
	{
		return type;
	}
	MyMatrix4& getMat()
	{
		return mat4;
	}
private:
	int i, j; // row and col index
	int type;
	MyMatrix4 mat4;
};

class CubeGrid
{
public:
	CubeGrid(float w_, float h_, int nrows_, int ncols_);
	~CubeGrid();

	void setMovingLabel(CubeElement* e);		// set the tags of current occupied valid grids to 1
	void resetMovingLabel(CubeElement* e);		// reset the tags of current occupied grids to 0
	int canLeft(CubeElement *e);
	int canRight(CubeElement *e);
	int canDown(CubeElement *e);
	int canRotate(CubeElement *e);
	int checkFullLines();

	void drawGrid();

private:
	void drawGridQuad(int i, int j);

private:
	float drow, dcol;	 // element width and height 
	int nrows, ncols;
	int** label;
};

class Game
{
public:
	Game()
	{

	}
	~Game()
	{
		delete grid; grid = 0;
		delete cube; cube = 0;
	}

	void init(float w_, float h_, int nrows_, int ncols_);
	void start();
	void step();
	void left();
	void right();
	void down();
	void rotate();
	void end();
	int nextCube();
	unsigned int seed;
	int isPaused();
	void pause();
	void resume();

	void draw();

private:
	CubeGrid* grid;
	CubeElement* cube;
	int nrows, ncols;
	int _pause;
};

