#include <GL/freeglut.h>  
#include <math.h>
#include<iostream>
#include <string.h>

#include "getbmp.h"

//textures
static unsigned int texture[5];


//cube
GLfloat x;
GLfloat y;
GLfloat z;

// vertices for the backg
GLfloat a = 50.0f;
GLfloat b5 = 1.0f;
GLfloat c = 50.0f;

// vertices for the z1


// variables to move outermost Object Frame (to move all the rendered environment)
GLfloat moveX = 0.0f;
GLfloat moveY = 0.0f;
GLfloat moveZ = 0.0f;

// variables to rotate outermost Object Frame (to move all the rendered environment)
GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;
GLfloat rotZ = 0.0f;

//variables to move the camera
GLfloat camY = 0.0f;
GLfloat camX = 0.0f;
GLfloat camZ = 0.0f;

// For animating the rotation of the objects
GLfloat animateRotation = 0.0f;
GLfloat animrotation2 = 0.0f;

//An array to store the normal vector data for the faces
GLfloat vNormal[3] = {};
//write text
char message[6][80];
int numberOfQuotes = 5, i;

GLfloat ssize = 5.0;
GLfloat y_1 = 15.0;

GLfloat ystep = 10.0f;

GLfloat windowW = 10;
GLfloat windowH = 10;


//load lighting
void initLighting() {

	//Decalring the Ambient, Diffuse components of the LIght_0 and the position in the eye coordinate system
	GLfloat L0_Ambient[] = { 0.8, 0.8, 0.0 ,1.0 };
	GLfloat L0_postion[] = { 0, 140, 0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, L0_postion);

	GLfloat L0_SpotDirection[] = { 0.0, -110.0, 0 };


	GLfloat L1_Ambient[] = { 0.5, 0.5, 0.5 ,1.0 };
	GLfloat L1_Diffuse[] = { 0, 0, 0.7, 1.0 };
	GLfloat L1_postion[] = { 0, 140, 0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, L1_Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, L1_postion);


	/*//Declaration of the ligt reflecting properties for the materials
	GLfloat specularReflectance[] = { 5.0, 5.0, 5.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflectance);*/
	

	GLfloat L2_Ambient[] = { 0.5, 0.5, 0.5 ,1.0 };
	GLfloat L2_Specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat L2_postion[] = { 0, 50, 0, 1.0 };
	GLfloat L2_SpotDirection[] = { 0.0, -1.0, 0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, L2_Ambient);
	glLightfv(GL_LIGHT2, GL_SPECULAR, L2_Specular);
	glLightfv(GL_LIGHT2, GL_POSITION, L2_postion);

	//Creating a spotlight from light_2 by declaring the direction vetor and area that the spotligt can shine(fov of the spotlight)
	//glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, L2_SpotDirection);
	//glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, -40.0);

	GLfloat L3_Ambient[] = { 0.5, 0.5, 0.5,1.0 };
	GLfloat L3_Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat L3_postion[] = { 500, 500, 0, 1.0 };

	glLightfv(GL_LIGHT3, GL_AMBIENT, L3_Ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, L3_Diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, L3_postion);




}

// Load external textures.
void initTextures()
{
	// Local storage for bmp image data.
	BitMapFile *image[5];

	// Load the images.
	image[0] = getbmp("C:/Users/Nishi/source/repos/finalproject/finalproject/images/floor2.bmp");
	image[1] = getbmp("C:/Users/Nishi/source/repos/finalproject/finalproject/images/grass3.bmp");
	image[2] = getbmp("C:/Users/Nishi/source/repos/finalproject/finalproject/images/door.bmp");
	image[3] = getbmp("C:/Users/Nishi/source/repos/finalproject/finalproject/images/sky.bmp");
	image[4] = getbmp("C:/Users/Nishi/source/repos/finalproject/finalproject/images/wall3.bmp");



	// Bind grass image to texture object texture[0]. 
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Bind sky image to texture object texture[1]
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->sizeX, image[1]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[2]->sizeX, image[2]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[2]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[3]->sizeX, image[3]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[3]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[4]->sizeX, image[4]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[4]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



}
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GLfloat globalAmbient[] = { 0.1, 0.1, 0.1, 1.0 };
	glEnable(GL_DEPTH_TEST);

	

	//Enable the adding of lights
	glEnable(GL_LIGHTING);

	
	glShadeModel(GL_SMOOTH);

	// Changing the global Ambient illumination without any lights present
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	initLighting();

	// Enabling the color tracking of each faces of the materials. this enables the color visibility of the materials
	glEnable(GL_COLOR_MATERIAL);

	// enable the normalization of the normal vectors (converting the vector values to the range 0-1)
	glEnable(GL_NORMALIZE);

	//texture
	glGenTextures(5, texture);
	initTextures();
	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//Cull back faces.
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);


}

//Calculate the normals for two vectors va, vb ( normal for a plane/face )
GLfloat* calNormal(GLfloat* va, GLfloat* vb) {
	vNormal[0] = va[1] * vb[2] - va[2] * vb[1];
	vNormal[1] = va[0] * vb[2] - va[2] * vb[0];
	vNormal[2] = va[0] * vb[1] - va[1] * vb[0];

	return vNormal;
}

GLfloat* findNormal(GLfloat* a, GLfloat* b, GLfloat* c) {

	GLfloat va[] = { b[0] - a[0], b[1] - a[1], b[2] - a[2] };
	GLfloat vb[] = { c[0] - a[0], c[1] - a[1], c[2] - a[2] };

	return calNormal(va, vb);
}


void door()
{

	glPushMatrix();
	glColor3f(0.4, 0, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-200, 150, -50);
	glVertex3f(-200, 150, 50);
	glVertex3f(-200, -50, 50);
	glVertex3f(-200, -50, -50);
	glEnd();
	glPopMatrix();
}
void dooropen(GLfloat angle)
{

	glPushMatrix();
	glTranslatef(0, 0, -350);
	glRotatef(angle, 1, 0, 0);
	door();
	glPopMatrix();
}

void story()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-200, 150, 350);
	glTexCoord2f(8.0, 0.0); glVertex3f(-200, -50, 350);
	glTexCoord2f(8.0, 1.0); glVertex3f(200, -50, 350);
	glTexCoord2f(0.0, 1.0); glVertex3f(200, 150, 350);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(200, 150, -350);
	glTexCoord2f(8.0, 0.0); glVertex3f(200, -50, -350);
	glTexCoord2f(8.0, 1.0); glVertex3f(-200, -50, -350);
	glTexCoord2f(0.0, 1.0); glVertex3f(-200, 150, -350);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(200, -50, -350);
	glTexCoord2f(8.0, 0.0); glVertex3f(200, 150, -350);
	glTexCoord2f(8.0, 1.0); glVertex3f(200, 150, 350);
	glTexCoord2f(0.0, 1.0); glVertex3f(200, -50, 350);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-200, -50, 350);
	glTexCoord2f(8.0, 0.0); glVertex3f(-200, -50, 50);
	glTexCoord2f(8.0, 1.0); glVertex3f(-200, 150, 50);
	glTexCoord2f(0.0, 1.0); glVertex3f(-200, 150, 350);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-200, 150, -50);
	glTexCoord2f(8.0, 0.0); glVertex3f(-200, 150, -350);
	glTexCoord2f(8.0, 1.0); glVertex3f(-200, -50, -350);
	glTexCoord2f(0.0, 1.0); glVertex3f(-200, -50, -50);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	door();
}

void sky()
{

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(800, -50, -800);
	glTexCoord2f(8.0, 0.0); glVertex3f(800, 250, -800);
	glTexCoord2f(8.0, 1.0); glVertex3f(-800, 250, 800);
	glTexCoord2f(0.0, 1.0); glVertex3f(-800, -50, 800);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//drawfullcube(200,-200,150,-50,350,-350);
void drawfullcube(GLfloat x, GLfloat a, GLfloat y, GLfloat b, GLfloat z, GLfloat c) {
	//right
	glBegin(GL_QUADS);
	//glColor3f(0.2, 0.2, 0.2);
	glVertex3f(a, y, z);
	glVertex3f(a, y, c);
	glVertex3f(a, b, c);
	glVertex3f(a, b, z);
	glEnd();

	// right
	glBegin(GL_QUADS);
	//glColor3f(0, 0, 1);
	glVertex3f(x, b, c);
	glVertex3f(x, y, c);
	glVertex3f(x, y, z);
	glVertex3f(x, b, z);
	glEnd();

	// front
	glBegin(GL_QUADS);
	//glColor3f(0.0, 0.5, 0.0);
	glVertex3f(x, y, c);
	glVertex3f(x, b, c);
	glVertex3f(a, b, c);
	glVertex3f(a, y, c);
	glEnd();

	// back
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(a, y, z);
	glVertex3f(a, b, z);
	glVertex3f(x, b, z);
	glVertex3f(x, y, z);
	glEnd();

	//bottom
	glBegin(GL_QUADS);
	//glColor3f(0.4, 0.0, 0.4);
	glVertex3f(a, b, z);
	glVertex3f(a, b, c);
	glVertex3f(x, b, c);
	glVertex3f(x, b, z);
	glEnd();

	//top
	glBegin(GL_QUADS);
	//glColor3f(0.6, 0.0, 0.0);
	glVertex3f(x, y, c);
	glVertex3f(a, y, c);
	glVertex3f(a, y, z);
	glVertex3f(x, y, z);
	glEnd();



}

void outergrass()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-200, -50, 350);
	glTexCoord2f(8.0, 0.0); glVertex3f(-200, -50, -350);
	glTexCoord2f(8.0, 1.0); glVertex3f(200, -50, -350);
	glTexCoord2f(0.0, 1.0); glVertex3f(200, -50, 350);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}
void fullground()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(800, -50.1, 800);
	glTexCoord2f(1.0, 0.0); glVertex3f(800, -50.1, -800);
	glTexCoord2f(1.0, 1.0); glVertex3f(-800, -50.1, -800);
	glTexCoord2f(0.0, 1.0); glVertex3f(-800, -50.1, 800);
	glEnd();

	glDisable(GL_TEXTURE_2D);


}


void roof()
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(250, 150.1, -400);
	glTexCoord2f(8.0, 0.0); glVertex3f(-250, 150.1, -400);
	glTexCoord2f(8.0, 1.0); glVertex3f(-250, 150.1, 400);
	glTexCoord2f(0.0, 1.0); glVertex3f(250, 150.1, 400);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}



void window(GLfloat x, GLfloat y, GLfloat z)
{

	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(50, -50, -50);
	glVertex3f(50, 50, -50);
	glVertex3f(50, 50, 50);
	glVertex3f(50, -50, 50);
	glEnd();
	glPopMatrix();
}
void windowline(GLfloat a, GLfloat b)
{
	GLfloat i = 0.0f;
	for (i = a; i <= b; i += 75)
	{
		glPushMatrix();
		glTranslatef(i, y, z);
		glColor3f(1, 0, 0);
		glBegin(GL_QUADS);
		//glColor3f(0.2, 0.2, 0.2);
		glVertex3f(-25, 100, -25);
		glVertex3f(-25, -25, -25);
		glVertex3f(25, -25, -25);
		glVertex3f(25, 100, -25);
		glEnd();
		glPopMatrix();
	}
}
void windowset()
{
	glPushMatrix();
	glTranslatef(0, 0, 375.1);
	windowline(-150, -25);
	windowline(25, 150);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -375.1);
	windowline(-150, -25);
	windowline(25, 150);
	glPopMatrix();
}


void table()
{
	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix();
	glNormal3f(0.0, 1.0, 0.0);
	drawfullcube(40, -40, -15, -20, 30, -30);
	glPushMatrix();
	glTranslatef(15, 0, 10);
	drawfullcube(3, -3, -20.1, -50, 3, -3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-15, 0, 10);
	drawfullcube(3, -3, -20.1, -50, 3, -3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-15, 0, -10);
	drawfullcube(3, -3, -20.1, -50, 3, -3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(15, 0, -10);
	drawfullcube(3, -3, -20.1, -50, 3, -3);
	glPopMatrix();
	glPopMatrix();
}
void bulb()
{
	glPushMatrix();
	glColor3f(0.5, 0, 0.5);
	drawfullcube(1, -1, 150.1, 120, 1, -1);
	glTranslatef(0, 110, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(10, 20, 20);
	glPopMatrix();
}

void treasure()
{
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glColor3f(0, 0.5, 0.3);
	glRotatef(-animateRotation, 0.0, 0.0, 1.0);
	glutSolidCube(20);
	glPopMatrix();
}

void tree(GLfloat x_3, GLfloat x_2, GLfloat y_2, GLfloat z_2)
{
	glPushMatrix();
	glColor3f(0.9, 0.4, 0);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, x_3, -50);
	glTranslatef(x_2, y_2, z_2);
	glutSolidCylinder(30, 150, 20, 20);
	glPushMatrix();
	glColor3f(0, 0.5, 0);
	glTranslatef(0, 0, 150);
	glutSolidCone(50, 150, 20, 20);
	glPopMatrix();
	glPopMatrix();
}
void treeline(GLfloat x_3, GLfloat t)
{
	GLfloat i = 0.0f;
	for (i = -t; i <= t; i += 200)
	{
		tree(x_3, i, 0, 0);
	}
}
void printonscreen()
{
	glPushMatrix();
	glRotatef(-90, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 15.1, 0.0);
	glColor3f(1, 0, 0);
	for (int l = 0, lenghOfQuote = 0; l < numberOfQuotes; l++)
	{
		lenghOfQuote = (int)strlen(message[l]);
		glPushMatrix();
		glScalef(1 / 22.38, 1 / 22.38, 1 / 22.38);
		for (i = 0; i < lenghOfQuote; i++)
		{

			glutStrokeCharacter(GLUT_STROKE_ROMAN, message[l][i]);
		}

		glPopMatrix();
		glTranslatef(10, 0, 150);
	}


	glPopMatrix();
}
void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	glPushMatrix();
	gluLookAt(-600.0 + camX, 2.0 + camY, 5.0 + camZ, 0, 0, 0, 0, 1.0, 0);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// move the object frame using keyboard keys
	glTranslatef(moveX, moveY, moveZ);
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);// camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)




	outergrass();
	fullground();
	story();
	glPushMatrix();
	roof();
	glPopMatrix();
	windowset();
	//sky();
	table();
	glPushMatrix();
	glTranslatef(0,-100,0);
		bulb();
	glPopMatrix();
	treasure();

	printonscreen();
	treeline(550, 650);
	treeline(-550, 650);
	glPopMatrix();
	//glPopMatrix();



	glutSwapBuffers();

}




void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		moveX -= 2;

	if (key == GLUT_KEY_DOWN)
		moveX += 2;

	if (key == GLUT_KEY_LEFT)
		rotY -= 5.0;

	if (key == GLUT_KEY_RIGHT)
		rotY += 5.0;

	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
	if (key == 'w')
		camY += 0.5;
	if (key == 's')
		camY -= 0.5;

	if (key == 'c')
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (key == 'C')
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (key == 'J')
		glEnable(GL_LIGHT0);
	if (key == 'j')
		glDisable(GL_LIGHT0);
	if (key == 'K')
		glEnable(GL_LIGHT1);
	if (key == 'k')
		glDisable(GL_LIGHT1);
	if (key == 'M')
		glEnable(GL_LIGHT3);
	if (key == 'm')
		glDisable(GL_LIGHT3);
	if (key == 't')
		glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	if (key == 's')
	{
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}
	if (key == 'z')
		glDisable(GLUT_FULL_SCREEN);
	



	glutPostRedisplay();

}


void Timer(int x) {
	animateRotation += animateRotation >= 360.0 ? -animateRotation : 5;
	glutPostRedisplay();



	glutPostRedisplay();

	glutTimerFunc(60, Timer, 1);
}

void changeSize(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	
	gluPerspective(120.0, aspect_ratio, 1.0, 900.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}

int main(int argc, char** argv) {

	
	strcpy_s(message[0], "PRESS t TO COLLECT TREASURE");
	strcpy_s(message[2], "PRESS s TO SWITCH ON LIGHTS");
	
	glutInit(&argc, argv);
	glutCreateWindow("OpenGL Final Project-S/14/551");
	glutInitWindowSize(GLUT_SCREEN_HEIGHT, GLUT_SCREEN_WIDTH);
	
	//glutInitWindowPosition(0, 0);

	
	//glutInitWindowPosition(100,100);
	init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	// keyboard function activation
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);

	glutTimerFunc(60.0, Timer, 1);
	glutMainLoop();

	
	return 0;

	
}


