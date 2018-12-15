/*
 * dispObjects.h
 *
 *  Created on: Sep 30, 2013
 *      Author: ankit
 */

#ifndef DISPOBJECTS_H_
#define DISPOBJECTS_H_

#include "declaration.h"
#include "Image.h"

void lines() {
	glColor3f (0.0, 0.0, 0.0);
	glLineWidth (3);
	float i;
	for(i=0; i<=1; i+=stepx) {
		glBegin(GL_LINES);
			glVertex3f(i,0,0);
			glVertex3f(i,1.0,0);
		glEnd();
	}
	for(i=0; i<=1; i+=stepy) {
		glBegin(GL_LINES);
			glVertex3f(0,i,0);
			glVertex3f(1.0,i,0);
		glEnd();
	}
	glBegin(GL_LINES);
		glVertex3f(0,1.0,0);
		glVertex3f(1.0,1.0,0);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//Draw the required grids.
	lines();

	//Image of NEW
	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, newGame.bytes_per_pixel, newGame.width, newGame.height, GL_RGBA, GL_UNSIGNED_BYTE, newGame.pixel_data);
	clearImage(0.0,1.0,0.25,0.125);

	//Image of happy Smiley.
	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, happy.bytes_per_pixel, happy.width, happy.height, GL_RGBA, GL_UNSIGNED_BYTE, happy.pixel_data);
	clearImage(0.25,1.0,0.125,0.125);

	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, flagTxt.bytes_per_pixel, flagTxt.width, flagTxt.height, GL_RGBA, GL_UNSIGNED_BYTE, flagTxt.pixel_data);
	clearImage(0.375,1.0,0.25,0.125);

	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, slash.bytes_per_pixel, slash.width, slash.height, GL_RGBA, GL_UNSIGNED_BYTE, slash.pixel_data);
	clearImage(0.805,1.0,0.015,0.125);

	drawActMines(0.625,0);
	drawActMines(0.82);
	glFlush();
}

int calcDigits(int n) {
	int d = 0;
	while(n>0) {
		d++;
		n /= 10;
	}
	return d;
}

void updateMinesNum (int temp, bool add) {
	int max = calcDigits(temp);
	max = max > dispStep ? max : dispStep;
	for(int i = max-1; i >= 0; i--) {
		initImage();
		switch(temp%10) {
		case 0:
			gluBuild2DMipmaps(GL_TEXTURE_2D, zero.bytes_per_pixel, zero.width, zero.height, GL_RGBA, GL_UNSIGNED_BYTE, zero.pixel_data);
			break;
		case 1:
			gluBuild2DMipmaps(GL_TEXTURE_2D, one.bytes_per_pixel, one.width, one.height, GL_RGBA, GL_UNSIGNED_BYTE, one.pixel_data);
			break;
		case 2:
			gluBuild2DMipmaps(GL_TEXTURE_2D, two.bytes_per_pixel, two.width, two.height, GL_RGBA, GL_UNSIGNED_BYTE, two.pixel_data);
			break;
		case 3:
			gluBuild2DMipmaps(GL_TEXTURE_2D, three.bytes_per_pixel, three.width, three.height, GL_RGBA, GL_UNSIGNED_BYTE, three.pixel_data);
			break;
		case 4:
			gluBuild2DMipmaps(GL_TEXTURE_2D, four.bytes_per_pixel, four.width, four.height, GL_RGBA, GL_UNSIGNED_BYTE, four.pixel_data);
			break;
		case 5:
			gluBuild2DMipmaps(GL_TEXTURE_2D, five.bytes_per_pixel, five.width, five.height, GL_RGBA, GL_UNSIGNED_BYTE, five.pixel_data);
			break;
		case 6:
			gluBuild2DMipmaps(GL_TEXTURE_2D, six.bytes_per_pixel, six.width, six.height, GL_RGBA, GL_UNSIGNED_BYTE, six.pixel_data);
			break;
		case 7:
			gluBuild2DMipmaps(GL_TEXTURE_2D, seven.bytes_per_pixel, seven.width, seven.height, GL_RGBA, GL_UNSIGNED_BYTE, seven.pixel_data);
			break;
		case 8:
			gluBuild2DMipmaps(GL_TEXTURE_2D, eight.bytes_per_pixel, eight.width, eight.height, GL_RGBA, GL_UNSIGNED_BYTE, eight.pixel_data);
			break;
		case 9:
			gluBuild2DMipmaps(GL_TEXTURE_2D, nine.bytes_per_pixel, nine.width, nine.height, GL_RGBA, GL_UNSIGNED_BYTE, nine.pixel_data);
			break;
		}
		clearImage(0.625+i*0.18/max,1.0,0.18/max,0.125);
		if(temp%10 != 0 && add)
			break;
		if(temp%10 != 9 && !add)
					break;
		temp /= 10;
	}
}

void drawActMines(float xpos, int temp, float ypos, float scaleX, float scaleY, int max) {
	for (int i = max-1; i >= 0; i--) {
		initImage();
		switch(temp%10) {
		case 0:
			gluBuild2DMipmaps(GL_TEXTURE_2D, zero.bytes_per_pixel, zero.width, zero.height, GL_RGBA, GL_UNSIGNED_BYTE, zero.pixel_data);
			break;
		case 1:
			gluBuild2DMipmaps(GL_TEXTURE_2D, one.bytes_per_pixel, one.width, one.height, GL_RGBA, GL_UNSIGNED_BYTE, one.pixel_data);
			break;
		case 2:
			gluBuild2DMipmaps(GL_TEXTURE_2D, two.bytes_per_pixel, two.width, two.height, GL_RGBA, GL_UNSIGNED_BYTE, two.pixel_data);
			break;
		case 3:
			gluBuild2DMipmaps(GL_TEXTURE_2D, three.bytes_per_pixel, three.width, three.height, GL_RGBA, GL_UNSIGNED_BYTE, three.pixel_data);
			break;
		case 4:
			gluBuild2DMipmaps(GL_TEXTURE_2D, four.bytes_per_pixel, four.width, four.height, GL_RGBA, GL_UNSIGNED_BYTE, four.pixel_data);
			break;
		case 5:
			gluBuild2DMipmaps(GL_TEXTURE_2D, five.bytes_per_pixel, five.width, five.height, GL_RGBA, GL_UNSIGNED_BYTE, five.pixel_data);
			break;
		case 6:
			gluBuild2DMipmaps(GL_TEXTURE_2D, six.bytes_per_pixel, six.width, six.height, GL_RGBA, GL_UNSIGNED_BYTE, six.pixel_data);
			break;
		case 7:
			gluBuild2DMipmaps(GL_TEXTURE_2D, seven.bytes_per_pixel, seven.width, seven.height, GL_RGBA, GL_UNSIGNED_BYTE, seven.pixel_data);
			break;
		case 8:
			gluBuild2DMipmaps(GL_TEXTURE_2D, eight.bytes_per_pixel, eight.width, eight.height, GL_RGBA, GL_UNSIGNED_BYTE, eight.pixel_data);
			break;
		case 9:
			gluBuild2DMipmaps(GL_TEXTURE_2D, nine.bytes_per_pixel, nine.width, nine.height, GL_RGBA, GL_UNSIGNED_BYTE, nine.pixel_data);
			break;
		}
		clearImage(xpos+i*scaleX,ypos,scaleX,scaleY);
		temp /= 10;
	}
}

void dispPress(int x, int y) {
	//Upper Triangle of Button Press.
	glColor3f(0.95,0.95,0.95);
	glBegin(GL_TRIANGLES);
		glVertex3f(y*stepx,(numRows-x)*stepy,0);
		glVertex3f((y+1)*stepx,(numRows-x)*stepy,0);
		glVertex3f((y+1)*stepx,(numRows-x-1)*stepy,0);
	glEnd();
	//Lower Triangle of Button Press.
	glColor3f(0.9,0.9,0.9);
	glBegin(GL_TRIANGLES);
		glVertex3f((y+1)*stepx,(numRows-x-1)*stepy,0);
		glVertex3f(y*stepx,(numRows-x-1)*stepy,0);
		glVertex3f(y*stepx,(numRows-x)*stepy,0);
	glEnd();

	//Image of shocked Smiley.
	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, open.bytes_per_pixel, open.width, open.height, GL_RGBA, GL_UNSIGNED_BYTE, open.pixel_data);
	clearImage(0.25,1.0,0.125,0.125);

	glFlush();
}

void dispBlank(int x, int y) {
	//Gray Blank square for blocks with zero mines.
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glVertex3f(y*stepx,(numRows-x)*stepy,0);
		glVertex3f((y+1)*stepx,(numRows-x)*stepy,0);
		glVertex3f((y+1)*stepx,(numRows-x-1)*stepy,0);
		glVertex3f(y*stepx,(numRows-x-1)*stepy,0);
	glEnd();
}

void dispFlag(int x, int y) {
//	if(a[x][y] == 9)
//		totalMines--;
	//Image of Flag.
	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, flag.bytes_per_pixel, flag.width, flag.height, GL_RGBA, GL_UNSIGNED_BYTE, flag.pixel_data);
	clearImage(y*stepx,(numRows-x-1)*stepy,stepx,stepy);

	lines();
}

void floodFillMark(int x, int y) {
	totalCellsBack--;
	int value = b[x][y];
	b[x][y]='#';
	if(value=='0') {
		if(x-1 >= 0 && b[x-1][y] != '#')
			floodFillMark(x-1,y);
		if(x+1 < numRows && b[x+1][y] != '#')
			floodFillMark(x+1,y);
		if(y-1 >= 0  && b[x][y-1] != '#')
			floodFillMark(x,y-1);
		if(y+1 < numCols && b[x][y+1] != '#')
			floodFillMark(x,y+1);
		if(x-1 >= 0 && y+1 < numCols && b[x-1][y+1] != '#')
			floodFillMark(x-1,y+1);
		if(x+1 < numRows && y+1 < numCols && b[x+1][y+1] != '#')
			floodFillMark(x+1,y+1);
		if(x-1 >= 0 && y-1 >= 0 && b[x-1][y-1] != '#')
			floodFillMark(x-1,y-1);
		if(x+1 < numRows && y-1 >= 0 && b[x+1][y-1] != '#')
			floodFillMark(x+1,y-1);
	}
}

void calc3BV() {
	for (int i = 0; i < numRows; ++i)
		for (int j = 0; j < numCols; ++j) {
			if(b[i][j] == '0') {
				_3BV++;
				floodFillMark(i,j);
			}
		}
	_3BV = totalCellsBack + _3BV;
}

void dispWin() {
	//236/255,194/255,194/255
	calc3BV();
	score = _3BV / float(Time);
	cout<<"3BV = "<<_3BV<<" Time = "<<Time<<" score = "<<score<<endl;

	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, win.bytes_per_pixel, win.width, win.height, GL_RGBA, GL_UNSIGNED_BYTE, win.pixel_data);
	clearImage(0,0.5,1,0.5);

	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, scoreTxt.bytes_per_pixel, scoreTxt.width, scoreTxt.height, GL_RGBA, GL_UNSIGNED_BYTE, scoreTxt.pixel_data);
	clearImage(0,0.25,0.5,0.25);

	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, instruction.bytes_per_pixel, instruction.width, instruction.height, GL_RGBA, GL_UNSIGNED_BYTE, instruction.pixel_data);
	clearImage(0,0,1,0.25);
	glFlush();

	drawActMines(0.5,score,0.25,0.09,0.25,2);
	glFlush();
	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, dot.bytes_per_pixel, dot.width, dot.height, GL_RGBA, GL_UNSIGNED_BYTE, dot.pixel_data);
	clearImage(0.5+0.18,0.25,0.05,0.25);
	drawActMines(0.73,(score-int(score))*1000,0.25,0.09,0.25,3);
}

void dispLoose(int x, int y) {
	//Image of mine blast.
	initImage(243.0/255, 203.0/255, 142.0/255);
	gluBuild2DMipmaps(GL_TEXTURE_2D, blast.bytes_per_pixel, blast.width, blast.height, GL_RGBA, GL_UNSIGNED_BYTE, blast.pixel_data);
	clearImage(y*stepx,(numRows-x-1)*stepy,stepx,stepy);
	b[x][y] = '9';
	glFlush();

	//Image of Game Over.
	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, gameOver.bytes_per_pixel, gameOver.width, gameOver.height, GL_RGBA, GL_UNSIGNED_BYTE, gameOver.pixel_data);
	clearImage(0.25+0.125,1.0,0.75-0.125,0.125);
	glFlush();

	//Image of sad Smiley.
	initImage();
	gluBuild2DMipmaps(GL_TEXTURE_2D, sad.bytes_per_pixel, sad.width, sad.height, GL_RGBA, GL_UNSIGNED_BYTE, sad.pixel_data);
	clearImage(0.25,1.0,0.125,0.125);
	glFlush();

	int i,j;

	for(i=0; i<numRows; i++)
		for(j=0; j<numCols; j++)
			if(a[i][j] == 9 && b[i][j] == '*') {
				initImage(243.0/255, 203.0/255, 142.0/255);
				gluBuild2DMipmaps(GL_TEXTURE_2D, bomb.bytes_per_pixel, bomb.width, bomb.height, GL_RGBA, GL_UNSIGNED_BYTE, bomb.pixel_data);
				clearImage(j*stepx,(numRows-i-1)*stepy,stepx,stepy);
				glFlush();
			}

	for(i=0; i<numRows; i++)
		for(j=0; j<numCols; j++)
			if(a[i][j] != 9 && b[i][j] == '9') {
				glColor3f(0.0,0.0,0.0);
				glLineWidth(10);
				glBegin(GL_LINES);
					glVertex3f(j*stepx,(numRows-i)*stepy,0);
					glVertex3f((j+1)*stepx,(numRows-i-1)*stepy,0);
					glVertex3f((j+1)*stepx,(numRows-i)*stepy,0);
					glVertex3f(j*stepx,(numRows-i-1)*stepy,0);
				glEnd();
				glFlush();
			}

	totalCells = 0;

	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &image);
	lines();
	glFlush();
}

#endif /* DISPOBJECTS_H_ */
