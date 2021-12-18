#include <math.h>
#include <vector>
#include <string>
#include <GL/glut.h>
#include "imageloader.h"
#include "glm.h"

#define PI 3.14
#define Y_ELEVEATION_RATIO 0.3f

typedef std::vector<std::vector<int>> matrix;
typedef std::vector<std::vector<std::vector<int>>> vec3D;



static int animationSelector = 0;

double eye[] = {0, 0, 3};
double center[] = {0, 0, 2};
double up[] = {0, 1, 0};
static int shoulder = 0, elbow = 0, body = 0;
static int shoulder_x = 0;
static int leftLegZ = 0, leftLegX = 0, leftKneeZ = 0, leftKneeX = 0, LeftFoot = 0;
static int shoulder_2 = 0, elbow_2 = 0;
static int shoulder_x2 = 0;
static int rightLegZ = 0, rightLegX = 0, rightKneeZ = 0, rightKneeX = 0, RightFoot = 0;

static int rotationAngel = 0;
static float jump = 0;

GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */
GLfloat mat_amb_diff[] = { 0.643, 0.753, 0.934, 1.0 };
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess[] = { 100.0 };


//int animation_1[9][17] = {
//    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//    {45,0,0,0,0,0,0,00,0,-45,0,-45,0,45,0,0},
//    {},
//    {},
//    {},
//    {},
//    {},
//    {},
//    {}
//};



matrix animation_1 = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {45, 0, 0, 0, 0, 0, 0, 0, 0, -45, 0, 0, -45, 0, 45, 0, 0, 0, 0},
    {90, 0, 0, 0, 0, 0, 0, 0, 0, -90, 0, 0, -90, 0, 90, 0 ,0, 0, 0},
    {45, 0, 0, 0, 0, 0, 0, 0, 0, -45, 0, 0, -45, 0, 45, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {45, 0, 0, 0, -45, 0, 45, 0, 0, -45, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {90, 0, 0, 0, -90, 0, 90, 0, 0, -90, 0, 0, 0, 0, 0, 0 ,0, 0, 0},
    {45, 0, 0, 0, -45, 0, 45, 0, 0, -45, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

matrix animation_2 = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0},
    {47, 0, 33, 0, 0, 8, 0, 0, 0, -47, 0, -33, 0, -8, 0, 0, 0, 1, 0},
    {94, 0, 66, 0, 0, 17, 0, 0, 0, -94, 0, -66, 0, -17, 0, 0, 0, 2, 0},
    {140, 0, 100, 0, 0, 25, 0, 0, 0, -140, 0, -100, 0, -25, 0, 0, 0, 3, 0},
    {94, 0, 66, 0, 0, 17, 0, 0, 0, -94, 0, -66, 0, -17, 0, 0, 0, 2, 0},
    {47, 0, 33, 0, 0, 8, 0, 0, 0, -47, 0, -33, 0, -8, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0}
};

matrix animation_3 = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -90},
    {0, -55, -15, 0, 0, 0, 0, 0, 0, 0, -55, 15, 0, 0, 0, 0, 0, 1, -90},
    {0, -85, -15, 0, 0, 0, 0, 0, 0, 0, -85, 15, 0, 0, 0, 0 ,0, 2, -90},
    {0, -55, -15, 0, 0, 0, 0, 0, 0, 0, -55, 15, 0, 0, 0, 0, 0 ,1, -90},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -90}
};

vec3D animation = {
    animation_1,
    animation_2,
    animation_3
};







//const char* modelname = "data/lamp.obj";

const char* stool = "data/stool.obj";
const char* lamp = "data/deskLamp1.obj";
const char* table = "data/tavolo.obj";
std::string path = "images/test.bmp";


// RGBA
GLfloat light_ambient[] = {0.0, 0.0, 0.0, 0.0};
GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
// x , y, z, w
GLfloat light_position[] = {0.5, 5.0, 0.0, 1.0};
GLfloat lightPos1[] = {-0.5, -5.0, -2.0, 1.0};

// Draw Model Function:
void drawmodel(char* filename)
{
	GLMmodel* model = glmReadOBJ(filename);
	glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, 90.0);
	glmScale(model, .15);
	glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image *image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);			 //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,				  //Always GL_TEXTURE_2D
				 0,							  //0 for now
				 GL_RGB,					  //Format OpenGL uses for image
				 image->width, image->height, //Width and height
				 0,							  //The border of the image
				 GL_RGB,					  //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE,			  //GL_UNSIGNED_BYTE, because pixels are stored
											  //as unsigned numbers
				 image->pixels);			  //The actual pixel data
	return textureId;						  //Returns the id of the texture
}

GLuint _textureId; //The id of the texture

//Initializes 3D rendering
void initRendering()
{
	Image *image = loadBMP(path.c_str());
	_textureId = loadTexture(image);
	delete image;
	// Turn on the power
	glEnable(GL_LIGHTING);          
	// Flip light switch
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	// assign light parameters
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	// Material Properties
	GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
	glEnable(GL_NORMALIZE);
	//Enable smooth shading
	glShadeModel(GL_SMOOTH);
	// Enable Depth buffer
	glEnable(GL_DEPTH_TEST);
}

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta) * p[0];
	temp[1] += cos(theta) * p[1];
	temp[2] += cos(theta) * p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}
void turnLeft()
{
	double theta = -PI/100;
    rotatePoint(up, theta, eye);
}

void turnRight()
{
	double theta = PI/100;
    rotatePoint(up, theta, eye);
}

void moveUp()
{
	double horizontal [3];
    double look [] = {center[0] -eye[0], center[1] -eye[1], center[2] -eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, PI/100, eye);
    rotatePoint(horizontal, PI/100, up);
}


void moveDown()
{

	double horizontal [3];
    double look [] = {center[0] -eye[0], center[1] -eye[1], center[2] -eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -PI/100, eye);
    rotatePoint(horizontal, -PI/100, up);
}

void moveForward()
{

	double speed = 0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}

void moveBack()
{

	double speed = -0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}

void reset()
{
	double e[] = { 0, 0, 3 };
	double c[] = { 0, 0, 2 };
	double u[] = { 0, 1, 0 };
    
	for (int i = 0; i < 3; i++)
	{
		eye[i] = e[i];
		center[i] = c[i];
		up[i] = u[i];
	}
}

void display(void)
{

	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Clear Depth and Color buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2, -1,  2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 2, -1,  2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 2, -1, -2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2, -1, -2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -0.7, 0.0);
	glScalef(20, 20, 20);
	drawmodel((char*)stool);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.0, -0.7, 0.0);
	glRotatef(90, 0, 1.0, 0);
	glScalef(30, 30, 30);
	drawmodel((char*)table);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.0, 0.1, 0.0);
    if (animationSelector == 2)
        glTranslatef(0.0, Y_ELEVEATION_RATIO * jump, 0.0);
	glScalef(3, 3, 3);
	drawmodel((char*)lamp);
	glPopMatrix();


	// FUll Robot:
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);

    if (animationSelector == 1)
        glTranslatef(0.0, Y_ELEVEATION_RATIO * jump, 0.0);
    else if (animationSelector == 2)
        glTranslatef(-2, 0.0, 0.0);

    glRotatef((GLfloat)rotationAngel, 0, 1.0, 0);
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    // The Chest(body) of robot:
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef((GLfloat)body, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.5, 4.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    //  The Head of Robot:
    glPushMatrix();
    glTranslatef(0.0, 2.5, 0.0);
    glutSolidSphere(0.42, 10, 10);
    glPopMatrix();
    glPopMatrix();

    //  The Right Arm of Robot:
    // The Shoulder:
    glPushMatrix();
    glTranslatef(-0.9, 1.85, 0.0);
    glRotatef((GLfloat)shoulder_x2, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder_2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.55, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    // The Elbow:
    glTranslatef(-0.15, -0.625, 0.0);
    glRotatef((GLfloat)elbow_2, 0.0, 0.0, 1.0);
    glTranslatef(0.15, -0.625, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    //The Fingers:
    //The first finger:
    glPushMatrix();
    glTranslatef(-0.1, -0.35, -0.1);
    //glRotatef((GLfloat)fingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp1, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    // the second finger:
    glPushMatrix();
    glTranslatef(-0.1, -0.35, 0.0);
    //glRotatef((GLfloat)fingerBase2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    // the third finger:
    glPushMatrix();
    glTranslatef(-0.1, -0.35, 0.1);
    //glRotatef((GLfloat)fingerBase3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    // the fourth finger:
    glPushMatrix();
    glTranslatef(0.1, -0.35, 0.0);
    //glRotatef((GLfloat)fingerBase4, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp4, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();


    //  The Left Arm of Robot:
    //  The Shoulder
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(0.9, 1.85, 0.0);
    glRotatef((GLfloat)shoulder_x, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.55, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    //  The Elbow:
    glTranslatef(0.15, -0.625, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(-0.15, -0.625, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    // The fingers:
    //  The first finger:
    glPushMatrix();
    glTranslatef(0.1, -0.35, -0.1);
    //glRotatef((GLfloat)fingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp1, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    //  The second finger:
    glPushMatrix();
    glTranslatef(0.1, -0.35, 0.0);
    //glRotatef((GLfloat)fingerBase2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    //  The third finger:
    glPushMatrix();
    glTranslatef(0.1, -0.35, 0.1);
    //glRotatef((GLfloat)fingerBase3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    //  The fourth finger:
    glPushMatrix();
    glTranslatef(-0.1, -0.35, 0.0);
    //glRotatef((GLfloat)fingerBase4, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp4, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();


    //   The Right Leg of Robot:
    // The leg
    glPushMatrix();
    glTranslatef(-0.55, -2.0, 0.0);
    glRotatef((GLfloat)rightLegZ, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rightLegX, 1.0, 0.0, 0.0);
    glTranslatef(0.05, -0.9, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    // The Knee:
    glTranslatef(0.0, -0.8, 0.0);
    glRotatef((GLfloat)rightKneeZ, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rightKneeX, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.9, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    // The foot:
    glTranslatef(0.0, -1.0, 0.0);
    glRotatef((GLfloat)RightFoot, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.55, 0.5, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();


    //  The Left Leg of Robot:
    // The leg:
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(0.55, -2.0, 0.0);
    glRotatef((GLfloat)leftLegZ, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)leftLegX, 1.0, 0.0, 0.0);
    glTranslatef(-0.05, -0.9, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    // The Knee:
    glTranslatef(0.0, -0.8, 0.0);
    glRotatef((GLfloat)leftKneeZ, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)leftKneeX, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.9, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    // The Foot:
    glTranslatef(0.0, -1.0, 0.0);
    glRotatef((GLfloat)LeftFoot, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.55, 0.5, 1.0);
    glutSolidCube(1.0);

    glPopMatrix();
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		turnLeft();
		break;
	case GLUT_KEY_RIGHT:
		turnRight();
		break;
	case GLUT_KEY_UP:
		if (center[1] <= 1.5)
			moveUp();
		break;
	case GLUT_KEY_DOWN:
		if (center[1] >= -1.5)
			moveDown();
		break;
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'f':
		moveForward();
		break;
	case 'b':
		moveBack();
		break;
	case 'r':
		reset();
		break;

	case 27:
		exit(0);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void setAngles(int frameIndex) {
    shoulder = animation[animationSelector][frameIndex][0];
    shoulder_x = animation[animationSelector][frameIndex][1];
    elbow = animation[animationSelector][frameIndex][2];
    body = animation[animationSelector][frameIndex][3];
    leftLegX = animation[animationSelector][frameIndex][4];
    leftLegZ = animation[animationSelector][frameIndex][5];
    leftKneeX = animation[animationSelector][frameIndex][6];
    leftKneeZ = animation[animationSelector][frameIndex][7];
    LeftFoot = animation[animationSelector][frameIndex][8];
    shoulder_2 = animation[animationSelector][frameIndex][9];
    shoulder_x2 = animation[animationSelector][frameIndex][10];
    elbow_2 = animation[animationSelector][frameIndex][11];
    rightLegX = animation[animationSelector][frameIndex][12];
    rightLegZ = animation[animationSelector][frameIndex][13];
    rightKneeX = animation[animationSelector][frameIndex][14];
    rightKneeZ = animation[animationSelector][frameIndex][15];
    RightFoot = animation[animationSelector][frameIndex][16];
    jump = animation[animationSelector][frameIndex][17];
    rotationAngel = animation[animationSelector][frameIndex][18];
}

static int frame = 0;

void timer(int value) {
    frame = frame % animation[animationSelector].size();
    setAngles(frame);
    frame++;
    glutPostRedisplay();
    glutTimerFunc(150, timer, 0);
}

void screen_menu(int value)
{
    switch (value) {
        case 0:
        case 1:
        case 2:
            animationSelector = value;
            break;
        case 3:
            path = "images/test.bmp";
            initRendering();
            break;
        case 4:
            path = "images/test1.bmp";
            initRendering();
            break;
        default:
            break;
    }
    frame = 0;
    reset();
    glutPostRedisplay();
}

void attachMenu()
{
	glutCreateMenu(screen_menu);
	glutAddMenuEntry("exercise", 0);
	glutAddMenuEntry("jump", 1);
	glutAddMenuEntry("hold lamp up", 2);

	glutAddMenuEntry("", -1);

	glutAddMenuEntry("natural wallpaper as floor", 3);
	glutAddMenuEntry("kung fu panda", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(750, 750);
    glutInitWindowPosition(300, 70);
    glutCreateWindow("TEXTURE MAPPING & Object Loading");
    
	initRendering();
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, 1.0, 0.1, 10);
	attachMenu();
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}
