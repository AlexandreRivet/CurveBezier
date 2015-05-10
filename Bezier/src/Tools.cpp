#include "includes.h"
#include "Tools.h"

void renderString(float x, float y, void* font, const char* message, float r, float g, float b)
{
	int len = (int)strlen(message);

	static float oldColor[4] = { 0 };
	glGetFloatv(GL_CURRENT_COLOR, oldColor);

	glColor3f(r, g, b);
	glRasterPos2f(x, y);

	//glColor3f(r, g, b);

	for (int i = 0; i < len; ++i)
	{
		glutBitmapCharacter(font, message[i]);
	}
	
	glColor3f(oldColor[0], oldColor[1], oldColor[2]);
}