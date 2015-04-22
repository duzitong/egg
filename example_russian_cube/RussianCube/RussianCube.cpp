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
		if (I >= nrows || I < 0) continue;
		for (int j = 0; j < 4; ++j)
		{
			int J = e->getJ() + j;
			if (J >= ncols || J < 0) continue;
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
		if (I >= nrows || I < 0) continue;
		for (int j = 0; j < 4; ++j)
		{
			int J = e->getJ() + j;
			if (J >= ncols || J < 0) continue;
			if (e->getMat().get(i, j))
				label[I][J] = 0;
		}
	}
}

int CubeGrid::canLeft(CubeElement *e)
{
	CubeElement tmp = *e;
	tmp.moveLeft();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (tmp.getMat().get(i,j) == 1)
			{
				int _i = tmp.getI()+i, _j = tmp.getJ()+j;
				if ((_i < 0) || (_j < 0) || (_j >= ncols) || (label[_i][_j] == 1))
					return 0;
			}		
		}
	}
	return 1;
}

int CubeGrid::canRight(CubeElement *e)
{
	CubeElement tmp = *e;
	tmp.moveRight();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (tmp.getMat().get(i,j) == 1)
			{
				int _i = tmp.getI()+i, _j = tmp.getJ()+j;
				if ((_i < 0) || (_j < 0) || (_j >= ncols) || (label[_i][_j] == 1))
					return 0;
			}		
		}
	}
	return 1;
}

int CubeGrid::canDown(CubeElement *e)
{
	CubeElement tmp = *e;
	tmp.moveDown();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (tmp.getMat().get(i,j) == 1)
			{
				int _i = tmp.getI()+i, _j = tmp.getJ()+j;
				if ((_i < 0) || (_j < 0) || (_j >= ncols) || (label[_i][_j] == 1))
					return 0;
			}		
		}
	}
	return 1;
}

int CubeGrid::canRotate(CubeElement *e)
{
	CubeElement tmp = *e;
	tmp.rotate();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (tmp.getMat().get(i,j) == 1)
			{
				int _i = tmp.getI()+i, _j = tmp.getJ()+j;
				if ((_i < 0) || (_j < 0) || (_j >= ncols) || (label[_i][_j] == 1))
					return 0;
			}		
		}
	}
	return 1;
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
	_pause = 0;
	nrows = nrows_;
	ncols = ncols_;
	grid = new CubeGrid(w_, h_, nrows, ncols);
	srand(time(NULL));
	cube = new CubeElement(nrows-4,ncols/2-2,rand()%7);
}

void Game::step()
{
	down();
}

void Game::left()
{
	grid->resetMovingLabel(cube);
	if (grid->canLeft(cube))
		cube->moveLeft();
	grid->setMovingLabel(cube);
}

void Game::right()
{
	grid->resetMovingLabel(cube);
	if (grid->canRight(cube))
		cube->moveRight();
	grid->setMovingLabel(cube);
}

void Game::down()
{
	grid->resetMovingLabel(cube);
if (grid->canDown(cube))
	{
		cube->moveDown();
		grid->setMovingLabel(cube);
	}
	else
	{
		grid->setMovingLabel(cube);
		nextCube();
	}
}

void Game::rotate()
{
	grid->resetMovingLabel(cube);
	if (grid->canRotate(cube))
		cube->rotate();
	grid->setMovingLabel(cube);
}

void Game::draw()
{
	grid->drawGrid();
}

void Game::nextCube()
{
	delete cube;
	cube = new CubeElement(nrows-4,ncols/2-2,rand()%7);
}

void Game::pause()
{
	_pause = 1;
}

void Game::resume()
{
	_pause = 0;
}

int Game::isPaused()
{
	return _pause;
}