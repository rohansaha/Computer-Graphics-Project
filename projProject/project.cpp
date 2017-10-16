/*===================================================================================================
PROGRAMMER:			Matt Revell and Rohan Saha
COURSE:				CSC 525/625 Computer Graphics
MODIFIED BY:			1. Matt Revell (50%)
					a. Design
					b. Bitmap for Birds
					c. Circles for Windows
					d. Lines for Door
					e. Text
				2. Rohan Saha (50%)
					a. Background PixelMap
					b. Polygon for House
					c. House Polygon Stipple
					d. Door Polygon Stipple
					e. Window Design
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

#include <iostream>			// includes IO stream lib
#include <fstream>			// includes file stream lib
#include <string>			// includes string lib
#include <math.h>			// includes math lib
#include <GL/glut.h>		// includes glut lib

//******* Function Prototype *********************************************************
void drawPolygon();
void writeToFile();
void drawCircle(float x, float y, int radius);
void filledInCircle(int x, int y, GLfloat radius);

//******* Global Variable *********************************************************
GLubyte pixelMap[600][600][3];
GLubyte readPixelMap[512][512][3];
int height = 600;
int width = 600;


// bitmap pattern for house 
GLubyte pattern1[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

// bitmap pattern for door 
GLubyte pattern2[] = {
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF };

// bitmap data for bird
GLubyte bird[] = {
	0x80, 0x01,     // Row 1
	0x40, 0x02,     // Row 2
	0x23, 0xC4,     // Row 3
	0x24, 0x24,     // Row 4
	0x14, 0x28,     // Row 5
	0x08, 0x10,     // Row 6
	0x00, 0x00,     // Row 7
};

//******* Function Definitions *********************************************************
void readFromFile() {
	std::ifstream fin;
	std::string fileInfo = "background.bin";
	// open a file
	fin.open(fileInfo, std::ios::binary);

	if (!fin)
	{
		std::cerr << "Unable to open " << fileInfo;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				fin.read((char*)&pixelMap[i][j][k], sizeof(GLubyte));
			}
		}
	}
	// deallocates memory for fin
	fin.close();
}

// Draws background image
void drawBackground() {
	// reads the binary file
	readFromFile();

	//sets the raster position
	glRasterPos2f(-300, -300);

	// draws the pixels
	glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelMap);
}

// Draws a house
void drawHouse() {
	glColor3f(0.502, 0.000, 0.000);			//maroon
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawPolygon();
	glEnable(GL_POLYGON_STIPPLE);				//Enbles Polygon stipple
	glColor3f(0.5, 0.35, 0.05);
	glPolygonStipple(pattern1);
	drawPolygon();
	glDisable(GL_POLYGON_STIPPLE);
}
void drawPolygon() {
	glBegin(GL_POLYGON);
	glVertex2i(-200, -200);         // Bottom left
	glVertex2i(-200, 100);           // Top left
	glVertex2i(200, 100);            // Top right
	glVertex2i(200, -200);          // Bottom right
	glEnd();
}

// Draws a door
void drawDoor() {
	//Draws frame for the door
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(-50, -200);
	glVertex2i(-50, -60);
	glVertex2i(50, -60);
	glVertex2i(50, -200);
	glEnd();

	//Draws door surface
	glColor3f(0.502, 0.000, 0.000);			//maroon
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2f(-48.5, -199);
	glVertex2f(-48.5, -61);
	glVertex2f(48, -61);
	glVertex2f(48, -199);
	glEnd();

	//Draws pattern for data
	glEnable(GL_POLYGON_STIPPLE);
	glColor3f(0.467, 0.533, 0.600);			//light state blue
	glPolygonStipple(pattern2);
	glBegin(GL_POLYGON);
	glVertex2f(-48.5, -199);
	glVertex2f(-48.5, -61);
	glVertex2f(48, -61);
	glVertex2f(48, -199);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

	//Draw door knob
	glColor3f(0, 0, 0);
	filledInCircle(35, -140, 5);
}

// Puts some text on the screen
void drawHouseNumber() {
	glColor3f(1.000, 1.000, 0.878);		// light yellow
	glRasterPos2f(-20, -50);
	std::string house_num = "101";
	for (int i = 0; i < house_num.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, house_num.at(i));
	}
}


void filledInCircle(int x, int y, GLfloat radius) {
	// Filled in circle code taken from https://gist.github.com/linusthe3rd/803118
	// Color must be set before calling this method
	GLfloat twicePi = 2.0f * 3.14159;
	int triangleAmount = 500;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(x, y);
	for (int i = 0; i < triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

//Draws frame for windows
void drawCircle(float xC, float yC, int radius) {
	const float pi = 3.141592653f;			// constant PI value
	for (float angle = 0; angle <= 2 * pi; angle += 0.01) {
		glBegin(GL_POINTS);					// uses points to draw face
		glVertex2f(xC + (radius*cos(angle)), yC + (radius*sin(angle)));				// draw the vertex point at the specified co-ordinate
		glEnd();
	}
}

// Draws 2 windows
void drawWindows() {
	//draws window frame
	glPointSize(3);
	glColor3f(0, 0, 0);
	drawCircle(-100, -15, 50);
	drawCircle(100, -15, 50);

	//draws windows glass
	glColor3f(0.439, 0.502, 0.565);		//slate grey
	filledInCircle(-100, -15, 48);
	filledInCircle(100, -15, 48);

	glLineWidth(2.5);
	// draws window pane
	glColor3f(0, 0, 0);					// color black
	glBegin(GL_LINE_STRIP);
	glVertex2i(-148, -15);
	glVertex2i(-52, -15);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2i(52, -15);
	glVertex2i(148, -15);
	glEnd();
}

// Draws bird at x, y location
void drawBird(int x, int y) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);     // Only read one byte at a time
	glColor3f(0, 0, 0);
	glRasterPos2i(x, y);
	glBitmap(16, 7, 0, 0, 0, 0, bird);
}

//Stores final image to binary file
void storeImage() {
	glReadPixels(50, 50, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, readPixelMap);
	writeToFile();
}

void writeToFile() {
	std::ofstream fout;
	std::string fileInfo = "C:\\TEMP\\savedImg.bin";
	// 1. open a file
	fout.open(fileInfo, std::ios::binary);
	if (!fout)
	{
		std::cerr << "Unable to open file savedImg.bin";
	}

	// 2. write to the file
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				fout.write((char *)&readPixelMap[i][j][k], sizeof(GLubyte));
			}
		}
	}

	// 3. wrap up
	fout.close();
}

void myInit() {
	glClearColor(1, 1, 1, 0);			// specify a background clor: white
	gluOrtho2D(-300, 300, -300, 300);	// specify a viewing area
}

void myDisplayCallback() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawBackground();
	drawHouse();
	drawWindows();
	drawDoor();
	drawHouseNumber();
	drawBird(-200, 200);
	drawBird(200, 200);
	drawBird(-100, 150);
	drawBird(100, 150);
	storeImage();
	glFlush();
}


int main(int argc, char ** argv) {
	glutInit(&argc, argv);					// optional in our environment

	glutInitWindowSize(600, 600);				// specify a window size
	glutInitWindowPosition(100, 0);				// specify a window position
	glutCreateWindow("Project 1");          		// create a titled window

	myInit();

	glutDisplayFunc(myDisplayCallback);			// register a callback

	glutMainLoop();					        // get into an infinite loop

	return 0;
}
