#include "global.h"
#include "Interface.h"

// Fonction appelée par le clavier
void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case '+':
		bezier.incStep();
		break;
	case '-':
		bezier.decStep();
		break;
	case 'r':
		bezier.reset();
		BEZIER_EDITED = -1;
		CURRENT_VERTEX_EDITED = 0;
		break;
	}

	glutPostRedisplay();
}

// Fonction appelée pour toute action de la souris (UP & DOWN)
void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		mouseDown(button, x, y);

	else if (state == GLUT_UP)
		mouseUp(button, x, y);
}

// Fonction appelée lorsque l'on bouge la souris
void motion(int x, int y)
{
	float xF = x;
	float yF = y;

	if (MIDDLE_BUTTON_PRESSED == true)
	{
		if (BEZIER_EDITED == 1)
		{
			if (CURRENT_VERTEX_EDITED >= 0 && CURRENT_VERTEX_EDITED <= bezier.getNbVertices())
			{
				bezier.getPointAt(CURRENT_VERTEX_EDITED - 1).setX(xF);
				bezier.getPointAt(CURRENT_VERTEX_EDITED - 1).setY(yF);
			}
		}
	}

	glutPostRedisplay();
}

// Fonction appelée lorsque l'on enfonce un bouton de la souris
void mouseDown(int button, int x, int y)
{
	float xF = x;
	float yF = y;

	// Clic gauche => Ajout d'un nouveau point dans le polygone en cours (soit à la fin soit insertion à l'espace en cours
	if (button == GLUT_LEFT_BUTTON)
	{
		if (CURRENT_VERTEX_EDITED == bezier.getNbVertices())
			bezier.add(Vector2(xF, yF));
		else
			bezier.insert(CURRENT_VERTEX_EDITED, Vector2(xF, yF));

		CURRENT_VERTEX_EDITED++;
		if (BEZIER_EDITED == -1)
			BEZIER_EDITED = 1;
	}

	// Clic molette:
	// - Début de drag
	// - Calcul du point le plus proche pour savoir quel point on édite
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		MIDDLE_BUTTON_PRESSED = true;

		float distance = 1000.0;
		if (BEZIER_EDITED == 1)
		{
			unsigned int size = bezier.getNbVertices();
			for (unsigned int i = 0; i < size; ++i)
			{
				Vector2 currentPoint = bezier.getPointAt(i);
				float currentDistance = currentPoint.distance(Vector2(xF, yF));
				if (currentDistance < distance)
				{
					distance = currentDistance;
					CURRENT_VERTEX_EDITED = (i + 1);
				}
			}
		}
	}

	glutPostRedisplay();
}

// Fonction appelée lorsque l'on relâche un bouton de la souris
void mouseUp(int button, int x, int y)
{
	if (button == GLUT_MIDDLE_BUTTON)
	{
		MIDDLE_BUTTON_PRESSED = false;
	}
}