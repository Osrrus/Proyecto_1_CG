
#include "Figure.h"
class CCircle : public CFigure
{
	public:
		CCircle();
		~CCircle();
		void display();
		void pintarCirculo(int, int, int, int,int);
		void octantes(int x, int y, int x1, int y1);
		void PintarBonding(int x1, int y1, int x2, int y2, int r);
		void cuandrantesBonding(int x, int y, int x1, int y1);
		void putPixel(int, int);
		void generarBonding();
		void generarBondingBox();
		void pintarLinea(int x1, int y1, int x2, int y2);
		void mover(int id, float x, float y);
};
