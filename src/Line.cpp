#include "Line.h"
#include "stdlib.h"

CLine::CLine()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = LINE;
}

CLine::~CLine()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CLine::display()
{
	glColor3fv(mColor);

	pintarLinea(mVertices[0][0], mVertices[0][1], mVertices[1][0],mVertices[1][1]);

}

void CLine::pintarLinea(int x1,int y1, int x2, int y2) {
	int dx, dy, x, y, d, IncE, IncNE,incremento;

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

				x ++;
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
					y+=incremento;

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
					x +=incremento;

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

void CLine::putPixel(int x,int y) {
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

void CLine::generarBonding() {

	glColor3fv(mBondingColor);
	pintarLinea(mBonding[0][0], mBonding[0][1], mBonding[1][0], mBonding[0][1]);
	pintarLinea(mBonding[0][0], mBonding[0][1], mBonding[0][0], mBonding[1][1]);
	pintarLinea(mBonding[1][0], mBonding[1][1], mBonding[1][0], mBonding[0][1]);
	pintarLinea(mBonding[1][0], mBonding[1][1], mBonding[0][0], mBonding[1][1]);
}

void CLine::generarBondingBox() {

	if (mVertices[0][0] > mVertices[1][0]) {
		mBonding[0][0] = mVertices[0][0];
		mBonding[1][0] = mVertices[1][0];
	}
	else {
		mBonding[0][0] = mVertices[1][0];
		mBonding[1][0] = mVertices[0][0];
	}

	if (mVertices[0][1] > mVertices[1][1]) {

		mBonding[0][1] = mVertices[0][1];
		mBonding[1][1] = mVertices[1][1];
	}
	else {
		mBonding[1][1] = mVertices[0][1];
		mBonding[0][1] = mVertices[1][1];
	}

}

void CLine::mover(int id, float x, float y) {

	mVertices[id][0] += x;
	mVertices[id][1] += y;
}