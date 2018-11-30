#pragma once

#include "../headers/glfw3.h"

enum FigureType
{
	NONE,
	LINE,
	QUAD,
	Circle,
	Triangle,
	Elipse,
	Besier,
};

class CFigure
{
protected:
	float **mVertices, mColor[3], mPaintColor[3],mBondingColor[3];
	bool mPaint;
	int mType;
	float mBonding[2][2];

public:
	CFigure();
	virtual ~CFigure();
	void setVertex(int id, float x, float y);
	void setColor(float r, float g, float b);
	void setBondingColor(float r, float g, float b);
	void setPaintColor(float r, float g, float b);
	void setBonding(int id, float x, float y);
	virtual void mover(int id, float x, float y) = 0;
	void paintFigure(bool a);
	virtual void display() = 0;
	virtual void generarBonding() = 0;
	virtual void generarBondingBox() = 0;
	int getType();
	float* getVertex(int id);
	float* getBonding(int id);
	float* getColor();
	float* getBondingColor();
	float* getPaintColor();
	float* getMidPoint();
	bool getPaintFigure();
};