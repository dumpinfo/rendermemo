/*
 * declaration.h
 *
 *  Created on: Sep 30, 2013
 *      Author: ankit
 */

#ifndef DECLARATION_H_
#define DECLARATION_H_

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>

using namespace std;

int **a;
char **b;
bool **c;

int numRows, numCols;
int minesnum = 0, totalMines, totalCells, totalCellsBack, dispStep, _3BV = 0;
int winW, winH;
float stepx, stepy, topPix, ppb, score;
bool startFlag = true;
int Time;

void onMouse (int, int, int, int);
void initMat (void);
void initGraph ();

void calcleft (int , int);
void calcWindowSize ();

void dispWin();
void display (void);
void lines (void);
void updateMinesNum (int, bool);
void drawActMines (float, int temp = totalMines, float ypos=1.0, float scaleX=0.18/dispStep, float scaleY=0.125, int max=dispStep);

#endif /* DECLARATION_H_ */
