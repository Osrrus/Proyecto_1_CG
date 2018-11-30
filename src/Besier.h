
#include "Figure.h"
#include <vector>
#include <utility> 

class CBesier : public CFigure
{
	protected:
		std::vector<std ::pair <float,float>* > puntosControl,puntos;
		std::pair <float, float> *punto;
		double paso = 0.0001;
		float VertXY1[2];
		float cPoint[3] = { 0.0,0.0,0.0 };
		float cLine[3] = { 1.0,0.0,0.0 };
		int numeroVertices = 3;
	public:
		CBesier();
		~CBesier();
		void display();
		void casitaHouse();
		void agregarPunto(float x, float y);
		void generarBonding();
		void generarBondingBox();
		void casitaHouseBonding();
		void pintarLinea(int x1, int y1, int x2, int y2);
		void putPixel(int x, int y);
		void setBack(int x, int y);
		void mover(int id, float x, float y);
		
};
