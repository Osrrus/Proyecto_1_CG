#pragma once

#include "Figure.h"
#include "Line.h"

class CQuad : public CFigure
{
	public:
		CQuad();
		~CQuad();
		void display();
		void generarBonding();
		void generarBondingBox();
		void pintarLinea(int x1, int y1, int x2, int y2);
		void putPixel(int x, int y);
		void paint();
		void mover(int id, float x, float y);
};
