/*
 * Main.c
 *
 *  Created on: 31.01.2019
 *      Author: Lukas Reining
 */
#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <GL/glut.h>

#define PRINT_FPS 1
#define RECURSIONS 3

//Drawing stuff
int WINDOW_WIDTH = 400;
int WINDOW_HEIGHT = 300;
int PREV_WINDOW_WIDTH = 400;
int PREV_WINDOW_HEIGHT = 400;
char windowTitle[25];
unsigned char fullscreen;

int t_lastFrame = 0;
int t_fpsUpdate = 0;
int fpsCounter = 0;
int fps = 0;

//Sierpinski stuff
int recursions = RECURSIONS;

typedef struct {
	int x1, y1;
	int x2, y2;
	int x3, y3;
} triangle;

void update(int elapsed) {
}

void sierpinski(triangle *tri, int recs) {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(tri->x1, tri->y1);
	glVertex2f(tri->x2, tri->y2);
	glVertex2f(tri->x3, tri->y3);
	glEnd();

	if (recs-- > 0) {

		int nX1 = (tri->x1 + tri->x2) / 2;
		int nY1 = (tri->y1 + tri->y2) / 2;

		int nX2 = (tri->x1 + tri->x3) / 2;
		int nY2 = (tri->y1 + tri->y3) / 2;

		int nX3 = (tri->x2 + tri->x3) / 2;
		int nY3 = (tri->y2 + tri->y3) / 2;

		triangle newTri1 = { nX1, nY1, nX2, nY2, nX3, nY3 };
		triangle newTri2 = { tri->x1, tri->y1, nX1, nY1, nX2, nY2 };
		triangle newTri3 = { nX1, nY1, tri->x2, tri->y2, nX3, nY3 };
		triangle newTri4 = { nX2, nY2, nX3, nY3, tri->x3, tri->y3 };

		glColor3f(1, 1, 1);
		glBegin(GL_TRIANGLES);
		glVertex2f(newTri1.x1, newTri1.y1);
		glVertex2f(newTri1.x2, newTri1.y2);
		glVertex2f(newTri1.x3, newTri1.y3);
		glEnd();

		sierpinski(&newTri2, recs);
		sierpinski(&newTri3, recs);
		sierpinski(&newTri4, recs);
	}
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

	triangle tri = { 0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, WINDOW_WIDTH, 0 };
	sierpinski(&tri, recursions);

	glFlush();  // Render now
}

void loop() {
	//Calculate time sice last frame
	int t_now = glutGet(GLUT_ELAPSED_TIME);
	int elapsed = t_now - t_lastFrame;
	t_lastFrame = t_now;

	//Stuff to do
	display();
	update(elapsed);
	//End stuff to do

	//If enabled per macro, print fps
	if (PRINT_FPS) {
		fpsCounter++;
		int t_newFpsUpdate = glutGet(GLUT_ELAPSED_TIME);
		int deltaTimeFPS = t_newFpsUpdate - t_fpsUpdate;
		if (deltaTimeFPS >= 1000) {
			t_fpsUpdate = t_newFpsUpdate;
			fps = fpsCounter;
			fpsCounter = 0;
		}
		sprintf(windowTitle, "Sierpinski (%i Recursions) (FPS: %i)", recursions,
				fps);
		glutSetWindowTitle(windowTitle);
	} else {
		sprintf(windowTitle, "Sierpinski (%i Recursions)", recursions);
		glutSetWindowTitle(windowTitle);
	}
}

/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluOrtho2D(0, width, 0, height);
	glutPostRedisplay();
}

void toggle_fullscreen() {
	if (fullscreen) {
		fullscreen = 0;
		glutReshapeWindow(PREV_WINDOW_WIDTH, PREV_WINDOW_HEIGHT);
	} else {
		fullscreen = 1;
		PREV_WINDOW_WIDTH = WINDOW_WIDTH;
		PREV_WINDOW_HEIGHT = WINDOW_HEIGHT;
		glutFullScreen();
	}
}

void spec_key_pressed(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if (--recursions < 0) {
			recursions = 0;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (++recursions > 10) {
			recursions = 10;
		}
		break;
	case GLUT_KEY_F11:
		toggle_fullscreen();
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Sierpinski"); // Create a window with the given title
	//glutFullScreen();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);     // Clear the color buffer (background)

	glutKeyboardFunc(NULL); // Register callback handler for getting pressed keys
	glutSpecialFunc(spec_key_pressed); // Register callback handler for getting pressed special keys
	glutKeyboardUpFunc(NULL); // Register callback handler for getting released keys
	glutSpecialUpFunc(NULL); // Register callback handler for getting realeased special keys
	glutReshapeFunc(reshape); // Register callback handler for window re-shape
	glutDisplayFunc(loop); // Register display callback handler for window re-paint
	glutIdleFunc(loop); //Constantly recall the display function
	glutMainLoop();           // Enter the event-processing loop
	return EXIT_SUCCESS;
}
