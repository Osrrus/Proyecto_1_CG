
#include "Figure.h"

class CElipse :public CFigure
{
	public:
		CElipse();
		~CElipse();
		void display();
		void pintarElipse(int,int,int,int,int);
		void pintar4(int x, int y, int cx, int cy);
		void pintarLinea(int, int, int, int);
		void PintarBonding(int cx, int cy, int a, int b, int r);
		void cuandrantesBonding(int x, int y, int x1, int y1);
		void mover(int id, float x, float y);
		void putPixel(int, int);
		void generarBonding();
		void generarBondingBox();
};
