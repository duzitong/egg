/*
 *  main.c
 *  This program draws several overlapping filled polygons
 *  to demonstrate the effect order has on alpha blending results.
 *  Use the 't' key to toggle the order of drawing polygons.
 */


#include <cstdlib>
#include <GL/glut.h>
#include "RussianCube.h"

static int leftFirst = GL_TRUE;
float _angle = 0.0;
int nrows = 15, ncols = 10, dw = 60;

Game russianCube;


/*  Initialize alpha blending function.
 */
static void init()
{
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glShadeModel (GL_FLAT);
   glClearColor (1.0, 1.0, 1.0, 0.0);

   russianCube.init(1.1f, 1.65f, 15, 10);

}

/*
static void drawQuad(void)
{
	//draw pink quad on RHS of screen 

	glBegin (GL_QUADS);
		glColor4f(1.0, 0.0, 0.0, 0.75);
		glVertex3f(0.45f,0.3f,0.0);
		glVertex3f(0.55f,0.3f,0.0);
		glVertex3f(0.55f,0.7f,0.0);
		glVertex3f(0.45f,0.7f,0.0);
	glEnd();
}
*/

/*
static void drawCubeElement(CubeElement* element)
{

}
*/

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   russianCube.draw();

   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h) 
      gluOrtho2D (0.0, 1.0, 0.0, 1.0*(GLfloat)h/(GLfloat)w);
   else 
      gluOrtho2D (0.0, 1.0*(GLfloat)w/(GLfloat)h, 0.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'w':
		  russianCube.rotate();
		  glutPostRedisplay();
		  break;
	  case 'a':
		  /* do something here*/
		  russianCube.left();
		  glutPostRedisplay();
		  break;
	  case 's':
		  russianCube.down();
		  glutPostRedisplay();
		  break;
	  case 'd':
		  /* do something here*/
		  // your commands
		  russianCube.right();
		  glutPostRedisplay();
         break;
	  case 'p':
		 russianCube.pause();
         break;
	  case 'r':
		  russianCube.resume();
		  break;
      case 27:  /*  Escape key  */
         exit(0);
         break;
      default:
         break;
   }
}

void timer(int value)
{
	if (value == 0)
	{
		russianCube.step();
		glutPostRedisplay();
		glutTimerFunc(700, timer, russianCube.isPause());
	}
	else
	{
		glutTimerFunc(700, timer, russianCube.isPause());
	}
}

/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
   glutInitWindowSize (400, 600);
   glutCreateWindow (argv[0]);
   init();
   glutReshapeFunc (reshape);
   glutKeyboardFunc (keyboard);
   glutDisplayFunc (display);
   glutTimerFunc (700, timer, russianCube.isPause());
   glutMainLoop();
   return 0;
}
