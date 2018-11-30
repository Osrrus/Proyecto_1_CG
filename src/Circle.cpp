#include "Circle.h"
#include "stdlib.h"


CCircle::CCircle()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = Circle;
}

CCircle::~CCircle()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CCircle::display()
{
	int r, rx, ry;

	rx = mVertices[1][0] - mVertices[0][0];
	rx = abs(rx);
	ry = mVertices[1][1] - mVertices[0][1];
	ry = abs(ry);

	if (rx >= ry) {
		pintarCirculo(mVertices[0][0], mVertices[0][1], mVertices[1][0], mVertices[1][1],rx);
	}
	else {
		pintarCirculo(mVertices[0][0], mVertices[0][1], mVertices[1][0], mVertices[1][1], ry);
	}
	

}

void CCircle::pintarCirculo(int x1, int y1, int x2, int y2,int r) {
	int x, y, d;
	x = 0;
	y = r;
	d = 1 - r;

	octantes(x, y,x1,y1);
	while (y > x) {
		if (d < 0) {
			d += 2 * x + 3;
		}
		else {

			d += 2 * (x - y) + 5;
			y -= 1;
		}

		x++;
		octantes(x, y,x1,y1);
	}
}

void CCircle::octantes(int x,int y,int x1, int y1) {

	if (mPaint) {
		glColor3fv(mPaintColor);
		pintarLinea(x1 + x, y1 + y, x1 - x, y1 + y);
		pintarLinea(x1 + x, y1 - y, x1 - x, y1 - y);
		pintarLinea(x1 + y, y1 + x, x1 - y, y1 + x);
		pintarLinea(x1 + y, y1 - x, x1 - y, y1 - x);
	}

	glColor3fv(mColor);
	putPixel( x1 +x, y1+y);
	putPixel( x1 -x, y1+y);
	putPixel( x1 +x, y1-y);
	putPixel( x1 -x, y1-y);

	putPixel( x1 +y, y1+x);
	putPixel( x1 -y, y1+x);
	putPixel( x1 +y, y1-x);
	putPixel( x1 -y, y1-x);

	

}

void CCircle::PintarBonding(int x1, int y1, int x2, int y2, int r) {
	int x, y, d;
	x = 0;
	y = r;
	d = 1 - r;

	cuandrantesBonding(x, y, x1, y1);
	while (y > x) {
		if (d < 0) {
			d += 2 * x + 3;
		}
		else {

			d += 2 * (x - y) + 5;
			y -= 1;
		}

		x++;
		cuandrantesBonding(x, y, x1, y1);
	}
}

void CCircle::cuandrantesBonding(int x, int y, int x1, int y1) {
	int a[] = { x,-x };
	int b[] = { y,-y };
	for (int i = 0; i < 2; i++) {

		if (mBonding[0][0] < x1+a[i]) {

			mBonding[0][0] = x1 + a[i];

		}
		if (mBonding[0][1] < y1+b[i]) {

			mBonding[0][1] = y1 + b[i];
		}
		if (mBonding[1][0] > x1 + a[i]) {

			mBonding[1][0] = x1 + a[i];

		}
		if (mBonding[1][1] > y1 + b[i]) {

			mBonding[1][1] = y1 + b[i];

		}


		if (mBonding[0][0] < x1 + b[i]) {

			mBonding[0][0] = x1 + b[i];

		}
		if (mBonding[0][1] < y1 + a[i]) {

			mBonding[0][1] = y1 + a[i];
		}
		if (mBonding[1][0] > x1 + b[i]) {

			mBonding[1][0] = x1 + b[i];

		}
		if (mBonding[1][1] > y1 + a[i]) {

			mBonding[1][1] = y1 + a[i];

		}
		
	}
}

void CCircle::putPixel(int x,int y) {
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

void CCircle::generarBonding() {

	glColor3fv(mBondingColor);
	pintarLinea(mBonding[0][0], mBonding[0][1], mBonding[1][0], mBonding[0][1]);
	pintarLinea(mBonding[0][0], mBonding[0][1], mBonding[0][0], mBonding[1][1]);
	pintarLinea(mBonding[1][0], mBonding[1][1], mBonding[1][0], mBonding[0][1]);
	pintarLinea(mBonding[1][0], mBonding[1][1], mBonding[0][0], mBonding[1][1]);
}

void CCircle::generarBondingBox() {

	mBonding[0][0] = 0;
	mBonding[0][1] = 0;
	mBonding[1][0] = INT_MAX;
	mBonding[1][1] = INT_MAX;

	int rx = mVertices[1][0] - mVertices[0][0];
	rx = abs(rx);
	int ry = mVertices[1][1] - mVertices[0][1];
	ry = abs(ry);

	if (rx >= ry) {
		PintarBonding(mVertices[0][0], mVertices[0][1], mVertices[1][0], mVertices[1][1], rx);
	}
	else {
		PintarBonding(mVertices[0][0], mVertices[0][1], mVertices[1][0], mVertices[1][1], ry);
	}

}

void CCircle::pintarLinea(int x1, int y1, int x2, int y2) {
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

void CCircle::mover(int id, float x, float y) {

	mVertices[id][0] += x;
	mVertices[id][1] += y;
}