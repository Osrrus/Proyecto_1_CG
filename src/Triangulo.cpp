#include "Triangulo.h"
#include "stdlib.h"


Triangulo::Triangulo()
{
	mVertices = new float*[3];
	for (int i = 0; i < 3; ++i)
		mVertices[i] = new float[2];

	mType = Triangle;
}


Triangulo::~Triangulo()
{
	for (int i = 0; i < 3; ++i)
		delete[] mVertices[i];
}

void Triangulo::display()
{	

	if (mPaint) {

		paint();

	}
	glColor3fv(mColor);
	pintarLinea(mVertices[0][0], mVertices[0][1], mVertices[1][0], mVertices[1][1]);
	pintarLinea(mVertices[0][0], mVertices[0][1], mVertices[2][0], mVertices[2][1]);
	pintarLinea(mVertices[1][0], mVertices[1][1], mVertices[2][0], mVertices[2][1]);
}

void Triangulo::pintarLinea(int x1, int y1, int x2, int y2) {
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

void Triangulo::putPixel(int x, int y) {
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

void Triangulo::generarBonding() {

	glColor3fv(mBondingColor);
	pintarLinea(mBonding[0][0], mBonding[0][1], mBonding[1][0], mBonding[0][1]);
	pintarLinea(mBonding[0][0], mBonding[0][1], mBonding[0][0], mBonding[1][1]);
	pintarLinea(mBonding[1][0], mBonding[1][1], mBonding[1][0], mBonding[0][1]);
	pintarLinea(mBonding[1][0], mBonding[1][1], mBonding[0][0], mBonding[1][1]);
}

void Triangulo::generarBondingBox() {

	mBonding[0][0] = 0;
	mBonding[0][1] = 0;
	mBonding[1][0] = INT_MAX;
	mBonding[1][1] = INT_MAX;

	for (int i = 0; i < 3; i++) {
		if (mVertices[i][0] > mBonding[0][0]) {
			mBonding[0][0] = mVertices[i][0];
		}
		if (mVertices[i][0] < mBonding[1][0]) {
			mBonding[1][0] = mVertices[i][0];
		}
		if (mVertices[i][1] > mBonding[0][1]) {
			mBonding[0][1] = mVertices[i][1];
		}
		if (mVertices[i][1] < mBonding[1][1]) {
			mBonding[1][1] = mVertices[i][1];
		}
	}
	for (int i = 0; i < 3; i++) {

		rectas[i].clear();
	}
	trazarLinea(mVertices[0][0], mVertices[0][1], mVertices[1][0], mVertices[1][1], 0);
	trazarLinea(mVertices[0][0], mVertices[0][1], mVertices[2][0], mVertices[2][1], 1);
	trazarLinea(mVertices[1][0], mVertices[1][1], mVertices[2][0], mVertices[2][1], 2);
}

void Triangulo::paint() {
	int i, j;
	bool ii, jj;
	glColor3fv(mPaintColor);
	for (int w = 0; w < 2; w++) {
		i = j = 0;
		ii = jj =true;
		while (ii || jj) {
			pintarLinea(rectas[w][i]->first, rectas[w][i]->second, rectas[w+1][j]->first, rectas[w+1][j]->second);
			if (i + 1 < rectas[w].size()) {
				i++;
			}
			else {
				ii = false;
			}
			if (j + 1 < rectas[w + 1].size()) {

				j++;
			}
			else {
				jj = false;
			}
		}

		if (w == 0) {
			i = j = 0;
			ii = jj = true;
			while (ii || jj) {
				pintarLinea(rectas[w][i]->first, rectas[w][i]->second, rectas[w + 2][j]->first, rectas[w + 2][j]->second);
				if (i + 1 < rectas[w].size()) {
					i++;
				}
				else {
					ii = false;
				}
				if (j + 1 < rectas[w + 2].size()) {

					j++;
				}
				else {
					jj = false;
				}
			}
		}
	}


}

void Triangulo::trazarLinea(int x1, int y1, int x2, int y2,int id) {
	int dx, dy, x, y, d, IncE, IncNE, incremento;

	dx = x2 - x1;
	dy = y2 - y1;



	x = x1;
	y = y1;

	punto = new std::pair <float, float>(x, y);
	rectas[id].push_back(punto);
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
				punto = new std ::pair <float, float>(x, y);
				rectas[id].push_back(punto);
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
				punto = new std::pair <float, float>(x, y);
				rectas[id].push_back(punto); 
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
				punto = new std::pair <float, float>(x, y);
				rectas[id].push_back(punto);

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
				punto = new std::pair <float, float>(x, y);
				rectas[id].push_back(punto);

			}
		}
	}
}

void Triangulo::mover(int id, float x, float y) {

	mVertices[id][0] += x;
	mVertices[id][1] += y;
}