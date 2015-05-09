#include <iostream>
#include <string>

#include "global.h"
#include "interface.h"

void specialKey(int k, int x, int y)
{
	float stepT = 5.0f;
	float stepR = 2.0f;
	float stepS = 0.5f;
	switch (k)
	{
	case GLUT_KEY_UP:
		if (CURRENT_CURVE_EDITED >= 0 && CURRENT_CURVE_EDITED < curves.size())
		{
			switch (TRANSFORMATION_MODE)
			{
			case TRANSLATION:
				curves[CURRENT_CURVE_EDITED]->translate(0.0f, -stepT);
				break;
			case ROTATION:
				curves[CURRENT_CURVE_EDITED]->scale(1.0f, stepS + 1.0f);
				break;
			}
		}
		break;
	case GLUT_KEY_DOWN:
		if (CURRENT_CURVE_EDITED >= 0 && CURRENT_CURVE_EDITED < curves.size())
		{
			switch (TRANSFORMATION_MODE)
			{
			case TRANSLATION:
				curves[CURRENT_CURVE_EDITED]->translate(0.0f, -stepT);
				break;
			case SCALING:
				curves[CURRENT_CURVE_EDITED]->translate(0.0f, stepT);
				break;
			}
		}
		break;
	case GLUT_KEY_LEFT:
		if (CURRENT_CURVE_EDITED >= 0 && CURRENT_CURVE_EDITED < curves.size())
		{
			switch (TRANSFORMATION_MODE)
			{
			case TRANSLATION:
				curves[CURRENT_CURVE_EDITED]->translate(-stepT, 0.0f);
				break;
			case ROTATION:
				curves[CURRENT_CURVE_EDITED]->rotate(-stepR);
				break;
			case SCALING:
				curves[CURRENT_CURVE_EDITED]->scale(stepS, 1.0f);
				break;
			}
		}
		break;
	case GLUT_KEY_RIGHT:
		if (CURRENT_CURVE_EDITED >= 0 && CURRENT_CURVE_EDITED < curves.size())
		{
			switch (TRANSFORMATION_MODE)
			{
			case TRANSLATION:
				curves[CURRENT_CURVE_EDITED]->translate(stepT, 0.0f);
				break;
			case ROTATION:
				curves[CURRENT_CURVE_EDITED]->rotate(stepR);
				break;
			case SCALING:
				curves[CURRENT_CURVE_EDITED]->scale(stepS + 1.0f, 1.0f);
				break;
			}
		}
		break;
	}

	glutPostRedisplay();
}

// Fonction appelée par le clavier
void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
		CURRENT_CURVE_EDITED = -1;
		CURRENT_VERTEX_EDITED = 0;
		glutPostRedisplay();
		break;
	case 127:
		if (CURRENT_CURVE_EDITED >= 0 && CURRENT_CURVE_EDITED < curves.size())
		{
			if (CURRENT_VERTEX_EDITED >= 1)
			{
				curves[CURRENT_CURVE_EDITED]->remove(CURRENT_VERTEX_EDITED - 1);
				curves[CURRENT_CURVE_EDITED]->compute();

				if (CURRENT_VERTEX_EDITED > curves[CURRENT_CURVE_EDITED]->getNbVertices())
					CURRENT_VERTEX_EDITED = curves[CURRENT_CURVE_EDITED]->getNbVertices();
			}
		}
		glutPostRedisplay();
		break;
	case '+':
		if (CURRENT_CURVE_EDITED >= 0 && CURRENT_CURVE_EDITED < curves.size())
		{
			curves[CURRENT_CURVE_EDITED]->incStep();
			curves[CURRENT_CURVE_EDITED]->compute();
		}
		glutPostRedisplay();
		break;
	case '-':
		if (CURRENT_CURVE_EDITED >= 0 && CURRENT_CURVE_EDITED < curves.size())
		{
			curves[CURRENT_CURVE_EDITED]->decStep();
			curves[CURRENT_CURVE_EDITED]->compute();
		}
		glutPostRedisplay();
		break;
	case 'r':
		if (CURRENT_CURVE_EDITED >= 0 && CURRENT_CURVE_EDITED < curves.size())
		{
			curves[CURRENT_CURVE_EDITED]->reset();
			CURRENT_VERTEX_EDITED = 0;
		}
		glutPostRedisplay();
		break;
	}
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
		if (CURRENT_CURVE_EDITED >= 0 && CURRENT_CURVE_EDITED < curves.size())
		{
			if (CURRENT_VERTEX_EDITED >= 0 && CURRENT_VERTEX_EDITED <= curves[CURRENT_CURVE_EDITED]->getNbVertices())
			{
				curves[CURRENT_CURVE_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1).setX(xF);
				curves[CURRENT_CURVE_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1).setY(yF);
				curves[CURRENT_CURVE_EDITED]->compute();
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
		if (CURRENT_CURVE_EDITED >= 0 && CURRENT_CURVE_EDITED < curves.size())
		{
			if (CURRENT_VERTEX_EDITED == curves[CURRENT_CURVE_EDITED]->getNbVertices())
				curves[CURRENT_CURVE_EDITED]->add(Vector2(xF, yF));
			else
				curves[CURRENT_CURVE_EDITED]->insert(CURRENT_VERTEX_EDITED, Vector2(xF, yF));
			curves[CURRENT_CURVE_EDITED]->compute();
		}
		CURRENT_VERTEX_EDITED++;
	}

	// Clic molette:
	// - Début de drag
	// - Calcul du point le plus proche pour savoir quel point on édite
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		MIDDLE_BUTTON_PRESSED = true;

		float distance = 1000.0;
		if (CURRENT_CURVE_EDITED >=0 && CURRENT_CURVE_EDITED < curves.size())
		{
			unsigned int size = curves[CURRENT_CURVE_EDITED]->getNbVertices();
			for (unsigned int i = 0; i < size; ++i)
			{
				Vector2 currentPoint = curves[CURRENT_CURVE_EDITED]->getPointAt(i);
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

void initMenu()
{
	int curveMenu = glutCreateMenu(selectCurve);
	glutAddMenuEntry("New", 11);
	
	glutCreateMenu(select);
	glutAddSubMenu("Curves", curveMenu);
	glutAddMenuEntry("Quit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void select(int selection)
{
	switch (selection)
	{
	case 2:
		exit(0);
		break;
	default:
		break;
	}
}

void selectCurve(int selection)
{
	switch (selection)
	{
	case 11:
		addCurveItem(1, curves.size());
		curves.push_back(new BezierCurve());

		CURRENT_CURVE_EDITED = curves.size() - 1;
		CURRENT_VERTEX_EDITED = 0;
		break;
	}
}

void addCurveItem(int parent, int index)
{
	std::string prefix = "Curve_";
	int base = parent * 100 + (20 + index * 10) + 1;
	int color_base = base * 10 + 1;

	// Crée le menu de couleur
	int color_tmp = glutCreateMenu(setColor);
	glutAddMenuEntry("Blue", color_base++);
	glutAddMenuEntry("Green", color_base++);
	glutAddMenuEntry("Red", color_base++);
	glutAddMenuEntry("White", color_base++);
	glutAddMenuEntry("Yellow", color_base++);

	// Crée le sous menu du polygone en cours
	int curve_tmp = glutCreateMenu(editCurve);
	glutAddSubMenu("Color", color_tmp);
	glutAddMenuEntry("Edit", ++base);
	glutAddMenuEntry("Translate", ++base);
	glutAddMenuEntry("Rotate", ++base);
	glutAddMenuEntry("Scale", ++base);
	glutAddMenuEntry("Remove", ++base);

	glutSetMenu(parent);
	glutAddSubMenu((prefix + std::to_string(index + 1)).c_str(), curve_tmp);
}

// Fonction appelée pour le choix d'une couleur
void setColor(int selection)
{
	int item_selected = (selection / 100) % 10;
	int polygon_selected = item_selected - 2;
	int color = selection % 10;

	switch (color)
	{
	case 1:											// Blue
		curves[polygon_selected]->setColor(0.0f, 0.0f, 1.0f);
		break;
	case 2:											// Green
		curves[polygon_selected]->setColor(0.0f, 1.0f, 0.0f);
		break;
	case 3:											// Red
		curves[polygon_selected]->setColor(1.0f, 0.0f, 0.0f);
		break;
	case 4:											// Yellow
		curves[polygon_selected]->setColor(1.0f, 1.0f, 1.0f);
		break;
	case 5:											// White
		curves[polygon_selected]->setColor(1.0f, 1.0f, 0.0f);
		break;
	}

	glutPostRedisplay();
}

void editCurve(int selection)
{
	int item_selected = (selection / 10) % 10;
	int curve_selected = item_selected - 2;
	int edition_selected = selection % 10;

	TRANSFORMATION_MODE = NONE;
	switch (edition_selected)
	{
	case 2:
		CURRENT_CURVE_EDITED = curve_selected;
		CURRENT_VERTEX_EDITED = curves[CURRENT_CURVE_EDITED]->getNbVertices();
		glutPostRedisplay();
		break;
	case 3:
		TRANSFORMATION_MODE = TRANSLATION;
		break;
	case 4:
		TRANSFORMATION_MODE = ROTATION;
		break;
	case 5:
		TRANSFORMATION_MODE = SCALING;
		break;
	case 6:
		glutSetMenu(1);
		for (unsigned int i = 0; i < curves.size(); ++i)
			glutRemoveMenuItem(2);

		curves.erase(curves.begin() + curve_selected);

		for (unsigned int i = 0; i < curves.size(); ++i)
			addCurveItem(1, i);

		if (curve_selected == CURRENT_CURVE_EDITED)
		{
			CURRENT_CURVE_EDITED = -1;
			CURRENT_VERTEX_EDITED = 0;
		}

		glutPostRedisplay();
		break;
	}
}