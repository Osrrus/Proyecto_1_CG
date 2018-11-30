#include "UserInterface.h"

extern int gWidth, gHeight;

// Global static pointer used to ensure a single instance of the class.
CUserInterface * CUserInterface::mInterface = NULL;

/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CUserInterface * CUserInterface::Instance() 
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		 mInterface = new CUserInterface();
 
   return mInterface;
}

CUserInterface::CUserInterface()
{
	mUserInterface = TwNewBar("Figure");

	TwDefine("Figure refresh = '0.0001f'");
	TwDefine("Figure resizable = false");
	TwDefine("Figure fontresizable = false");
	TwDefine("Figure movable = false");
	TwDefine("Figure visible = false");
	TwDefine("Figure position = '20 20'");
	TwDefine("Figure size = '220 320'");

	TwAddVarRO(mUserInterface, "meshType", TW_TYPE_STDSTRING, &mFigureType, "label='Type' readonly=true");
	TwAddVarRW(mUserInterface, "color", TW_TYPE_COLOR3F, &mFigureColor[0], "label = 'Color'");
	TwAddSeparator(mUserInterface,"Figure",NULL);
	TwAddVarRW(mUserInterface, "paint", TW_TYPE_BOOLCPP,&paint,"label = 'Paint'");
	TwAddVarRW(mUserInterface, "paintColor", TW_TYPE_COLOR3F, &paintColor[0], "label = 'Paint Color'");
	TwAddSeparator(mUserInterface, "ColorFigure", NULL);
	TwAddVarRW(mUserInterface, "figurePosition", TW_TYPE_INT8, &figurePosition, "label = 'upDown' min=0");
	TwAddVarRW(mUserInterface, "eraseFigure", TW_TYPE_BOOLCPP, &erase, "label = 'Eliminar'");
	TwAddSeparator(mUserInterface, "optionsFigure", NULL);
}

CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setFigureColor(float *color)
{
	mFigureColor[0] = color[0];
	mFigureColor[1] = color[1];
	mFigureColor[2] = color[2];
}

void CUserInterface::setPaintColor(float *color)
{
	paintColor[0] = color[0];
	paintColor[1] = color[1];
	paintColor[2] = color[2];
}

void CUserInterface::setPaintFigure(bool p)
{
	paint = p;

}

void CUserInterface::setEreaseFigure()
{
	erase = false;
}

void CUserInterface::setFigurePosition(int p)
{
	figurePosition = p;
}

void CUserInterface::setFigureType(string type)
{
	mFigureType = type;
}

float* CUserInterface::getFigureColor()
{
	return mFigureColor;
}

float* CUserInterface::getPaintColor()
{
	return paintColor;
}

bool CUserInterface::getPaintFigure() {

	return paint;

}

int CUserInterface::getFigurePosition() {

	return figurePosition;

}

bool CUserInterface::getEreaseFigure() {

	return erase;

}