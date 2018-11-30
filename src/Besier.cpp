#include "Besier.h"
#include <iostream>

CBesier::CBesier()
{
	mType = Besier;
}

CBesier::~CBesier()
{
	for (int i = 0; i < 0; ++i)
		delete[] mVertices[i];

	puntosControl.clear();
}

void CBesier::display() {
	glColor3fv(mColor);
	puntos.clear();
	for (int i = 0; i < puntosControl.size(); i++) {
		punto = new std::pair <float, float>(puntosControl[i]->first, puntosControl[i]->second);
		puntos.push_back(punto);
	}
	casitaHouse();
	glColor3fv(cLine);
	for (int i = 0; i < puntosControl.size()-1; i++) {
		pintarLinea(puntosControl[i]->first, puntosControl[i]->second, puntosControl[i + 1]->first, puntosControl[i + 1]->second);
	}
	glColor3fv(cPoint);
	glPointSize(5);
	for (int i = 0; i < puntosControl.size(); i++) {
		glBegin(GL_POINTS);
			glVertex2i(puntosControl[i]->first, puntosControl[i]->second);
		glEnd();
	}
	glPointSize(1);
}

void CBesier::casitaHouse() {
	int n = puntos.size();
	glBegin(GL_LINE_STRIP);
	for (double tt = 0.0; tt < 1.0; tt += paso)
	{
		for (int rr = 0; rr < (n - 1); rr++)
		{
			for (int ii = 0; ii < (n - 1) - rr; ii++)
			{
				puntos[ii]->first = float((1.0 - tt) * puntos[ii]->first) + float(tt * puntos[ii + 1]->first);
				puntos[ii]->second = float((1.0 - tt) * puntos[ii]->second) + float(tt * puntos[ii + 1]->second);
			}
		}
		VertXY1[0] = puntos[0]->first;
		VertXY1[1] = puntos[0]->second;
		glVertex2fv(VertXY1);
	}
	glEnd();
}

void CBesier::agregarPunto(float x,float y) {

	punto = new std::pair <float, float>(x, y);
	puntosControl.push_back(punto);

}

void CBesier::generarBonding() {

	glColor3fv(mBondingColor);
	pintarLinea(mBonding[0][0], mBonding[0][1], mBonding[1][0], mBonding[0][1]);
	pintarLinea(mBonding[0][0], mBonding[0][1], mBonding[0][0], mBonding[1][1]);
	pintarLinea(mBonding[1][0], mBonding[1][1], mBonding[1][0], mBonding[0][1]);
	pintarLinea(mBonding[1][0], mBonding[1][1], mBonding[0][0], mBonding[1][1]);
}

void CBesier::generarBondingBox() {

	mBonding[0][0] = 0;
	mBonding[0][1] = 0;
	mBonding[1][0] = INT_MAX;
	mBonding[1][1] = INT_MAX;

	puntos.clear();
	for (int i = 0; i < puntosControl.size(); i++) {
		punto = new std::pair <float, float>(puntosControl[i]->first, puntosControl[i]->second);
		puntos.push_back(punto);
	}
	casitaHouseBonding();
	
}

void CBesier::casitaHouseBonding() {
	int n = puntos.size();
	for (double tt = 0.0; tt < 1.0; tt += paso)
	{
		for (int rr = 0; rr < (n - 1); rr++)
		{
			for (int ii = 0; ii < (n - 1) - rr; ii++)
			{
				puntos[ii]->first = float((1.0 - tt) * puntos[ii]->first) + float(tt * puntos[ii + 1]->first);
				puntos[ii]->second = float((1.0 - tt) * puntos[ii]->second) + float(tt * puntos[ii + 1]->second);
			}
		}

		if (puntos[0]->first > mBonding[0][0]) {
			mBonding[0][0] = puntos[0]->first;
		}
		if (puntos[0]->first  < mBonding[1][0]) {
			mBonding[1][0] = puntos[0]->first;
		}
		if (puntos[0]->second > mBonding[0][1]) {
			mBonding[0][1] = puntos[0]->second;
		}
		if (puntos[0]->second < mBonding[1][1]) {
			mBonding[1][1] = puntos[0]->second;
		}
	}
}

void CBesier::pintarLinea(int x1, int y1, int x2, int y2) {
	int dx, dy, x, y, d, IncE, IncNE, incremento;

	dx = x2 - x1;
	dy = y2 - y1;



	x = x1;
	y = y1;

	putPixel(x, y);
	if (abs(dx) > abs(dy)) {

		if (dx >= 0) {

			if (y <= y2) {

				incremento = 1;
				d = dx - 2 * dy;
				IncE = -2 * dy;
				IncNE = 2 * (dx - dy);

			}
			else {

				incremento = -1;
				d = dx + 2 * dy;
				IncE = 2 * dy;
				IncNE = 2 * (dx + dy);
			}

			while (x < x2) {
				if (d <= 0) {

					d = d + IncNE;
					y += incremento;

				}
				else {
					d = d + IncE;
				}

				x++;
				putPixel(x, y);
			}
		}
		else {

			if (y <= y2) {
				incremento = 1;
				d = -dx - 2 * dy;
				IncE = -2 * dy;
				IncNE = 2 * (-dx - dy);
			}
			else {

				incremento = -1;
				d = -dx + 2 * dy;
				IncE = 2 * dy;
				IncNE = 2 * (-dx + dy);
			}

			while (x > x2) {

				if (d <= 0) {

					d = d + IncNE;
					y += incremento;

				}
				else {
					d = d + IncE;
				}

				x--;
				putPixel(x, y);
			}
		}
	}
	else {


		if (dy >= 0) {

			if (x > x2) {
				incremento = -1;
				d = dy + 2 * dx;
				IncE = 2 * dx;
				IncNE = 2 * (dy + dx);
			}
			else {
				incremento = 1;
				d = dy - 2 * dx;
				IncE = -2 * dx;
				IncNE = 2 * (dy - dx);
			}

			while (y < y2) {
				if (d <= 0) {

					d = d + IncNE;
					x += incremento;

				}
				else {
					d = d + IncE;
				}

				y++;
				putPixel(x, y);

			}

		}
		else {

			if (x > x2) {
				incremento = -1;
				d = -dy + 2 * dx;
				IncE = 2 * dx;
				IncNE = 2 * (-dy + dx);
			}
			else {
				incremento = 1;
				d = -dy - 2 * dx;
				IncE = -2 * dx;
				IncNE = 2 * (-dy - dx);
			}



			while (y > y2) {
				if (d <= 0) {

					d = d + IncNE;
					x += incremento;

				}
				else {
					d = d + IncE;
				}

				y--;
				putPixel(x, y);

			}
		}
	}

}

void CBesier::putPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CBesier::setBack(int x, int y) {

	puntosControl.back()->first = x;
	puntosControl.back()->second = y;
}

void CBesier::mover(int id ,float x, float y) {

	for (int i = 0; i < puntosControl.size(); i++) {
		puntosControl[i]->first += x;
		puntosControl[i]->second += y;
	}
}
