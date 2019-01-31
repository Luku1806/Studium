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
#include <pthread.h>

#define PRINT_FPS 1

//Drawing stuff
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 400;
char windowTitle[25];

int t_lastFrame = 0;
int t_fpsUpdate = 0;
int fps = 0;

double **picBuffer = NULL;

//Navigation stuff
float movement_speed = 0.001;
unsigned char up = 0;
unsigned char down = 0;
unsigned char left = 0;
unsigned char right = 0;
unsigned char zoomIn = 0;
unsigned char zoomOut = 0;
unsigned char resUp = 0;
unsigned char resDown = 0;

//Mandelbrot stuff
int max_iteration = 100;

double middleX = -0.75;
double middleY = 0;

double rangeX = 3.5;
double rangeY = 2;

//Used for giving arguments into mandelbrotthread
typedef struct mta {
	int id;
	int threadCount;
} thread_args;

////////////////////////MANDELBROT////////////////////////////////////////

void delBuffer() {
	if (picBuffer != NULL) {
		free(picBuffer);
	}
}

void initBuffer() {
	delBuffer();
	// allocate data pointers
	//allocate memory for rows
	picBuffer = (double **) malloc(WINDOW_WIDTH * sizeof(double*));
	//for each row allocate memory for columns
	for (int i = 0; i < WINDOW_WIDTH; i++) {
		picBuffer[i] = (double *) malloc(WINDOW_HEIGHT * sizeof(double));
	}
}

void calcImage() {
	if (picBuffer == NULL) {
		initBuffer();
	}
	for (int x = 0; x < WINDOW_WIDTH; x++) {
		for (int y = 0; y < WINDOW_HEIGHT; y++) {

			double x0 = (double) x / (double) WINDOW_WIDTH;
			double y0 = (double) y / (double) WINDOW_HEIGHT;

			x0 = x0 * rangeX + middleX - rangeX / 2;
			y0 = y0 * rangeY + middleY - rangeY / 2;

			double real = 0;
			double imaginary = 0;

			int iteration = 0;
			while (real * real + imaginary * imaginary <= 4
					&& iteration < max_iteration) {
				double temp = real * real - imaginary * imaginary + x0;
				imaginary = 2 * real * imaginary + y0;
				real = temp;
				iteration++;
			}

			double colorVal = (double) iteration / max_iteration;
			picBuffer[x][y] = colorVal;
		}
	}
}

void *calcImageParallel(void *args) {
	thread_args* targs = (thread_args*) args;
	if (picBuffer == NULL) {
		initBuffer();
	}
	for (int x = targs->id; x < WINDOW_WIDTH; x += targs->threadCount) {
		for (int y = 0; y < WINDOW_HEIGHT; y++) {

			double x0 = (double) x / (double) WINDOW_WIDTH;
			double y0 = (double) y / (double) WINDOW_HEIGHT;

			x0 = x0 * rangeX + middleX - rangeX / 2;
			y0 = y0 * rangeY + middleY - rangeY / 2;

			double real = 0;
			double imaginary = 0;

			int iteration = 0;
			while (real * real + imaginary * imaginary <= 4
					&& iteration < max_iteration) {
				double temp = real * real - imaginary * imaginary + x0;
				imaginary = 2 * real * imaginary + y0;
				real = temp;
				iteration++;
			}

			double colorVal = (double) iteration / max_iteration;
			picBuffer[x][y] = colorVal;
		}
	}
	pthread_exit(0);
	return NULL;
}

void doParralelCalc(int threadCount) {
	pthread_t threads[threadCount];
	thread_args *arguments[threadCount];
	for (int i = 0; i < threadCount; i++) {
		arguments[i] = malloc(sizeof(thread_args));
		arguments[i]->id = i;
		arguments[i]->threadCount = threadCount;
		pthread_create(&threads[i], NULL, &calcImageParallel,
				(void*) arguments[i]);
	}
	//Join them all
	for (int i = 0; i < threadCount; i++) {
		pthread_join(threads[i], NULL);
		free(arguments[i]);
	}
}

///////////////////////END MANDELBROT////////////////////////////////////

void update(int elapsed) {
	int newMaxIteration;
	if (down) {
		middleY -= movement_speed * rangeY * elapsed;
	}
	if (left) {
		middleX -= movement_speed * rangeX * elapsed;
	}
	if (up) {
		middleY += movement_speed * rangeY * elapsed;
	}
	if (right) {
		middleX += movement_speed * rangeX * elapsed;
	}
	if (zoomOut) {
		rangeX /= 0.8;
		rangeY /= 0.8;
	}
	if (zoomIn) {
		rangeX *= 0.8;
		rangeY *= 0.8;
	}
	if (resDown) {
		newMaxIteration = (int) (max_iteration * 0.9);
		if (newMaxIteration == max_iteration) {
			max_iteration--;
		} else {
			max_iteration = newMaxIteration;
		}
	}
	if (resUp) {
		newMaxIteration = (int) (max_iteration / 0.9);
		if (newMaxIteration == max_iteration) {
			max_iteration++;
		} else {
			max_iteration = newMaxIteration;
		}
	}
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (int x = 0; x < WINDOW_WIDTH; x++) {
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			glColor3f(picBuffer[x][y], 0, 0);
			glVertex2i(x, y);
		}
	}
	glEnd();
	glFlush();  // Render now
}

void loop() {
	//Calculate time sice last frame
	int t_now = glutGet(GLUT_ELAPSED_TIME);
	int elapsed = t_now - t_lastFrame;
	t_lastFrame = t_now;

	//Calc, render, move
	//calcImage();
	doParralelCalc(8);
	display();
	update(elapsed);

	//If enabled per macro, print fps
	if (PRINT_FPS) {
		fps++;
		int t_newFpsUpdate = glutGet(GLUT_ELAPSED_TIME);
		int deltaTimeFPS = t_newFpsUpdate - t_fpsUpdate;
		if (deltaTimeFPS >= 1000) {
			t_fpsUpdate = t_newFpsUpdate;
			sprintf(windowTitle, "Mandelbrot (FPS: %i)", fps);
			glutSetWindowTitle(windowTitle);
			fps = 0;
		}
	}
}

/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	initBuffer();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluOrtho2D(0, width, 0, height);
	glutPostRedisplay();
}

void key_pressed(unsigned char key, int x, int y) {
	switch (key) {
	case 's':
		down = 1;
		break;
	case 'a':
		left = 1;
		break;
	case 'w':
		up = 1;
		break;
	case 'd':
		right = 1;
		break;
	case '-':
		zoomOut = 1;
		break;
	case '+':
		zoomIn = 1;
		break;
	case 'q':
		resDown = 1;
		break;
	case 'e':
		resUp = 1;
		break;
	}
}

void spec_key_pressed(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_DOWN:
		key_pressed('s', 0, 0);
		break;
	case GLUT_KEY_LEFT:
		key_pressed('a', 0, 0);
		break;
	case GLUT_KEY_UP:
		key_pressed('w', 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		key_pressed('d', 0, 0);
		break;
	}
}

void key_released(unsigned char key, int x, int y) {
	switch (key) {
	case 's':
		down = 0;
		break;
	case 'a':
		left = 0;
		break;
	case 'w':
		up = 0;
		break;
	case 'd':
		right = 0;
		break;
	case '-':
		zoomOut = 0;
		break;
	case '+':
		zoomIn = 0;
		break;
	case 'q':
		resDown = 0;
		break;
	case 'e':
		resUp = 0;
		break;
	}
}

void spec_key_released(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_DOWN:
		key_released('s', 0, 0);
		break;
	case GLUT_KEY_LEFT:
		key_released('a', 0, 0);
		break;
	case GLUT_KEY_UP:
		key_released('w', 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		key_released('d', 0, 0);
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("Mandelbrot"); // Create a window with the given title
	//glutFullScreen();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);     // Clear the color buffer (background)

	glutKeyboardFunc(key_pressed); // Register callback handler for getting pressed keys
	glutSpecialFunc(spec_key_pressed); // Register callback handler for getting pressed special keys
	glutKeyboardUpFunc(key_released); // Register callback handler for getting released keys
	glutSpecialUpFunc(spec_key_released); // Register callback handler for getting realeased special keys
	glutReshapeFunc(reshape); // Register callback handler for window re-shape
	glutDisplayFunc(loop); // Register display callback handler for window re-paint
	glutIdleFunc(loop); //Constantly recall the display function
	glutMainLoop();           // Enter the event-processing loop
	delBuffer();
	return EXIT_SUCCESS;
}
