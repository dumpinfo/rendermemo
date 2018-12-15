/*
 * Image.h
 *
 *  Created on: Sep 29, 2013
 *      Author: ankit
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "Images/num1.c"
#include "Images/num2.c"
#include "Images/num3.c"
#include "Images/num4.c"
#include "Images/num5.c"
#include "Images/num6.c"
#include "Images/num7.c"
#include "Images/num8.c"

#include "Images/new.c"
#include "Images/flagsTxt.c"
#include "Images/gameOver.c"

#include "Images/flag.c"
#include "Images/bomb.c"
#include "Images/blast.c"

#include "Images/happy.c"
#include "Images/open.c"
#include "Images/sad.c"

#include "Images/win.c"
#include "Images/instruction.c"
#include "Images/scoreTxt.c"
#include "Images/dot.c"

#include "Images/slash.c"
#include "Images/zero.c"
#include "Images/one.c"
#include "Images/two.c"
#include "Images/three.c"
#include "Images/four.c"
#include "Images/five.c"
#include "Images/six.c"
#include "Images/seven.c"
#include "Images/eight.c"
#include "Images/nine.c"

GLuint image;

void initImage(float R = 1, float G = 1, float B = 1) {
	glGenTextures(1, &image);
	glEnable(GL_TEXTURE_2D);
	glColor3f(R,G,B);
}

void clearImage(float transX, float transY, float scaleX, float scaleY) {
	glPushMatrix();
		glTranslatef(transX,transY,0);
		glScalef(scaleX,scaleY,1);
		glBegin(GL_QUADS);
			glTexCoord2d(0.0, 1.0); glVertex2d(0.0, 0.0);
			glTexCoord2d(0.0, 0.0); glVertex2d(0.0, 1.0);
			glTexCoord2d(1.0, 0.0); glVertex2d(1.0, 1.0);
			glTexCoord2d(1.0, 1.0); glVertex2d(1.0, 0.0);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &image);
}


#endif /* IMAGE_H_ */
