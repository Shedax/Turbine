#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
float current_angle = 0.1f;
float step_angle;
float Xcenter = 168.0f;
float Ycenter = 180.0f;
int num = 1;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 400, 0.0, 300.0);
}

void drawTurbine() {
	ifstream F;
	F.open("speed.txt");//opening the file 
	if (F)//if the file was opened correctly
	{
		std::string s;
		std::getline(F, s); //speed data
		size_t digits = s.find_first_of("1234567890+-");
		num = atoi(s.c_str() + digits);//getting a number from a string
		std::cout << "" << std::endl;
		F.close();//closing the stream
	}
	step_angle = 0.1f * num; //changing the rotation speed
	// draw the tower
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(160, 40);
	glVertex2f(163, 180);
	glVertex2f(160, 40);
	glVertex2f(175, 40);
	glVertex2f(175, 40);
	glVertex2f(172, 180);
	glEnd();
	// Rotate 
	glPushMatrix();
	glTranslatef(Xcenter, Ycenter, 0.0f);
	glRotatef(current_angle, 0, 0, 1);
	current_angle += step_angle;
	glTranslatef(-Xcenter, -Ycenter, 0.0f);
	// draw first rotor blade
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(173, 180);
	glVertex2f(163, 180);
	glVertex2f(168, 270);
	glEnd();
	// draw second rotor blade
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(170, 174);
	glVertex2f(175, 180);
	glVertex2f(247, 140);
	glEnd();
	// draw third rotor blade
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(162, 180);
	glVertex2f(167, 174);
	glVertex2f(88, 140);
	glEnd();
	// circle in the middle
	float theta;
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i <= 360; i++) {
		theta = i * 3.142 / 180;
		glVertex2f(168 + 7 * cos(theta), 180 + 6.5 * sin(theta));
	}
	glEnd();
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawTurbine(); //drawing process
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay(); //marks the current window as needing to be redisplayed
}

void idle() {
	display();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //initialize the GLUT library
	//canvas settings
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Wind Turbine");
	init();
	glutIdleFunc(idle); //global idle callback
	glutDisplayFunc(display);
	glutMainLoop(); // looping of the drawing process
	return 0;
}