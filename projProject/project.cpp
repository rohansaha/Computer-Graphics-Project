/*===================================================================================================
PROGRAMMER:				Matt Revell and Rohan Saha
COURSE:					CSC 525/625 Computer Graphics
MODIFIED BY:			N/A
LAST MODIFIED DATE:		10/16/2017
DESCRIPTION:			Demo: 2D Object Rendering 
NOTE:					N/A
FILES:					project.cpp, (projProject.sln, ...)
IDE/COMPILER:			MicroSoft Visual Studio 2017
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on projProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+F5					to EXECUTE
===================================================================================================*/

#include <iostream>			// includes input output stream
#include <fstream>			// includes file stream
#include <string>			// includes string
#include <gl\glut.h>		// include GLUT library

using  namespace  std;

//******* Function prototypes *********************************************************
void readFromFile(string fileInfo, GLubyte numbers[512][512][3]);
void drawPixelMap();


//******* Global Variable *********************************************************
GLubyte pixelMap[512][512][3];
int height = 512;
int width = 512;

//******* Function definitions ********************************************************
void draw_XY_Axis_PixelMap()
{
	drawPixelMap();						// draws the autumn image

	glColor3f(0, 0, 0);					// draw X and Y in color black

										//Draw X and Y Characters on positive X and Y axis
	glRasterPos2f(290, 0);									// uses (205,0) postion to print the X character
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');			// draws X character for X axis

	glRasterPos2f(0, 290);									// uses (0,205) postion to print the Y character
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');			// draws Y character for y axis

															//Draw X and Y Characters on negative X and Y axis
	glRasterPos2f(-295, 0);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');

	glRasterPos2f(0, -295);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');

	//Draw X and Y axis
	glPointSize(1);
	glBegin(GL_POINTS);					// use points to form X-Y axes
	for (int x = -280; x <= 280; x++)	// draw X-axis
		glVertex2i(x, 0);
	for (int y = -280; y <= 280; y++)	// draw Y-axis
		glVertex2i(0, y);
	glEnd();
}

void drawPixelMap()
{
	string fileName = "C:\\TEMP\\autumn.bin";

	// reads the binary file
	readFromFile(fileName, pixelMap);

	//sets the raster position
	glRasterPos2f(-255, -255);

	// draws the pixels
	glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelMap);
}

void readFromFile(string fileInfo, GLubyte numbers[512][512][3])
{
	ifstream fin;

	// open a file
	fin.open(fileInfo, ios::binary);

	if (!fin)
	{
		cerr << "Unable to open file ";
		exit(0);   // call system to stop
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				fin.read((char*)&numbers[i][j][k], sizeof(GLubyte));
			}
		}
	}

	// deallocates memory for fin
	fin.close();
}

void myInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	gluOrtho2D(-300, 300, -300, 300);	// specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	draw_XY_Axis_PixelMap();			// draw the X-Y axis and then draws the bitmap

	glFlush();						// flush out the buffer contents
}

//***********************************************************************************
void main(int argc, char ** argv)
{
	//glutInit(& argc, argv);					// optional in our environment

	glutInitWindowSize(600, 600);				// specify a window size
	glutInitWindowPosition(100, 0);				// specify a window position
	glutCreateWindow("2D Object Rendering");			// create a titled window

	myInit();									// setting up

	glutDisplayFunc(myDisplayCallback);			// register a callback

	glutMainLoop();								// get into an infinite loop

												// deallocates memory for pixelmap array
	delete pixelMap[512][512];
	delete pixelMap[512];
	delete pixelMap;
}