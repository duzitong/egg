#include "RussianCube.h"
#include <GL/glut.h>
#include <time.h>

CubeGrid::CubeGrid(float w_, float h_, int nrows_, int ncols_) : 
	  nrows(nrows_), ncols(ncols_), drow(h_/nrows_), dcol(w_/ncols_) 
{
	label = new int*[nrows];
	for (int i = 0; i < nrows; ++i)
	{
		label[i] = new int[ncols];
		for (int j = 0; j < ncols; ++j)
		label[i][j] = 0;
	}
}

CubeGrid::~CubeGrid()
{
	if (this->label != 0)
	{
		for(int i = 0; i < nrows; ++i)
		{
			delete[] label[i];
		}
		delete[] label;
	}
}



void CubeGrid::setMovingLabel(CubeElement* e)
{
	for (int i = 0; i < 4; ++i)
	{
		int I = e->getI() + i;
		if (I >= nrows) continue;
		for (int j = 0; j < 4; ++j)
		{
			int J = e->getJ() + j;
			if (J >= ncols) continue;
			if (abs(e->getMat().get(i,j)) > 0.5f)
			{
				label[I][J] = 1;
			}
		}
	}
}

void CubeGrid::resetMovingLabel(CubeElement* e)
{
	for (int i = 0; i < 4; ++i)
	{
		int I = e->getI() + i;
		if (I >= nrows) continue;
		for (int j = 0; j < 4; ++j)
		{
			int J = e->getJ() + j;
			if (J >= ncols) continue;
			label[I][J] = 0;
		}
	}
}

int CubeGrid::get(int row, int col)
{
	return label[row][col];
}

void CubeGrid::drawGrid()
{
	for (int i = 0; i < nrows; ++i)
	{
		for (int j = 0; j < ncols; ++j)
		{
			if (label[i][j] == 1)
				drawGridQuad(i,j);
		}
	}
}

void CubeGrid::drawGridQuad(int i, int j)
{
	float x1 = j*dcol, x2 = (j+1)*dcol;
	float y1 = i*drow, y2 = (i+1)*drow;
	// draw line
	glColor4f(0, 0, 0, 1);
	glLineWidth(2);
	glBegin (GL_LINES);
	glVertex2f(x1,y1);
	glVertex2f(x1,y2);
	glVertex2f(x1,y1);
	glVertex2f(x2,y1);
	glVertex2f(x1,y2);
	glVertex2f(x2,y2);
	glVertex2f(x2,y1);
	glVertex2f(x2,y2);
	glEnd();
	// draw quad
	glColor4f(1, 0, 0, 0.75);
	glBegin (GL_QUADS);
	glVertex3f(x1,y1,0.0);
	glVertex3f(x2,y1,0.0);
	glVertex3f(x2,y2,0.0);
	glVertex3f(x1,y2,0.0);
	glEnd();
}

void Game::init(float w_, float h_, int nrows_, int ncols_)
{
	nrows = nrows_;
	ncols = ncols_;
	grid = new CubeGrid(w_, h_, nrows, ncols);
	srand(time(NULL));
	cube = new CubeElement(nrows-1,ncols/2,0);
}

void Game::step()
{
	grid->resetMovingLabel(cube);
	if (canDown())
		cube->moveDown();
	else
		nextCube();
	grid->setMovingLabel(cube);
}

void Game::left()
{
	grid->resetMovingLabel(cube);
	if (canLeft())
		cube->moveLeft();
	grid->setMovingLabel(cube);
}

void Game::right()
{
	grid->resetMovingLabel(cube);
	if (canRight())
		cube->moveRight();
	grid->setMovingLabel(cube);
}

void Game::down()
{
	grid->resetMovingLabel(cube);
	if (canDown())
		cube->moveDown();
	else
		nextCube();
	grid->setMovingLabel(cube);
}

void Game::rotate()
{
	grid->resetMovingLabel(cube);
	if (canRotate())
		cube->rotate();
	grid->setMovingLabel(cube);
}

void Game::draw()
{
	grid->drawGrid();
}

bool Game::canLeft()
{
	//grid->label
	//cube
	return true;
}

bool Game::canRight()
{
	//grid->label
	//cube
	return true;
}

bool Game::canDown()
{
	//grid->label
	//cube
	return true;
}

bool Game::canRotate()
{
	//grid->label
	//cube
	return true;
}

void Game::nextCube()
{
	delete cube;
	cube = new CubeElement(nrows-1,ncols/2,rand()%7);
}

void Game::pause()
{
	_pause = 1;
}

void Game::resume()
{
	_pause = 0;
}

int Game::isPause()
{
	return _pause;
}