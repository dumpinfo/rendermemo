/*
 * calculation.h
 *
 *  Created on: Oct 3, 2013
 *      Author: ankit
 */

#ifndef CALCULATION_H_
#define CALCULATION_H_

#include "dispObjects.h"

int calcMines(int x, int y) {
	int sum = 0;

	if(x-1 >= 0)
		sum += a[x-1][y];
	if(x+1 < numRows)
		sum += a[x+1][y];
	if(y-1 >= 0)
		sum += a[x][y-1];
	if(y+1 < numCols)
		sum += a[x][y+1];
	if(x-1 >= 0 && y+1 < numCols)
		sum += a[x-1][y+1];
	if(x+1 < numRows && y+1 < numCols)
		sum += a[x+1][y+1];
	if(x-1 >= 0 && y-1 >= 0)
		sum += a[x-1][y-1];
	if(x+1 < numRows && y-1 >= 0)
		sum += a[x+1][y-1];

	return sum/9;
}

void calcLeft(int x, int y) {
	if(a[x][y] == 9)
		dispLoose(x,y);
	else {
		if(startFlag) {
			startFlag = false;
			Time = time(NULL);
		}
		totalCells--;
		int num = calcMines(x,y);

		if(b[x][y] == '9')
			updateMinesNum(--minesnum,false);
		b[x][y] = 48 + num;

		switch(num) {
			case 0:
				dispBlank(x, y);
				break;
			case 1:
				initImage();
				gluBuild2DMipmaps(GL_TEXTURE_2D, num1.bytes_per_pixel, num1.width, num1.height, GL_RGBA, GL_UNSIGNED_BYTE, num1.pixel_data);
				clearImage(y*stepx,(numRows-x-1)*stepy,stepx,stepy);
				break;
			case 2:
				initImage();
				gluBuild2DMipmaps(GL_TEXTURE_2D, num2.bytes_per_pixel, num2.width, num2.height, GL_RGBA, GL_UNSIGNED_BYTE, num2.pixel_data);
				clearImage(y*stepx,(numRows-x-1)*stepy,stepx,stepy);
				break;
			case 3:
				initImage();
				gluBuild2DMipmaps(GL_TEXTURE_2D, num3.bytes_per_pixel, num3.width, num3.height, GL_RGBA, GL_UNSIGNED_BYTE, num3.pixel_data);
				clearImage(y*stepx,(numRows-x-1)*stepy,stepx,stepy);
				break;
			case 4:
				initImage();
				gluBuild2DMipmaps(GL_TEXTURE_2D, num4.bytes_per_pixel, num4.width, num4.height, GL_RGBA, GL_UNSIGNED_BYTE, num4.pixel_data);
				clearImage(y*stepx,(numRows-x-1)*stepy,stepx,stepy);
				break;
			case 5:
				initImage(x,y);
				gluBuild2DMipmaps(GL_TEXTURE_2D, num5.bytes_per_pixel, num5.width, num5.height, GL_RGBA, GL_UNSIGNED_BYTE, num5.pixel_data);
				clearImage(y*stepx,(numRows-x-1)*stepy,stepx,stepy);
				break;
			case 6:
				initImage(x,y);
				gluBuild2DMipmaps(GL_TEXTURE_2D, num6.bytes_per_pixel, num6.width, num6.height, GL_RGBA, GL_UNSIGNED_BYTE, num6.pixel_data);
				clearImage(y*stepx,(numRows-x-1)*stepy,stepx,stepy);
				break;
			case 7:
				initImage(x,y);
				gluBuild2DMipmaps(GL_TEXTURE_2D, num7.bytes_per_pixel, num7.width, num7.height, GL_RGBA, GL_UNSIGNED_BYTE, num7.pixel_data);
				clearImage(y*stepx,(numRows-x-1)*stepy,stepx,stepy);
				break;
			case 8:
				initImage(x,y);
				gluBuild2DMipmaps(GL_TEXTURE_2D, num8.bytes_per_pixel, num8.width, num8.height, GL_RGBA, GL_UNSIGNED_BYTE, num8.pixel_data);
				clearImage(y*stepx,(numRows-x-1)*stepy,stepx,stepy);
				break;
		}

		if(num==0) {
			if(x-1 >= 0 && (b[x-1][y] == '*' || b[x-1][y] == '9'))
				calcLeft(x-1,y);
			if(x+1 < numRows && (b[x+1][y] == '*' || b[x+1][y] == '9'))
				calcLeft(x+1,y);
			if(y-1 >= 0  && (b[x][y-1] == '*' || b[x][y-1] == '9'))
				calcLeft(x,y-1);
			if(y+1 < numCols && (b[x][y+1] == '*' || b[x][y+1] == '9'))
				calcLeft(x,y+1);
			if(x-1 >= 0 && y+1 < numCols && (b[x-1][y+1] == '*' || b[x-1][y+1] == '9'))
				calcLeft(x-1,y+1);
			if(x+1 < numRows && y+1 < numCols && (b[x+1][y+1] == '*' || b[x+1][y+1] == '9'))
				calcLeft(x+1,y+1);
			if(x-1 >= 0 && y-1 >= 0 && (b[x-1][y-1] == '*' || b[x-1][y-1] == '9'))
				calcLeft(x-1,y-1);
			if(x+1 < numRows && y-1 >= 0 && (b[x+1][y-1] == '*' || b[x+1][y-1] == '9'))
				calcLeft(x+1,y-1);
		}
		if(totalCells == 0) {
			Time = time(NULL)-Time;
			dispWin();
		}
		else
			lines();
	}
}

void calcWindowSize () {
	int screenW = glutGet(GLUT_SCREEN_WIDTH);
	int screenH = glutGet(GLUT_SCREEN_HEIGHT);

	if(numRows >= numCols) {
		rows:
		winH = screenH - 70;
		ppb = (winH / 1.125) / numRows;
		winW = ppb * numCols;
	}
	else {
		winW = screenW - 100;
		ppb = winW / numCols;
		winH = ppb * numRows  * 1.125;
		if(winH > screenH-70)
			goto rows;
	}
	topPix = winH / 9;
}

#endif /* CALCULATION_H_ */
