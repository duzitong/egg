#include "RussianCube.h"
#include <GL/glut.h>


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

void CubeGrid::drawGrid()
{
	glColor4f(0.5, 0.7, 0.5, 0.75);
	glBegin (GL_QUADS);
	for (int i = 0; i < nrows; ++i)
	{
		for (int j = 0; j < ncols; ++j)
		{
			if (label[i][j] == 1)
				drawGridQuad(i,j);
		}
	}
	glEnd();
}

void CubeGrid::drawGridQuad(int i, int j)
{
	float x1 = j*dcol, x2 = (j+1)*dcol;
	float y1 = i*drow, y2 = (i+1)*drow;
	glVertex3f(x1,y1,0.0);
	glVertex3f(x2,y1,0.0);
	glVertex3f(x2,y2,0.0);
	glVertex3f(x1,y2,0.0);
}

void Game::init(float w_, float h_, int nrows_, int ncols_)
{
	nrows = nrows_;
	ncols = ncols_;
	grid = new CubeGrid(w_, h_, nrows, ncols);
	cube = new CubeElement(nrows-1,ncols/2,0);
}

void Game::step()
{
	grid->resetMovingLabel(cube);
	cube->moveDown();
	if (cube->getI() == 0)
		cube->setI(nrows-1);
	grid->setMovingLabel(cube);
}

void Game::left()
{
	grid->resetMovingLabel(cube);
	cube->moveLeft();
	if (cube->getI() == 0)
		cube->setI(nrows-1);
	grid->setMovingLabel(cube);
}

void Game::right()
{
	grid->resetMovingLabel(cube);
	cube->moveRight();
	if (cube->getI() == 0)
		cube->setI(nrows-1);
	grid->setMovingLabel(cube);
}

void Game::draw()
{
	grid->drawGrid();
}


