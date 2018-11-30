#pragma once

#include "Figure.h"

class CLine : public CFigure
{
	public:
		CLine();
		~CLine();
		void display();
		void pintarLinea(int,int,int,int);
		void putPixel(int, int);
		void generarBonding();
		void generarBondingBox();
		void mover(int id, float x, float y);
};

