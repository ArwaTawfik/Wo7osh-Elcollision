#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>

int WIDTH = 1280;
int HEIGHT = 720;

GLuint tex;
GLuint bushtex;
GLuint spiketex;

char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 200;
int playerX = -18;
int playerY = 1;
int playerZ = 17;
int playerR = 270;
int step = 1;

bool moveright = true;
bool moveleft = true;
bool moveup = true;
bool movedown = true;
class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};



//Note on camera:
//--Eye is where the camera itself is
//--AT is the point where the camera is looking at

// so to move it forward i translate the eye and at at the same time

Vector Eye(0, 30,15 );
Vector At(0, 0,0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_annie;
//--Bassel
Model_3DS model_grassWall;
Model_3DS model_brickWall;
//--Arwa
Model_3DS model_bear;
Model_3DS model_apple;
//salma
Model_3DS model_coin;

//---
// Textures
GLTexture tex_ground;
GLTexture tex_brickground;
GLTexture tex_grasswall;
GLTexture tex_bush;


//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}
void moveUp() {
	if (playerZ>-59) {
		playerR = 0;
		playerZ -= step;
	}
	else {
		//collision
	}
}
void moveDown() {
	if (playerZ < 19) {
		playerR = 180;
		playerZ += step;
	}
	else {
		//collision
	}
}
void moveLeft() {
	if (playerX > -19) {
		playerR = 90;
		playerX -= step;
	}
	else {
		//collision
	}
}
void moveRight() {
	if (playerX < 19) {
		playerR = 270;
		playerX += step;
	}
	else {
		//collision
	}
}

void spe(int k, int x0, int y0) // keyboard special key function takes 3 parameters								// int k: is the special key pressed such as the keyboard arrows the f1,2,3 and so on
{
	if (k == GLUT_KEY_RIGHT && moveright) { //if the right arrow is pressed, then the object will be translated in the x axis by 10. (moving right)
		moveRight();
	}
	if (k == GLUT_KEY_LEFT && moveleft)
	{ //if the left arrow is pressed, then the object will be translated in the x axis by -10. (moving left)
		moveLeft();
	}
	if (k == GLUT_KEY_UP && moveup) { //if the up arrow is pressed, then the object will be translated in the y axis by 10. (moving upwords)
		moveUp();
	}
	if (k == GLUT_KEY_DOWN && movedown) { //if the down arrow is pressed, then the object will be translated in the y axis by -10. (moving downwords)
		moveDown();
	}
	glutPostRedisplay(); //redisplay to update the screen with the changes
}
//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	//render level1 Ground
	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();
	

	//----render Level2 Ground
	glBindTexture(GL_TEXTURE_2D, tex_brickground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, -60);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, -60);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

//=======================================================================
// Display Function
//=======================================================================

void skyBox() {
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);
	glPopMatrix();

}

void bushes() {
	glPushMatrix();
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(9, 1, 3);
	//glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, bushtex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 2, 100, 100);
	gluDeleteQuadric(qobj);
	glPopMatrix();

	glPushMatrix();
	//GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(-12, 1, -10);
	//glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, bushtex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 2, 100, 100);
	gluDeleteQuadric(qobj);
	glPopMatrix();

}


void spike() {
	glPushMatrix();
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glRotated(-90, 1, 0, 0);
	glTranslatef(0,-3.0f,0);
	glBindTexture(GL_TEXTURE_2D, spiketex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	// glu.gluCylinder(quadric, bottomRadius, topRadius, height, slices, rings)
	gluCylinder(qobj, 0.3, 0, 2, 50, 50);
	gluDeleteQuadric(qobj);
	glPopMatrix();
}
void spikes() {


	glPushMatrix();
	glTranslated(5, 1, 3);
	spike();
	glPopMatrix();

	glPushMatrix();
	glTranslated(5, 1, 4);
	spike();
	glPopMatrix();
	glPushMatrix();
	glTranslated(5, 1, 5);
	spike();
	glPopMatrix();
	glPushMatrix();
	glTranslated(5, 1, 6);
	spike();
	glPopMatrix();

}

void brickWall(int g,int z) {
	//draw brickwall
	glPushMatrix();
	glTranslatef(g, 3, -25+z);
	glScalef(0.4, 0.5, 1);
	model_brickWall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(g, 3, -24.7+z);
	glScalef(0.4, 0.5, 1);
	model_brickWall.Draw();
	glPopMatrix();

}

void grassWall(int g, int z) {
	//draw brickwall
	glPushMatrix();
	glTranslatef(g, 3, -15 + z);
	glScalef(0.4, 0.5, 1);
	model_grassWall.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(g, 3, -15.7 + z);
	glScalef(0.4, 0.5, 1);
	model_grassWall.Draw();
	glPopMatrix();

}

void brickBorders() {
	int g = -20;
	for (int i = 0;i < 8;i++) {
		glPushMatrix();
		glTranslatef(-20, 3, g);
		glRotatef(90, 0, 1, 0);
		glScalef(0.4, 0.5, 1);
		model_brickWall.Draw();
		glPopMatrix();
		g = g - 5;
	}
	g = -20;
	for (int i = 0;i < 8;i++) {
		glPushMatrix();
		glTranslatef(20, 3, g);
		glRotatef(90, 0, 1, 0);
		glScalef(0.4, 0.5, 1);
		model_brickWall.Draw();
		glPopMatrix();
		g = g - 5;
	}
}

void grassBorders() {
	int g = 20;
	for (int i = 0;i < 8;i++) {
		glPushMatrix();
		glTranslatef(-20, 3, g);
		glRotatef(90, 0, 1, 0);
		glScalef(0.4, 0.5, 1);
		model_grassWall.Draw();
		glPopMatrix();
		g = g - 5;
	}
	g = 20;
	for (int i = 0;i < 8;i++) {
		glPushMatrix();
		glTranslatef(20, 3, g);
		glRotatef(90, 0, 1, 0);
		glScalef(0.4, 0.5, 1);
		model_grassWall.Draw();
		glPopMatrix();
		g = g - 5;
	}
}

void coin(int x, int z) {

	glPushMatrix();
	glTranslated(x, 1, z);
	glScaled(0.3, 0.3, 0.3);
	model_coin.Draw();
	glPopMatrix();
	
}
void drawCoins() {
	//level1 coins
	coin(3,4);
	coin(-8,17);
	coin(4,-11);
	//level2 coins
	coin(3, -36);
	coin(15, -57);
	coin(4, -43);
	
}

void drawBrickWalls(int noWall,int z) {
	//noWall is where I dont want a wall to block path

	int g = -20;
	for (int i = 0;i < 8;i++) {
		if (i != noWall) {
			brickWall(g, z);
		}	
		g = g + 5;
	}


}



void drawGrassWalls(int noWall, int z) {
	//noWall is where I dont want a wall to block path

	int g = -20;
	for (int i = 0;i < 8;i++) {
		if (i != noWall) {
			grassWall(g, z);
		}
		g = g + 5;
	}


}

void drawSpikes() {

	glPushMatrix();
	glTranslatef(10,-1,-58);
	spikes();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-11, -1, -37);
	spikes();
	glPopMatrix();
}

void drawLevel1Walls() {

	drawGrassWalls(-1, 35);

	drawGrassWalls(6,30);

	drawGrassWalls(1, 23);

	drawGrassWalls(4, 16);

	drawGrassWalls(6, 9);

	drawGrassWalls(3, 2);

	drawGrassWalls(1, -4.5);

	grassBorders();

}

void drawLevel2Walls() {

	//you can pick where the missing wall is
	//by changeing fhte first parameter
	//from 0 => 7
	drawBrickWalls(4,0);

	drawBrickWalls(6,-7);

	drawBrickWalls(1,-14);

	drawBrickWalls(5, -21);

	drawBrickWalls(2, -28);

	drawBrickWalls(-1, -35);

	
	brickBorders();

}



void renderLevel1() {

	drawLevel1Walls();

	bushes();

}

void renderLevel2() {

	drawLevel2Walls();
	drawSpikes();
	
}
void drawPlayer() {
	   glPushMatrix();
	   glTranslated(playerX,playerY,playerZ);
		glScalef(0.1, 0.1, 0.1);
		glRotatef(playerR, 0,1, 0);
		model_bear.Draw();
		glPopMatrix();
}
void drawGoal() {
	glPushMatrix();
	glTranslated(0,5,0);
	glScalef(1, 1, 1);
	model_apple.Draw();
	glPopMatrix();
}



void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	RenderGround();

	drawPlayer();
	drawGoal();
	renderLevel1();

	renderLevel2();
	drawCoins();
	// Draw Tree Model
	/*glPushMatrix();
	glTranslatef(10, 0, 0);
	glScalef(0.7, 0.7, 0.7);
	model_tree.Draw();
	glPopMatrix();*/

	// Draw house Model
	/*glPushMatrix();
	glRotatef(90.f, 1, 0, 0);
	model_house.Draw();
	glPopMatrix();*/


	//sky box
	skyBox();


	glutSwapBuffers();
}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	
	switch (button)
	{
	case'a':
			Eye.x -= 0.2;
			At.x -= 0.2;
			break;
	case'd':
		Eye.x += 0.2;
		At.x += 0.2;
		break;
		
	case'w':
		Eye.z -= 0.2;
		At.z -= 0.2;
		break;
	case's':
		Eye.z += 0.2;
		At.z += 0.2;
		break;


	case GLUT_KEY_F1:
		exit(0);
		break;
	default:
		break;
	}

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x,Eye.y,Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw s

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.z += -0.1;
		At.z += -0.1;
	}
	else
	{
		Eye.z += 0.1;
		At.z +=0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================

void LoadAssets()
{
	// Loading Model files

	//model_house.Load("Models/house/house.3DS");

	//model_tree.Load("Models/tree/Tree1.3ds");

	model_brickWall.Load("models/brickWall/wall.3DS");

	model_grassWall.Load("models/grassWall/wall.3DS");
	model_bear.Load("models/ted-bear/ted.3ds");
	model_coin.Load("models/coin/Coin.3ds");

	tex_brickground.Load("Textures/brickFloor.bmp");
	tex_ground.Load("Textures/grass.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
	loadBMP(&bushtex, "Textures/bush.bmp", true);
	loadBMP(&spiketex, "Textures/spikes.bmp", true);
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(0, 0);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(spe);

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}