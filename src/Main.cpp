#include "Main.h"
#include "Line.h"
#include "Quad.h"
#include "Circle.h"
#include "Triangulo.h"
#include "Elipse.h"
#include "Besier.h"
#include "UserInterface.h"

using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
bool gPress;
CUserInterface * userInterface;
vector <CFigure *> figures;
CFigure * auxFigure;
FigureType figureSelected;
int picked,conFigure = 0;
int tFirst = 0,bFirst = 0;
float tx, ty, tx2, ty2;
float bx, by, bx2, by2,bx3,by3;
int picking;
bool draw,newBezier = true;
CBesier *auxBesier;

void pick(int x, int y)
{
	picked = -1;
	userInterface->hide();

	for (unsigned int i = 0; i < figures.size(); i++)
	{
		float *v1 = figures[i]->getBonding(0);
		float *v2 = figures[i]->getBonding(1);
		float max[2];
		float min[2];

		// This should be precalculated

		max[0] = MAX(v1[0], v2[0]);
		max[1] = MAX(v1[1], v2[1]);

		min[0] = MIN(v1[0], v2[0]);
		min[1] = MIN(v1[1], v2[1]);

		if (x >= min[0] && x <= max[0] && y >= min[1] && y <= max[1])
		{
			picked = i;

			userInterface->setFigureColor(figures[picked]->getColor());
			userInterface->setPaintColor(figures[picked]->getPaintColor());
			userInterface->setPaintFigure(figures[picked]->getPaintFigure());
			userInterface->setFigurePosition(picked);
			userInterface->setEreaseFigure();
			userInterface->show();

			int type = figures[picked]->getType();

			if (type == LINE)
				userInterface->setFigureType("Line");
			else if (type == QUAD)
				userInterface->setFigureType("Quad");
			else if (type == Circle)
				userInterface->setFigureType("Circle");
			else if (type == Triangle)
				userInterface->setFigureType("Triangle");
			else if (type == Elipse)
				userInterface->setFigureType("Elipse");
			else if (type == Besier)
				userInterface->setFigureType("Bezier");

			break;
		}
	}
}

void updateUserInterface()
{
	if (picked > -1)
	{

		if (userInterface->getEreaseFigure()) {
			delete figures[picked];
			figures.erase(figures.begin() + picked);
			picked = -1;
			conFigure--;
		}
		else {
			float * color = userInterface->getFigureColor();
			bool p = userInterface->getPaintFigure();
			float * paintColor = userInterface->getPaintColor();
			unsigned int pos = userInterface->getFigurePosition();

			figures[picked]->setColor(color[0], color[1], color[2]);
			figures[picked]->setPaintColor(paintColor[0], paintColor[1], paintColor[2]);
			figures[picked]->paintFigure(p);

			if (pos >= 0 ) {
				if (pos >= figures.size()) {
					pos = figures.size() - 1;
				}
				auxFigure = figures[picked];
				figures[picked] = figures[pos];
				figures[pos] = auxFigure;
				picked = pos;
			}
		}	
	}
}

void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (unsigned int i = 0; i < figures.size(); i++)
		figures[i]->display();

	if (picked > -1) {
		figures[picked]->generarBonding();
	}
	
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, gWidth, 0, gHeight, -1.0f, 1.0f);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_P:
			figureSelected = NONE;
			userInterface->hide();
			break;

		case GLFW_KEY_L:
			figureSelected = LINE;
			userInterface->hide();
			break;

		case GLFW_KEY_Q:
			figureSelected = QUAD;
			userInterface->hide();
			break;
		case GLFW_KEY_C:
			figureSelected = Circle;
			userInterface->hide();
			break;
		case GLFW_KEY_E:
			figureSelected = Elipse;
			userInterface->hide();
			break;
		case GLFW_KEY_B:
			figureSelected = Besier;
			userInterface->hide();
			break;
		case GLFW_KEY_T:
			figureSelected = Triangle;
			userInterface->hide();
			break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;

	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);

		if (figureSelected == NONE) {

			if (picked > -1) {

				int a = picked;
				pick(int(ax), int(ay));

				if (picked == a) {

					draw = true;
					gPress = true;
					
				}
			}
			else {

				pick(int(ax), int(ay));
			}

		}
		else if (figureSelected == LINE)
		{
			CLine *line = new CLine();
			line->setVertex(0, ax, ay);
			line->setVertex(1, ax, ay);
			figures.push_back(line);

			gPress = true;
		}
		else if (figureSelected == QUAD)
		{
			CQuad *quad = new CQuad();
			quad->setVertex(0, ax, ay);
			quad->setVertex(1, ax, ay);
			figures.push_back(quad);

			gPress = true;
		}
		else if (figureSelected == Circle) 
		{
			CCircle *circle = new CCircle();
			circle->setVertex(0, ax, ay);
			circle->setVertex(1, ax, ay);
			figures.push_back(circle);

			gPress = true;
		}
		else if (figureSelected == Elipse)
		{
			CElipse *elipse = new CElipse();
			elipse->setVertex(0, ax, ay);
			elipse->setVertex(1, ax, ay);
			figures.push_back(elipse);

			gPress = true;
		}
		else if (figureSelected == Triangle)
		{
			if (tFirst == 0)
			{
				tx = ax;
				ty = ay;
				tFirst++;
			}
			else if(tFirst == 1)
			{
				tx2 = ax;
				ty2 = ay;
				tFirst++;
			}
			else {
				Triangulo *triangle = new Triangulo;
				triangle->setVertex(0, tx, ty);
				triangle->setVertex(1, tx2, ty2);
				triangle->setVertex(2, ax, ay);
				figures.push_back(triangle);
				tFirst = 0;
				gPress = true;
			}
		}
		else if (figureSelected == Besier)
		{
			if (newBezier) {
				CBesier *besier = new CBesier;
				besier->agregarPunto(ax, ay);
				figures.push_back(besier);
				bx = conFigure;
				auxBesier = besier;
				newBezier = false;
			}
			else {
				auxBesier->agregarPunto(ax, ay);
				figures[bx]->generarBondingBox();
			}
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		draw = false;
		gPress = false;
	}

	if (gPress == false && conFigure != figures.size()) {

		figures[conFigure]->generarBondingBox();
		conFigure = figures.size();
		
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && figureSelected == Besier) {
		newBezier = true;
	}
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;

	if (gPress)
	{
		if (draw) {
			float ax = float(x);
			float ay = gHeight - float(y);
			float *mid = figures[picked]->getMidPoint();
			ax += -mid[0];
			ay += -mid[1];
			//ax = ax / 2;
			//ay = ay / 2;

			if (figures[picked]->getType() == Triangle) {
				figures[picked]->mover(0, ax,ay);
				figures[picked]->mover(1, ax,ay);
				figures[picked]->mover(2, ax,ay);
				figures[picked]->generarBondingBox();
			}
			else if (figures[picked]->getType() == Besier) {
				figures[picked]->mover(0,ax, ay);
				figures[picked]->generarBondingBox();
			}
			else {
				figures[picked]->mover(0, ax, ay);
				figures[picked]->mover(1, ax, ay);
				figures[picked]->generarBondingBox();
			}
			


		}
		else if (figureSelected == Besier) {
			float ax = float(x);
			float ay = gHeight - float(y);
			
		}
		else if (figureSelected == Triangle)
		{
			float ax = float(x);
			float ay = gHeight - float(y);

			figures.back()->setVertex(2, ax, ay);
		}else
		{
		
			float ax = float(x);
			float ay = gHeight - float(y);

			figures.back()->setVertex(1, ax, ay);
		}
	}
}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < figures.size(); i++)
		delete figures[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Proyecto1_Ricardo_Osuna", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();

	return true;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	gPress = false;
	figureSelected = LINE;
	picked = -1;

	if (!initGlfw() || !initUserInterface())
		return EXIT_FAILURE;

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	while (!glfwWindowShouldClose(gWindow))
	{
		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}