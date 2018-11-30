#include "Elipse.h"
#include "stdlib.h"

CElipse::CElipse()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = Elipse;
}

CElipse::~CElipse()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CElipse::display() {

	glColor3fv(mColor);

	int dx = mVertices[1][0] - mVertices[0][0], 
		dy = mVertices[1][1] - mVertices[0][1];

	dx = abs(dx);
	dy = abs(dy);

	pintarElipse(mVertices[0][0], mVertices[0][1], dx, dy, dy);
}

void CElipse::pintarElipse(int cx, int cy, int a, int b, int r) {
	int x, y, d, aCuadrado, bCuadrado;

	x = 0;
	y = b;
	aCuadrado = a * a;
	bCuadrado = b * b;
	d = b * ((b << 2) - (aCuadrado << 2)) + aCuadrado;

	pintar4(x, y, cx, cy);
	while (bCuadrado  * ((x + 1) << 1) < aCuadrado *((y << 1) - 1)) {

		if (d < 0)
			d = d + ((bCuadrado *((x << 1) + 3)) << 2);
		else {
			d = d + ((bCuadrado *((x << 1) + 3) + aCuadrado * (-(y << 1) + 2)) << 2);
			y = y - 1;
		}
		x = x + 1;

		pintar4(x, y, cx, cy);
	}

	d = bCuadrado * (((x*x) << 2) + (x << 2) + 1) + aCuadrado * (((y*y) << 2) - (y << 3) + 4) - ((aCuadrado * bCuadrado) << 2);
	while (y > 0) {

		if (d < 0) {

			d = d + ((bCuadrado *((x + 2) << 1) + aCuadrado * (-(y << 1) + 3)) << 2);
			x = x + 1;
		}
		else {
			d = d + (aCuadrado *(-(y << 1) + 3) << 2);

		}
		y = y - 1;
		pintar4(x, y, cx, cy);
	}
}

void CElipse::pintar4(int x, int y, int x1, int y1) {

	if (mPaint) {
		glColor3fv(mPaintColor);
		pintarLinea(x1 + x, y1 + y, x1 - x, y1 + y);
		pintarLinea(x1 + x, y1 - y, x1 - x, y1 - y);
	}

	putPixel(x1 + x, y1 + y);
	putPixel(x1 + x, y1 - y);
	putPixel(x1 - x, y1 + y);
	putPixel(x1 - x, y1 - y);
}

void CElipse::putPixel(int x, int y) {
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

void CElipse::generarBonding() {

	glColor3fv(mBondingColor);
	pintarLinea(mBonding[0][0], mBonding[0][1], mBonding[1][0], mBonding[0][1]);
	pintarLinea(mBonding[0][0], mBonding[0][1], mBonding[0][0], mBonding[1][1]);
	pintarLinea(mBonding[1][0], mBonding[1][1], mBonding[1][0], mBonding[0][1]);
	pintarLinea(mBonding[1][0], mBonding[1][1], mBonding[0][0], mBonding[1][1]);

}

void CElipse::generarBondingBox() {

	mBonding[0][0] = 0;
	mBonding[0][1] = 0;
	mBonding[1][0] = INT_MAX;
	mBonding[1][1] = INT_MAX;

	int dx = mVertices[1][0] - mVertices[0][0],
		dy = mVertices[1][1] - mVertices[0][1];

	dx = abs(dx);
	dy = abs(dy);

	PintarBonding(mVertices[0][0], mVertices[0][1], dx, dy, dy);

}

void CElipse::pintarLinea(int x1, int y1, int x2, int y2) {
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

void CElipse::PintarBonding(int cx, int cy, int a, int b, int r) {

	int x, y, d, aCuadrado, bCuadrado;

	x = 0;
	y = b;
	aCuadrado = a * a;
	bCuadrado = b * b;
	d = b * ((b << 2) - (aCuadrado << 2)) + aCuadrado;

	cuandrantesBonding(x, y, cx, cy);
	while (bCuadrado  * ((x + 1) << 1) < aCuadrado *((y << 1) - 1)) {

		if (d < 0)
			d = d + ((bCuadrado *((x << 1) + 3)) << 2);
		else {
			d = d + ((bCuadrado *((x << 1) + 3) + aCuadrado * (-(y << 1) + 2)) << 2);
			y = y - 1;
		}
		x = x + 1;

		cuandrantesBonding(x, y, cx, cy);
	}

	d = bCuadrado * (((x*x) << 2) + (x << 2) + 1) + aCuadrado * (((y*y) << 2) - (y << 3) + 4) - ((aCuadrado * bCuadrado) << 2);
	while (y > 0) {

		if (d < 0) {

			d = d + ((bCuadrado *((x + 2) << 1) + aCuadrado * (-(y << 1) + 3)) << 2);
			x = x + 1;
		}
		else {
			d = d + (aCuadrado *(-(y << 1) + 3) << 2);

		}
		y = y - 1;
		cuandrantesBonding(x, y, cx, cy);
	}
}

void CElipse::cuandrantesBonding(int x, int y, int x1, int y1) {
	int a[] = { x,-x };
	int b[] = { y,-y };
	for (int i = 0; i < 2; i++) {

		if (mBonding[0][0] < x1 + a[i]) {

			mBonding[0][0] = x1 + a[i];

		}
		if (mBonding[0][1] < y1 + b[i]) {

			mBonding[0][1] = y1 + b[i];
		}
		if (mBonding[1][0] > x1 + a[i]) {

			mBonding[1][0] = x1 + a[i];

		}
		if (mBonding[1][1] > y1 + b[i]) {

			mBonding[1][1] = y1 + b[i];

		}
	}
}

void CElipse::mover(int id, float x, float y) {

	mVertices[id][0] += x;
	mVertices[id][1] += y;
}