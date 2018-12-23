#include <stdlib.h>
#include<GL/gl.h>
#include<stdio.h>
#include <GL/glut.h>
#include "imageloader.h"
float _angle = 0.0, _anglex = 0.0, k = 1;
GLuint _textureAC, _textureNotice, _textureGallery, _textureGate, _textureChannel, _textureBrick, _textureDCE, _textureLab, _textureDoor, _textureWindow1, _textureParking, _textureGrass, _textureRoof, _textureMainRoad, _textureWindow, _textureSky, _textureFloor, _textureRail, _textureRoad;
static int menu_id, value = 0, window = 0;
GLfloat currentPosition[3] = {0.0, 0.0, 0.0};

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	Image* image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\bricks.bmp");
	_textureBrick = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\door.bmp");
	_textureDoor = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\grass.bmp");
	_textureGrass = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\roof.bmp");
	_textureRoof = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\window.bmp");
	_textureWindow = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\sky.bmp");
	_textureSky = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\floor.bmp");
	_textureFloor = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\rail.bmp");
	_textureRail = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\road.bmp");
	_textureRoad = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\road1.bmp");
	_textureMainRoad = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\parking.bmp");
	_textureParking = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\window1.bmp");
	_textureWindow1 = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\lab.bmp");
	_textureLab = loadTexture(image);
    image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\DCE.bmp");
	_textureDCE = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\channel.bmp");
	_textureChannel = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\gate.bmp");
	_textureGate = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\gallery.bmp");
	_textureGallery = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\notice.bmp");
	_textureNotice = loadTexture(image);
	image = loadBMP("C:\\Users\\utkar\\Desktop\\3d\\ac.bmp");
	_textureAC = loadTexture(image);
	delete image;
    }

void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar,-1.0, 2.0, 1.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
}

void myresize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h/ (GLfloat) w, 2.0* (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat) w/ (GLfloat) h, 2.0* (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void drawACRight(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureAC);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(x, y + 7.2, z + 1.5);
            glTexCoord3f(0.0, 1.0, -1);  glVertex3f(x, y + 10, z + 1.5);
            glTexCoord3f(1.0, 1.0, -1);  glVertex3f(x, y + 10, z - 1.5);
            glTexCoord3f(1.0, 0.0, 1);  glVertex3f(x, y + 7.2, z - 1.5);
        glEnd();
    glPopMatrix();
}

void drawACFront(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureAC);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 0.0, 0.1); glVertex3f(x + 1.5, y + 7.2, z);
            glTexCoord3f(0.0, 1.0, 0.1); glVertex3f(x + 1.5, y + 10, z);
            glTexCoord3f(1.0, 1.0, 0.1); glVertex3f(x - 1.5 , y + 10, z);
            glTexCoord3f(1.0, 0.0, 0.1); glVertex3f(x - 1.5, y + 7.2, z);
        glEnd();
    glPopMatrix();
}

void drawDCE(){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureDCE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-34.9, 85, 10);
            glTexCoord3f(0.0,1.0,-1);  glVertex3f(-34.9, 88, 10);
            glTexCoord3f(1.0,1.0,-1);  glVertex3f(-34.9, 88, 0);
            glTexCoord3f(1.0, 0.0,1);  glVertex3f(-34.9, 85, 0);
        glEnd();
    glPopMatrix();
}

void drawChannel(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureChannel);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(x-5, y, z);
            glTexCoord3f(0.0,1.0,-1);  glVertex3f(x-5, y + 15, z);
            glTexCoord3f(1.0,1.0,-1);  glVertex3f(x+10, y + 15, z);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(x+10, y, z);
        glEnd();
    glPopMatrix();
}

void drawParking(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureParking);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(x-90, y, z+80);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(x-90, y, z-80);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(x-55, y, z-80);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(x-55, y, z+80);
        glEnd();
    glPopMatrix();
}

void drawMPLab(){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureLab);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(1.0, 0.0, 1);  glVertex3f(0, 85, 29.9);
            glTexCoord3f(1.0, 1.0, -1);  glVertex3f(0, 88, 29.9);
            glTexCoord3f(0.0, 1.0, -1);  glVertex3f(15, 88, 29.9);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(15, 85, 29.9);
        glEnd();
    glPopMatrix();
}

void drawGallery(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureGallery);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 0, 0.1); glVertex3f(x - 10, y, z);
            glTexCoord3f(0, 1.0, 0.1); glVertex3f(x - 10, y + 15, z);
            glTexCoord3f(1, 1.0, 0.1); glVertex3f(x + 10 , y + 15, z);
            glTexCoord3f(1.0, 0.0, 0.1); glVertex3f(x + 10, y, z);
        glEnd();
    glPopMatrix();
}

void drawGateFront(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureGate);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 0, 0.1); glVertex3f(x - 1.5, y, z);
            glTexCoord3f(0, 1.0, 0.1); glVertex3f(x - 1.5, y + 10, z);
            glTexCoord3f(1, 1.0, 0.1); glVertex3f(x + 1.5 , y + 10, z);
            glTexCoord3f(1.0, 0.0, 0.1); glVertex3f(x + 1.5, y, z);
        glEnd();
    glPopMatrix();
}

void drawGateRight(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureGate);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(x, y, z - 1.5);
            glTexCoord3f(0.0, 1.0, -1);  glVertex3f(x, y + 10, z - 1.5);
            glTexCoord3f(1.0, 1.0, -1);  glVertex3f(x, y + 10, z + 1.5);
            glTexCoord3f(1.0, 0.0, 1);  glVertex3f(x, y, z + 1.5);
        glEnd();
    glPopMatrix();
}

void drawMainRoad(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureMainRoad);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(x-120, y, z+100);
            glTexCoord3f(0.0,1.0,-1);  glVertex3f(x-120, y, z-100);
            glTexCoord3f(1.0,1.0,-1);  glVertex3f(x-90, y, z-100);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(x-90, y, z+100);
        glEnd();
    glPopMatrix();
}

void drawRoad(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoad);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(x-70, y, z+70);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(x-70, y, z+90);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(x+70, y, z+90);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(x+70, y, z+70);
        glEnd();
    glPopMatrix();
}

void drawNotice(float x, float y, float z){
glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureNotice);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 1.0, 1);  glVertex3f(x, y, z + 3);
            glTexCoord3f(1.0, 1.0, -1);  glVertex3f(x, y + 7, z + 3);
            glTexCoord3f(1.0, 0.0, -1);  glVertex3f(x, y + 7, z - 3);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(x, y, z - 3);
        glEnd();
    glPopMatrix();
}

void drawWindowRight(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureWindow);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 1);  glVertex3f(x, y + 1, z + 1.5);
            glTexCoord3f(2.0, 2.0, -1);  glVertex3f(x, y + 6, z + 1.5);
            glTexCoord3f(2.0, 0.0, -1);  glVertex3f(x, y + 6, z - 1.5);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(x, y + 1, z - 1.5);
        glEnd();
    glPopMatrix();
}

void drawWindow1Left(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureWindow1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(1.0, 0.0, 1);  glVertex3f(x, y + 1, z + 1.5);
            glTexCoord3f(1.0, 1.0, -1);  glVertex3f(x, y + 10, z + 1.5);
            glTexCoord3f(0.0, 1.0, -1);  glVertex3f(x, y + 10, z - 1.5);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(x, y + 1, z - 1.5);
        glEnd();
    glPopMatrix();
}

void drawWindowFront(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureWindow);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 0.1); glVertex3f(x - 1.5, y + 1, z);
            glTexCoord3f(4.0, 2.0, 0.1); glVertex3f(x - 1.5, y + 6, z);
            glTexCoord3f(4.0, 0.0, 0.1); glVertex3f(x + 1.5 , y + 6, z);
            glTexCoord3f(0.0, 0.0, 0.1); glVertex3f(x + 1.5, y + 1, z);
        glEnd();
    glPopMatrix();
}

void drawGrass(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureGrass);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(x-50, -y, z+50);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(x-50, -y, z-50);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(x+50, -y, z-50);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(x+50, -y, z+50);
        glEnd();
    glPopMatrix();
}

void drawFrontFloor(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureFloor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(-x, y, z+14);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(-x, y, z-14);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(x, y, z-14);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(x, y, z+14);
        glEnd();
    glPopMatrix();
}

void drawLeftFloor(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureFloor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(-x-14, y, -z);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(-x-14, y, z);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(-x+14, y, z);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(-x+14, y, -z);
        glEnd();
    glPopMatrix();
}

void drawBackFloor(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureFloor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(-x, y, -z-14);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(-x, y, -z+14);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(x-40, y, -z+14);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(x-40, y, -z-14);
        glEnd();
    glPopMatrix();
}

void drawRightFloor(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureFloor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(x+14, y, z);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(x-14, y, z);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(x-14, y, -(z/2));
            glTexCoord3f(70.0,70.0,1);  glVertex3f(x+14, y, -(z/2));
        glEnd();
    glPopMatrix();
}

void drawBackLowerFloor(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureFloor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(x+4, y, -z);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(x+4, y, -(z/3));
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(x-4, y, -(z/3));
            glTexCoord3f(70.0,70.0,1);  glVertex3f(x-4, y, -z);
        glEnd();
    glPopMatrix();
}

void drawBackRightFloor(float x, float y, float z){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureFloor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(x/5, y, -z-4);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(x, y, -z-4);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(x, y, -z+4);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(x/5, y, -z+4);
        glEnd();
    glPopMatrix();
}

void drawPillar(float x, float y, float z){
    glColor3d(1.0, 0.9921, 0.8156);
    glPushMatrix();
    glRotatef(_angle, 0.0, 1.0, 0.0);
    glTranslatef(x, y, z-21.5);
    glScaled(1.0, 240.0, 1.0);
    glutSolidCube(1);
    glPopMatrix();
}

void drawBackRailing(float x, float y, float z, float height){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRail);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, -1);  glVertex3f(-x, y, -z);
            glTexCoord3f(4.0, 2.0, -1);  glVertex3f(-x, y+height, -z);
            glTexCoord3f(4.0, 0.0, -1);  glVertex3f(-x+34.5, y+height , -z);
            glTexCoord3f(0.0, 0.0, -1);  glVertex3f(-x+34.5, y, -z);
        glEnd();
    glPopMatrix();
}

void drawFrontRailing(float x, float y, float z, float height){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRail);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 0.1); glVertex3f(-x, y, -z);
            glTexCoord3f(4.0, 2.0, 0.1); glVertex3f(-x, y + height, -z);
            glTexCoord3f(4.0, 0.0, 0.1); glVertex3f(-x+54, y+height, -z);
            glTexCoord3f(0.0, 0.0, 0.1); glVertex3f(-x+54.0, y, -z);
        glEnd();
    glPopMatrix();
}

void drawRightRailing(float x, float y, float z, float height){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRail);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 1);  glVertex3f(x, y, -z);
            glTexCoord3f(2.0, 2.0, -1);  glVertex3f(x, y, z+15);
            glTexCoord3f(2.0, 0.0, -1);  glVertex3f(x, y + height, z+15);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(x, y + height, -z);
        glEnd();
    glPopMatrix();
}

void drawLeftRailing(float x, float y, float z, float height){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRail);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 1);  glVertex3f(-x, y, z);
            glTexCoord3f(2.0, 2.0, -1);  glVertex3f(-x, y, -z);
            glTexCoord3f(2.0, 0.0, -1);  glVertex3f(-x, y + height, -z);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(-x, y + height, z);
        glEnd();
    glPopMatrix();
}

void drawBackLeftRailing(float x, float y, float z, float height){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRail);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 1);  glVertex3f(x, y, -z);
            glTexCoord3f(2.0, 2.0, -1);  glVertex3f(x, y, -z-15);
            glTexCoord3f(2.0, 0.0, -1);  glVertex3f(x, y + height, -z-15);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(x, y + height, -z);
        glEnd();
    glPopMatrix();
}

void drawRightBackRailing(float x, float y, float z, float height){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRail);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, -1);  glVertex3f(x, y, -z);
            glTexCoord3f(4.0, 2.0, -1);  glVertex3f(x, y+height, -z);
            glTexCoord3f(4.0, 0.0, -1);  glVertex3f(x+20, y+height , -z);
            glTexCoord3f(0.0, 0.0, -1);  glVertex3f(x+20, y, -z);
        glEnd();
    glPopMatrix();
}

void drawWalls(int y, int height){
    // Front Side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 0.1); glVertex3f(-35, y + height, 30);
            glTexCoord3f(4.0, 2.0, 0.1); glVertex3f(35, y + height, 30);
            glTexCoord3f(4.0, 0.0, 0.1); glVertex3f(35, y, 30);
            glTexCoord3f(0.0, 0.0, 0.1); glVertex3f(-35, y, 30);
        glEnd();
    glPopMatrix();

        // Front Outer Side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 0.1); glVertex3f(-55, y + height, 50);
            glTexCoord3f(4.0, 2.0, 0.1); glVertex3f(55, y + height, 50);
            glTexCoord3f(4.0, 0.0, 0.1); glVertex3f(55, y, 50);
            glTexCoord3f(0.0, 0.0, 0.1); glVertex3f(-55, y, 50);
        glEnd();
    glPopMatrix();

    //LEFT SIDE
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 1);  glVertex3f(-35, y, 30);
            glTexCoord3f(2.0, 2.0, -1);  glVertex3f(-35, y, -30);
            glTexCoord3f(2.0, 0.0, -1);  glVertex3f(-35, y + height, -30);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(-35, y + height, 30);
        glEnd();
    glPopMatrix();

    //LEFT Outer SIDE
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 1);  glVertex3f(-55, y, 50);
            glTexCoord3f(2.0, 2.0, -1);  glVertex3f(-55, y, -50);
            glTexCoord3f(2.0, 0.0, -1);  glVertex3f(-55, y + height, -50);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(-55, y + height, 50);
        glEnd();
    glPopMatrix();

    //BACK SIDE
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, -1);  glVertex3f(-35, y, -30);
            glTexCoord3f(4.0, 2.0, -1);  glVertex3f(15, y, -30);
            glTexCoord3f(4.0, 0.0, -1);  glVertex3f(15, y + height, -30);
            glTexCoord3f(0.0, 0.0, -1);  glVertex3f(-35, y + height, -30);
        glEnd();
    glPopMatrix();

    //BACK OUTER SIDE
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, -1);  glVertex3f(-55, y, -50);
            glTexCoord3f(4.0, 2.0, -1);  glVertex3f(15, y, -50);
            glTexCoord3f(4.0, 0.0, -1);  glVertex3f(15, y + height, -50);
            glTexCoord3f(0.0, 0.0, -1);  glVertex3f(-55, y + height, -50);
        glEnd();
    glPopMatrix();

    //RIGHT SIDE
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 1);  glVertex3f(35, y, -15);
            glTexCoord3f(2.0, 2.0, -1);  glVertex3f(35, y, 30);
            glTexCoord3f(2.0, 0.0, -1);  glVertex3f(35, y + height, 30);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(35, y + height, -15);
        glEnd();
    glPopMatrix();

    //RIGHT OUTER SIDE
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 1);  glVertex3f(55, y, -15);
            glTexCoord3f(2.0, 2.0, -1);  glVertex3f(55, y, 50);
            glTexCoord3f(2.0, 0.0, -1);  glVertex3f(55, y + height, 50);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(55, y + height, -15);
        glEnd();
    glPopMatrix();

    //RIGHT BACK OUTER SIDE
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, -1);  glVertex3f(35, y, -15);
            glTexCoord3f(4.0, 2.0, -1);  glVertex3f(55, y, -15);
            glTexCoord3f(4.0, 0.0, -1);  glVertex3f(55, y + height, -15);
            glTexCoord3f(0.0, 0.0, -1);  glVertex3f(35, y + height, -15);
        glEnd();
    glPopMatrix();

    //RIGHT OUTER SIDE
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0, 2.0, 1);  glVertex3f(15, y, -30);
            glTexCoord3f(2.0, 2.0, -1);  glVertex3f(15, y, -50);
            glTexCoord3f(2.0, 0.0, -1);  glVertex3f(15, y + height, -50);
            glTexCoord3f(0.0, 0.0, 1);  glVertex3f(15, y + height, -30);
        glEnd();
    glPopMatrix();

    int i = 0, y1 = -1, height1 = 4;
    for(i = 0; i <= 7; i++){
        drawWindowFront(32, y1 + height1, 29.9);
        drawWindowFront(28, y1 + height1, 29.9);
        drawWindowFront(24, y1 + height1, 29.9);
        drawWindowFront(20, y1 + height1, 29.9);
        drawWindowFront(12, y1 + height1, 29.9);
        drawWindowFront(8, y1 + height1, 29.9);
        drawWindowFront(4, y1 + height1, 29.9);
        drawWindowFront(0, y1 + height1, 29.9);
        drawWindowFront(-31, y1 + height1, 29.9);
        drawWindowFront(-18, y1 + height1, -29.9);
        drawWindowFront(-14, y1 + height1, -29.9);
        drawWindowFront(-10, y1 + height1, -29.9);
        drawWindowFront(-.5, y1 + height1, -29.9);
        drawWindowFront(3.5, y1 + height1, -29.9);
        drawWindowFront(7.5, y1 + height1, -29.9);
        drawWindowRight(34.9, y1 + height1, -12);
        drawWindowRight(34.9, y1 + height1, -8);
        drawWindowRight(34.9, y1 + height1, -4);
        drawWindowRight(34.9, y1 + height1, 4);
        drawWindowRight(34.9, y1 + height1, 8);
        drawWindowRight(34.9, y1 + height1, 12);
        drawWindowRight(34.9, y1 + height1, 20);
        drawWindowRight(34.9, y1 + height1, 24);
        drawWindowRight(34.9, y1 + height1, 28);
        drawWindowRight(-34.9, y1 + height1, -28);
        drawWindowRight(-34.9, y1 + height1, -24);
        drawWindowRight(-34.9, y1 + height1, -16);
        drawWindowRight(-34.9, y1 + height1, -12);
        drawWindowRight(-34.9, y1 + height1, -8);
        //drawWindowRight(-34.9, y1 + height1, 0);
        //drawWindowRight(-34.9, y1 + height1, 4);
        drawWindowRight(-34.9, y1 + height1, 8);
        drawWindowRight(-34.9, y1 + height1, 16);
        drawWindowRight(-34.9, y1 + height1, 20);
        drawWindowRight(-34.9, y1 + height1, 24);
        drawWindow1Left(-55.1, y1 + height1, -45);
        drawWindow1Left(-55.1, y1 + height1, -40);
        drawWindow1Left(-55.1, y1 + height1, -35);
        drawWindow1Left(-55.1, y1 + height1, -30);
        drawWindow1Left(-55.1, y1 + height1, -25);
        drawWindow1Left(-55.1, y1 + height1, -20);
        drawWindow1Left(-55.1, y1 + height1, -15);
        drawWindow1Left(-55.1, y1 + height1, -10);
        drawWindow1Left(-55.1, y1 + height1, -5);
        drawWindow1Left(-55.1, y1 + height1, 0);
        drawWindow1Left(-55.1, y1 + height1, 5);
        drawWindow1Left(-55.1, y1 + height1, 10);
        drawWindow1Left(-55.1, y1 + height1, 15);
        drawWindow1Left(-55.1, y1 + height1, 20);
        drawWindow1Left(-55.1, y1 + height1, 25);
        drawWindow1Left(-55.1, y1 + height1, 30);
        drawWindow1Left(-55.1, y1 + height1, 35);
        drawWindow1Left(-55.1, y1 + height1, 40);
        drawWindow1Left(-55.1, y1 + height1, 45);
        drawNotice(-34.8, y1 + height1, 2);
        drawACFront(-31, y1 + height1, 29.9);
        if(i!=5){
            drawACFront(0, y1 + height1, 29.9);
            drawACFront(4, y1 + height1, 29.9);
            drawACFront(8, y1 + height1, 29.9);
            drawACFront(12, y1 + height1, 29.9);
            drawACRight(-34.9, y1 + height1, 0);
            drawACRight(-34.9, y1 + height1, 4);
            drawACRight(-34.9, y1 + height1, 8);
        }
        drawACRight(34.9, y1 + height1, -12);
        drawACRight(34.9, y1 + height1, -8);
        drawACRight(34.9, y1 + height1, -4);
        drawACRight(34.9, y1 + height1, 4);
        drawACRight(34.9, y1 + height1, 8);
        drawACRight(34.9, y1 + height1, 12);
        drawACRight(34.9, y1 + height1, 20);
        drawACRight(34.9, y1 + height1, 24);
        drawACRight(34.9, y1 + height1, 28);
        drawACRight(-34.9, y1 + height1, -28);
        drawACRight(-34.9, y1 + height1, -24);
        drawACRight(-34.9, y1 + height1, -16);
        drawACRight(-34.9, y1 + height1, -12);
        drawACRight(-34.9, y1 + height1, -8);
        drawACRight(-34.9, y1 + height1, 16);
        drawACRight(-34.9, y1 + height1, 20);
        drawACRight(-34.9, y1 + height1, 24);
        drawACFront(20, y1 + height1, 29.9);
        drawACFront(24, y1 + height1, 29.9);
        drawACFront(28, y1 + height1, 29.9);
        drawACFront(32, y1 + height1, 29.9);
        drawACFront(-31, y1 + height1, 29.9);
        drawACFront(-18, y1 + height1, -29.9);
        drawACFront(-14, y1 + height1, -29.9);
        drawACFront(-10, y1 + height1, -29.9);
        drawACFront(-.5, y1 + height1, -29.9);
        drawACFront(3.5, y1 + height1, -29.9);
        drawACFront(7.5, y1 + height1, -29.9);
        y1 += 15;
    }
    y1 = -.5;
    for(i = 0; i < 8; i++){
        drawChannel(-30, y1, -29.9);
        drawGateFront(-6, y1, -29.9);
        drawGateFront(11.5, y1, -29.9);
        drawGateRight(34.9, y1, 0);
        drawGateRight(34.9, y1, 16);
        drawGateFront(16, y1, 29.9);
        drawGateFront(-4, y1, 29.9);
        drawGallery(-18, y1, 29.9);
        drawGateRight(-34.9, y1, 28);
        drawGateRight(-34.9, y1, 12);
        drawGateRight(-34.9, y1, -4);
        drawGateRight(-34.9, y1, -20);
        y1 += 15;
    }
    drawPillar(7.6, -.5, 0);
    drawPillar(7.6, -.5, 4.6);
    drawPillar(7.6, -.5, 9.1);
    drawPillar(7.6, -0.5, 13.7);
    drawPillar(14.6, -.5, -4.6);
    drawPillar(14.6, -.5, 0);
    drawPillar(14.6, -.5, 4.6);
    //drawPillar(14.6, -.5, 9.1);
    drawPillar(14.5, -.5, 13.7);
    drawPillar(18.6, -.5, 13.7);
    drawPillar(22.7, -.5, 13.7);
    drawPillar(26.8, -.5, 13.7);
    drawPillar(18.6, -.5, 7.1);
    drawPillar(22.7, -.5, 7.1);
    drawPillar(26.8, -.5, 7.1);
    drawPillar(30.9, -.5, 7.1);
}

GLdouble viewer[] = {0.0, 0.0, 5.0};

void bitmap_output(float x, float y, float z, char *string, void *font){
  int len, i;
  glRasterPos3f(x, y, z);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

void front(){
    glClearColor(0.0, 0.0, 1.0, 1.0);
	glColor3f(0.0,1.0,0.0);
	bitmap_output(-1.3, 1.7, 0, "BANGALORE INSTITUTE OF TECHNOLOGY",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-1.60, 1.3, 0, "COMPUTER GRAPHICS AND VISUALIZATION(15CSL68) ",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-.5, .9, 0, "MINI PROJECT",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-1.2, .5, 0, "BIT COLLEGE 3D MODEL SIMULATION",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-1.8, -.1, 0, "SUBMITTED BY-",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-2.0, -.4, 0,"NAME- UTKARSH ASHU",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(1.5, -.4, 0,"USN- 1BI15CS177",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(-2.0, -.7, 0, "NAME- UTKARSH GUPTA",GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(1.5, -.7,0, "USN- 1BI15CS178",GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1.0,0.0,0.0);
	glColor3f(0.0,1.0,0.0);
	bitmap_output(1.8, -.9, 0, "Press Enter to continue.......",GLUT_BITMAP_HELVETICA_18);
}

void firstPerson(){
    glLoadIdentity();
    gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    front();
    glutSwapBuffers();
}

void BirdEye(){
    glLoadIdentity();
    gluLookAt(55, 90, -40, 0.0, 90.0, 0.0, 0.0, 1.0, 0.0 );
    glutPostRedisplay();
}

void menu(int num){
    if(num == 0)
        exit(0);
    else
        value = num;
    glutPostRedisplay();
}

void createMenu(void){
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Bird Eye", 1);
    glutAddMenuEntry("First Person", 2);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawSky(){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureSky);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-300,500,-70);
            glTexCoord3f(1.0,1.0,0.1);  glVertex3f(300,500,-70);
            glTexCoord3f(1.0,0.0,0.1);  glVertex3f(300,-1.5,-70);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-300,-1.5,-70);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureSky);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-120,500,-300);
            glTexCoord3f(1.0,1.0,0.1);  glVertex3f(-120,500,300);
            glTexCoord3f(1.0,0.0,0.1);  glVertex3f(-120,-1.5,300);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-120,-1.5,-300);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureSky);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-300,500,90);
            glTexCoord3f(1.0,1.0,0.1);  glVertex3f(300,500,90);
            glTexCoord3f(1.0,0.0,0.1);  glVertex3f(300,-1.5,90);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-300,-1.5,90);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureSky);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,1.0,0.1);  glVertex3f(120,500,-300);
            glTexCoord3f(1.0,1.0,0.1);  glVertex3f(120,500,300);
            glTexCoord3f(1.0,0.0,0.1);  glVertex3f(120,-1.5,300);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(120,-1.5,-300);
        glEnd();
    glPopMatrix();
}

void drawSphere(double a){
    glPushMatrix();
        glTranslated(0.0, 5.0, -5.0);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glRotated(a, 0.0, 0.0, 1.0);
        glutWireSphere(5.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0.0, 10.0, -15.0);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glRotated(a, 0.0, 0.0, 1.0);
        glutWireSphere(5.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-5.0, 5.0, -20.0);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glRotated(a, 0.0, 0.0, 1.0);
        glutWireSphere(5.0, 50, 50);
    glPopMatrix();
}

void renderScene(void) {
    createMenu();
    const double z = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = z * 90.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    drawSky();
    // Grass
    drawGrass(0, 1, 50);
    drawGrass(100, 1, 50);
    drawGrass(-100,1, 50);
    drawGrass(0,1, -50);
    drawGrass(100,1, -50);
    drawGrass(-100,1, -50);

    int i = 0,y = -1, height = 15;
    for(i = 0; i<=7; i++){
        drawWalls(y, height);
        y += height;
    }
    y=-.5;
    height=15;
    for(i=0;i<=8;i++)
    {
        drawFrontFloor(55, y, 36);
        drawLeftFloor(41, y, 30);
        drawBackFloor(55, y, 36);
        drawRightFloor(41, y, 30);
        drawBackLowerFloor(11, y, 30);
        drawBackRightFloor(35, y, 11);
        y = y + height;
    }
    y = -.5;
    for(i = 0; i < 9; i++){
        drawBackRailing(27, y, 22, 4);
        drawFrontRailing(27, y, -22, 4);
        drawRightRailing(27, y, -22, 4);
        drawLeftRailing(27, y, 22, 4);
        drawBackLeftRailing(15, y, 15, 4);
        drawBackLeftRailing(7, y, 7, 4);
        drawRightBackRailing(7, y, 7, 4);
        drawRightBackRailing(15, y, 15, 4);
        if(i == 8){
            drawRightBackRailing(35, y, 15, 4);
            drawBackRailing(55, y, 50, 4);
            drawBackRailing(20.5, y, 50, 4);
            drawBackRailing(19.5, y, 50, 4);
            drawBackLeftRailing(15, y, 35,4);
            drawBackLeftRailing(15, y, 30,4);
            drawRightRailing(55, y, -30, 4);
            drawLeftRailing(55, y, 50, 4);
            drawFrontRailing(55, y, -50, 4);
            drawFrontRailing(2, y, -50, 4);
            drawFrontRailing(-1, y, -50, 4);
        }
        y = y + 15;
    }
    drawMPLab();
    drawDCE();
    drawRoad(0, -.95, 0);
    drawMainRoad(0, -.9, 0);
    drawParking(0, -.9, 0);
    drawSphere(a);
    switch(value){
        case 1: _angle = 0;
                BirdEye();
                value = 0;
                glutSwapBuffers();
                break;
        case 2: _angle = 0;
                firstPerson();
                value = 0;
                glutSwapBuffers();
                break;
    }
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

void handleKeypress1(int key, int x, int y){
	switch (key) {
        case GLUT_KEY_RIGHT:
            glTranslated(-1, 0.0, 0.0);
            currentPosition[0] += 1;
            break;
        case GLUT_KEY_LEFT:
            glTranslated(1, 0.0, 0.0);
            currentPosition[0] -= 1;
            break;
        case GLUT_KEY_UP:
            glTranslated(0.0, 0.0, 1);
            currentPosition[2] -= 1;
            break;
        case GLUT_KEY_DOWN:
            glTranslated(0.0, 0.0, -1);
            currentPosition[2] += 1;
            break;
        case GLUT_KEY_PAGE_UP:
            glTranslated(0.0, -1, 0.0);
            currentPosition[1] += 1;
            break;
        case GLUT_KEY_PAGE_DOWN:
            glTranslated(0.0, 1, 0.0);
            currentPosition[1] -= 1;
            break;
        case GLUT_KEY_HOME:
            _angle += 1;
            if (_angle > 360) _angle = 0.0;
            break;
        case GLUT_KEY_END:
            _angle -= 1;
            if (_angle > 360) _angle = 0.0;
            break;
        case GLUT_KEY_F5:
            _anglex += .1;
            if(_anglex > 360) _anglex = 0.0;
            glRotatef(_anglex, 1.0, 0.0, 0.0);
            break;
        default:
            break;
	}
	glutPostRedisplay();
}

void keypress(unsigned char key, int x, int y){
    if(key == 13){
        glutDestroyWindow(window);
    }
}

void init(void){
		glClearColor(1.0,1.0,1.0,1.0);
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(0.0,600.0,0.0,600.0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(600,600);
    glutCreateWindow("BANGALORE INSTITUTE OF TECHNOLOGY");
    glutDisplayFunc(renderScene);
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(resize);
    glutSpecialFunc(handleKeypress1);
    createMenu();
    Initialize();
    glutFullScreen();
    window = glutCreateWindow("First Page");
    glutDisplayFunc(display);
    glutReshapeFunc(myresize);
    glutKeyboardFunc(keypress);
    glutFullScreen();
    init();
	glutMainLoop();
}
