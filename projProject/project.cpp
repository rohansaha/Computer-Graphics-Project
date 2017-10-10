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

#include <iostream>
#include <string>
#include <math.h>
#include <GL/glut.h>


GLubyte bird[] = {
    0x80, 0x01,     // Row 1
    0x40, 0x02,     // Row 2
    0x23, 0xC4,     // Row 3
    0x24, 0x24,     // Row 4
    0x14, 0x28,     // Row 5
    0x08, 0x10,     // Row 6
    0x00, 0x00,     // Row 7
};

// Draws a bird at the given x and y coordinates
void drawBird(int x, int y) {
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);     // Only read one byte at a time
    glColor3f(0, 0, 0);
    glRasterPos2i(x, y);
    glBitmap(16, 7, 0, 0, 0, 0, bird);
}


// Draws a door
void drawDoor() {
    glLineWidth(2.5);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(-25, -300);
    glVertex2i(-25, -225);
    glVertex2i(25, -225);
    glVertex2i(25, -300);
    glEnd();
}

// Puts some text on the screen
void drawHouseNumber() {
    glColor3f(0, 0, 0);
    glRasterPos2f(-7, -220);
    std::string house_num = "101";
    for(int i=0; i<house_num.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, house_num.at(i));
    }
}


void filledInCircle(int x, int y, GLfloat radius) {
    // Filled in circle code taken from https://gist.github.com/linusthe3rd/803118
    // Color must be set before calling this method
    GLfloat twicePi = 2.0f * 3.14159;
    int triangleAmount = 500;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(x, y);
    for(int i=0; i<triangleAmount; i++) {
        glVertex2f(
            x + ( radius * cos( i * twicePi / triangleAmount )),
            y + ( radius * sin( i * twicePi / triangleAmount ))
        );
    }
    glEnd();
}

// Draws 2 windows
void drawWindows() {
    glColor3f(.2, .4, 0);
    filledInCircle(-100, -75, 20);
    filledInCircle(100, -75, 20);
}

// Draws a house
void drawHouse() {
    glColor3f(0, .2, .4);
    glBegin(GL_POLYGON);
    glVertex2i(-200, -300);         // Bottom left
    glVertex2i(-200, 0);           // Top left
    glVertex2i(200, 0);            // Top right
    glVertex2i(200, -300);          // Bottom right
    glEnd();
}


void myInit() {
	glClearColor(1, 1, 1, 0);			// specify a background clor: white
	gluOrtho2D(-300, 300, -300, 300);	// specify a viewing area
}


void myDisplayCallback() {
	glClear(GL_COLOR_BUFFER_BIT);
    drawHouse();
    drawWindows();
    drawDoor();
    drawHouseNumber();
    drawBird(100, 100);
    drawBird(130, 200);
    drawBird(-75, 150);
	glFlush();
}


int main(int argc, char ** argv) {
	glutInit(& argc, argv);					// optional in our environment

	glutInitWindowSize(600, 600);				// specify a window size
	glutInitWindowPosition(100, 0);				// specify a window position
	glutCreateWindow("Project 1");          		// create a titled window

	myInit();

	glutDisplayFunc(myDisplayCallback);			// register a callback

	glutMainLoop();					        // get into an infinite loop

    return 0;
}
