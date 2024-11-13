#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h> 
#include<Windows.h>
#include<random>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
bool isRandomRunning = false;
void main(int argc, char** argv)
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}
GLvoid drawScene()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawScene_C()
{
	glClearColor(0, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawScene_m()
{
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawScene_y()
{
	glClearColor(1, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawScene_random() {
	int r = rand() % 2;
	int g = rand() % 2;
	int b = rand() % 2;
	glClearColor(r, g, b, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawScene_k()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
void drawInTime(int value) {
	if (isRandomRunning) {
		drawScene_random();
		glutPostRedisplay();
		glutTimerFunc(1000, drawInTime, 0);
	}
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
GLvoid Keyboard(unsigned char key, int x, int y)
{

	switch (key) {
	case 'c':glutDisplayFunc(drawScene_C); break;

	case 'm':glutDisplayFunc(drawScene_m); break;
	case 'y':glutDisplayFunc(drawScene_y); break;
	case 'w':glutDisplayFunc(drawScene); break;
	case 'k':glutDisplayFunc(drawScene_k); break;
	case 'a':glutDisplayFunc(drawScene_random); break;
	case 't':
		if (!isRandomRunning) {
			isRandomRunning = true;
			glutTimerFunc(0, drawInTime, 0);
		}
		else {
			glutTimerFunc(0, drawInTime, 0);
		}
		break;
	case 's':
		isRandomRunning = false;
		break;
	case'q':glutLeaveMainLoop(); break;
	}
	glutPostRedisplay();
}