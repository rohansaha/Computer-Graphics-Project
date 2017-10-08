/*===================================================================================================
PROGRAMMER:				Matt Revell and Rohan Saha
COURSE:					CSC 525/625 Computer Graphics
MODIFIED BY:			N/A
LAST MODIFIED DATE:		10/16/2017
DESCRIPTION:			Project 1
NOTE:					N/A
FILES:					project.cpp
IDE/COMPILER:			MicroSoft Visual Studio 2017
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on projProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+F5					to EXECUTE
Optionaly for *nix enviroments
g++ -o project project.cpp -lglut -lGLU -lGL
===================================================================================================*/

#include <GL/glut.h>


//******* Function definitions ********************************************************
void drawAxis() {
	glColor3f(0, 0, 0);					
							
	glRasterPos2f(290, 0);			
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');	

	glRasterPos2f(0, 290);			
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');

	//Draw X and Y axis
	glPointSize(1);
	glBegin(GL_POINTS);
	for (int x = -280; x <= 280; x++)	// draw X-axis
		glVertex2i(x, 0);
	for (int y = -280; y <= 280; y++)	// draw Y-axis
		glVertex2i(0, y);
	glEnd();
}


void myInit() {
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	gluOrtho2D(-300, 300, -300, 300);	// specify a viewing area
}

//***********************************************************************************
void myDisplayCallback() {
	glClear(GL_COLOR_BUFFER_BIT);

        drawAxis();

	glFlush();
}

//***********************************************************************************
int main(int argc, char ** argv) {
	glutInit(& argc, argv);					// optional in our environment

	glutInitWindowSize(600, 600);				// specify a window size
	glutInitWindowPosition(100, 0);				// specify a window position
	glutCreateWindow("Project 1");          		// create a titled window

	myInit();						// setting up

	glutDisplayFunc(myDisplayCallback);			// register a callback

	glutMainLoop();					        // get into an infinite loop

        return 0;
}
