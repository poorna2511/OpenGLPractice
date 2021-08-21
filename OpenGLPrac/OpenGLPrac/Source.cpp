// C program to demonstrate
// drawing a circle using
// OpenGL
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<vector>
using namespace std;

#define pi 3.142857

float xPos = 0;
float yPos = 0;

struct Circle
{
	int x = -600, y = 0;
	bool prevCollidedStat = false;
	bool curCollidedStat = false;
};

Circle redCircle1, redCircle2, redCircle3, redCircle4, redCircle5, redCircle6, blueCircle;

vector<Circle> vectOfRedCircles, vectOfBlueCircles;

float blackCircleRadius = 16;
int justARandNum = 0;//for backgeoud color changing

// function to initialize
void myInit(void)
{
	// making background color black as first
	// 3 arguments all are 0.0
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// making picture color green (in RGB mode), as middle argument is 1.0
	glColor4f(0.0, 0.0, 1.0, 0.9f);

	// breadth of picture boundary is 1 pixel
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// setting window dimension in X- and Y- direction
	gluOrtho2D(-500, 500, -250, 250);
}

bool isKeyPressed = false;

void MoveCircles(Circle &circle)
{
	glBegin(GL_TRIANGLES);

	int redCricleXPos, redCricleYPos;

	if (circle.x <= -600)
	{
		circle.x = 600;
		circle.y = rand() % 400 - 200;
	}

	float x, y, i;

	for (i = 0; i < (2 * pi); i += 0.001)
	{
		x = 20 * cos(i) + circle.x;
		y = 20 * sin(i) + circle.y;

		glVertex2i(x, y);

		x = 20 * cos(i + 0.001) + circle.x;
		y = 20 * sin(i + 0.001) + circle.y;

		glVertex2i(x, y);
		glVertex2i(circle.x, +circle.y);
	}

	if (isKeyPressed == false)
		circle.x = circle.x - 2;
	else
	{
		circle.x = circle.x - 10;
	}

	glEnd();
}

void ColiderAction()
{
	for (int idx = 0; idx < vectOfRedCircles.size(); idx++)
	{
		Circle &redCircle = vectOfRedCircles[idx];

		//collide check for red circle 1
		float centerDist = sqrt(((xPos - 250 - redCircle.x)*(xPos - 250 - redCircle.x)) + (((200 * sin(yPos)) - redCircle.y)*((200 * sin(yPos)) - redCircle.y)));

		if (centerDist < 20 + blackCircleRadius && blackCircleRadius > 2)
			redCircle.curCollidedStat = true;
		else
			redCircle.curCollidedStat = false;

		if (redCircle.prevCollidedStat == false && redCircle.curCollidedStat == true)
			blackCircleRadius = blackCircleRadius/2;

		redCircle.prevCollidedStat = redCircle.curCollidedStat;
	}

	//collide check for blue circle
	float centerDist = sqrt(((xPos - 250 - blueCircle.x)*(xPos - 250 - blueCircle.x)) + (((200 * sin(yPos)) - blueCircle.y)*((200 * sin(yPos)) - blueCircle.y)));

	if (centerDist < 20 + blackCircleRadius && blackCircleRadius < 100)
		blueCircle.curCollidedStat = true;
	else
		blueCircle.curCollidedStat = false;

	if (blueCircle.prevCollidedStat == false && blueCircle.curCollidedStat == true)
	{
		justARandNum = rand() % 100;
		blackCircleRadius = blackCircleRadius * 2;
	}

	blueCircle.prevCollidedStat = blueCircle.curCollidedStat;
}

bool redCircle2CanStart = false;
bool blueCircleCanStart = false;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	float x, y, i;
	glColor4f(0.0, 0.0, 0.0, 0.9f);

	// iterate y up to 2*pi, i.e., 360 degree
	// with small increment in angle as
	// glVertex2i just draws a point on specified co-ordinate
	for (i = 0; i < (2 * pi); i += 0.001)
	{
		// let 200 is radius of circle and as,
		// circle is defined as x=r*cos(i) and y=r*sin(i)
		x = blackCircleRadius * cos(i) + xPos;
		y = blackCircleRadius * sin(i) +(200 * sin(yPos));

		glVertex2i(x - 250, y);

		x = blackCircleRadius * cos(i + 0.001) + xPos;
		y = blackCircleRadius * sin(i + 0.001) + (200 * sin(yPos));

		glVertex2i(x - 250, y);
		glVertex2i(xPos - 250, (200 * sin(yPos)));
	}

	glEnd();

	yPos = yPos + 0.02;

	glColor4f(1.0, 0.0, 0.0, 0.9f);
	
	for (int idx = 0; idx < vectOfRedCircles.size(); idx++)
	{
		MoveCircles(vectOfRedCircles[idx]);
	}
	
	//blue circles
	glColor4f(0.0, 0.0, 1.0, 0.9f);

	MoveCircles(blueCircle);

	//just for background color changes ...LOL
	if (isKeyPressed == true)
	{
		double x = blueCircle.x, y = blueCircle.y, z;
		x = (abs(x) + justARandNum)/(500 + justARandNum);
		y = (abs(y) + justARandNum )/ (500 + justARandNum);
		z = (x + y)/2;

		glClearColor(x, y, z, 1.0f);
		glutPostRedisplay();
	}

	////red circles 1
	//glColor4f(1.0, 0.0, 0.0, 0.9f);
	//MoveCircles(redCircle1);

	////red circles 2
	//if (redCircle1.x < 5 && redCircle2CanStart == false)
	//	redCircle2CanStart = true;

	//if (redCircle2CanStart == true)
	//	MoveCircles(redCircle2);

	////blue circles
	//glColor4f(0.0, 0.0, 1.0, 0.9f);

	//if (redCircle2.x < 150 && redCircle2CanStart == true && blueCircleCanStart == false)
	//	blueCircleCanStart = true;

	//if( blueCircleCanStart == true)
	//	MoveCircles(blueCircle);

	isKeyPressed = false;

	ColiderAction();

	glFlush();
}

void keyDown(int key, int x, int y)
{
	isKeyPressed = true;


	//if (key == GLUT_KEY_RIGHT)
	//	xPos = xPos + 10;

	//if (key == GLUT_KEY_LEFT)
	//	xPos = xPos - 10;

	//if (key == GLUT_KEY_UP)
	//	yPos = yPos + 3;

	//if (key == GLUT_KEY_DOWN)
	//	yPos = yPos - 3;

	//glutPostRedisplay();
}

/* Called back when timer expired [NEW] */
void timer(int value) {
	glutPostRedisplay();      // Post re-paint request to activate display()
	glutTimerFunc(10, timer, 0); // next timer call milliseconds later
}

int main(int argc, char** argv)
{
	blueCircle.x = 900;

	vectOfRedCircles.push_back(redCircle1);
	vectOfRedCircles.push_back(redCircle2);
	vectOfRedCircles.push_back(redCircle3);
	vectOfRedCircles.push_back(redCircle4);
	vectOfRedCircles.push_back(redCircle5);
	vectOfRedCircles.push_back(redCircle6);

	for (int idx = 0; idx < vectOfRedCircles.size(); idx++)
	{
		vectOfRedCircles[idx].x = -600 + (idx + 1)*(1200 / (vectOfRedCircles.size() + 1));
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glShadeModel(GL_SMOOTH);

	// giving window size in X- and Y- direction
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(0, 0);

	// Giving name to window
	glutCreateWindow("Circle Drawing");
	myInit();
	
	glutDisplayFunc(display);
	glutSpecialFunc(keyDown);

	glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]

	glutMainLoop();

	return 0;
}
