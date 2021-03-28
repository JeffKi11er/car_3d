#include <stdio.h>
#include <stdlib.h>
#include <GL\glut.h>
#include <math.h>
#include <string.h>



#define ESCAPE 27

GLint window;
GLint window2;
GLint Xsize = 1800;
GLint Ysize = 1000;
float i, theta;
GLint nml = 0, day = 1;

char name3[] = "PROJECT:  3D CAR  ANIMATION";
char name1[] = "USNIVERSITY OF SCIENCE AND TECHNOLOGY OF HANOI";
char name2[] = "HELP";
char name4[] = "MOUSE";
char name5[] = "PRESS RIGHT BUTTON FOR MENU";
char name6[] = "KEYBOARD";
char name7[] = "X-Y-Z KEYS FOR CORRESPONDING ROTATION";
char name8[] = "A-S-Q CAR CUSTOM SIZE SELECTION";
char name9[] = "U-F FOR CAMERA VIEW SETTINGS";
char name10[] = "USE LEFT ARROW(<-) AND RIGHT ARROW(->) TO MOVE CAR";
char name11[] = "ESCAPE TO EXIT";
char name12[] = "PRESS SPACE BAR TO ENTER";

GLfloat xt = 0.0, yt = 0.0, zt = 0.0, xw = 0.0;
GLfloat tx = 295, ty = 62;
GLfloat xs = 1.0, ys = 1.0, zs = 1.0;

GLfloat xangle = 0.0, yangle = 0.0, zangle = 0.0, angle = 0.0;

GLfloat r = 0, g = 0, b = 1;
GLint light = 1;
int count = 1, flg = 1;
int view = 0;
int flag1 = 0, aflag = 1;
int flag2 = 0, wheelflag = 0;
GLUquadricObj* t;

//a
float pos_x, pos_y, pos_z;


int x_old = 0, y_old = 0;
int current_scroll = 5;
float zoom_per_scroll;

bool is_holding_mouse = false;
bool is_updated = false;

static void SpecialKeyFunc(int Key, int x, int y);

/* Simple  transformation routine */
GLvoid Transform(GLfloat Width, GLfloat Height)
{
	glViewport(0, 0, Width, Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, Width / Height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}



GLvoid InitGL(GLfloat Width, GLfloat Height)
{

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLineWidth(2.0);
	Transform(Width, Height);
	t = gluNewQuadric();
	gluQuadricDrawStyle(t, GLU_FILL);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);


	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

}


void init()
{
	glClearColor(0, 0, 0, 0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 900.0, 0.0, 600.0, 50.0, -50.0);
	glutPostRedisplay();
}




void display_string(int x, int y, char* string, int font)
{
	int len, i;
	glColor3f(0.8, 0.52, 1.0);
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		if (font == 1)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		if (font == 2)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
		if (font == 3)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
		if (font == 4)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
	}

}

void display1(void)
{

	glClearColor(1.0, 1.0, 0.1, 1.0);
	display_string(180, 540, name1, 1);
	display_string(215, 500, name3, 1);
	display_string(390, 470, name2, 2);
	display_string(10, 450, name4, 2);
	display_string(10, 410, name5, 3);
	display_string(10, 370, name6, 2);
	display_string(10, 340, name7, 3);
	display_string(10, 310, name8, 3);
	display_string(10, 280, name9, 3);
	display_string(10, 250, name10, 3);
	display_string(10, 220, name11, 3);
	display_string(250, 150, name12, 2);
	glutPostRedisplay();
	glutSwapBuffers();

}

void mouse(int button, int state, int x, int y) {
    is_updated = true;

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            x_old = x;
            y_old = y;
            is_holding_mouse = true;
        } else
            is_holding_mouse = false;
    } else if (state == GLUT_UP) {
        switch (button) {
        case 3:
            if (current_scroll > 0) {
                current_scroll--;
                pos_z += zoom_per_scroll;
            }
            break;
        case 4:
            if (current_scroll < 15) {
                current_scroll++;
                pos_z -= zoom_per_scroll;
            }
            break;
        }
    }
}

void motion(int x, int y) {
    if (is_holding_mouse) {
        is_updated = true;

        yangle += (x - x_old);
        x_old = x;
        if (yangle > 360.0f)
            yangle -= 360.0f;
        else if (yangle < 0.0f)
            yangle += 360.0f;

        xangle += (y - y_old);
        y_old = y;
        if (xangle > 90.0f)
            xangle = 90.0f;
        else if (xangle < -90.0f)
            xangle = -90.0f;
    }
}


GLvoid DrawGLScene()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (view == 0)
	{
		init();
		display1();
	}
	else
	{
		if (count == 1)
			InitGL(Xsize, Ysize);
		if (aflag == 1)
			glClearColor(1, 1, 1, 1);
		else
			glClearColor(0.1, 0.1, 0.1, 0);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-1.0, 0.0, -3.5);
		glRotatef(xangle, 1.0, 0.0, 0.0);
		glRotatef(yangle, 0.0, 1.0, 0.0);
		glRotatef(zangle, 0.0, 0.0, 1.0);
		glTranslatef(xt, yt, zt);
		glScalef(xs, ys, zs);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		if (flag2 == 1)
		{
			GLfloat fogcolour[4] = { 1.0,1.0,1.0,1.0 };

			glFogfv(GL_FOG_COLOR, fogcolour);
			glFogf(GL_FOG_DENSITY, 0.1);
			glFogi(GL_FOG_MODE, GL_EXP);
			glFogf(GL_FOG_START, 3.0);
			glFogf(GL_FOG_END, 100.0);
			glHint(GL_FOG_HINT, GL_FASTEST);
			glEnable(GL_FOG);/* ENABLE */
		}
		if (flag2 == 0)
		{
			glDisable(GL_FOG);
		}

		if (!aflag) {
			glBegin(GL_POINTS);
			glColor3f(1, 1, 1);
			glPointSize(200.0);
			int ccount = 0;
			float x = 10, y = 10;
			while (ccount < 20)
			{
				glVertex2f(x, y);
				x += 10;
				y += 10;
				if (y > Ysize) y -= 10;
				if (x > Xsize) x -= 10;
				ccount++;
			}
			glEnd();
		}

		glColor3f(1.0, .75, 0.0);
		glPointSize(30.0);
		glBegin(GL_POINTS);
		glVertex3f(0.3, 0.3, 0.3);
		glVertex3f(0.3, 0.3, 0.5);
		glEnd();
		glPointSize(200.0);

		glColor3f(1.0, .75, 0.0);
		glPointSize(50.0);
		glBegin(GL_POINTS);
		glVertex3f(1.9, 0.3, 0.3);
		glVertex3f(1.9, 0.3, 0.5);
		glEnd();
		glPointSize(200.0);


		glBegin(GL_QUADS);

		/* top of cube*/
		//************************FRONT BODY****************************************
		glColor3f(0.8118, 0.0, 0.0);
		/*Phan mui xe*/
		glVertex3f(0.3f, 0.4f, 0.6f);
		glVertex3f(0.6f, 0.5f, 0.6f);
		glVertex3f(0.6f, 0.5f, 0.2f);
		glVertex3f(0.3f, 0.4f, 0.2f);

		/* bottom of cube*/
		glColor3f(0.2f, 0.5f, 0.3f);
		glVertex3f(0.3f, 0.2f, 0.6f);
		glVertex3f(0.6f, 0.2f, 0.6f);
		glVertex3f(0.6f, 0.2f, 0.2f);
		glVertex3f(0.3f, 0.2f, 0.2f);

		/* front of cube*/
		glColor3f(0.7098, 0.5137, 0.7608);
		glVertex3f(0.3, 0.2, 0.6);
		glVertex3f(0.3, 0.4, 0.6);
		glVertex3f(0.3, 0.4, 0.2);
		glVertex3f(0.3, 0.2, 0.2);

		/* back of cube.*/
		glColor3f(0.7961, 0.8078, 0.2314);
		glVertex3f(0.6, 0.2, 0.6);
		glVertex3f(0.6, 0.5, 0.6);
		glVertex3f(0.6, 0.5, 0.2);
		glVertex3f(0.6, 0.2, 0.2);

		/* left of cube*/
		glColor3f(0.2314, 0.5961, 0.8078);
		glVertex3f(0.3f, 0.2f, 0.6f);
		glVertex3f(0.6f, 0.2f, 0.6f);
		glVertex3f(0.6f, 0.5f, 0.6f);
		glVertex3f(0.3f, 0.4f, 0.6f);

		/* Right of cube */
		glColor3f(0.8078, 0.2314, 0.3255);
		glVertex3f(0.3f, 0.2f, 0.2f);
		glVertex3f(0.6f, 0.2f, 0.2f);
		glVertex3f(0.6f, 0.5f, 0.2f);
		glVertex3f(0.3f, 0.4f, 0.2f);
		//****************************************************************************
		/*Phan mui tran xe*/
		glColor3f(r, g, b);
		glVertex3f(0.7, 0.65, 0.6);
		glVertex3f(0.7, 0.65, 0.2);
		glVertex3f(1.7, 0.65, 0.2);        //top cover
		glVertex3f(1.7, 0.65, 0.6);
		//***************************back guard******************************
		
		/*Phan duoi xe*/
		glColor3f(0.8118, 0.0, 0.0);           /* Set The Color To Blue*/
		glVertex3f(1.8, 0.5, 0.6);
		glVertex3f(1.8, 0.5, 0.2);
		glVertex3f(1.9, 0.4, 0.2);
		glVertex3f(1.9, 0.4, 0.6);

		/* bottom of cube*/
		glColor3f(0.2, 0.5, 0.3);
		glVertex3f(1.9, 0.2, 0.6);
		glVertex3f(1.9, 0.2, 0.2);
		glVertex3f(1.8, 0.2, 0.2);
		glVertex3f(1.8, 0.2, 0.6);

		/* back of cube.*/
		glColor3f(0.8078, 0.2314, 0.3255);
		glVertex3f(1.9, 0.4, 0.6);
		glVertex3f(1.9, 0.4, 0.2);
		glVertex3f(1.9, 0.2, 0.2);
		glVertex3f(1.9, 0.2, 0.6);

		/* left of cube*/
		glColor3f(0.7961, 0.8078, 0.2314);
		glVertex3f(1.8, 0.2, 0.2);
		glVertex3f(1.8, 0.5, 0.2);
		glVertex3f(1.9, 0.4, 0.2);
		glVertex3f(1.9, 0.2, 0.2);

		/* Right of cube */
		glColor3f(0.7098, 0.5137, 0.7608);
		glVertex3f(1.8, 0.2, 0.6);
		glVertex3f(1.8, 0.5, 0.6);
		glVertex3f(1.9, 0.4, 0.6);
		glVertex3f(1.9, 0.2, 0.6);
		//******************MIDDLE BODY************************************
		/*Than xe*/
		glColor3f(r, g, b);
		glVertex3f(0.6, 0.5, 0.6);
		glVertex3f(0.6, 0.2, 0.6);
		glVertex3f(1.8, 0.2, 0.6);
		glVertex3f(1.8, 0.5, 0.6);

		/* bottom of cube*/
		glVertex3f(0.6, 0.2, 0.6);
		glVertex3f(0.6, 0.2, 0.2);
		glVertex3f(1.8, 0.2, 0.2);
		glVertex3f(1.8, 0.2, 0.6);

		/* back of cube.*/
		glVertex3f(0.6, 0.5, 0.2);
		glVertex3f(0.6, 0.2, 0.2);
		glVertex3f(1.8, 0.2, 0.2);
		glVertex3f(1.8, 0.5, 0.2);
		//*********************ENTER WINDOW**********************************
		
		/*Cua so 2 ben*/
		glColor3f(0.3, 0.3, 0.3);
		glVertex3f(0.75, 0.63, 0.2);
		glVertex3f(0.75, 0.5, 0.2);        //quad front window
		glVertex3f(1.2, 0.5, 0.2);
		glVertex3f(1.22, 0.63, 0.2);

		glVertex3f(1.27, 0.63, .2);
		glVertex3f(1.25, 0.5, 0.2);        //quad back window
		glVertex3f(1.65, 0.5, 0.2);
		glVertex3f(1.67, 0.63, 0.2);

		glColor3f(r, g, b);
		glVertex3f(0.7, 0.65, 0.2);
		glVertex3f(0.7, 0.5, .2);       //first separation
		glVertex3f(0.75, 0.5, 0.2);
		glVertex3f(0.77, 0.65, 0.2);

		glVertex3f(1.2, 0.65, 0.2);
		glVertex3f(1.2, 0.5, .2);       //second separation
		glVertex3f(1.25, 0.5, 0.2);
		glVertex3f(1.27, 0.65, 0.2);

		glVertex3f(1.65, 0.65, 0.2);
		glVertex3f(1.65, 0.5, .2);     //3d separation
		glVertex3f(1.7, 0.5, 0.2);
		glVertex3f(1.7, 0.65, 0.2);

		glVertex3f(0.75, 0.65, 0.2);
		glVertex3f(0.75, 0.63, 0.2);        //line strip
		glVertex3f(1.7, 0.63, 0.2);
		glVertex3f(1.7, 0.65, 0.2);

		glVertex3f(0.75, 0.65, 0.6);
		glVertex3f(0.75, 0.63, 0.6);        //line strip
		glVertex3f(1.7, 0.63, 0.6);
		glVertex3f(1.7, 0.65, 0.6);

		glColor3f(0.3, 0.3, 0.3);
		glVertex3f(0.77, 0.63, 0.6);
		glVertex3f(0.75, 0.5, 0.6);        //quad front window
		glVertex3f(1.2, 0.5, 0.6);
		glVertex3f(1.22, 0.63, 0.6);

		glVertex3f(1.27, 0.63, .6);
		glVertex3f(1.25, 0.5, 0.6);        //quad back window
		glVertex3f(1.65, 0.5, 0.6);
		glVertex3f(1.67, 0.63, 0.6);

		glColor3f(r, g, b);
		glVertex3f(0.7, 0.65, 0.6);
		glVertex3f(0.7, 0.5, .6);       //first separation
		glVertex3f(0.75, 0.5, 0.6);
		glVertex3f(0.77, 0.65, 0.6);

		glVertex3f(1.2, 0.65, 0.6);
		glVertex3f(1.2, 0.5, .6);       //second separation
		glVertex3f(1.25, 0.5, 0.6);
		glVertex3f(1.27, 0.65, 0.6);

		glVertex3f(1.65, 0.65, 0.6);
		glVertex3f(1.65, 0.5, .6);
		glVertex3f(1.7, 0.5, 0.6);
		glVertex3f(1.7, 0.65, 0.6);
		glEnd();


		//**************************************************************
		glBegin(GL_QUADS);
		/*Cua so phia truoc sau*/
		/* top of cube*/
		glColor3f(0.3, 0.3, 0.3);
		glVertex3f(0.6, 0.5, 0.6);
		glVertex3f(0.6, 0.5, 0.2);        //quad front window
		glVertex3f(0.7, 0.65, 0.2);
		glVertex3f(0.7, 0.65, 0.6);

		glVertex3f(1.7, 0.65, .6);
		glVertex3f(1.7, 0.65, 0.2);        //quad back window
		glVertex3f(1.8, 0.5, 0.2);
		glVertex3f(1.8, 0.5, 0.6);


		//*****************************road and surrounding development***********************************
		if (flag1)
		{
			glPushMatrix();
			glTranslatef(xw, 0, 0);
			glColor3f(0, 1, 0);
			glVertex3f(-100, 0.1, -100);
			glVertex3f(-100, 0.1, 0);         //a green surroundings
			glVertex3f(100, 0.1, 0);
			glVertex3f(100, 0.1, -100);

			glColor3f(0.7, 0.7, 0.7);
			glVertex3f(-100, 0.1, 0);
			glVertex3f(-100, 0.1, 0.45);         //a long road
			glVertex3f(100, 0.1, 0.45);
			glVertex3f(100, 0.1, 0);

			glColor3f(1.0, 0.75, 0.0);
			glVertex3f(-100, 0.1, 0.45);       //a median
			glVertex3f(-100, 0.1, 0.55);
			glVertex3f(100, 0.1, 0.55);
			glVertex3f(100, 0.1, 0.45);

			glColor3f(0.7, 0.7, 0.7);
			glVertex3f(-100, 0.1, 0.55);
			glVertex3f(-100, 0.1, 1);         //a long road
			glVertex3f(100, 0.1, 1);
			glVertex3f(100, 0.1, 0.55);

			glColor3f(0, 1, 0);
			glVertex3f(-100, 0.1, 1);
			glVertex3f(-100, 0.1, 100);         //a green surroundings
			glVertex3f(100, 0.1, 100);
			glVertex3f(100, 0.1, 1);
			glPopMatrix();
		}
		glEnd();

		if (wheelflag)
		{
			glPushMatrix();
			glTranslatef(xw, 0, 0);
			glColor3f(0.5, .2, 0.3);
			glBegin(GL_QUADS);
			for (i = 0; i < 200; i += 0.2)
			{
				glVertex3f(-100 + i, 0, 1);
				glVertex3f(-99.9 + i, 0, 1);
				glVertex3f(-99.9 + i, 0.2, 1);
				glVertex3f(-100 + i, 0.2, 1);
				i += 0.5;
			}
			for (i = 0; i < 200; i += 0.2)
			{
				glVertex3f(-100 + i, 0, 0);
				glVertex3f(-99.9 + i, 0, 0);
				glVertex3f(-99.9 + i, 0.2, 0);
				glVertex3f(-100 + i, 0.2, 0);
				i += 0.5;
			}
			glEnd();
			glPopMatrix();
		}
		//*************************************************************************************************
		glBegin(GL_TRIANGLES);                /* start drawing the cube.*/
		/*Canh cua so truoc va sau xe*/
		  /* top of cube*/
		glColor3f(0.3, 0.3, 0.3);
		glVertex3f(0.6, 0.5, 0.6);
		glVertex3f(0.7, 0.65, 0.6);       // tri front window
		glVertex3f(0.7, 0.5, 0.6);

		glVertex3f(0.6, 0.5, 0.2);
		glVertex3f(0.7, 0.65, 0.2);       // tri front window
		glVertex3f(0.7, 0.5, 0.2);

		glVertex3f(1.7, 0.65, 0.2);
		glVertex3f(1.8, 0.5, 0.2);       // tri back window
		glVertex3f(1.7, 0.5, 0.2);

		glVertex3f(1.7, 0.65, 0.6);
		glVertex3f(1.8, 0.5, 0.6);       // tri back window
		glVertex3f(1.7, 0.5, 0.6);

		glEnd();
		//************IGNITION SYSTEM**********************************
		/*Bo xe*/
		glPushMatrix();
		glColor3f(0.8118, 0.0, 0.0);
		glTranslatef(1.41, 0.2, 0.3);
		glRotatef(90.0, 0, 1, 0);
		gluCylinder(t, 0.02, 0.03, .5, 10, 10);
		glPopMatrix();
		//********************WHEEL*********************************************
		/*Banh xe*/
		glColor3f(0.7, 0.7, 0.7);
		glPushMatrix();
		glBegin(GL_LINE_STRIP);
		for (theta = 0; theta < 360; theta = theta + 20)
		{
			glVertex3f(0.7, 0.2, 0.62);
			glVertex3f(0.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		for (theta = 0; theta < 360; theta = theta + 20)
		{
			glVertex3f(0.7, 0.2, 0.18);
			glVertex3f(0.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		for (theta = 0; theta < 360; theta = theta + 20)
		{
			glVertex3f(1.65, 0.2, 0.18);
			glVertex3f(1.65 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		for (theta = 0; theta < 360; theta = theta + 20)
		{
			glVertex3f(1.65, 0.2, 0.62);
			glVertex3f(1.65 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
		}
		glEnd();
		/*Banh xe*/
		glTranslatef(0.7, 0.2, 0.6);
		glColor3f(0.7098, 0.5137, 0.7608);
		glutSolidTorus(0.035, 0.09, 10, 25);

		glTranslatef(0, 0, -0.4);
		glutSolidTorus(0.035, 0.09, 10, 25);

		glTranslatef(0.95, 0, 0);
		glutSolidTorus(0.035, 0.09, 10, 25);

		glTranslatef(0, 0, 0.4);
		glutSolidTorus(0.035, 0.09, 10, 25);
		glPopMatrix();

		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
		glutPostRedisplay();
		glutSwapBuffers();
	}
}



void NormalKey(GLubyte key, GLint x, GLint y)
{
	switch (key) {
	case ESCAPE: printf("escape pressed. exit.\n");
		glutDestroyWindow(window);
		exit(0);
		break;

	case ' ':view = 1;
		DrawGLScene();
		break;

	case 'x': xangle += 5.0;
		glutPostRedisplay();
		break;

	case 'X':xangle -= 5.0;
		glutPostRedisplay();
		break;

	case 'y':
		yangle += 5.0;
		glutPostRedisplay();
		break;

	case 'Y':
		yangle -= 5.0;
		glutPostRedisplay();
		break;

	case 'z':
		zangle += 5.0;
		glutPostRedisplay();
		break;

	case 'Z':
		zangle -= 5.0;
		glutPostRedisplay();
		break;

	case 'u':
		yt += 0.2;
		glutPostRedisplay();
		break;

	case 'U':
		yt -= 0.2;
		glutPostRedisplay();
		break;

	case 'f':
		zt += 0.2;
		glutPostRedisplay();
		break;

	case 'F':
		zt -= 0.2;
		glutPostRedisplay();
		break;

	case 's':zs += .2;
		glutPostRedisplay();
		break;

	case 'S':zs -= 0.2;
		glutPostRedisplay();
		break;

	case 'a':ys += .2;
		glutPostRedisplay();
		break;

	case 'A':ys -= 0.2;
		glutPostRedisplay();
		break;

	case 'q':xs += .2;
		glutPostRedisplay();
		break;

	case 'Q':xs -= 0.2;
		glutPostRedisplay();
		break;


	default:
		break;
	}

}

static void SpecialKeyFunc(int Key, int x, int y)
{
	switch (Key) {
	case GLUT_KEY_RIGHT:
		if (!wheelflag)
			xt += 0.2;
		if (wheelflag)
		{
			angle += 5;
			xw += 0.2;
		}
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		if (!wheelflag)
			xt -= 0.2;
		if (wheelflag)
		{
			angle += 5;
			xw -= 0.2;
		}
		glutPostRedisplay();
		break;
	}
}

void myMenu(int id)
{
	if (id == 1)
	{
		flag1 = 0;
		wheelflag = 0;
		glutPostRedisplay();

	}
	if (id == 2)
	{
		flag1 = 1;
		flag2 = 0;
		wheelflag = 0;
		xangle += 5.0;
		glutPostRedisplay();
	}
	if (id == 3)
	{
		flag2 = 1;
		wheelflag = 0;
		xangle += 5.0;
		glutPostRedisplay();
	}
	if (id == 4)
	{
		wheelflag = 1;
		glutPostRedisplay();
	}
	if (id == 5)
	{
		if (day)
		{

			if (light)
			{
				count++;
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				light = 0;
			}
			else
			{
				count--;
				light = 1;
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
			}
			glutPostRedisplay();
		}
		else
		{

			if (nml == 0 && flag2 == 2)
			{
				flag2 = 0;
				nml = 1;
			}
			else
			{
				flag2 = 2;
				nml = 0;

				aflag = 0;
				day = 0;

				glClearColor(0.1, 0.1, 0.1, 0);
				GLfloat fogcolour[4] = { 0.0,0.0,0.0,1.0 };

				glFogfv(GL_FOG_COLOR, fogcolour);
				glFogf(GL_FOG_DENSITY, 0.5);
				glFogi(GL_FOG_MODE, GL_EXP);
				/* end */
				glHint(GL_FOG_HINT, GL_FASTEST);
				glEnable(GL_FOG);


				glutPostRedisplay();
			}
		}

	}


	if (id == 12)
	{
		aflag = 1;
		day = 1;
		glClearColor(1, 1, 1, 1);
		glDisable(GL_FOG);
		glutPostRedisplay();
	}

	if (id == 13)
	{
		aflag = 0;
		day = 0;
		flag2 = 2;
		glClearColor(0.1, 0.1, 0.1, 0);
		GLfloat fogcolour[4] = { 0.0,0.0,0.0,1.0 };

		glFogfv(GL_FOG_COLOR, fogcolour);
		glFogf(GL_FOG_DENSITY, 0.5);
		glFogi(GL_FOG_MODE, GL_EXP);

		glHint(GL_FOG_HINT, GL_FASTEST);
		glEnable(GL_FOG);

		glutPostRedisplay();
	}
}

void colorMenu(int id)
{
	if (id == 6)
	{
		r = g = 0;
		b = 1;
		glutPostRedisplay();

	}
	if (id == 7)
	{
		r = 0.8;
		b = g = 0;
		glutPostRedisplay();
	}
	if (id == 8)
	{
		g = 1;
		r = b = 0;
		glutPostRedisplay();
	}
	if (id == 9)
	{
		r = b = g = 0;
		glutPostRedisplay();
	}
	if (id == 10)
	{
		b = 0;
		r = g = 1;
		glutPostRedisplay();
	}
	if (id == 11)
	{
		b = r = g = .7;
		glutPostRedisplay();
	}

}

void myreshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(Xsize, Ysize);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("3D CAR ANIMATION");



	glutReshapeFunc(myreshape);
	glutDisplayFunc(DrawGLScene);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(NormalKey);
	glutSpecialFunc(SpecialKeyFunc);
	InitGL(Xsize, Ysize);
	int submenu = glutCreateMenu(colorMenu);
	glutAddMenuEntry("blue", 6);
	glutAddMenuEntry("red", 7);
	glutAddMenuEntry("green", 8);
	glutAddMenuEntry("black", 9);
	glutAddMenuEntry("yellow", 10);
	glutAddMenuEntry("grey", 11);
	glutCreateMenu(myMenu);
	glutAddMenuEntry("car model mode", 1);
	glutAddMenuEntry("car driving mode", 2);
	glutAddMenuEntry("fog effect", 3);
	glutAddMenuEntry("wheel effect", 4);
	glutAddMenuEntry("toggle light", 5);
	glutAddSubMenu("car colors", submenu);
	glutAddMenuEntry("daymode", 12);
	glutAddMenuEntry("Night mode", 13);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 1;
}