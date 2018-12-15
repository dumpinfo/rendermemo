//============================================================================
// Name        : mineSweeper.cpp
// Author      : Ankit Shah, Jay Jain, Kartik.
// Version     :
// Copyright   : This source code is free to use, reproduce and distribute
//				 without any prior permission of the concerned authors.
// Description : A simple MineSweeper Game
//============================================================================

#include "calculation.h"

void onMouse(int button, int state, int x, int y) {
	if(y-topPix < 0) {
		if(x<winW/4) {
			display();
			initMat();
			startFlag = true;
		}
	}
	else if (totalCells>0){
		x /= ppb; y = (y-topPix) / ppb;
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && b[y][x] == '*')
			dispPress(y,x);

		if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && b[y][x] == '*') {
			//Image of happy Smiley.
			initImage();
			gluBuild2DMipmaps(GL_TEXTURE_2D, happy.bytes_per_pixel, happy.width, happy.height, GL_RGBA, GL_UNSIGNED_BYTE, happy.pixel_data);
			clearImage(0.25,1.0,0.125,0.125);

			calcLeft(y,x);
			glFlush();
		}

		if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && (b[y][x] == '*' || b[y][x] == '9')) {
			if(b[y][x] == '*') {
				updateMinesNum(++minesnum,true);
				b[y][x] = '9';
				dispFlag(y,x);
			}
			else {
				glColor3f(1.0,1.0,1.0);
				glBegin(GL_POLYGON);
					glVertex3f(x*stepx,(numRows-y)*stepy,0);
					glVertex3f((x+1)*stepx,(numRows-y)*stepy,0);
					glVertex3f((x+1)*stepx,(numRows-y-1)*stepy,0);
					glVertex3f(x*stepx,(numRows-y-1)*stepy,0);
				glEnd();

				glColor3f(0.0,0.0,0.0);
				glBegin(GL_LINES);
					glVertex3f(x*stepx,(numRows-y)*stepy,0);		glVertex3f((x+1)*stepx,(numRows-y)*stepy,0);
					glVertex3f((x+1)*stepx,(numRows-y)*stepy,0);	glVertex3f((x+1)*stepx,(numRows-y-1)*stepy,0);
					glVertex3f((x+1)*stepx,(numRows-y-1)*stepy,0);	glVertex3f(x*stepx,(numRows-y-1)*stepy,0);
					glVertex3f(x*stepx,(numRows-y-1)*stepy,0);		glVertex3f(x*stepx,(numRows-y)*stepy,0);
				glEnd();

				b[y][x] = '*';
				updateMinesNum(--minesnum,false);
			}
			glFlush();
		}
	}
}

void initMat () {
	srand(time(NULL));
	int i,j,x,y;

	for (i = 0;i<numRows;i++)
		for(j=0;j<numCols;j++) {
			a[i][j]=0;
			b[i][j]='*';
			c[i][j]=false;
		}

	for (i =0 ;i<totalMines;i++) {
		ranst:
		x = rand()%numRows;
		y = rand()%numCols;
		if(a[x][y] != 9) {
			a[x][y] = 9;
			c[x][y] = true;
		}
		else
			goto ranst;
	}

	totalCells = numRows*numCols - totalMines;
	totalCellsBack = totalCells;
	minesnum = 0;
	_3BV = 0;
}

void initGraph () {
	glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.125, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	cout<<"Enter the number of rows : ";
	cin>>numRows;
	stepy = 1 / float(numRows);
	cout<<"Enter the number of columns : ";
	cin>>numCols;
	stepx = 1 / float(numCols);
	int max = numRows*numCols - 10;
	enter:
	cout<<"Enter the number of mines, Enter 0 to choose automatically : ";
	cin>>totalMines;
	if(totalMines == 0)
		totalMines = numRows*numCols*0.15625;
	if(totalMines > max) {
		cout<<"Maximum number of mines for the board can be "<<max<<endl;
		goto enter;
	}

	dispStep = calcDigits(totalMines);

	int i;
	a = new int*[numRows];
	b = new char*[numRows];
	c = new bool*[numRows];
	for (i = 0; i < numRows; ++i) {
		a[i] = new int[numCols];
		b[i] = new char[numCols];
		c[i] = new bool[numCols];
	}

	calcWindowSize();

	glutInitWindowSize (winW,winH);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("MineSweeper");

	initGraph();
	initMat();

	glutDisplayFunc(display);
	glutMouseFunc(onMouse);
	glutMainLoop();
	return 0;
}
