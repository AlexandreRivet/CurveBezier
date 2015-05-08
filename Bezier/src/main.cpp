#include "includes.h"
#include "global.h"
#include "interface.h"

void reshape(int w, int l)
{
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	// Clear de la zone de dessin
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	bezier.compute();
	bezier.draw();

	// Dessin du carré d'édition
	if (BEZIER_EDITED != -1)
	{
		Vector2 vector_tmp = bezier.getPointAt(CURRENT_VERTEX_EDITED - 1);

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex2f(vector_tmp.getX() - 5, vector_tmp.getY() - 5);
		glVertex2f(vector_tmp.getX() + 5, vector_tmp.getY() - 5);
		glVertex2f(vector_tmp.getX() + 5, vector_tmp.getY() + 5);
		glVertex2f(vector_tmp.getX() - 5, vector_tmp.getY() + 5);
		glEnd();
	}

	glFlush();
}

int main(int argc, char** argv)
{
	/*bezier.add(Vector2(77, 152));
	bezier.add(Vector2(218, 148));
	bezier.add(Vector2(328, 241));
	bezier.add(Vector2(135, 197));
	bezier.add(Vector2(123, 108));
	bezier.add(Vector2(272, 50));*/
	bezier.compute();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Fenetrage et remplissage");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();
	return 0;
}