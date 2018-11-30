#pragma once

#include "../headers/AntTweakBar.h"
#include <iostream>
#include <string>

using std::string;

//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	float mFigureColor[3];
	float paintColor[3];
	bool paint, erase;
	string mFigureType;
	unsigned int figurePosition;

public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setFigureColor(float *color);
	void setPaintColor(float * color);
	void setPaintFigure(bool p);
	void setEreaseFigure();
	void setFigurePosition(int p);
	void setFigureType(string type);
	float* getFigureColor();
	float* getPaintColor();
	bool getPaintFigure();

	int getFigurePosition();

	bool getEreaseFigure();

private:
	///Private constructor
	CUserInterface(); 
};