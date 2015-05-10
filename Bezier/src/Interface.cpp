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
				curves[CURRENT_CURVE_EDITED]->translate(0.0f, stepT);
				break;
			case SCALING:
				curves[CURRENT_CURVE_EDITED]->scale(1.0f, stepT);
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
	
	int first_c0 = glutCreateMenu(firstCurveConnection);
	int second_c0 = glutCreateMenu(secondCurveConnection);
	int first_c1 = glutCreateMenu(firstCurveConnection);
	int second_c1 = glutCreateMenu(secondCurveConnection);
	int first_c2 = glutCreateMenu(firstCurveConnection);
	int second_c2 = glutCreateMenu(secondCurveConnection);

	int c0_menu = glutCreateMenu(empty);
	glutAddSubMenu("First", first_c0);
	glutAddSubMenu("Second", second_c0);
	
	int c1_menu = glutCreateMenu(empty);
	glutAddSubMenu("First", first_c1);
	glutAddSubMenu("Second", second_c1);

	int c2_menu = glutCreateMenu(empty);
	glutAddSubMenu("First", first_c2);
	glutAddSubMenu("Second", second_c2);

	int connectionMenu = glutCreateMenu(empty);
	glutAddSubMenu("C0", c0_menu);
	glutAddSubMenu("C1", c1_menu);
	glutAddSubMenu("C2", c2_menu);

	glutCreateMenu(select);
	glutAddSubMenu("Curves", curveMenu);
	glutAddSubMenu("Connection", connectionMenu);
	glutAddMenuEntry("Quit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void select(int selection)
{
	switch (selection)
	{
	case 3:
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
		// Demande à l'utilisateur de saisir l'intervalle de paramétrage
		int a, b;
		std::cout << "Entrez a: " << std::endl;
		std::cin >> a;
		std::cout << "Entrez b: " << std::endl;
		std::cin >> b;
		
		// Ajout dans les différents menus
		addCurveItem(1, curves.size());
		
		// Création de la bézier
		BezierCurve* bezier = new BezierCurve();
		bezier->setParametricSpace(a, b);
		curves.push_back(bezier);

		// Mise à jour des variables
		CURRENT_CURVE_EDITED = curves.size() - 1;
		CURRENT_VERTEX_EDITED = 0;
		break;
	}
}

void firstCurveConnection(int selection)
{
	FIRST_CURVE = selection % 10;;
}

void secondCurveConnection(int selection)
{
	int connection_type = selection / 10;
	SECOND_CURVE = selection % 10;

	if ((FIRST_CURVE == -1 || SECOND_CURVE == -1) || (FIRST_CURVE == SECOND_CURVE))
		return;

	// Au choix de la deuxième on effectue le raccordement en question
	Vector2 lastVec, firstVec, translation, P1, P2;
	float lambda, lambda1, distanceCurve1, distanceCurve2, r1, r2;
	switch (connection_type)
	{
	case 3:																		// C0 connection
		lastVec = curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 1);
		firstVec = curves[SECOND_CURVE]->getPointAt(0);
		translation = lastVec - firstVec;
		curves[SECOND_CURVE]->translate(translation.getX(), translation.getY());
		break;
	case 5:																		// C1 connection
		lastVec = curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 1);
		firstVec = curves[SECOND_CURVE]->getPointAt(0);
		translation = lastVec - firstVec;
		curves[SECOND_CURVE]->translate(translation.getX(), translation.getY());
		
		r1 = abs(curves[FIRST_CURVE]->getEnd() - curves[FIRST_CURVE]->getStart());
		r2 = abs(curves[SECOND_CURVE]->getEnd() - curves[SECOND_CURVE]->getStart());
		lambda = r1 / (r1 + r2);

		// distanceCurve1 = curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 1).distance(curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 2));
		// distanceCurve2 = curves[SECOND_CURVE]->getPointAt(0).distance(curves[SECOND_CURVE]->getPointAt(1));
		// lambda = distanceCurve1 / (distanceCurve2 + distanceCurve1);

		P1 = (curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 1) - curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 2) * (1 - lambda)) / lambda;

		curves[SECOND_CURVE]->getPointAt(1).setX(P1.getX());
		curves[SECOND_CURVE]->getPointAt(1).setY(P1.getY());
		curves[SECOND_CURVE]->compute();
		break;
	case 7:																		// C2 connection
		lastVec = curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 1);
		firstVec = curves[SECOND_CURVE]->getPointAt(0);
		translation = lastVec - firstVec;
		curves[SECOND_CURVE]->translate(translation.getX(), translation.getY());

		r1 = abs(curves[FIRST_CURVE]->getEnd() - curves[FIRST_CURVE]->getStart());
		r2 = abs(curves[SECOND_CURVE]->getEnd() - curves[SECOND_CURVE]->getStart());
		lambda = r1 / (r1 + r2);

		// distanceCurve1 = curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 1).distance(curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 2));
		// distanceCurve2 = curves[SECOND_CURVE]->getPointAt(0).distance(curves[SECOND_CURVE]->getPointAt(1));
		// lambda = distanceCurve1 / (distanceCurve2 + distanceCurve1);

		P1 = (curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 1) - curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 2) * (1 - lambda)) / lambda;

		curves[SECOND_CURVE]->getPointAt(1).setX(P1.getX());
		curves[SECOND_CURVE]->getPointAt(1).setY(P1.getY());

		// distanceCurve1 = curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 1).distance(curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 2));
		// distanceCurve2 = curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 2).distance(curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 3));
		// lambda = distanceCurve2 / (distanceCurve2 + distanceCurve1);

		D = (curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 2) - curves[FIRST_CURVE]->getPointAt(curves[FIRST_CURVE]->getNbVertices() - 3) * (1 - lambda)) / lambda;

		distanceCurve1 = curves[SECOND_CURVE]->getPointAt(0).distance(curves[SECOND_CURVE]->getPointAt(1));
		distanceCurve2 = curves[SECOND_CURVE]->getPointAt(1).distance(curves[SECOND_CURVE]->getPointAt(2));
		lambda = distanceCurve1 / (distanceCurve2 + distanceCurve1);

		P2 = (curves[SECOND_CURVE]->getPointAt(1) - D * (1 - lambda)) / lambda;

		curves[SECOND_CURVE]->getPointAt(2).setX(P2.getX());
		curves[SECOND_CURVE]->getPointAt(2).setY(P2.getY());
		curves[SECOND_CURVE]->compute();
		break;
	}
	glutPostRedisplay();

	FIRST_CURVE = -1;
	SECOND_CURVE = -1;
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

	// Copie juste pour la sélection dans les raccordements
	// C0
	glutSetMenu(2);
	glutAddMenuEntry((prefix + std::to_string(index + 1)).c_str(), 20 + index);
	glutSetMenu(3);
	glutAddMenuEntry((prefix + std::to_string(index + 1)).c_str(), 30 + index);

	// C1
	glutSetMenu(4);
	glutAddMenuEntry((prefix + std::to_string(index + 1)).c_str(), 40 + index);
	glutSetMenu(5);
	glutAddMenuEntry((prefix + std::to_string(index + 1)).c_str(), 50 + index);

	// C2
	glutSetMenu(6);
	glutAddMenuEntry((prefix + std::to_string(index + 1)).c_str(), 60 + index);
	glutSetMenu(7);
	glutAddMenuEntry((prefix + std::to_string(index + 1)).c_str(), 70 + index);
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
		glutPostRedisplay();
		break;
	case 4:
		TRANSFORMATION_MODE = ROTATION;
		glutPostRedisplay();
		break;
	case 5:
		TRANSFORMATION_MODE = SCALING;
		glutPostRedisplay();
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

void empty(int selection)
{

}