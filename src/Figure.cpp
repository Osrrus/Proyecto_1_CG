#include "Figure.h"

CFigure::CFigure()
{
	mColor[0] = mColor[1] = mColor[2] = 0.0f;
	mBondingColor[1] = mBondingColor[2] = 0.0f;
	mBondingColor[0] = 1.0f;
}

CFigure::~CFigure()
{
	delete[] mVertices;
}

void CFigure::setVertex(int id, float x, float y)
{
	mVertices[id][0] = x;
	mVertices[id][1] = y;
}

void CFigure::setBonding(int id, float x, float y)
{
	mBonding[id][0] = x;
	mBonding[id][1] = y;
}

void CFigure::setColor(float r, float g, float b)
{
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
}

void CFigure::setBondingColor(float r, float g, float b)
{
	mBondingColor[0] = r;
	mBondingColor[1] = g;
	mBondingColor[2] = b;
}

void CFigure::setPaintColor(float r, float g, float b)
{
	mPaintColor[0] = r;
	mPaintColor[1] = g;
	mPaintColor[2] = b;
}

void CFigure::paintFigure(bool a) {

	mPaint = a;

}

int CFigure::getType()
{
	return mType;
}

float* CFigure::getVertex(int id)
{
	return mVertices[id];
}

float* CFigure::getBonding(int id)
{
	return mBonding[id];
}

float* CFigure::getColor()
{
	return mColor;
}

float* CFigure::getBondingColor()
{
	return mBondingColor;
}

float* CFigure::getPaintColor()
{
	return mPaintColor;
}

float* CFigure::getMidPoint() {
	float aux[1][2];
	aux[0][0] = mBonding[0][0] - mBonding[1][0];
	aux[0][1] = mBonding[0][1] - mBonding[1][1];
	aux[0][0] = aux[0][0]/2;
	aux[0][1] = aux[0][1]/2;

	aux[0][0] = aux[0][0] + mBonding[1][0];
	aux[0][1] = aux[0][1] + mBonding[1][1];
	return aux[0];
}

bool CFigure::getPaintFigure()
{
	return mPaint;
}

/*void CFigure::mover(int id, float x, float y) {

	mVertices[id][0] += x;
	mVertices[id][1] += y;
}*/