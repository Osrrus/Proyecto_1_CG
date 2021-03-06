#include "Figure.h"
#include <vector>

class Triangulo :public CFigure
{
	protected:
		std::vector <std::pair <float, float>*> rectas[3];
		std::pair <float, float> *punto;
		float lineas[3][3];
	public:
		Triangulo();
		~Triangulo();
		void display();
		void pintarLinea(int, int, int, int);
		void mover(int id, float x, float y);
		void putPixel(int, int);
		void generarBonding();
		void generarBondingBox();
		void paint();
		void trazarLinea(int x1, int y1, int x2, int y2, int id);
};
