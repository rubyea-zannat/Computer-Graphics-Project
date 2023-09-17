#include <iostream>
#include<GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
# define PI 3.14159265358979323846
#include<cstring>

using namespace std;


bool temp = 0;
int triangleAmount = 1000;
GLfloat twicePi = 2.0f * PI;
GLfloat position = 0.0f;
GLfloat speed = 0.01f;
float move_wave =0.0f;
bool Bus_Stop = false;

bool handup= false;
bool night = false;
bool winter = false;
bool rain = false;
float rain1 = 0.0;

float spin_x = 0;
float spin_y = 0;
float spin_z = 0;

static GLfloat spin =0.0;
static GLfloat spin_speed = 0.2;

int i = 0;


void clearColor(float r, float g, float b,float bb)
{
    glClearColor(r,g,b,bb);
}

void setSpin(float x, float y, float z)
{
    spin_x = x;
    spin_y = y;
    spin_z = z;
}

void spinDisplay(void)
{
    spin=spin+spin_speed;
    if(spin>360.0)
    {
        spin=spin-360.0;
    }
    glutPostRedisplay();
}


void spinDisplayReverse(void)
{
    spin=spin-spin_speed;
    if(spin<360.0)
    {
        spin=spin+360.0;
    }
    glutPostRedisplay();
}


//(All points are set anti-clockwise) //
void Background()
{
    glBegin(GL_QUADS);
    glColor3ub(97, 150, 61); // Summer
    if(night)
    {
        glColor3ub(69, 85, 54); // Night
    }
    else if(winter)
    {
        glColor3ub(142, 134, 126); // Winter
    }

    glVertex2f(-1.0f, 0.5f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 0.5f);

    glEnd();
}

void Sky()
{
    glBegin(GL_QUADS);
    glColor3ub(173, 216, 230); // Light Blue
    if(night)
    {
        glColor3ub(11, 37, 58); // Dark Blue
    }
    else if(winter)
    {
        glColor3ub(214, 228, 229); // Light Grey
    }

    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-1.0f, 0.5f);
    glVertex2f(1.0f, 0.5f);
    glVertex2f(1.0f, 1.0f);
    glEnd();
}

//Sun's Update Function
GLfloat positionSun = 0.02f;
GLfloat speedSun = 0.003f;

void updateSun(int value)
{
    if(positionSun < -1.0)
        positionSun = 1.0f;

    positionSun -= speedSun;

    glutPostRedisplay();
    glutTimerFunc(300, updateSun, 0);
}

void Sun()
{
    //Sun
    glPushMatrix();
    glTranslatef(-1.6f, positionSun, 0.0f);
    if(night || winter)
    {
        glTranslatef(-2.0f, positionSun, 0.0f);
    }

    int i;

    GLfloat pSun = 0.85f;
    GLfloat qSun = 0.85f;
    GLfloat rSun = 0.07f;
    int triangleSun = 40;
    GLfloat tpSun = twicePi;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 0); // Yellow

    glVertex2f(pSun, qSun);
    for(i= 0; i<=triangleSun; i++)
    {
        glVertex2f (
            pSun+(rSun*cos(i*tpSun/triangleSun)),
            qSun+(rSun*sin(i*tpSun/triangleSun))
        );
    }
    glEnd ();
    glPopMatrix();
}

//Clouds's Update Function
GLfloat positionCloud = 0.0f;
GLfloat speedCloud = 0.01f;

void updateCloud(int value)
{
    if(positionCloud < -1.0)
        positionCloud = 1.0f;

    positionCloud -= speedCloud;

    glutPostRedisplay();
    glutTimerFunc(100, updateCloud, 0);
}

void CloudShape()
{
    // Circle 1 (left)
    glPushMatrix();
    glTranslatef(-positionCloud, 0.0f, 0.0f);

    int i;

    GLfloat pCloud_1 = 0.19f;
    GLfloat qCloud_1 = 0.85f;
    GLfloat rCloud_1 = 0.08f;
    int triangleCloud_1 = 40;
    GLfloat tpCloud_1 = twicePi;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (255, 255, 255);
    glVertex2f (pCloud_1, qCloud_1);
    for(i=0; i<=triangleCloud_1; i++)
    {
        glVertex2f (
            pCloud_1+(rCloud_1*cos(i*tpCloud_1/triangleCloud_1)),
            qCloud_1+(rCloud_1*sin(i*tpCloud_1/triangleCloud_1))
        );
    }
    glEnd();


    // Circle 2 (center)
    GLfloat pCloud_2 = 0.28f;
    GLfloat qCloud_2 = 0.85f;
    GLfloat rCloud_2 = 0.1f;
    int triangleCloud_2 = 40;
    GLfloat tpCloud_2 = twicePi;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 255);
    glVertex2f (pCloud_2, qCloud_2);
    for(i=0; i<=triangleCloud_2; i++)
    {
        glVertex2f (
            pCloud_2+(rCloud_2*cos(i*tpCloud_2/triangleCloud_2)),
            qCloud_2+(rCloud_2*sin(i*tpCloud_2/triangleCloud_2))
        );
    }
    glEnd ();


    // Circle 3 (right)
    GLfloat pCloud_3 = 0.40f;
    GLfloat qCloud_3 = 0.85f;
    GLfloat rCloud_3 = 0.09f;
    int triangleCloud_3 = 40;
    GLfloat tpCloud_3 = twicePi;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 255);
    glVertex2f (pCloud_3, qCloud_3);
    for(i=0; i<=triangleCloud_3; i++)
    {
        glVertex2f (
            pCloud_3+(rCloud_3*cos(i*tpCloud_3/triangleCloud_3)),
            qCloud_1+(rCloud_3*sin(i*tpCloud_3/triangleCloud_3))
        );
    }
    glEnd ();
    glPopMatrix();
}


void Clouds()
{
    glPushMatrix();
    glTranslatef(-0.57f, 0.43f, 0.0f);
    if(night)
    {
        glTranslatef(3.0f, 0.0f, 0.0f);
    }
    glScalef(0.65f, 0.65f, 0.0f);
    CloudShape(); // no. 2
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    if(night)
    {
        glTranslatef(3.0f, 0.0f, 0.0f);
    }
    CloudShape(); // no. 3
    glPopMatrix();

    if(winter)
    {
        // Winter Clouds //
        glPushMatrix();
        glTranslatef(-0.97f, 0.23f, 0.0f);
        if(night)
        {
            glTranslatef(3.0f, 0.0f, 0.0f);
        }
        glScalef(0.75f, 0.75f, 0.0f);
        CloudShape(); // no. 1
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.7f, 0.5f, 0.0f);
        if(night)
        {
            glTranslatef(3.0f, 0.0f, 0.0f);
        }
        glScalef(0.55f, 0.55f, 0.0f);
        CloudShape(); // no. 4
        glPopMatrix();
    }
}


//Moon's Update Function
GLfloat positionMoon = 0.01f;
GLfloat speedMoon = 0.01f;

void updateMoon(int value)
{
    if(positionMoon < -1.0)
        positionMoon = 1.0f;

    positionMoon -= speedMoon;

    glutPostRedisplay();
    glutTimerFunc(300, updateMoon, 0);
}


void Moon()
{
    if(night)
    {
        //Moon
        glPushMatrix();
        glTranslatef(-1.7f, positionMoon, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, positionMoon, 0.0f);
        }

        int i;

        GLfloat pMoon = 0.85f;
        GLfloat qMoon = 0.85f;
        GLfloat rMoon = 0.058f;
        int triangleMoon = 40;
        GLfloat tpMoon = twicePi;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(255, 255, 255);

        glVertex2f(pMoon, qMoon);
        for(i= 0; i<=triangleMoon; i++)
        {
            glVertex2f (
                pMoon+(rMoon*cos(i*tpMoon/triangleMoon)),
                qMoon+(rMoon*sin(i*tpMoon/triangleMoon))
            );
        }
        glEnd ();
        glPopMatrix();
    }
}

void StarShape()
{
    glPushMatrix();
    glScalef(0.01f, 0.01f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);

    glVertex2f(0.0f, 0.75f);
    glVertex2f(0.5f, -0.75f);

    glVertex2f(0.5f, -0.75f);
    glVertex2f(-0.75f, 0.35f);

    glVertex2f(-0.75f, 0.35f);
    glVertex2f(0.75f, 0.35f);

    glVertex2f(0.75f, 0.35f);
    glVertex2f(-0.5f, -0.75f);

    glVertex2f(-0.5f, -0.75f);
    glVertex2f(0.0f, 0.75f);

    glEnd();
    glPopMatrix();
}

void Stars()
{
    if(night)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.85f, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, 0.0f, 0.0f);
        }
        StarShape(); // Star 1
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.25f, 0.87f, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, 0.0f, 0.0f);
        }
        StarShape(); // Star 2
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.31f, 0.84f, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, 0.0f, 0.0f);
        }
        StarShape(); // Star 3
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.35f, 0.78f, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, 0.0f, 0.0f);
        }
        StarShape(); // Star 4
        glPopMatrix();


        glPushMatrix();
        glTranslatef(-0.24f, 0.88f, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, 0.0f, 0.0f);
        }
        StarShape(); // Star 5
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.51f, 0.9f, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, 0.0f, 0.0f);
        }
        StarShape(); // Star 6
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.63f, 0.91f, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, 0.0f, 0.0f);
        }
        StarShape(); // Star 7
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.65f, 0.77f, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, 0.0f, 0.0f);
        }
        StarShape(); // Star 8
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.76f, 0.93f, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, 0.0f, 0.0f);
        }
        StarShape(); // Star 9
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.55f, 0.82f, 0.0f);
        if(!night && winter)
        {
            glTranslatef(-3.0f, 0.0f, 0.0f);
        }
        StarShape(); // Star 10
        glPopMatrix();
    }

}

void MountainHighlights()
{
    // Mountain_1(front)
    glBegin(GL_TRIANGLES);
    glColor3ub(116, 168, 42);
    if(night)
    {
        glColor3ub(36, 56, 54);
    }
    else if(winter) //[snow]
    {
        glColor3ub(255, 255, 255);
    }
    glVertex2f(-0.9f, 0.75f);
    glVertex2f(-0.95f, 0.66f);
    glVertex2f(-0.87f, 0.73f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(116, 168, 42);
    if(night)
    {
        glColor3ub(36, 56, 54);
    }
    else if(winter) //[snow]
    {
        glColor3ub(255, 255, 255);
    }

    glVertex2f(-0.8f, 0.64f);
    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.84f, 0.66f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(116, 168, 42);
    if(night)
    {
        glColor3ub(36, 56, 54);
    }
    else if(winter) //[snow]
    {
        glColor3ub(255, 255, 255);
    }

    glVertex2f(-0.69f, 0.64f);
    glVertex2f(-0.65f, 0.67f);
    glVertex2f(-0.58f, 0.58f);

    glEnd();


    // Mountain_4(back)
    glPushMatrix();
    glTranslatef(0.78f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3ub(116, 168, 42);
    if(night)
    {
        glColor3ub(36, 56, 54);
    }
    else if(winter) //[snow]
    {
        glColor3ub(255, 255, 255);
    }

    glVertex2f(-0.9f, 0.75f);
    glVertex2f(-0.95f, 0.66f);
    glVertex2f(-0.87f, 0.73f);

    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.78f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(116, 168, 42);
    if(night)
    {
        glColor3ub(36, 56, 54);
    }
    else if(winter) //[snow]
    {
        glColor3ub(255, 255, 255);
    }

    glVertex2f(-0.58f, 0.6f);
    glVertex2f(-0.55f, 0.6f);
    glVertex2f(-0.55f, 0.6f);
    glVertex2f(-0.5f, 0.5f);

    glEnd();
    glPopMatrix();


    // Mountain_7(back)
    glPushMatrix();
    glTranslatef(1.6f, -0.02f, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3ub(116, 168, 42);
    if(night)
    {
        glColor3ub(36, 56, 54);
    }
    else if(winter) //[snow]
    {
        glColor3ub(255, 255, 255);
    }

    glVertex2f(-0.8f, 0.64f);
    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.84f, 0.66f);

    glEnd();

    glEnd();
    glPopMatrix();


    // Mountain_3(front)
    glPushMatrix();
    glTranslatef(0.20f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(173, 255, 47);
    if(night)
    {
        glColor3ub(13, 32, 39);
    }
    else if(winter) //[snow]
    {
        glColor3ub(255, 255, 255);
    }
    glVertex2f(-0.65f, 0.5f);
    glVertex2f(-0.63f, 0.55f);
    glVertex2f(-0.55f, 0.65f);
    glVertex2f(-0.57f, 0.55f);

    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.20f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(173, 255, 47);
    if(night)
    {
        glColor3ub(13, 32, 39);
    }
    else if(winter) //[snow]
    {
        glColor3ub(255, 255, 255);
    }
    glVertex2f(-0.5f, 0.68f);
    glVertex2f(-0.47f, 0.66f);
    glVertex2f(-0.47f, 0.66f);
    glVertex2f(-0.44f, 0.73f);

    glEnd();
    glPopMatrix();


    // Mountain_6(front)

    glPushMatrix();
    glTranslatef(0.97f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(173, 255, 47);
    if(night)
    {
        glColor3ub(13, 32, 39);
    }
    else if(winter) //[snow]
    {
        glColor3ub(255, 255, 255);
    }

    glVertex2f(-0.65f, 0.5f);
    glVertex2f(-0.63f, 0.55f);
    glVertex2f(-0.55f, 0.65f);
    glVertex2f(-0.57f, 0.55f);

    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.97f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(173, 255, 47);
    if(night)
    {
        glColor3ub(13, 32, 39);
    }
    else if(winter) //[snow]
    {
        glColor3ub(255, 255, 255);
    }

    glVertex2f(-0.2f, 0.6f);
    glVertex2f(-0.18f, 0.58f);
    glVertex2f(-0.15f, 0.6f);

    glEnd();
    glPopMatrix();
}

void Mountains()
{
    // Mountain_2(back)
    glPushMatrix();
    glTranslatef(0.3f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(31, 56, 27);

    if(night)
    {
        glColor3ub(4, 28, 36);
    }
    else if(winter)
    {
        glColor3ub(66, 60, 58);
    }

    glVertex2f(-1.0f, 0.5f);
    glVertex2f(-1.0f, 0.65f);

    glVertex2f(-1.0f, 0.65f);
    glVertex2f(-0.97f, 0.68f);

    glVertex2f(-0.97f, 0.68f);
    glVertex2f(-0.95f, 0.66f);

    glVertex2f(-0.95f, 0.66f);
    glVertex2f(-0.9f, 0.77f);

    glVertex2f(-0.9f, 0.77f);
    glVertex2f(-0.87f, 0.73f);

    glVertex2f(-0.87f, 0.73f);
    glVertex2f(-0.84f, 0.66f);

    glVertex2f(-0.84f, 0.66f);
    glVertex2f(-0.8f, 0.7f);

    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.78f, 0.68f);

    glVertex2f(-0.78f, 0.68f);
    glVertex2f(-0.73f, 0.73f);

    glVertex2f(-0.73f, 0.73f);
    glVertex2f(-0.68f, 0.64f);

    glVertex2f(-0.68f, 0.64f);
    glVertex2f(-0.65f, 0.67f);

    glVertex2f(-0.65f, 0.67f);
    glVertex2f(-0.58f, 0.58f);

    glVertex2f(-0.58f, 0.58f);
    glVertex2f(-0.55f, 0.6f);

    glVertex2f(-0.55f, 0.6f);
    glVertex2f(-0.5f, 0.5f);

    glEnd();
    glPopMatrix();


    // Mountain_1(front)
    glBegin(GL_POLYGON);
    glColor3ub(65, 125, 25);

    if(night)
    {
        glColor3ub(52, 68, 36);
    }
    else if(winter)
    {
        glColor3ub(122, 112, 102);
    }

    glVertex2f(-1.0f, 0.5f);
    glVertex2f(-1.0f, 0.65f);

    glVertex2f(-1.0f, 0.65f);
    glVertex2f(-0.97f, 0.68f);

    glVertex2f(-0.97f, 0.68f);
    glVertex2f(-0.95f, 0.66f);

    glVertex2f(-0.95f, 0.66f);
    glVertex2f(-0.9f, 0.75f);

    glVertex2f(-0.9f, 0.75f);
    glVertex2f(-0.87f, 0.73f);

    glVertex2f(-0.87f, 0.73f);
    glVertex2f(-0.84f, 0.66f);

    glVertex2f(-0.84f, 0.66f);
    glVertex2f(-0.8f, 0.7f);

    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.78f, 0.68f);

    glVertex2f(-0.78f, 0.68f);
    glVertex2f(-0.73f, 0.73f);

    glVertex2f(-0.73f, 0.73f);
    glVertex2f(-0.68f, 0.64f);

    glVertex2f(-0.68f, 0.64f);
    glVertex2f(-0.65f, 0.67f);

    glVertex2f(-0.65f, 0.67f);
    glVertex2f(-0.58f, 0.58f);

    glVertex2f(-0.58f, 0.58f);
    glVertex2f(-0.55f, 0.6f);

    glVertex2f(-0.55f, 0.6f);
    glVertex2f(-0.5f, 0.5f);

    glEnd();
    glPopMatrix();


    // Mountain_5(back)
    glPushMatrix();
    glTranslatef(0.8f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(31, 56, 27);

    if(night)
    {
        glColor3ub(4, 28, 36);
    }
    else if(winter)
    {
        glColor3ub(66, 60, 58);
    }

    glVertex2f(-0.65f, 0.5f);
    glVertex2f(-0.63f, 0.55f);

    glVertex2f(-0.63f, 0.55f);
    glVertex2f(-0.61f, 0.53f);

    glVertex2f(-0.61f, 0.53f);
    glVertex2f(-0.55f, 0.65f);

    glVertex2f(-0.55f, 0.65f);
    glVertex2f(-0.52f, 0.63f);

    glVertex2f(-0.52f, 0.63f);
    glVertex2f(-0.5f, 0.68f);

    glVertex2f(-0.5f, 0.68f);
    glVertex2f(-0.47f, 0.66f);

    glVertex2f(-0.47f, 0.66f);
    glVertex2f(-0.44f, 0.73f);

    glVertex2f(-0.44f, 0.73f);
    glVertex2f(-0.4f, 0.7f);

    glVertex2f(-0.4f, 0.7f);
    glVertex2f(-0.35f, 0.62f);

    glVertex2f(-0.35f, 0.62f);
    glVertex2f(-0.3f, 0.66f);

    glVertex2f(-0.3f, 0.66f);
    glVertex2f(-0.28f, 0.63f);

    glVertex2f(-0.28f, 0.63f);
    glVertex2f(-0.24f, 0.69f);

    glVertex2f(-0.24f, 0.69f);
    glVertex2f(-0.18f, 0.58f);

    glVertex2f(-0.18f, 0.58f);
    glVertex2f(-0.15f, 0.6f);

    glVertex2f(-0.15f, 0.6f);
    glVertex2f(-0.11f, 0.55f);

    glVertex2f(-0.11f, 0.55f);
    glVertex2f(-0.1f, 0.5f);

    glEnd();
    glPopMatrix();


    // Mountain_4(front)
    glPushMatrix();
    glTranslatef(0.78f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(65, 125, 25);

    if(night)
    {
        glColor3ub(52, 68, 36);
    }
    else if(winter)
    {
        glColor3ub(122, 112, 102);
    }

    glVertex2f(-1.0f, 0.5f);
    glVertex2f(-1.0f, 0.65f);

    glVertex2f(-1.0f, 0.65f);
    glVertex2f(-0.97f, 0.68f);

    glVertex2f(-0.97f, 0.68f);
    glVertex2f(-0.95f, 0.66f);

    glVertex2f(-0.95f, 0.66f);
    glVertex2f(-0.9f, 0.75f);

    glVertex2f(-0.9f, 0.75f);
    glVertex2f(-0.87f, 0.73f);

    glVertex2f(-0.87f, 0.73f);
    glVertex2f(-0.84f, 0.66f);

    glVertex2f(-0.84f, 0.66f);
    glVertex2f(-0.8f, 0.7f);

    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.78f, 0.68f);

    glVertex2f(-0.78f, 0.68f);
    glVertex2f(-0.73f, 0.73f);

    glVertex2f(-0.73f, 0.73f);
    glVertex2f(-0.68f, 0.64f);

    glVertex2f(-0.68f, 0.64f);
    glVertex2f(-0.65f, 0.67f);

    glVertex2f(-0.65f, 0.67f);
    glVertex2f(-0.58f, 0.58f);

    glVertex2f(-0.58f, 0.58f);
    glVertex2f(-0.55f, 0.6f);

    glVertex2f(-0.55f, 0.6f);
    glVertex2f(-0.5f, 0.5f);

    glEnd();
    glPopMatrix();


    // Mountain_7(back)
    glPushMatrix();
    glTranslatef(1.3f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(65, 125, 25);

    if(night)
    {
        glColor3ub(52, 68, 36);
    }
    else if(winter)
    {
        glColor3ub(122, 112, 102);
    }

    glVertex2f(-0.65f, 0.5f);
    glVertex2f(-0.63f, 0.55f);

    glVertex2f(-0.63f, 0.55f);
    glVertex2f(-0.61f, 0.53f);

    glVertex2f(-0.61f, 0.53f);
    glVertex2f(-0.55f, 0.65f);

    glVertex2f(-0.55f, 0.65f);
    glVertex2f(-0.52f, 0.63f);

    glVertex2f(-0.52f, 0.63f);
    glVertex2f(-0.5f, 0.68f);

    glVertex2f(-0.5f, 0.68f);
    glVertex2f(-0.47f, 0.66f);

    glVertex2f(-0.47f, 0.66f);
    glVertex2f(-0.44f, 0.73f);

    glVertex2f(-0.44f, 0.73f);
    glVertex2f(-0.4f, 0.7f);

    glVertex2f(-0.4f, 0.7f);
    glVertex2f(-0.35f, 0.62f);

    glVertex2f(-0.35f, 0.62f);
    glVertex2f(-0.3f, 0.66f);

    glVertex2f(-0.3f, 0.66f);
    glVertex2f(-0.28f, 0.63f);

    glVertex2f(-0.28f, 0.63f);
    glVertex2f(-0.24f, 0.69f);

    glVertex2f(-0.24f, 0.69f);
    glVertex2f(-0.18f, 0.58f);

    glVertex2f(-0.18f, 0.58f);
    glVertex2f(-0.15f, 0.6f);

    glVertex2f(-0.15f, 0.6f);
    glVertex2f(-0.11f, 0.55f);

    glVertex2f(-0.11f, 0.55f);
    glVertex2f(-0.1f, 0.5f);

    glEnd();
    glPopMatrix();


    // Mountain_3(front)
    glPushMatrix();
    glTranslatef(0.20f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(116, 168, 42);

    if(night)
    {
        glColor3ub(36, 56, 54);
    }
    else if(winter)
    {
        glColor3ub(166, 138, 109);
    }

    glVertex2f(-0.65f, 0.5f);
    glVertex2f(-0.63f, 0.55f);

    glVertex2f(-0.63f, 0.55f);
    glVertex2f(-0.61f, 0.53f);

    glVertex2f(-0.61f, 0.53f);
    glVertex2f(-0.55f, 0.65f);

    glVertex2f(-0.55f, 0.65f);
    glVertex2f(-0.52f, 0.63f);

    glVertex2f(-0.52f, 0.63f);
    glVertex2f(-0.5f, 0.68f);

    glVertex2f(-0.5f, 0.68f);
    glVertex2f(-0.47f, 0.66f);

    glVertex2f(-0.47f, 0.66f);
    glVertex2f(-0.44f, 0.73f);

    glVertex2f(-0.44f, 0.73f);
    glVertex2f(-0.4f, 0.7f);

    glVertex2f(-0.4f, 0.7f);
    glVertex2f(-0.35f, 0.62f);

    glVertex2f(-0.35f, 0.62f);
    glVertex2f(-0.3f, 0.66f);

    glVertex2f(-0.3f, 0.66f);
    glVertex2f(-0.28f, 0.63f);

    glVertex2f(-0.28f, 0.63f);
    glVertex2f(-0.24f, 0.69f);

    glVertex2f(-0.24f, 0.69f);
    glVertex2f(-0.18f, 0.58f);

    glVertex2f(-0.18f, 0.58f);
    glVertex2f(-0.15f, 0.6f);

    glVertex2f(-0.15f, 0.6f);
    glVertex2f(-0.11f, 0.55f);

    glVertex2f(-0.11f, 0.55f);
    glVertex2f(-0.1f, 0.5f);

    glEnd();
    glPopMatrix();


    // Mountain_6(front)
    glPushMatrix();
    glTranslatef(0.97f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(116, 168, 42);

    if(night)
    {
        glColor3ub(36, 56, 54);
    }
    else if(winter)
    {
        glColor3ub(166, 138, 109);
    }

    glVertex2f(-0.65f, 0.5f);
    glVertex2f(-0.63f, 0.55f);

    glVertex2f(-0.63f, 0.55f);
    glVertex2f(-0.61f, 0.53f);

    glVertex2f(-0.61f, 0.53f);
    glVertex2f(-0.55f, 0.65f);

    glVertex2f(-0.55f, 0.65f);
    glVertex2f(-0.52f, 0.63f);

    glVertex2f(-0.52f, 0.63f);
    glVertex2f(-0.5f, 0.68f);

    glVertex2f(-0.5f, 0.68f);
    glVertex2f(-0.47f, 0.66f);

    glVertex2f(-0.47f, 0.66f);
    glVertex2f(-0.44f, 0.73f);

    glVertex2f(-0.44f, 0.73f);
    glVertex2f(-0.4f, 0.7f);

    glVertex2f(-0.4f, 0.7f);
    glVertex2f(-0.35f, 0.62f);

    glVertex2f(-0.35f, 0.62f);
    glVertex2f(-0.3f, 0.66f);

    glVertex2f(-0.3f, 0.66f);
    glVertex2f(-0.28f, 0.63f);

    glVertex2f(-0.28f, 0.63f);
    glVertex2f(-0.24f, 0.69f);

    glVertex2f(-0.24f, 0.69f);
    glVertex2f(-0.18f, 0.58f);

    glVertex2f(-0.18f, 0.58f);
    glVertex2f(-0.15f, 0.6f);

    glVertex2f(-0.15f, 0.6f);
    glVertex2f(-0.11f, 0.55f);

    glVertex2f(-0.11f, 0.55f);
    glVertex2f(-0.1f, 0.5f);

    glEnd();
    glPopMatrix();
}


void railLine()
{

    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);

    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.01f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.02f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.03f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.04f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.05f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.06f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.07f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.08f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.09f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.11f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.12f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.13f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.14f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.15f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.16f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.17f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.18f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.19f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.21f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.22f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.23f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.24f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.25f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.26f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.27f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.28f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.29f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.3f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.31f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.32f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.33f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.34f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.35f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.36f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.37f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.38f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.39f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.41f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.42f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.43f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.44f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.45f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.46f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.47f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.48f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.49f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.51f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.52f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.53f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.54f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.55f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.56f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.57f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.58f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.59f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.61f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.62f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.63f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.64f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.65f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.66f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.67f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.68f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.69f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.71f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.72f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.73f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.74f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.75f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.76f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.77f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.78f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.79f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.81f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.82f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.83f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.84f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.85f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.86f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.87f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.88f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.89f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.91f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.92f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.93f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.94f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.95f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.96f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.97f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.98f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.99f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    //again

    glPushMatrix();
    glTranslatef(1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(0.01f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.02f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.03f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.04f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.05f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.06f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.07f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.08f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.09f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.11f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.12f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.13f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.14f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.15f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.16f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.17f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.18f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.19f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.21f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.22f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.23f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.24f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.25f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.26f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.27f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.28f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.29f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.3f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.31f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.32f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.33f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.34f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.35f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.36f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.37f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.38f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.39f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.41f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.42f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.43f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.44f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.45f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.46f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.47f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.48f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.49f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.51f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.52f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.53f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.54f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.55f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.56f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.57f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.58f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.59f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.61f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.62f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.63f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.64f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.65f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.66f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.67f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.68f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.69f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.71f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.72f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.73f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.74f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.75f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.76f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.77f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.78f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.79f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.81f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.82f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.83f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.84f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.85f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.86f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.87f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.88f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.89f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.91f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.92f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.93f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.94f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.95f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.96f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.97f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.98f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.99f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.995f, 0.45f);
    glVertex2f(-0.995f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();
    glPopMatrix();

    glPopMatrix();


    glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(-1.0f, 0.467f);
    glVertex2f(1.0f,0.467f);
    glVertex2f(1.0f,0.46f);
    glVertex2f(-1.0f,0.46f);

    glVertex2f(-1.0f, 0.485f);
    glVertex2f(1.0f,0.485f);
    glVertex2f(1.0f, 0.49f);
    glVertex2f(-1.0f, 0.49f);

    glEnd();

}

GLfloat rail_position = 0.1f;
GLfloat rail_speed = 0.01f;
void updateRail(int value)
{
    if(rail_position <-1.0)

        rail_position = 1.0f;


    rail_position -= rail_speed;


    glutPostRedisplay();

    glutTimerFunc(150, updateRail, 0);

}


void rail()
{


    // rail line end /////////////////////////////////////>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<??????????

    //rail start/////////////////////.......................

    glPushMatrix();
    glTranslatef(rail_position,0.0f, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(1.0f,0.4f,0.0f);
    glVertex2f(0.02f,0.51f);
    glVertex2f(0.105f,0.51f);
    glVertex2f(0.105f,0.46f);
    glVertex2f(0.0f,0.46f);

    glColor3f(0.0f,0.3f,0.6f);
    glVertex2f(0.02f,0.505f);
    glVertex2f(0.1f,0.505f);
    glVertex2f(0.1f,0.5f);
    glVertex2f(0.02f,0.5f);

    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(0.02f,0.476f);
    glVertex2f(0.1f,0.476f);
    glVertex2f(0.1f,0.465f);
    glVertex2f(0.02f,0.465f);

    glColor3f(0.0f,0.3f,0.6f);
    glVertex2f(0.025f,0.471f);
    glVertex2f(0.1f,0.471f);
    glVertex2f(0.1f,0.465f);
    glVertex2f(0.021f,0.465f);
//..
    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.012f,0.495f);
    glVertex2f(0.019f,0.495f);
    glVertex2f(0.019f,0.48f);
    glVertex2f(0.007f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.022f,0.495f);
    glVertex2f(0.03f,0.495f);
    glVertex2f(0.03f,0.48f);
    glVertex2f(0.022f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.032f,0.495f);
    glVertex2f(0.04f,0.495f);
    glVertex2f(0.04f,0.48f);
    glVertex2f(0.032f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.042f,0.495f);
    glVertex2f(0.05f,0.495f);
    glVertex2f(0.05f,0.48f);
    glVertex2f(0.042f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.052f,0.495f);
    glVertex2f(0.06f,0.495f);
    glVertex2f(0.06f,0.48f);
    glVertex2f(0.052f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.062f,0.495f);
    glVertex2f(0.07f,0.495f);
    glVertex2f(0.07f,0.48f);
    glVertex2f(0.062f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.072f,0.495f);
    glVertex2f(0.08f,0.495f);
    glVertex2f(0.08f,0.48f);
    glVertex2f(0.072f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.082f,0.495f);
    glVertex2f(0.09f,0.495f);
    glVertex2f(0.09f,0.48f);
    glVertex2f(0.082f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.092f,0.495f);
    glVertex2f(0.099f,0.495f);
    glVertex2f(0.099f,0.48f);
    glVertex2f(0.092f,0.48f);

    glEnd();




    glBegin(GL_QUADS);
    glColor3f(1.0f,0.4f,0.0f);
    glVertex2f(0.205f,0.51f);
    glVertex2f(0.102f,0.51f);
    glVertex2f(0.102f,0.46f);
    glVertex2f(0.205f,0.46f);

    glColor3f(0.0f,0.3f,0.6f);
    glVertex2f(0.199f,0.505f);
    glVertex2f(0.102f,0.505f);
    glVertex2f(0.102f,0.5f);
    glVertex2f(0.199f,0.5f);


    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(0.11f,0.465f);
    glVertex2f(0.105f,0.465f);
    glVertex2f(0.105f,0.5f);
    glVertex2f(0.11f,0.5f);

    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(0.199f,0.476f);
    glVertex2f(0.105f,0.476f);
    glVertex2f(0.105f,0.465f);
    glVertex2f(0.199f,0.465f);

    glColor3f(0.0f,0.3f,0.6f);
    glVertex2f(0.11f,0.471f);
    glVertex2f(0.199f,0.471f);
    glVertex2f(0.199f,0.465f);
    glVertex2f(0.107f,0.465f);

//windus
    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.12f,0.495f);
    glVertex2f(0.112f,0.495f);
    glVertex2f(0.112f,0.48f);
    glVertex2f(0.12f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.13f,0.495f);
    glVertex2f(0.122f,0.495f);
    glVertex2f(0.122f,0.48f);
    glVertex2f(0.13f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.14f,0.495f);
    glVertex2f(0.132f,0.495f);
    glVertex2f(0.132f,0.48f);
    glVertex2f(0.14f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.15f,0.495f);
    glVertex2f(0.142f,0.495f);
    glVertex2f(0.142f,0.48f);
    glVertex2f(0.15f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.16f,0.495f);
    glVertex2f(0.152f,0.495f);
    glVertex2f(0.152f,0.48f);
    glVertex2f(0.16f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.17f,0.495f);
    glVertex2f(0.162f,0.495f);
    glVertex2f(0.162f,0.48f);
    glVertex2f(0.17f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.18f,0.495f);
    glVertex2f(0.172f,0.495f);
    glVertex2f(0.172f,0.48f);
    glVertex2f(0.18f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.19f,0.495f);
    glVertex2f(0.182f,0.495f);
    glVertex2f(0.182f,0.48f);
    glVertex2f(0.19f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.1985f,0.495f);
    glVertex2f(0.192f,0.495f);
    glVertex2f(0.192f,0.48f);
    glVertex2f(0.1985f,0.48f);


    glEnd();


    glBegin(GL_QUADS);
    glColor3f(1.0f,0.4f,0.0f);
    glVertex2f(0.305f,0.51f);
    glVertex2f(0.202f,0.51f);
    glVertex2f(0.202f,0.46f);
    glVertex2f(0.305f,0.46f);

    glColor3f(0.0f,0.3f,0.6f);
    glVertex2f(0.3f,0.505f);
    glVertex2f(0.202f,0.505f);
    glVertex2f(0.202f,0.5f);
    glVertex2f(0.3f,0.5f);


    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(0.21f,0.465f);
    glVertex2f(0.205f,0.465f);
    glVertex2f(0.205f,0.5f);
    glVertex2f(0.21f,0.5f);

    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(0.3f,0.476f);
    glVertex2f(0.205f,0.476f);
    glVertex2f(0.205f,0.465f);
    glVertex2f(0.3f,0.465f);

    glColor3f(0.0f,0.3f,0.6f);
    glVertex2f(0.21f,0.471f);
    glVertex2f(0.3f,0.471f);
    glVertex2f(0.3f,0.465f);
    glVertex2f(0.207f,0.465f);

    //..
    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.22f,0.495f);
    glVertex2f(0.212f,0.495f);
    glVertex2f(0.212f,0.48f);
    glVertex2f(0.22f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.23f,0.495f);
    glVertex2f(0.222f,0.495f);
    glVertex2f(0.222f,0.48f);
    glVertex2f(0.23f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.24f,0.495f);
    glVertex2f(0.232f,0.495f);
    glVertex2f(0.232f,0.48f);
    glVertex2f(0.24f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.25f,0.495f);
    glVertex2f(0.242f,0.495f);
    glVertex2f(0.242f,0.48f);
    glVertex2f(0.25f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.26f,0.495f);
    glVertex2f(0.252f,0.495f);
    glVertex2f(0.252f,0.48f);
    glVertex2f(0.26f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.27f,0.495f);
    glVertex2f(0.262f,0.495f);
    glVertex2f(0.262f,0.48f);
    glVertex2f(0.27f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.28f,0.495f);
    glVertex2f(0.272f,0.495f);
    glVertex2f(0.272f,0.48f);
    glVertex2f(0.28f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.29f,0.495f);
    glVertex2f(0.282f,0.495f);
    glVertex2f(0.282f,0.48f);
    glVertex2f(0.29f,0.48f);

    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.3f,0.495f);
    glVertex2f(0.292f,0.495f);
    glVertex2f(0.292f,0.48f);
    glVertex2f(0.3f,0.48f);

    glEnd();

    glPopMatrix();
}
void road()
{

    // bridge Middle_line

    glColor3ub(128,128,128);
    glBegin(GL_QUADS);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.12f,0.4f);
    glVertex2f(0.12f,-0.37f);
    glVertex2f(0.1f,-0.37f);
    glEnd();




    glBegin(GL_QUADS);

    glColor3f(0.2f,0.2f,0.2f);
    glVertex2f(-1.0f, -0.1f);
    glVertex2f(1.0f, -0.1f);
    glVertex2f(1.0f, 0.1f);
    glVertex2f(-1.0f, 0.1f);

    glColor3ub(160,160,160);
    glVertex2f(-0.3f, 0.01f);
    glVertex2f(0.3f, 0.01f);
    glVertex2f(0.3f,-0.01f);
    glVertex2f(-0.3f,-0.01f);
    glEnd();

    if (winter)
    {
        glLineWidth(5);
        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(-.45,0.05);
        glVertex2f(-0.455,0.05);//up left

        glEnd();

        glLineWidth(5);
        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(-.55,0.07);
        glVertex2f(-0.555,0.075);//up left

        glEnd();


        glPushMatrix();
        glTranslatef(-0.2f,0.0f, 0.0f);
        glLineWidth(5);
        glBegin(GL_LINES);

        glColor3ub(255,255,255);
        glVertex2f(-.55,0.07);
        glVertex2f(-0.555,0.075);//up left

        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.7f,-0.05f, 0.0f);
        glLineWidth(5);
        glBegin(GL_LINES);

        glColor3ub(255,255,255);
        glVertex2f(-.55,0.07);
        glVertex2f(-0.555,0.075);//up left

        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.5f,0.01f, 0.0f);
        glLineWidth(5);
        glBegin(GL_LINES);

        glColor3ub(255,255,255);
        glVertex2f(-.55,0.07);
        glVertex2f(-0.555,0.075);//up left

        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.5f,0.01f, 0.0f);
        glLineWidth(5);
        glBegin(GL_LINES);

        glColor3ub(255,255,255);
        glVertex2f(-.55,0.07);
        glVertex2f(-0.555,0.075);//up left

        glEnd();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(-0.9f,-0.05f, 0.0f);
        glLineWidth(5);
        glBegin(GL_LINES);

        glColor3ub(255,255,255);
        glVertex2f(-.55,0.07);
        glVertex2f(-0.555,0.075);//up left

        glEnd();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.9f,0.05f, 0.0f);
        glLineWidth(5);
        glBegin(GL_LINES);

        glColor3ub(255,255,255);
        glVertex2f(-.55,0.07);
        glVertex2f(-0.555,0.075);//up left

        glEnd();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.95f,-0.15f, 0.0f);
        glLineWidth(5);
        glBegin(GL_LINES);

        glColor3ub(255,255,255);
        glVertex2f(-.55,0.07);
        glVertex2f(-0.555,0.075);//up left

        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.95f,-0.15f, 0.0f);
        glLineWidth(5);
        glBegin(GL_LINES);

        glColor3ub(255,255,255);
        glVertex2f(-.55,0.07);
        glVertex2f(-0.555,0.075);//up left

        glEnd();
        glPopMatrix();



    }


    glPushMatrix();
    glTranslatef(-0.2f,0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.01f);
    glVertex2f(0.05f, 0.01f);
    glVertex2f(0.05f,-0.01f);
    glVertex2f(-0.05f,-0.01f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4f,0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.01f);
    glVertex2f(0.05f, 0.01f);
    glVertex2f(0.05f,-0.01f);
    glVertex2f(-0.05f,-0.01f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6f,0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.01f);
    glVertex2f(0.05f, 0.01f);
    glVertex2f(0.05f,-0.01f);
    glVertex2f(-0.05f,-0.01f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8f,0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.01f);
    glVertex2f(0.05f, 0.01f);
    glVertex2f(0.05f,-0.01f);
    glVertex2f(-0.05f,-0.01f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f,0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.01f);
    glVertex2f(0.05f, 0.01f);
    glVertex2f(0.05f,-0.01f);
    glVertex2f(-0.05f,-0.01f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.2f,0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.01f);
    glVertex2f(0.05f, 0.01f);
    glVertex2f(0.05f,-0.01f);
    glVertex2f(-0.05f,-0.01f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4f,0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.01f);
    glVertex2f(0.05f, 0.01f);
    glVertex2f(0.05f,-0.01f);
    glVertex2f(-0.05f,-0.01f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6f,0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.01f);
    glVertex2f(0.05f, 0.01f);
    glVertex2f(0.05f,-0.01f);
    glVertex2f(-0.05f,-0.01f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8f,0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.01f);
    glVertex2f(0.05f, 0.01f);
    glVertex2f(0.05f,-0.01f);
    glVertex2f(-0.05f,-0.01f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0f,0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.01f);
    glVertex2f(0.05f, 0.01f);
    glVertex2f(0.05f,-0.01f);
    glVertex2f(-0.05f,-0.01f);
    glEnd();
    glPopMatrix();
}


GLfloat bus_position = -0.1f;
GLfloat bus_position1 = 0.0f;
GLfloat bus_speed = 0.01f;
void updateBus(int value)
{


    if(bus_position >1.4)

        bus_position = -1.0f;


    bus_position += bus_speed;

    if(bus_position1 <-1.40)

        bus_position1 = 1.0f;


    bus_position1 -= bus_speed;


    glutPostRedisplay();

    glutTimerFunc(100, updateBus, 0);

}

void bus()
{

    clearColor(0.0f, 0.7f, 0.4f, 1.0f);
    int triangleAmount = 1000;
    GLfloat twicePi = 2.0f * PI;

//BUS01
    glPushMatrix();
    glTranslatef(bus_position,0,0);
    GLfloat xb1=-0.455f;
    GLfloat yb1=0.095f;
    GLfloat radiusb1 =.01f;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xb1, yb1);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xb1 + (radiusb1 * cos(i *  twicePi / triangleAmount)),
                    yb1 + (radiusb1 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    if(night) // light
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.6f,0.2f);
        glVertex2f(-0.445f, 0.097f);
        glVertex2f(-0.455f, 0.095f);
        glColor3f(1.0f,1.0f,0.79f);
        glVertex2f(-0.435f, 0.06f);
        glVertex2f(-0.39f, 0.06f);

        glEnd();
    }



    glBegin(GL_QUADS);
    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(-.45,.188);//up right
    glVertex2f(-.45,.06);
    glColor3f(0.98, 0.88, 0.02);
    glVertex2f(-.6,.06);
    glVertex2f(-.6,.188);//up left
    glEnd();
    if (winter)
    {
        glLineWidth(10);
        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(-.45,.188);
        glVertex2f(-.6,.188);//up left

        glEnd();


    }
    glBegin(GL_QUADS);
    glColor3f(0.00, 0.00, 0.00);
    glVertex2f(-.45,.077);
    glVertex2f(-.45,.069);
    glVertex2f(-.46,.069);
    glVertex2f(-.46,.077);
    glEnd();
//
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-.465,.17);
    glVertex2f(-.465,.14);
    glVertex2f(-.48,.14);
    glVertex2f(-.48,.17);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-.465,.17);
    glVertex2f(-.465,.14);
    glVertex2f(-.48,.14);
    glVertex2f(-.48,.17);
    glEnd();

    glLineWidth(6);
    glBegin(GL_LINES);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.455f,.17f);
    glVertex2f(-.455f,.12f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.59f,.12f);
    glVertex2f(-.47f,.12f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.59f,.1f);
    glVertex2f(-.47f,.1f);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.465,.17);
    glVertex2f(-.465,.14);
    glVertex2f(-.48,.14);
    glVertex2f(-.48,.17);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.49,.17);
    glVertex2f(-.49,.14);
    glVertex2f(-.505,.14);
    glVertex2f(-.505,.17);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.515,.17);
    glVertex2f(-.515,.14);
    glVertex2f(-.530,.14);
    glVertex2f(-.530,.17);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.540,.17);
    glVertex2f(-.540,.14);
    glVertex2f(-.555,.14);
    glVertex2f(-.555,.17);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.565,.17);
    glVertex2f(-.565,.14);
    glVertex2f(-.580,.14);
    glVertex2f(-.580,.17);
    glEnd();

    GLfloat xb2=-0.49f;
    GLfloat yb2=0.06f;
    GLfloat radiusb2 =.02f;
    glColor3f(0.10, 0.10, 0.10);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xb2, yb2);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xb2 + (radiusb2 * cos(i *  twicePi / triangleAmount)),
                    yb2 + (radiusb2 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


    GLfloat xb3=-.49f;
    GLfloat yb3=0.06f;
    GLfloat radiusb3 =.014f;
    glColor3f(0.47, 0.46, 0.46 );
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xb3, yb3);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xb3 + (radiusb3 * cos(i *  twicePi / triangleAmount)),
                    yb3 + (radiusb3 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();



    GLfloat xb4=-.57f;
    GLfloat yb4=0.06f;
    glColor3f(0.10, 0.10, 0.10 );
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xb4, yb4);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xb4 + (radiusb2 * cos(i *  twicePi / triangleAmount)),
                    yb4 + (radiusb2 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();



    GLfloat xb5=-.57f;
    GLfloat yb5=0.06f;
    glColor3f(0.47, 0.46, 0.46 );
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xb5, yb5);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xb5 + (radiusb3 * cos(i *  twicePi / triangleAmount)),
                    yb5 + (radiusb3 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glPopMatrix();


//BUS02
    glPushMatrix();

    glTranslatef(bus_position1,0,0);

    glPushMatrix();
    glTranslatef(0.09f,-0.125f, 0.0f);
    glRotatef(180,0,1,0);



    GLfloat xb6=-0.455f;
    GLfloat yb6=0.095f;
    GLfloat radiusb6 =.01f;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xb6, yb6);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xb6 + (radiusb6 * cos(i *  twicePi / triangleAmount)),
                    yb6 + (radiusb6 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    if(night)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.6f,0.2f);
        glVertex2f(-0.445f, 0.097f);
        glVertex2f(-0.455f, 0.095f);
        glColor3f(1.0f,1.0f,0.79f);
        glVertex2f(-0.435f, 0.06f);
        glVertex2f(-0.39f, 0.06f);

        glEnd();
    }

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.4, 0.0);
    glVertex2f(-.45,.188);
    glVertex2f(-.45,.06);
    glColor3f(1.0, 0.2, 0.2);
    glVertex2f(-.6,.06);
    glVertex2f(-.6,.188);
    glEnd();

    if (winter)
    {
        glLineWidth(7);
        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(-.45,.188);
        glVertex2f(-.6,.188);
        glEnd();


    }


    glBegin(GL_QUADS);
    glColor3f(0.00, 0.00, 0.00);
    glVertex2f(-.45,.077);
    glVertex2f(-.45,.069);
    glVertex2f(-.46,.069);
    glVertex2f(-.46,.077);
    glEnd();

    glLineWidth(6);
    glBegin(GL_LINES);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.455f,.17f);
    glVertex2f(-.455f,.12f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.59f,.12f);
    glVertex2f(-.47f,.12f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.59f,.1f);
    glVertex2f(-.47f,.1f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.465,.17);
    glVertex2f(-.465,.14);
    glVertex2f(-.48,.14);
    glVertex2f(-.48,.17);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.465,.17);
    glVertex2f(-.465,.14);
    glVertex2f(-.48,.14);
    glVertex2f(-.48,.17);
    glEnd();



    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.465,.17);
    glVertex2f(-.465,.14);
    glVertex2f(-.48,.14);
    glVertex2f(-.48,.17);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.465,.17);
    glVertex2f(-.465,.14);
    glVertex2f(-.48,.14);
    glVertex2f(-.48,.17);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.465,.17);
    glVertex2f(-.465,.14);
    glVertex2f(-.48,.14);
    glVertex2f(-.48,.17);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.76, 0.77, 0.78);
    glVertex2f(-.465,.17);
    glVertex2f(-.465,.14);
    glVertex2f(-.48,.14);
    glVertex2f(-.48,.17);
    glEnd();



    GLfloat xb7=-0.49f;
    GLfloat yb7=0.06f;
    GLfloat radiusb7 =.02f;
    glColor3f(0.10, 0.10, 0.10);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xb7, yb7);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xb7 + (radiusb7 * cos(i *  twicePi / triangleAmount)),
                    yb7 + (radiusb7 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


    GLfloat xb8=-.49f;
    GLfloat yb8=0.06f;
    GLfloat radiusb8 =.014f;
    glColor3f(0.47, 0.46, 0.46 );
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xb8, yb8);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xb8 + (radiusb8 * cos(i *  twicePi / triangleAmount)),
                    yb8 + (radiusb8 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();



    GLfloat xb9=-.57f;
    GLfloat yb9=0.06f;
    GLfloat radiusb9 =.02f;
    glColor3f(0.10, 0.10, 0.10 );
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xb9, yb9);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xb9 + (radiusb9 * cos(i *  twicePi / triangleAmount)),
                    yb9 + (radiusb9 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();



    GLfloat xb10=-.57f;
    GLfloat yb10=0.06f;
    GLfloat radiusb10 =.014f;
    glColor3f(0.47, 0.46, 0.46);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xb10, yb10);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xb10 + (radiusb10 * cos(i *  twicePi / triangleAmount)),
                    yb10 + (radiusb10* sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glLoadIdentity();
    glPopMatrix();
    glPopMatrix();

}

GLfloat helicopter_position = 0.1f;
GLfloat helicopter_speed = 0.01f;
void updateHelicopter(int value)
{


    if(helicopter_position <-1.0 )

        helicopter_position = 1.0f;

    helicopter_position -= helicopter_speed;


    glutPostRedisplay();

    glutTimerFunc(100, updateHelicopter, 0);


}



void helicopter()
{
    //Helicopter Body

    glPushMatrix();
    glTranslatef(helicopter_position, 0.5f, 0.0f);
    glScalef(0.38,0.45,0);
    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex2f(-0.83f, 0.72f); // left ground
    glVertex2f(-0.8f, 0.69f);
    glVertex2f(-0.65f, 0.69f);


    glVertex2f(-0.61f, 0.69f);
    glVertex2f(-0.55f, 0.74f);
    glVertex2f(-0.45f, 0.74f);
    glVertex2f(-0.45f, 0.765f);


    glVertex2f(-0.55f, 0.765f);
    glVertex2f(-0.65f, 0.85f);
    glVertex2f(-0.71f, 0.85f);
    glVertex2f(-0.77f, 0.81f);

    glEnd();

//////////////////////////////////////////////////
//Glass

// Glass front
    glBegin(GL_QUADS);
    glColor3ub(224, 255, 255); //Middle River and background
    glVertex2f(-0.83f, 0.72f);
    glVertex2f(-0.73f, 0.72f);
    glVertex2f(-0.73f, 0.81f);
    glVertex2f(-0.77f, 0.81f);
    glEnd();


    // Glass front
    glBegin(GL_QUADS);
    glColor3ub(224, 255, 255);
    glVertex2f(-0.67f, 0.72f);
    glVertex2f(-0.67f, 0.85f);
    glVertex2f(-0.68f, 0.85f);
    glVertex2f(-0.68f, 0.72f);
    glEnd();

//////////////////////////////////////////////////
//Wing Front
    // top low-1
    glBegin(GL_QUADS);
    glColor3ub(224, 255, 255); //Middle River and background
    glVertex2f(-0.66f, 0.85f);
    glVertex2f(-0.67f, 0.87f);
    glVertex2f(-0.69f, 0.87f);
    glVertex2f(-0.70f, 0.85f);


    glEnd();

// top low-2
    glBegin(GL_QUADS);
    glColor3ub(224, 255, 255); //Middle River and background

    glVertex2f(-0.675f, 0.85f);
    glVertex2f(-0.675f, 0.91f);
    glVertex2f(-0.685f, 0.91f);
    glVertex2f(-0.685f, 0.85f);



    glEnd();

//top low-3 black
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.675f, 0.91f);
    glVertex2f(-0.665f, 0.92f);
    glVertex2f(-0.675f, 0.93f);
    glVertex2f(-0.685f, 0.93f);
    glVertex2f(-0.695f, 0.92f);
    glVertex2f(-0.685f, 0.91f);
    glEnd();

    //top low-3 black
    glBegin(GL_QUADS);
    glColor3ub(224, 255, 255); //Middle River and background
    glVertex2f(-0.77f, 0.93f);
    glVertex2f(-0.77f, 0.91f);
    glVertex2f(-0.685f, 0.91f);
    glVertex2f(-0.685f, 0.92f);
    glEnd();



    //top low-3 black
    glBegin(GL_QUADS);
    glColor3ub(224, 255, 255); //Middle River and background
    glVertex2f(-0.78f, 0.94f);
    glVertex2f(-0.78f, 0.91f);
    glVertex2f(-0.685f, 0.91f);
    glVertex2f(-0.685f, 0.92f);
    glEnd();




    //top low-3 black
    glBegin(GL_QUADS);
    glColor3ub(224, 255, 255); //Middle River and background
    glVertex2f(-0.675f, 0.91f);
    glVertex2f(-0.57f, 0.91f);
    glVertex2f(-0.57f, 0.94f);
    glVertex2f(-0.675f, 0.92f);
    glEnd();

//////////////////////////////////////////////////
//Wing Back

//Back wing 1st
    glBegin(GL_QUADS);
    glColor3ub(224, 255, 255); //Middle River and background
    glVertex2f(-0.46f, 0.76f);
    glVertex2f(-0.46f, 0.83f);
    glVertex2f(-0.45f, 0.83f);
    glVertex2f(-0.45f, 0.76f);

    glEnd();

//Back wing 2nd
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); //Middle River and background
    glVertex2f(-0.465f, 0.83f);
    glVertex2f(-0.45f, 0.83f);
    glVertex2f(-0.445f, 0.845f);
    glVertex2f(-0.45f, 0.85f);
    glVertex2f(-0.465f, 0.85f);
    glVertex2f(-0.47f, 0.845f);

    glEnd();

    //Back Main Wing left
    glBegin(GL_QUADS);
    glColor3ub(224, 255, 255); //Middle River and background
    glVertex2f(-0.51f, 0.84f);
    glVertex2f(-0.46f, 0.83f);
    glVertex2f(-0.46f, 0.85f);
    glVertex2f(-0.51f, 0.87f);

    glEnd();

//Back Main Wing right
    glBegin(GL_QUADS);
    glColor3ub(224, 255, 255); //Middle River and background
    glVertex2f(-0.45f, 0.83f);
    glVertex2f(-0.40f, 0.84f);
    glVertex2f(-0.40f, 0.87f);
    glVertex2f(-0.45f, 0.85f);

    glEnd();

    glPopMatrix();

}






GLfloat car_position = -0.1f;
GLfloat car_position1 = 0.0f;
GLfloat car_speed = 0.01f;
void updateCar(int value)
{


    if(car_position >1.0 )

        car_position = -1.0f;

    car_position += car_speed;
    if(car_position1 <-1.0)

        car_position1 = 1.0f;

    car_position1 -= car_speed;


    glutPostRedisplay();

    glutTimerFunc(100, updateCar, 0);

}
void car()
{
    clearColor(0.0f, 0.7f, 0.4f, 1.0f);
    if(night)
    {
        clearColor(0.07, 0.30, 0.15, 1);
    }


//    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat twicePi = 2.0f * PI;
    int triangleAmount = 1000;

//BODY
    glPushMatrix();
    glTranslatef(car_position,0,0);
    glPushMatrix();
    glTranslatef(0.5f,0.1f,0.0f);
    glRotatef(180,0,1,0),
              glBegin(GL_QUADS);
    glColor3f(0.0f,0.5f,0.0f);
    glVertex2f(0.42f, 0.0175f);
    glVertex2f(0.42f, -0.02f);
    glVertex2f(0.32f, -0.02f);
    glVertex2f(0.33f, 0.0175f);


    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.5f,0.0f);
    glVertex2f(0.42f, -0.02f);
    glVertex2f(0.42f, -0.067f);
    glVertex2f(0.3f, -0.067f);
    glVertex2f(0.3f, -0.02f);

    glEnd();

    if (winter)
    {
        glLineWidth(10);
        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(0.42f, 0.0175f);
        glVertex2f(0.33f, 0.0175f);
        glEnd();


    }

//Light....................................................................
    glBegin(GL_QUADS);
    glColor3f(1.0f,0.038f,0.27f);



    glVertex2f(0.306f, -0.02f);
    glVertex2f(0.309f, -0.032f);

    glVertex2f(0.3f, -0.032f);
    glVertex2f(0.3f, -0.02f);




    glEnd();

    if(night)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.6f,0.2f);
        glVertex2f(0.3f, -0.025f);
        glVertex2f(0.3f, -0.032f);
        glColor3f(1.0f,1.0f,0.79f);
        glVertex2f(0.28f, -0.067f);
        glVertex2f(0.25f, -0.067f);

        glEnd();
    }

//back light.............................................
    glBegin(GL_QUADS);
    glColor3f(1.0f,0.38f,0.27f);

    glVertex2f(0.42f, -0.04f);
    glVertex2f(0.413f, -0.04);
    glVertex2f(0.413f, -0.054f);
    glVertex2f(0.42f, -0.054f);


    glEnd();
//  //BACK SIDE WHELL.......................................................

    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);

    glVertex2f(0.42f, -0.018f);
    glVertex2f(0.425f, -0.018f);
    glVertex2f(0.425f, -0.05f);
    glVertex2f(0.42f, -0.053f);



    glEnd();


    //window1..............................

    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);


    glVertex2f(0.352f, 0.012f);
    glVertex2f(0.352f, -0.02f);
    glVertex2f(0.325f, -0.02f);
    glVertex2f(0.334f, 0.012f);
    glEnd();

    //window2..................
    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);

    glVertex2f(0.354f, 0.012f);
    glVertex2f(0.354f, -0.02f);
    glVertex2f(0.374f, -0.02f);
    glVertex2f(0.374f, 0.012f);



    glEnd();


    //window3.................................

    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);

    glVertex2f(0.41f, 0.012f);
    glVertex2f(0.41f, -0.02f);
    glVertex2f(0.376f, -0.02f);
    glVertex2f(0.376f, 0.012f);



    glEnd();
//
    //Door1..........................................


    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);

    glVertex2f(0.352f, -0.023f);
    glVertex2f(0.352f, -0.027f);
    glVertex2f(0.344f, -0.027f);
    glVertex2f(0.344f, -0.023f);



    glEnd();

    //Door2..........................................................



    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);

    glVertex2f(0.373f, -0.023f);
    glVertex2f(0.373f, -0.027f);
    glVertex2f(0.367f, -0.027f);
    glVertex2f(0.367f, -0.023f);



    glEnd();

    //wheel1...................................



    GLfloat xc=0.33f;
    GLfloat yc=-0.067f;
    GLfloat radiusc =0.015f;

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc, yc); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xc + (radiusc * cos(i *  twicePi / triangleAmount)),
                    yc+ (radiusc * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


    GLfloat xc1=0.33f;
    GLfloat yc1=-0.067f;
    GLfloat radiusc3 =0.008f;

    glColor3f(0.50f, 0.50f, 0.50f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc1, yc1); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xc1 + (radiusc3 * cos(i *  twicePi / triangleAmount)),
                    yc1 + (radiusc3 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


//wheel2.................................


    GLfloat xc2=0.39f;
    GLfloat yc2=-0.067f;
    GLfloat radiusc4=0.015f;

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc2, yc2); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xc2 + (radiusc4 * cos(i *  twicePi / triangleAmount)),
                    yc2 + (radiusc4 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();



    GLfloat xc3=0.39f;
    GLfloat yc3=-0.067f;
    GLfloat radiusc5=0.008f;

    glColor3f(0.50f, 0.50f, 0.50f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc3, yc3); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xc3 + (radiusc5 * cos(i *  twicePi / triangleAmount)),
                    yc3 + (radiusc5 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();
    glLoadIdentity();

    glPopMatrix();


    glPopMatrix();


//CAR3
    glPushMatrix();
    glTranslatef(car_position1,0,0);
    glPushMatrix();
    glTranslatef(-0.45f,0.0f,0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex2f(0.4f, 0.0175f);
    glVertex2f(0.42f, -0.02f);
    glVertex2f(0.32f, -0.02f);
    glVertex2f(0.33f, 0.0175f);
    glEnd();

    if (winter)
    {
        glLineWidth(10);
        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(0.42f, 0.0175f);
        glVertex2f(0.33f, 0.0175f);
        glEnd();


    }

    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex2f(0.42f, -0.02f);
    glVertex2f(0.42f, -0.067f);
    glVertex2f(0.3f, -0.067f);
    glVertex2f(0.3f, -0.02f);

    glEnd();



//Light....................................................................
    glBegin(GL_QUADS);
    glColor3f(1.0f,0.038f,0.27f);



    glVertex2f(0.306f, -0.02f);
    glVertex2f(0.309f, -0.032f);

    glVertex2f(0.3f, -0.032f);
    glVertex2f(0.3f, -0.02f);


    glEnd();
    if(night)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.6f,0.2f);
        glVertex2f(0.3f, -0.025f);
        glVertex2f(0.3f, -0.032f);
        glColor3f(1.0f,1.0f,0.79f);
        glVertex2f(0.28f, -0.067f);
        glVertex2f(0.25f, -0.067f);

        glEnd();
    }
//back light.............................................
    glBegin(GL_QUADS);
    glColor3f(1.0f,0.38f,0.27f);

    glVertex2f(0.42f, -0.04f);
    glVertex2f(0.413f, -0.04);
    glVertex2f(0.413f, -0.054f);
    glVertex2f(0.42f, -0.054f);


    glEnd();
//  //BACK SIDE WHELL.......................................................
//
//   glBegin(GL_QUADS);
//    glColor3f(0.8f,1.0f,1.0f);
//
//    glVertex2f(0.42f, -0.018f);
//    glVertex2f(0.425f, -0.018f);
//    glVertex2f(0.425f, -0.05f);
//    glVertex2f(0.42f, -0.053f);
//
//
//
//    glEnd();


    //window1..............................

    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);


    glVertex2f(0.352f, 0.012f);
    glVertex2f(0.352f, -0.02f);
    glVertex2f(0.325f, -0.02f);
    glVertex2f(0.334f, 0.012f);
    glEnd();

    //window2..................
    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);

    glVertex2f(0.354f, 0.012f);
    glVertex2f(0.354f, -0.02f);
    glVertex2f(0.374f, -0.02f);
    glVertex2f(0.374f, 0.012f);



    glEnd();


    //window3.................................

    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);

    glVertex2f(0.394f, 0.012f);
    glVertex2f(0.41f, -0.02f);
    glVertex2f(0.376f, -0.02f);
    glVertex2f(0.376f, 0.012f);



    glEnd();
//
    //Door1..........................................


    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);

    glVertex2f(0.352f, -0.023f);
    glVertex2f(0.352f, -0.027f);
    glVertex2f(0.344f, -0.027f);
    glVertex2f(0.344f, -0.023f);



    glEnd();

    //Door2..........................................................



    glBegin(GL_QUADS);
    glColor3f(0.8f,1.0f,1.0f);

    glVertex2f(0.373f, -0.023f);
    glVertex2f(0.373f, -0.027f);
    glVertex2f(0.367f, -0.027f);
    glVertex2f(0.367f, -0.023f);



    glEnd();

    //wheel1...................................



    GLfloat xc5=0.33f;
    GLfloat yc5=-0.067f;

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc, yc); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xc5 + (radiusc * cos(i *  twicePi / triangleAmount)),
                    yc5+ (radiusc * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


    GLfloat xc6=0.33f;
    GLfloat yc6=-0.067f;

    glColor3f(0.50f, 0.50f, 0.50f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc6, yc6); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xc6 + (radiusc3 * cos(i *  twicePi / triangleAmount)),
                    yc6 + (radiusc3 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


//wheel2.................................


    GLfloat xc7=0.39f;
    GLfloat yc7=-0.067f;
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc7, yc7); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xc7 + (radiusc4 * cos(i *  twicePi / triangleAmount)),
                    yc7 + (radiusc4 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    GLfloat xc8=0.39f;
    GLfloat yc8=-0.067f;
    glColor3f(0.50f, 0.50f, 0.50f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc8, yc8); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xc8 + (radiusc5 * cos(i *  twicePi / triangleAmount)),
                    yc8 + (radiusc5 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glPopMatrix();
    glPopMatrix();

}

void bridge1()
{
    int x;

    GLfloat p21=-0.08f;
    GLfloat q21= 0.1f;
    GLfloat r21 = 0.08f;
    int tringle10=40;

    GLfloat tp4 =1.0f * PI  ;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub(224, 255, 255);
    if(winter)
    {
        glColor3ub (245,245,245);
    }
    glVertex2f (p21,q21);
    for(x= 0; x<=tringle10; x++)
    {
        glVertex2f (
            p21+(r21*cos(x*tp4/tringle10)),
            q21+(r21*sin(x*tp4/tringle10))
        );


    }
    glEnd ();


    //circle 2

    int i;

    GLfloat p1=0.101f;
    GLfloat q1=0.1f;
    GLfloat r1 = 0.1f;
    int tringle2=40;

    GLfloat tp2 =1.0f * PI  ;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub(224, 255, 255);
    if(winter)
    {
        glColor3ub (245,245,245);
    }
    glVertex2f (p1,q1);
    for(i= 0; i<=tringle2; i++)
    {
        glVertex2f (
            p1+(r1*cos(i*tp2/tringle2)),
            q1+(r1*sin(i*tp2/tringle2))
        );


    }
    glEnd ();

    //circle 3
    int y;

    GLfloat p3=0.28f;
    GLfloat q3=0.1f;
    GLfloat r3 = 0.08f;
    int tringle3=40;

    GLfloat tp5 =1.0f * PI  ;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub(224, 255, 255);
    if(winter)
    {
        glColor3ub (245,245,245);
    }
    glVertex2f (p3,q3);
    for(y= 0; y<=tringle3; y++)
    {
        glVertex2f (
            p3+(r3*cos(y*tp5/tringle3)),
            q3+(r3*sin(y*tp5/tringle3))
        );


    }
    glEnd ();



//bridge column 1
    glColor3ub(47,79,79);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.15f, -0.1f);
    glVertex2f(-0.075f,-0.2f);
    glVertex2f(0.0f, -0.1f);

    glEnd();

    glColor3ub(47,79,79);
    glBegin(GL_QUADS);
    glVertex2f(-0.1f, -0.15f);
    glVertex2f(-0.05f,-0.15f);
    glVertex2f(-0.05f,-0.37f);
    glVertex2f(-0.1f,-0.37f);

    glEnd();


//bridge column 2
    glColor3ub(47,79,79);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2f, -0.1f);
    glVertex2f(0.275f,-0.2f);
    glVertex2f(0.35f, -0.1f);


    glEnd();

    glColor3ub(47,79,79);
    glBegin(GL_QUADS);
    glVertex2f(0.3f, -0.15f);
    glVertex2f(0.25f,-0.15f);
    glVertex2f(0.25f,-0.37f);
    glVertex2f(0.3f,-0.37f);

    glEnd();

    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3ub(210,105,30);
    glVertex2f(-0.2f, 0.1f);
    glVertex2f(0.1f,0.4f);

    glEnd();

    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3ub(210,105,30);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(0.1f,0.4f);

    glEnd();

    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3ub(210,105,30);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(0.12f,0.4f);

    glEnd();

    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3ub(210,105,30);
    glVertex2f(0.4f, -0.1f);
    glVertex2f(0.12f,0.4f);

    glEnd();

}

void bridge2()
{
    //circle 4

    int a;

    GLfloat a6=0.28f;
    GLfloat b6=-0.1f;
    GLfloat radius2 = 0.08f;
    int tringle5=40;

    GLfloat tp13 =1.0f * PI  ;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub(224, 255, 255);
    if(winter)
    {
        glColor3ub (245,245,245);
    }
    glVertex2f (a6,b6);
    for(a= 0; a<=tringle5; a++)
    {
        glVertex2f (
            a6+(radius2*cos(a*tp13/tringle5)),
            b6+(radius2*sin(a*tp13/tringle5))
        );


    }
    glEnd ();

    //circle 5
    int k;

    GLfloat k1=0.101f;;
    GLfloat k2=-0.1f;
    GLfloat radius10 = 0.1f;
    int tringle7=40;

    GLfloat tp14 =1.0f * PI  ;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub(224, 255, 255);
    if(winter)
    {
        glColor3ub (245,245,245);
    }
    glVertex2f (k1,k2);
    for(k= 0; k<=tringle7; k++)
    {
        glVertex2f (
            k1+(radius10*cos(k*tp14/tringle7)),
            k2+(radius10*sin(k*tp14/tringle7))
        );


    }
    glEnd ();

    //circle6
    int z;

    GLfloat p23=-0.08f;
    GLfloat q23= -0.1f;
    GLfloat r23 = 0.08f;
    int tringle15=40;

    GLfloat tp9 =1.0f * PI  ;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub(224, 255, 255);
    if(winter)
    {
        glColor3ub (245,245,245);
    }
    glVertex2f (p23,q23);
    for(z= 0; z<=tringle15; z++)
    {
        glVertex2f (
            p23+(r23*cos(z*tp9/tringle15)),
            q23+(r23*sin(z*tp9/tringle15))
        );


    }
    glEnd ();
}

void seaside()
{
    glBegin(GL_QUADS);
    glColor3ub(210,180,140); //Color
    glVertex2f(-1.0f, -0.4f);
    glVertex2f(1.0f, -0.4f);
    glVertex2f(1.0f, 0.05f);
    glVertex2f(-1.0f, -0.05f);
    glEnd();

    if(night)
    {
        glBegin(GL_QUADS);
        glColor3ub(192,192,192);

        // glColor3ub(100,182,236); //Color
        glVertex2f(-1.0f, -0.4f);
        glVertex2f(1.0f, -0.4f);
        glVertex2f(1.0f, 0.05f);
        glVertex2f(-1.0f, -0.05f);
        glEnd();
    }
}



float _rain1x = 0.0;
float _rain2x = 0.0;
float _rain3x = 0.0;
float _rain4x = 0.0;
float _rain5x = 0.0;
float _rain6x = 0.0;
float _rain7x = 0.0;
float _rain8x = 0.0;
float _rain9x = 0.0;
float _rain10x = 0.0;
float _rain11x = 0.0;

float _rain1y = 0.0;
float _rain2y = 0.0;
float _rain3y = 0.0;
float _rain4y = 0.0;
float _rain5y = 0.0;
float _rain6y = 0.0;
float _rain7y = 0.0;
float _rain8y = 0.0;
float _rain9y = 0.0;
float _rain10y = 0.0;
float _rain11y = 0.0;
float _rain12y = 0.0;
float _rain13y = 0.0;
float _rain14y = 0.0;
float _rain15y = 0.0;

void rainyday()
{
    if(rain)
    {
        glPushMatrix();
        glTranslatef(_rain1x,_rain1y,0);
        glLineWidth(1.5);

        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPushMatrix();
        glTranslatef(-.05,0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();
        glPopMatrix();
        glPopMatrix();

        //rain 2 <<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        glPushMatrix();
        glTranslatef(_rain2x,_rain2y,0);

        glPushMatrix();
        glTranslatef(-.02,-.2,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPushMatrix();
        glTranslatef(-.05,0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();

        //rain 3 <<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        glPushMatrix();
        glTranslatef(_rain3x,_rain3y,0);

        glPushMatrix();
        glTranslatef(-.0,-.4,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPushMatrix();
        glTranslatef(-.05,0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();


        //rain 4 <<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        glPushMatrix();
        glTranslatef(_rain4x,_rain4y,0);

        glPushMatrix();
        glTranslatef(-.03,-.6,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPushMatrix();
        glTranslatef(-.05,0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();

        //rain 5 <<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        glPushMatrix();
        glTranslatef(_rain5x,_rain5y,0);

        glPushMatrix();
        glTranslatef(-.03,-.8,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPushMatrix();
        glTranslatef(-.05,0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();


        //rain 6 <<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        glPushMatrix();
        glTranslatef(_rain6x,_rain6y,0);

        glPushMatrix();
        glTranslatef(-.03,-1.0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPushMatrix();
        glTranslatef(-.05,0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();

        //rain 7 <<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        glPushMatrix();
        glTranslatef(_rain7x,_rain7y,0);

        glPushMatrix();
        glTranslatef(-.03,-1.2,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPushMatrix();
        glTranslatef(-.05,0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();


        //rain 8 <<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        glPushMatrix();
        glTranslatef(_rain8x,_rain8y,0);

        glPushMatrix();
        glTranslatef(-.0,-1.4,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPushMatrix();
        glTranslatef(-.05,0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();

        //rain 9 <<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        glPushMatrix();
        glTranslatef(_rain9x,_rain9y,0);

        glPushMatrix();
        glTranslatef(-.03,-1.6,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPushMatrix();
        glTranslatef(-.05,0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();

        //rain 10 <<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        glPushMatrix();
        glTranslatef(_rain10x,_rain10y,0);

        glPushMatrix();
        glTranslatef(-.03,-1.8,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPushMatrix();
        glTranslatef(-.05,0,0);
        glBegin(GL_LINES);
        glColor3f(1,1,1);

        glVertex2f(-.95,.9);
        glVertex2f(-.955,.85);

        glVertex2f(-.85,.9);
        glVertex2f(-.855,.85);

        glVertex2f(-.75,.9);
        glVertex2f(-.755,.85);

        glVertex2f(-.65,.9);
        glVertex2f(-.655,.85);

        glVertex2f(-.55,.9);
        glVertex2f(-.555,.85);

        glVertex2f(-.45,.9);
        glVertex2f(-.455,.85);

        glVertex2f(-.35,.9);
        glVertex2f(-.355,.85);

        glVertex2f(-.25,.9);
        glVertex2f(-.255,.85);

        glVertex2f(-.15,.9);
        glVertex2f(-.155,.85);

        glVertex2f(-.05,.9);
        glVertex2f(-.055,.85);

        glVertex2f(.05,.9);
        glVertex2f(.045,.85);

        glVertex2f(.15,.9);
        glVertex2f(.145,.85);

        glVertex2f(.25,.9);
        glVertex2f(.245,.85);

        glVertex2f(.35,.9);
        glVertex2f(.345,.85);

        glVertex2f(.45,.9);
        glVertex2f(.445,.85);

        glVertex2f(.55,.9);
        glVertex2f(.545,.85);

        glVertex2f(.65,.9);
        glVertex2f(.645,.85);

        glVertex2f(.75,.9);
        glVertex2f(.745,.85);

        glVertex2f(.85,.9);
        glVertex2f(.845,.85);

        glVertex2f(.95,.9);
        glVertex2f(.945,.85);

        glVertex2f(1.05,.9);
        glVertex2f(1.045,.85);

        glVertex2f(1.15,.9);
        glVertex2f(1.145,.85);

        glVertex2f(1.25,.9);
        glVertex2f(1.245,.85);

        glVertex2f(1.35,.9);
        glVertex2f(1.345,.85);

        glEnd();

        glPopMatrix();
        glPopMatrix();
        glPopMatrix();

    }
}

void resetRain()
{
    _rain1y = 0.0;
    _rain2y = 0.0;
    _rain3y = 0.0;
    _rain4y = 0.0;
    _rain5y = 0.0;
    _rain6y = 0.0;
    _rain7y = 0.0;
    _rain8y = 0.0;
    _rain9y = 0.0;
    _rain10y = 0.0;

    i = 0;
}


GLfloat boat_position = 0.0f;
GLfloat boat_position1 = -1.0f;
GLfloat boat_speed = 0.01f;
void updateBoat(int value)
{
    if(boat_position >2.0 )

        boat_position = -1.0f;

    boat_position += boat_speed;
    if(boat_position1 <-1.0)

        boat_position1 = 1.5f;

    boat_position1 -= boat_speed;

    glutPostRedisplay();
    glutTimerFunc(100, updateBoat, 0);

}

void boat1()
{
    glPushMatrix();
    glTranslatef(boat_position1,0,0);
//lower
    glBegin(GL_QUADS);
    glColor3ub(47,79,79);
    glVertex2f(-0.65f, -0.7f);
    glVertex2f(-0.55f, -0.7f);
    glVertex2f(-0.5f, -0.6f);
    glVertex2f(-0.7f, -0.6f);
    glEnd();

    if (night)
    {
        glBegin(GL_QUADS);
        glColor3ub(0,51,102);
        glVertex2f(-0.65f, -0.7f);
        glVertex2f(-0.55f, -0.7f);
        glVertex2f(-0.5f, -0.6f);
        glVertex2f(-0.7f, -0.6f);
        glEnd();

    }

    if (winter)
    {

        glBegin(GL_POLYGON);
        glColor3ub(255,255,255);
        glVertex2f(-0.7f, -0.6f);
        glVertex2f(-0.65f, -0.54f);
        glVertex2f(-0.54f, -0.54f);
        glVertex2f(-0.5f, -0.6f);
        glVertex2f(-0.54f, -0.6f);
        glVertex2f(-0.54f, -0.56f);
        glVertex2f(-0.65f, -0.56f);
        glVertex2f(-0.65f, -0.6f);
        glEnd();

    }
//upper
    glBegin(GL_QUADS);
    glColor3ub(240,230,140);

    glVertex2f(-0.65f, -0.6f);
    glVertex2f(-0.65f, -0.56f);
    glVertex2f(-0.54f, -0.56f);
    glVertex2f(-0.54f, -0.6f);
    glEnd();


    if (night)
    {
        glBegin(GL_QUADS);
        glColor3ub(102,102,0);
        glVertex2f(-0.65f, -0.6f);
        glVertex2f(-0.65f, -0.56f);
        glVertex2f(-0.54f, -0.56f);
        glVertex2f(-0.54f, -0.6f);
        glEnd();

    }

//Triangle 1
    glBegin(GL_TRIANGLES);
    glColor3ub(255,99,71);

    glVertex2f(-0.6f, -0.56f);
    glVertex2f(-0.57f, -0.58f);
    glVertex2f(-0.6f, -0.45f);

    glEnd();

    glLineWidth(0.3);
    glBegin(GL_LINES);
    glColor3ub(255,99,71);
    glVertex2f(-0.6f, -0.56f);
    glVertex2f(-0.6f, -0.6f);

    glEnd();

//Triangle 2
    glBegin(GL_TRIANGLES);
    glColor3ub(255,99,71);
    glVertex2f(-0.61f, -0.56f);
    glVertex2f(-0.64f, -0.58f);
    glVertex2f(-0.61f, -0.45f);

    glEnd();

    glLineWidth(0.3);
    glBegin(GL_LINES);
    glColor3ub(255,99,71);
    glVertex2f(-0.61f, -0.56f);
    glVertex2f(-0.61f, -0.6f);

    glEnd();

    //Triangle 3
    glBegin(GL_TRIANGLES);
    glColor3ub(255,99,71);

    glVertex2f(-0.63f, -0.56f);
    glVertex2f(-0.66f, -0.58f);
    glVertex2f(-0.63f, -0.5f);

    glEnd();

    glLineWidth(0.3);
    glBegin(GL_LINES);
    glColor3ub(255,99,71);
    glVertex2f(-0.63f, -0.56f);
    glVertex2f(-0.63f, -0.6f);

    glEnd();
    // glPopMatrix();

    if (night)
    {

//Triangle 1
        glBegin(GL_TRIANGLES);
        glColor3ub(102,0,0);

        glVertex2f(-0.6f, -0.56f);
        glVertex2f(-0.57f, -0.58f);
        glVertex2f(-0.6f, -0.45f);

        glEnd();

        glLineWidth(0.3);
        glBegin(GL_LINES);
        glColor3ub(255,99,71);
        glVertex2f(-0.6f, -0.56f);
        glVertex2f(-0.6f, -0.6f);

        glEnd();

//Triangle 2
        glBegin(GL_TRIANGLES);
        glColor3ub(102,0,0);
        glVertex2f(-0.61f, -0.56f);
        glVertex2f(-0.64f, -0.58f);
        glVertex2f(-0.61f, -0.45f);

        glEnd();

        glLineWidth(0.3);
        glBegin(GL_LINES);
        glColor3ub(102,0,0);
        glVertex2f(-0.61f, -0.56f);
        glVertex2f(-0.61f, -0.6f);

        glEnd();

        //Triangle 3
        glBegin(GL_TRIANGLES);
        glColor3ub(102,0,0);

        glVertex2f(-0.63f, -0.56f);
        glVertex2f(-0.66f, -0.58f);
        glVertex2f(-0.63f, -0.5f);

        glEnd();

        glLineWidth(0.3);
        glBegin(GL_LINES);
        glColor3ub(102,0,0);
        glVertex2f(-0.63f, -0.56f);
        glVertex2f(-0.63f, -0.6f);

        glEnd();
    }

    glPopMatrix();


}
void boat3()
{
    //small boat
    glPushMatrix();
    glTranslatef(boat_position,0,0);
//        glPushMatrix();
//        glTranslatef(0.8f, -0.08f, 0.0f);
    glScalef(1.54,1.5,0);


    glBegin(GL_POLYGON);

    glColor3ub(139,69,19);

    glVertex2f(-0.75f, -0.47f);
    glVertex2f(-0.65f, -0.47f);

    glVertex2f(-0.6f, -0.4f);
    glVertex2f(-0.65f, -0.47f);

    glVertex2f(-0.8f, -0.4f);
    glVertex2f(-0.75f, -0.47f);

    glVertex2f(-0.6f, -0.4f);
    glVertex2f(-0.65f, -0.44f);

    glVertex2f(-0.75f, -0.44f);
    glVertex2f(-0.8f, -0.4f);

    glVertex2f(-0.65f, -0.44f);
    glVertex2f(-0.75f, -0.44f);

    glEnd();

    glBegin(GL_QUADS);

    glColor3ub(147,112,219);

    glVertex2f(-0.72f, -0.39f);
    glVertex2f(-0.67f, -0.39f);
    glVertex2f(-0.65f, -0.435f);
    glVertex2f(-0.7f, -0.435f);


    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f,0.0f,0.0f);

    glVertex2f(-0.72f, -0.39f);
    glVertex2f(-0.7f, -0.43f);
    glVertex2f(-0.75f, -0.418f);


    glEnd();
    // glLoadIdentity();
    glPopMatrix();
}

void boat2()
{
    // badha boat
    //lower
    glPushMatrix();
    glTranslatef(-0.41f, 0.65f, 0.0f);
    glScalef(0.6,0.6,0);

    glBegin(GL_QUADS);
    glColor3ub(0,139,139);

    glVertex2f(0.65f, -0.7f);
    glVertex2f(0.55f, -0.7f);
    glVertex2f(0.5f, -0.6f);
    glVertex2f(0.7f, -0.6f);
    glEnd();

    if (night)
    {

        glBegin(GL_QUADS);
        glColor3ub(0,102,102);

        glVertex2f(0.65f, -0.7f);
        glVertex2f(0.55f, -0.7f);
        glVertex2f(0.5f, -0.6f);
        glVertex2f(0.7f, -0.6f);
        glEnd();
    }

//upper
    glBegin(GL_QUADS);
    glColor3ub(219,112,147);

    glVertex2f(0.65f, -0.6f);
    glVertex2f(0.65f, -0.56f);
    glVertex2f(0.54f, -0.56f);
    glVertex2f(0.54f, -0.6f);
    glEnd();
    if (night)
    {

        glBegin(GL_QUADS);
        glColor3ub(51,0,102);

        glVertex2f(0.65f, -0.6f);
        glVertex2f(0.65f, -0.56f);
        glVertex2f(0.54f, -0.56f);
        glVertex2f(0.54f, -0.6f);
        glEnd();
    }


//Triangle 1
    glBegin(GL_TRIANGLES);
    glColor3ub(255,228,196);

    glVertex2f(0.6f, -0.56f);
    glVertex2f(0.57f, -0.58f);
    glVertex2f(0.6f, -0.45f);

    glEnd();

    glLineWidth(0.3);
    glBegin(GL_LINES);
    glColor3ub(255,228,196);
    glVertex2f(0.6f, -0.56f);
    glVertex2f(0.6f, -0.6f);

    glEnd();

//Triangle 2
    glBegin(GL_TRIANGLES);
    glColor3ub(255,228,196);
    glVertex2f(0.61f, -0.56f);
    glVertex2f(0.64f, -0.58f);
    glVertex2f(0.61f, -0.45f);

    glEnd();

    glLineWidth(0.3);
    glBegin(GL_LINES);
    glColor3ub(255,228,196);
    glVertex2f(0.61f, -0.56f);
    glVertex2f(0.61f, -0.6f);

    glEnd();

    //Triangle 3
    glBegin(GL_TRIANGLES);
    glColor3ub(255,228,196);

    glVertex2f(0.63f, -0.56f);
    glVertex2f(0.66f, -0.58f);
    glVertex2f(0.63f, -0.5f);

    glEnd();

    glLineWidth(0.3);
    glBegin(GL_LINES);
    glColor3ub(255,228,196);
    glVertex2f(0.63f, -0.56f);
    glVertex2f(0.63f, -0.6f);

    glEnd();
    glPopMatrix();

    //Badha boat Lathi
    glBegin(GL_POLYGON);
    glColor3ub(139,69,19);

    glVertex2f(-0.14f, 0.22f);
    glVertex2f(-0.143f, 0.23f);
    glVertex2f(-0.1f, 0.33f);
    glVertex2f(-0.097f, 0.32f);
    glVertex2f(-0.14f, 0.22f);

    glEnd();
}

void bench2()
{
    //bench 1

    glPushMatrix();
    glTranslated(-0.45f,-0.02f,0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.33, 0.19, 0.19);

    glVertex2f(.11,-.238);
    glVertex2f(.10,-.244);

    glVertex2f(.11,-.33);
    glVertex2f(.10,-.327);

    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(0.80,0.52,0.25);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8,0.3,0.1);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();


    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.85, 0.83, 0.80);
    glVertex2f(.11,-.29);
    glVertex2f(.15,-.29);

    glVertex2f(.11,-.28);
    glVertex2f(.15,-.28);

    glVertex2f(.11,-.27);
    glVertex2f(.15,-.27);

    glVertex2f(.11,-.26);
    glVertex2f(.15,-.26);

    glVertex2f(.11,-.25);
    glVertex2f(.15,-.25);

    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);

    glVertex2f(.11,-.30);
    glVertex2f(.15,-.30);

    glVertex2f(.11,-.31);
    glVertex2f(.15,-.31);

    glVertex2f(.11,-.32);
    glVertex2f(.15,-.32);

    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);

    glEnd();
    glPopMatrix();



    glPushMatrix();
    glTranslated(-0.53f,-0.02f,0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.33, 0.19, 0.19);

    glVertex2f(.11,-.238);
    glVertex2f(.10,-.244);

    glVertex2f(.11,-.33);
    glVertex2f(.10,-.327);

    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(0.80,0.52,0.25);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8,0.3,0.1);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();


    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.85, 0.83, 0.80);
    glVertex2f(.11,-.29);
    glVertex2f(.15,-.29);

    glVertex2f(.11,-.28);
    glVertex2f(.15,-.28);

    glVertex2f(.11,-.27);
    glVertex2f(.15,-.27);

    glVertex2f(.11,-.26);
    glVertex2f(.15,-.26);

    glVertex2f(.11,-.25);
    glVertex2f(.15,-.25);

    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);

    glVertex2f(.11,-.30);
    glVertex2f(.15,-.30);

    glVertex2f(.11,-.31);
    glVertex2f(.15,-.31);

    glVertex2f(.11,-.32);
    glVertex2f(.15,-.32);

    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);

    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-0.64f,-0.02f,0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.33, 0.19, 0.19);

    glVertex2f(.11,-.238);
    glVertex2f(.10,-.244);

    glVertex2f(.11,-.33);
    glVertex2f(.10,-.327);

    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(0.80,0.52,0.25);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8,0.3,0.1);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();


    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.85, 0.83, 0.80);
    glVertex2f(.11,-.29);
    glVertex2f(.15,-.29);

    glVertex2f(.11,-.28);
    glVertex2f(.15,-.28);

    glVertex2f(.11,-.27);
    glVertex2f(.15,-.27);

    glVertex2f(.11,-.26);
    glVertex2f(.15,-.26);

    glVertex2f(.11,-.25);
    glVertex2f(.15,-.25);

    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);

    glVertex2f(.11,-.30);
    glVertex2f(.15,-.30);

    glVertex2f(.11,-.31);
    glVertex2f(.15,-.31);

    glVertex2f(.11,-.32);
    glVertex2f(.15,-.32);

    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);

    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.72f,-0.02f,0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.33, 0.19, 0.19);

    glVertex2f(.11,-.238);
    glVertex2f(.10,-.244);

    glVertex2f(.11,-.33);
    glVertex2f(.10,-.327);

    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(0.80,0.52,0.25);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8,0.3,0.1);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();


    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.85, 0.83, 0.80);
    glVertex2f(.11,-.29);
    glVertex2f(.15,-.29);

    glVertex2f(.11,-.28);
    glVertex2f(.15,-.28);

    glVertex2f(.11,-.27);
    glVertex2f(.15,-.27);

    glVertex2f(.11,-.26);
    glVertex2f(.15,-.26);

    glVertex2f(.11,-.25);
    glVertex2f(.15,-.25);

    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);

    glVertex2f(.11,-.30);
    glVertex2f(.15,-.30);

    glVertex2f(.11,-.31);
    glVertex2f(.15,-.31);

    glVertex2f(.11,-.32);
    glVertex2f(.15,-.32);

    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);

    glEnd();
    glPopMatrix();



}



void sea()
{

    glBegin(GL_QUADS);
    glColor3ub(100,182,236); //Color
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.4f);
    glVertex2f(-1.0f, -0.4f);
    glColor3ub(100,182,236);

    glEnd();
    if(night)
    {
        glBegin(GL_QUADS);
        glColor3ub(70, 130, 180);

        // glColor3ub(100,182,236); //Color
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, -0.4f);
        glVertex2f(-1.0f, -0.4f);
        //glColor3ub(100,182,236);
        glEnd();
    }

    //River_upper

    glBegin(GL_POLYGON);
    glColor3ub(100,182,236);
    glVertex2f(-0.2f,-0.4f);
    glVertex2f(0.35f,-0.4f);
    glVertex2f(0.4f,-0.22f);
    glVertex2f(-0.25f,-0.22f);
    glVertex2f(-0.2f,-0.4f);

    glEnd();

    if(night)
    {

        glBegin(GL_POLYGON);
        glColor3ub(70, 130, 180);
        glVertex2f(-0.2f,-0.4f);
        glVertex2f(0.35f,-0.4f);
        glVertex2f(0.4f,-0.22f);
        glVertex2f(-0.25f,-0.22f);
        glVertex2f(-0.2f,-0.4f);

        glEnd();

    }

    glBegin(GL_POLYGON);
    glColor3ub(100,182,236);
    glVertex2f(-0.25f,-0.22f);
    glVertex2f(-0.1f,0.2f);
    glVertex2f(0.26f,0.2f);
    glVertex2f(0.4f,-0.22f);
    glVertex2f(-0.25f,-0.22f);

    glEnd();

    if(night)
    {

        glBegin(GL_POLYGON);
        glColor3ub(70,130,180);

        glVertex2f(-0.25f,-0.22f);
        glVertex2f(-0.1f,0.2f);
        glVertex2f(0.26f,0.2f);
        glVertex2f(0.4f,-0.22f);
        glVertex2f(-0.25f,-0.22f);

        glEnd();



    }


    glBegin(GL_POLYGON);
    glColor3ub(100,182,236);
    glVertex2f(-0.1f,0.2f);
    glVertex2f(0.26f,0.2f);
    glVertex2f(0.29f,0.35f);
    glVertex2f(-0.12f,0.4f);
    glVertex2f(-0.1f,0.2f);

    glEnd();
    if(night)
    {

        glBegin(GL_POLYGON);
        glColor3ub(70,130,180);

        glVertex2f(-0.1f,0.2f);
        glVertex2f(0.26f,0.2f);
        glVertex2f(0.29f,0.35f);
        glVertex2f(-0.12f,0.4f);
        glVertex2f(-0.1f,0.2f);
        glEnd();
    }


    glBegin(GL_POLYGON);
    glColor3ub(100,182,236);
    glVertex2f(-0.12f,0.4f);
    glVertex2f(0.12f,0.5f);
    glVertex2f(0.35f,0.5f);
    glVertex2f(0.29f,0.35f);
    glVertex2f(-0.12f,0.4f);

    glEnd();

    if(night)
    {

        glBegin(GL_POLYGON);
        glColor3ub(70,130,180);

        glVertex2f(-0.12f,0.4f);
        glVertex2f(0.12f,0.5f);
        glVertex2f(0.35f,0.5f);
        glVertex2f(0.29f,0.35f);
        glVertex2f(-0.12f,0.4f);

        glEnd();

    }
}

void wave()  //id4
{

    glLoadIdentity();
    glColor3ub(190,230,250); // Clear the color buffer (background)
    // glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(0.0f,move_wave, 0.0f);//for move
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glVertex2f(-1.0f,-0.95f);
    glVertex2f(-1.0f,-0.97f);
    glVertex2f(1.0f,-0.98f);
    glVertex2f(1.0f,-0.975f);
    glEnd();

    glColor3ub(190,230,250); // Clear the color buffer (background)
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glVertex2f(-1.0f,-0.9f);
    glVertex2f(-1.0f,-0.92f);
    glVertex2f(1.0f,-0.93f);
    glVertex2f(1.0f,-0.925f);
    glEnd();

    glColor3ub(190,230,250); // Clear the color buffer (background)
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glVertex2f(-1.0f,-0.85f);
    glVertex2f(-1.0f,-0.87f);
    glVertex2f(1.0f,-0.88f);
    glVertex2f(1.0f,-0.875f);
    glEnd();

    glColor3ub(190,230,250); // Clear the color buffer (background)
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glVertex2f(-1.0f,-0.8f);
    glVertex2f(-1.0f,-0.82f);
    glVertex2f(1.0f,-0.83f);
    glVertex2f(1.0f,-0.825f);
    glEnd();

    glColor3ub(190,230,250); // Clear the color buffer (background)
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glVertex2f(-1.0f,-0.7f);
    glVertex2f(-1.0f,-0.72f);
    glVertex2f(1.0f,-0.73f);
    glVertex2f(1.0f,-0.725f);
    glEnd();

    glColor3ub(190,230,250); // Clear the color buffer (background)
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glVertex2f(-1.0f,-0.6f);
    glVertex2f(-1.0f,-0.62f);
    glVertex2f(1.0f,-0.63f);
    glVertex2f(1.0f,-0.625f);
    glEnd();

    glColor3ub(190,230,250); // Clear the color buffer (background)
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glVertex2f(-1.0f,-0.5f);
    glVertex2f(-1.0f,-0.52f);
    glVertex2f(1.0f,-0.53f);
    glVertex2f(1.0f,-0.525f);
    glEnd();

    glColor3ub(190,230,250); // Clear the color buffer (background)
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glVertex2f(-1.0f,-0.45f);
    glVertex2f(-1.0f,-0.47f);
    glVertex2f(1.0f,-0.48f);
    glVertex2f(1.0f,-0.475f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f,-0.36f);
    glVertex2f(-0.2f,-0.37f);
    glVertex2f(0.35f,-0.38f);
    glVertex2f(0.35f,-0.375f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.22f,-0.3f);
    glVertex2f(-0.22f,-0.31f);
    glVertex2f(0.35f,-0.32f);
    glVertex2f(0.35f,-0.315f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.23f,-0.27f);
    glVertex2f(-0.23f,-0.275f);
    glVertex2f(0.37f,-0.28f);
    glVertex2f(0.37f,-0.285f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.22f,-0.23f);
    glVertex2f(-0.22f,-0.22f);
    glVertex2f(0.37f,-0.23f);
    glVertex2f(0.37f,-0.235f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f,-0.17f);
    glVertex2f(-0.2f,-0.18f);
    glVertex2f(0.35f,-0.19f);
    glVertex2f(0.35f,-0.185f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f,-0.1f);
    glVertex2f(-0.2f,-0.12f);
    glVertex2f(0.35f,-0.13f);
    glVertex2f(0.35f,-0.125f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f,0.0f);
    glVertex2f(-0.1f,0.02f);
    glVertex2f(0.3f,0.03f);
    glVertex2f(0.35f,0.025f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f,0.1f);
    glVertex2f(-0.1f,0.12f);
    glVertex2f(0.25f,0.117f);
    glVertex2f(0.25f,0.115f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f,0.15f);
    glVertex2f(-0.1f,0.16f);
    glVertex2f(0.25f,0.159f);
    glVertex2f(0.25f,0.165f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f,0.21f);
    glVertex2f(-0.1f,0.22f);
    glVertex2f(0.26f,0.219f);
    glVertex2f(0.26f,0.225f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.11f,0.31f);
    glVertex2f(-0.11f,0.32f);
    glVertex2f(0.28f,0.32f);
    glVertex2f(0.28f,0.328f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.01f,0.37f);
    glVertex2f(-0.01f,0.38f);
    glVertex2f(0.28f,0.38f);
    glVertex2f(0.28f,0.388f);
    glEnd();

    glColor3ub(190,230,250);
    glBegin(GL_POLYGON);
    glVertex2f(0.1f,0.42f);
    glVertex2f(0.1f,0.425f);
    glVertex2f(0.32f,0.435f);
    glVertex2f(0.32f,0.4255f);
    glEnd();

    glPopMatrix();

}

void update_wave(int value) //id40
{
    move_wave += 0.01; //assume as moving speed
    if(move_wave>0.075) //water layer -35 |-45+13=-32
    {
        move_wave =-0.01;//-32+20=-52 then start form -52
    }
    glutPostRedisplay();
    glutTimerFunc(200, update_wave, 0);
}

GLfloat ship_position = 0.1f;
GLfloat ship_speed = 0.01f;
void updateShip(int value)
{


    if(ship_position >1.0)

        ship_position = -1.0f;


    ship_position += ship_speed;


    glutPostRedisplay();

    glutTimerFunc(100, updateShip, 0);

}

void ship()
{

    glPushMatrix();
    glTranslatef(ship_position,0.0f, 0.0f);
// lower 1
    glBegin(GL_POLYGON);
    glColor3ub(119,136,153); //Color
    glVertex2f(0.11f, -0.95f);
    glVertex2f(0.33f, -0.95f);
    glVertex2f(0.39f, -0.74f);
    glVertex2f(0.31f, -0.74f);
    glVertex2f(0.3f, -0.81f);
    glVertex2f(0.05f, -0.81f);
    glEnd();

    if(night)
    {

        glBegin(GL_POLYGON);
        glColor3ub(64,64,64); //Color
        glVertex2f(0.11f, -0.95f);
        glVertex2f(0.33f, -0.95f);
        glVertex2f(0.39f, -0.74f);
        glVertex2f(0.31f, -0.74f);
        glVertex2f(0.3f, -0.81f);
        glVertex2f(0.05f, -0.81f);
        glEnd();


    }


    if (winter)
    {

        glBegin(GL_QUADS);
        glColor3ub(255,255,255);
        glVertex2f(0.05f, -0.81f);
        glVertex2f(0.11f, -0.81f);
        glVertex2f(0.13f, -0.72f);
        glVertex2f(0.1f, -0.72f);
        glVertex2f(0.11f, -0.8f);
        glVertex2f(0.05f, -0.8f);


        glEnd();

    }
//lower 2
    glBegin(GL_POLYGON);
    glColor3ub(188,143,143); //Color
    glVertex2f(0.11f, -0.81f);
    glVertex2f(0.13f, -0.72f);
    glVertex2f(0.35f, -0.72f);
    glVertex2f(0.37f, -0.74f);
    glVertex2f(0.31f, -0.74);
    glVertex2f(0.3f, -0.81f);
    glEnd();

    if(night)
    {

        glBegin(GL_POLYGON);
        glColor3ub(128,128,128); //Color
        glVertex2f(0.11f, -0.81f);
        glVertex2f(0.13f, -0.72f);
        glVertex2f(0.35f, -0.72f);
        glVertex2f(0.37f, -0.74f);
        glVertex2f(0.31f, -0.74);
        glVertex2f(0.3f, -0.81f);
        glEnd();

    }

    if (winter)
    {

        glBegin(GL_POLYGON);
        glColor3ub(255,255,255);
        glVertex2f(0.13f, -0.72f);
        glVertex2f(0.15f, -0.72f);
        glVertex2f(0.17f, -0.67f);
        glVertex2f(0.16f, -0.67f);
        glVertex2f(0.15f, -0.7f);
        glVertex2f(0.13f, -0.7f);

        glEnd();

    }
//
// if (winter)
//    {
//
//      glBegin(GL_POLYGON);
//    glColor3ub(255,255,255);
//    glVertex2f(-0.,0.51);
//    glVertex2f(-0.699,0.52);
//    glVertex2f(-0.72f, 0.53f);
//    glVertex2f(-0.8f, 0.511f);
//    glVertex2f(-0.9,0.53);
//    glEnd();
//
//    }
//upper 1
    glBegin(GL_QUADS);
    glColor3ub(255,239,213); //Color
    glVertex2f(0.15f, -0.72f);
    glVertex2f(0.17f, -0.67f);
    glVertex2f(0.31f, -0.67f);
    glVertex2f(0.33f, -0.72f);

    glEnd();

    if (winter)
    {

        glBegin(GL_QUADS);
        glColor3ub(255,255,255);
        glVertex2f(0.17f, -0.67f);
        glVertex2f(0.2f, -0.67f);
        glVertex2f(0.2f, -0.62f);
        glVertex2f(0.18f, -0.62f);

        glEnd();

    }

//upper 2
    glBegin(GL_QUADS);
    glColor3ub(244,164,96); //Color
    glVertex2f(0.2f, -0.67f);
    glVertex2f(0.2f, -0.62f);
    glVertex2f(0.26f, -0.62f);
    glVertex2f(0.29f, -0.67f);

    glEnd();

    if (winter)
    {

        glBegin(GL_POLYGON);
        glColor3ub(255,255,255);
        glVertex2f(0.39f, -0.74f);
        glVertex2f(0.37f, -0.74f);
        glVertex2f(0.35f, -0.72f);
        glVertex2f(0.33f, -0.72f);
        glVertex2f(0.31f, -0.67f);
        glVertex2f(0.29f, -0.67f);
        glVertex2f(0.26f, -0.62f);
        glVertex2f(0.28f, -0.62f);
        glVertex2f(0.39f, -0.74f);

        glEnd();

    }


//ship circles
//circle 1
    int x;

    GLfloat p2=0.14f;
    GLfloat q2= -0.88f;
    GLfloat r2 = 0.021f;
    int tringle3=40;

    GLfloat tp3 =2.0f * PI  ;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub ( 240,255,255);
    glVertex2f (p2,q2);
    for(x= 0; x<=tringle3; x++)
    {
        glVertex2f (
            p2+(r2*cos(x*tp3/tringle3)),
            q2+(r2*sin(x*tp3/tringle3))
        );


    }
    glEnd ();


    //circle 2

    int i;

    GLfloat p1=0.19f;
    GLfloat q1=-0.88f;
    GLfloat r1 = 0.021f;
    int tringle2=40;

    GLfloat tp2 =2.0f * PI  ;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub ( 240,255,255);
    glVertex2f (p1,q1);
    for(i= 0; i<=tringle2; i++)
    {
        glVertex2f (
            p1+(r1*cos(i*tp2/tringle2)),
            q1+(r1*sin(i*tp2/tringle2))
        );


    }
    glEnd ();

    //circle 3
    int y;

    GLfloat p3=0.24f;
    GLfloat q3=-0.88f;
    GLfloat r3 = 0.021f;
    int tringle4=40;

    GLfloat tp4 =2.0f * PI  ;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub ( 240,255,255);
    glVertex2f (p3,q3);
    for(y= 0; y<=tringle3; y++)
    {
        glVertex2f (
            p3+(r3*cos(y*tp4/tringle4)),
            q2+(r3*sin(y*tp4/tringle4))
        );


    }
    glEnd ();

    //circle 4
    int a;

    GLfloat a2=0.29f;
    GLfloat b2=-0.88f;
    GLfloat radius2 = 0.021f;
    int tringle5=40;

    GLfloat tp13 =2.0f * PI  ;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub ( 240,255,255);
    glVertex2f (a2,b2);
    for(a= 0; a<=tringle5; a++)
    {
        glVertex2f (
            a2+(radius2*cos(a*tp13/tringle5)),
            b2+(radius2*sin(a*tp13/tringle5))
        );


    }
    glEnd ();

//ship windows
//window1
    glBegin(GL_QUADS);
    glColor3ub(255,255,255); //Color
    glVertex2f(0.13f, -0.79f);
    glVertex2f(0.13f, -0.75f);
    glVertex2f(0.15f, -0.75f);
    glVertex2f(0.15f, -0.79f);

    glEnd();

    if(night)
    {

        glBegin(GL_QUADS);
        glColor3ub(255,255,102); //Color
        glVertex2f(0.13f, -0.79f);
        glVertex2f(0.13f, -0.75f);
        glVertex2f(0.15f, -0.75f);
        glVertex2f(0.15f, -0.79f);


    }

//window2
    glBegin(GL_QUADS);
    glColor3ub(255,255,255); //Color
    glVertex2f(0.16f, -0.79f);
    glVertex2f(0.16f, -0.75f);
    glVertex2f(0.18f, -0.75f);
    glVertex2f(0.18f, -0.79f);

    glEnd();

    if(night)
    {

        glBegin(GL_QUADS);
        glColor3ub(255,255,102); //Color
        glVertex2f(0.16f, -0.79f);
        glVertex2f(0.16f, -0.75f);
        glVertex2f(0.18f, -0.75f);
        glVertex2f(0.18f, -0.79f);

        glEnd();
    }

//window3
    glBegin(GL_QUADS);
    glColor3ub(255,255,255); //Color
    glVertex2f(0.19f, -0.79f);
    glVertex2f(0.19f, -0.75f);
    glVertex2f(0.21f, -0.75f);
    glVertex2f(0.21f, -0.79f);

    glEnd();

    if(night)
    {

        glBegin(GL_QUADS);
        glColor3ub(255,255,102); //Color
        glVertex2f(0.19f, -0.79f);
        glVertex2f(0.19f, -0.75f);
        glVertex2f(0.21f, -0.75f);
        glVertex2f(0.21f, -0.79f);

        glEnd();
    }

//window4
    glBegin(GL_QUADS);
    glColor3ub(255,255,255); //Color
    glVertex2f(0.22f, -0.79f);
    glVertex2f(0.22f, -0.75f);
    glVertex2f(0.24, -0.75f);
    glVertex2f(0.24f, -0.79f);

    glEnd();

    if(night)
    {

        glBegin(GL_QUADS);
        glColor3ub(255,255,102); //Color
        glVertex2f(0.22f, -0.79f);
        glVertex2f(0.22f, -0.75f);
        glVertex2f(0.24, -0.75f);
        glVertex2f(0.24f, -0.79f);


        glEnd();
    }

//window5
    glBegin(GL_QUADS);
    glColor3ub(255,255,255); //Color
    glVertex2f(0.25f, -0.79f);
    glVertex2f(0.25f, -0.75f);
    glVertex2f(0.27, -0.75f);
    glVertex2f(0.27f, -0.79f);

    glEnd();

    if(night)
    {

        glBegin(GL_QUADS);
        glColor3ub(255,255,102); //Color
        glVertex2f(0.25f, -0.79f);
        glVertex2f(0.25f, -0.75f);
        glVertex2f(0.27, -0.75f);
        glVertex2f(0.27f, -0.79f);

        glEnd();

    }
//window6
    glBegin(GL_QUADS);
    glColor3ub(255,255,255); //Color
    glVertex2f(0.28f, -0.79f);
    glVertex2f(0.28f, -0.75f);
    glVertex2f(0.3, -0.75f);
    glVertex2f(0.3f, -0.79f);

    glEnd();
    if(night)
    {

        glBegin(GL_QUADS);
        glColor3ub(255,255,102); //Color
        glVertex2f(0.28f, -0.79f);
        glVertex2f(0.28f, -0.75f);
        glVertex2f(0.3, -0.75f);
        glVertex2f(0.3f, -0.79f);


        glEnd();

    }

//ship upperclosewindow
//window1
    glBegin(GL_QUADS);
    glColor3ub(105,105,105); //Color
    glVertex2f(0.2f, -0.71f);
    glVertex2f(0.2f, -0.68f);
    glVertex2f(0.315, -0.68f);
    glVertex2f(0.327f, -0.71f);

    glEnd();

    if(night)
    {

        glBegin(GL_QUADS);
        glColor3ub(255,255,153); //Color
        glVertex2f(0.2f, -0.71f);
        glVertex2f(0.2f, -0.68f);
        glVertex2f(0.315, -0.68f);
        glVertex2f(0.327f, -0.71f);

        glEnd();

    }

    glBegin(GL_LINES);
    glColor3ub(255,250,250); //Color
    glVertex2f(0.24f, -0.71f);
    glVertex2f(0.24f, -0.68f);

    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255,250,250); //Color
    glVertex2f(0.28f, -0.71f);
    glVertex2f(0.28f, -0.68f);

    glEnd();

//left stick
    glBegin(GL_QUADS);
    glColor3ub(65,105,225); //Color
    glVertex2f(0.22f, -0.62f);
    glVertex2f(0.21f, -0.62f);
    glVertex2f(0.21f, -0.58f);
    glVertex2f(0.22f, -0.58f);

    glEnd();

//Middle stick
    glBegin(GL_QUADS);
    glColor3ub(240,230,140); //Color
    glVertex2f(0.24f, -0.62f);
    glVertex2f(0.23f, -0.62f);
    glVertex2f(0.23f, -0.54f);
    glVertex2f(0.24f, -0.54f);

    glEnd();

//Right stick
    glBegin(GL_QUADS);
    glColor3ub(250,128,114); //Color
    glVertex2f(0.25f, -0.62f);
    glVertex2f(0.245f, -0.62f);
    glVertex2f(0.245f, -0.56f);
    glVertex2f(0.25f, -0.56f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(255,69,0); //Color
    glVertex2f(0.245f, -0.562f);
    glVertex2f(0.245f, -0.53f);
    glVertex2f(0.28f, -0.548f);

    glEnd();


//    if(winter)
//    {
//
//    }
    glPopMatrix();
}


void handleMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        ship_speed += 0.01f;
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        ship_speed = 0.0f;
    }
}


void bench1()
{

//bench 1

    glPushMatrix();
    glTranslated(0.36f,0.02f,0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.33, 0.19, 0.19);

    glVertex2f(.11,-.238);
    glVertex2f(.10,-.244);

    glVertex2f(.11,-.33);
    glVertex2f(.10,-.327);

    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(0.80,0.52,0.25);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8,0.3,0.1);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();


    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(0,255,255);
    glVertex2f(.11,-.29);
    glVertex2f(.15,-.29);

    glVertex2f(.11,-.28);
    glVertex2f(.15,-.28);

    glVertex2f(.11,-.27);
    glVertex2f(.15,-.27);

    glVertex2f(.11,-.26);
    glVertex2f(.15,-.26);

    glVertex2f(.11,-.25);
    glVertex2f(.15,-.25);

    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);

    glVertex2f(.11,-.30);
    glVertex2f(.15,-.30);

    glVertex2f(.11,-.31);
    glVertex2f(.15,-.31);

    glVertex2f(.11,-.32);
    glVertex2f(.15,-.32);

    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);

    glEnd();
    glPopMatrix();


    //bench 2

    glPushMatrix();
    glTranslated(0.53f,0.02f,0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.33, 0.19, 0.19);

    glVertex2f(.11,-.238);
    glVertex2f(.10,-.244);

    glVertex2f(.11,-.33);
    glVertex2f(.10,-.327);

    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(0.80,0.52,0.25);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8,0.3,0.1);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();


    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(0,255,255);
    glVertex2f(.11,-.29);
    glVertex2f(.15,-.29);

    glVertex2f(.11,-.28);
    glVertex2f(.15,-.28);

    glVertex2f(.11,-.27);
    glVertex2f(.15,-.27);

    glVertex2f(.11,-.26);
    glVertex2f(.15,-.26);

    glVertex2f(.11,-.25);
    glVertex2f(.15,-.25);

    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);

    glVertex2f(.11,-.30);
    glVertex2f(.15,-.30);

    glVertex2f(.11,-.31);
    glVertex2f(.15,-.31);

    glVertex2f(.11,-.32);
    glVertex2f(.15,-.32);

    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);

    glEnd();
    glPopMatrix();

    //bench 3

    glPushMatrix();
    glTranslated(0.45f,0.02f,0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.33, 0.19, 0.19);

    glVertex2f(.11,-.238);
    glVertex2f(.10,-.244);

    glVertex2f(.11,-.33);
    glVertex2f(.10,-.327);

    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(0.80,0.52,0.25);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8,0.3,0.1);
    glVertex2f(.12,-.21);
    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);
    glVertex2f(.16,-.21);
    glEnd();


    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(0,255,255);
    glVertex2f(.11,-.29);
    glVertex2f(.15,-.29);

    glVertex2f(.11,-.28);
    glVertex2f(.15,-.28);

    glVertex2f(.11,-.27);
    glVertex2f(.15,-.27);

    glVertex2f(.11,-.26);
    glVertex2f(.15,-.26);

    glVertex2f(.11,-.25);
    glVertex2f(.15,-.25);

    glVertex2f(.11,-.24);
    glVertex2f(.15,-.24);

    glVertex2f(.11,-.30);
    glVertex2f(.15,-.30);

    glVertex2f(.11,-.31);
    glVertex2f(.15,-.31);

    glVertex2f(.11,-.32);
    glVertex2f(.15,-.32);

    glVertex2f(.11,-.33);
    glVertex2f(.15,-.33);

    glEnd();

    glPopMatrix();

}



void tree()
{

    glPushMatrix();
    // glTranslatef(boat_position,0,0);
//        glPushMatrix();
    glTranslatef(-1.09f, -0.42f, 0.0f);
    glScalef(0.25,0.4,0);
    glBegin(GL_QUADS);                 // Each set of 4 vertices form a quad
    glColor3ub(153,76,0); // Tree
    glVertex2f(0.7f, 0.18f);    // x, y
    glVertex2f(0.75f,0.18f);    // x, y
    glVertex2f(0.75f, 0.35f);
    glVertex2f(0.7f, 0.35f);

    glEnd();


    glBegin(GL_TRIANGLES);              // Each set of 4 vertices form a quad
    glColor3ub(34,139,34); // Tree Traiangle 1
    glVertex2f(0.55f, 0.35f);    // x, y
    glVertex2f(0.9f,0.35f);    // x, y
    glVertex2f(0.725f, 0.6f);

    glEnd();

    glBegin(GL_TRIANGLES);              // Each set of 4 vertices form a quad
    glColor3ub(34,139,34); // Tree Traiangle 2
    glVertex2f(0.58f, 0.47f);    // x, y
    glVertex2f(0.87f,0.47f);    // x, y
    glVertex2f(0.725f, 0.7f);

    glEnd();

    glPopMatrix();


    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.64f, 0.2f);
    glVertex2f(-0.64f, 0.3f);
    glVertex2f(-0.65f, 0.3f);
    glVertex2f(-0.65f, 0.2f);
    glEnd();


    GLfloat xt01=-0.645f; //upper circle
    GLfloat yt01=0.3f;
    GLfloat radiust01 =0.035f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt01, yt01);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt01 + (radiust01 * cos(i *  twicePi / triangleAmount)),
                    yt01 + (radiust01 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


    GLfloat xt02=-0.645f; //middle circle
    GLfloat yt02=0.33f;
    GLfloat radiust02 =0.034f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt02, yt02);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt02 + (radiust02 * cos(i *  twicePi / triangleAmount)),
                    yt02 + (radiust02 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    GLfloat xt03=-0.645f;
    GLfloat yt03=0.36f;
    GLfloat radiust03 =0.027f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt03, yt03);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt03 + (radiust03 * cos(i *  twicePi / triangleAmount)),
                    yt03 + (radiust03 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glPushMatrix();
    // glTranslatef(boat_position,0,0);
//        glPushMatrix();
    glTranslatef(-0.17f, -0.55f, 0.0f);
    //glScalef(0.25,0.4,0);
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.64f, 0.2f);
    glVertex2f(-0.64f, 0.3f);
    glVertex2f(-0.65f, 0.3f);
    glVertex2f(-0.65f, 0.2f);
    glEnd();


    GLfloat xt11=-0.645f; //upper circle
    GLfloat yt11=0.3f;
    GLfloat radiust11 =0.035f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt11, yt11);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt11 + (radiust11 * cos(i *  twicePi / triangleAmount)),
                    yt11 + (radiust11 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


    GLfloat xt12=-0.645f; //middle circle
    GLfloat yt12=0.33f;
    GLfloat radiust12 =0.034f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt12, yt12);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt12 + (radiust12 * cos(i *  twicePi / triangleAmount)),
                    yt12 + (radiust12 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    GLfloat xt13=-0.645f;
    GLfloat yt13=0.36f;
    GLfloat radiust13 =0.027f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt13, yt13);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt13 + (radiust13 * cos(i *  twicePi / triangleAmount)),
                    yt13 + (radiust13 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glPopMatrix();


    glPushMatrix();
    // glTranslatef(boat_position,0,0);
//        glPushMatrix();
    glTranslatef(-0.07f, -0.55f, 0.0f);
    //glScalef(0.25,0.4,0);
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.64f, 0.2f);
    glVertex2f(-0.64f, 0.3f);
    glVertex2f(-0.65f, 0.3f);
    glVertex2f(-0.65f, 0.2f);
    glEnd();


    GLfloat xt15=-0.645f; //upper circle
    GLfloat yt15=0.3f;
    GLfloat radiust15 =0.035f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt15, yt15);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt15 + (radiust15 * cos(i *  twicePi / triangleAmount)),
                    yt15 + (radiust15 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


    GLfloat xt17=-0.645f; //middle circle
    GLfloat yt17=0.33f;
    GLfloat radiust17 =0.034f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt17, yt17);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt17 + (radiust17 * cos(i *  twicePi / triangleAmount)),
                    yt17 + (radiust17 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    GLfloat xt19=-0.645f;
    GLfloat yt19=0.36f;
    GLfloat radiust19 =0.027f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt19, yt19);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt19 + (radiust19 * cos(i *  twicePi / triangleAmount)),
                    yt19 + (radiust19 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glPopMatrix();

    ////tree2 left most side
    //................................................

    glBegin(GL_QUADS);//root
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.96f, 0.2f);
    glVertex2f(-0.96f, 0.35f);
    glVertex2f(-0.95f, 0.35f);
    glVertex2f(-0.95f, 0.2f);
    glEnd();


    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.02f, 0.02f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.03f, 0.02f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.04f, 0.02f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.04f, 0.01f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.02f, 0.01f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();
    glPopMatrix();



//

    GLfloat xt4=-0.955f;//first circle
    GLfloat yt4=0.4f;
    GLfloat radiust4 =0.0288f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt4, yt4);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt4 + (radiust4 * cos(i *  twicePi / triangleAmount)),
                    yt4 + (radiust4 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    GLfloat xt5=-0.955f;//second circle
    GLfloat yt5=0.37f;
    GLfloat radiust5 =0.03f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt5, yt5);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt5 + (radiust5 * cos(i *  twicePi / triangleAmount)),
                    yt5 + (radiust5 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    GLfloat xt6=-0.955f;
    GLfloat yt6=0.34f;
    GLfloat radiust6 =0.035f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt6, yt6);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt6 + (radiust6 * cos(i *  twicePi / triangleAmount)),
                    yt6 + (radiust6 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

}
void tree1()
{
    glPushMatrix();
    // glTranslatef(boat_position,0,0);
//        glPushMatrix();
    glTranslatef(0.25f, 0.05f, 0.0f);
    //glScalef(0.25,0.4,0);
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.64f, 0.2f);
    glVertex2f(-0.64f, 0.3f);
    glVertex2f(-0.65f, 0.3f);
    glVertex2f(-0.65f, 0.2f);
    glEnd();


    GLfloat xt11=-0.645f; //upper circle
    GLfloat yt11=0.3f;
    GLfloat radiust11 =0.035f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt11, yt11);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt11 + (radiust11 * cos(i *  twicePi / triangleAmount)),
                    yt11 + (radiust11 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


    GLfloat xt12=-0.645f; //middle circle
    GLfloat yt12=0.33f;
    GLfloat radiust12 =0.034f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt12, yt12);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt12 + (radiust12 * cos(i *  twicePi / triangleAmount)),
                    yt12 + (radiust12 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    GLfloat xt13=-0.645f;
    GLfloat yt13=0.36f;
    GLfloat radiust13 =0.027f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt13, yt13);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt13 + (radiust13 * cos(i *  twicePi / triangleAmount)),
                    yt13 + (radiust13 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glPopMatrix();


    glPushMatrix();
    // glTranslatef(boat_position,0,0);
//        glPushMatrix();
    glTranslatef(0.45f, 0.01f, 0.0f);
    //glScalef(0.25,0.4,0);
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.64f, 0.2f);
    glVertex2f(-0.64f, 0.3f);
    glVertex2f(-0.65f, 0.3f);
    glVertex2f(-0.65f, 0.2f);
    glEnd();


    GLfloat xt15=-0.645f; //upper circle
    GLfloat yt15=0.3f;
    GLfloat radiust15 =0.035f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt15, yt15);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt15 + (radiust15 * cos(i *  twicePi / triangleAmount)),
                    yt15 + (radiust15 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


    GLfloat xt17=-0.645f; //middle circle
    GLfloat yt17=0.33f;
    GLfloat radiust17 =0.034f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt17, yt17);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt17 + (radiust17 * cos(i *  twicePi / triangleAmount)),
                    yt17 + (radiust17 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    GLfloat xt19=-0.645f;
    GLfloat yt19=0.36f;
    GLfloat radiust19 =0.027f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt19, yt19);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt19 + (radiust19 * cos(i *  twicePi / triangleAmount)),
                    yt19 + (radiust19 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glPopMatrix();

    ////tree2 left most side
    //................................................

    glBegin(GL_QUADS);//root
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.96f, 0.2f);
    glVertex2f(-0.96f, 0.35f);
    glVertex2f(-0.95f, 0.35f);
    glVertex2f(-0.95f, 0.2f);
    glEnd();


    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.02f, 0.02f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.03f, 0.02f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4f, 0.2f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4f, 0.1f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2f, 0.1f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.95f, 0.2f);
    glVertex2f(-0.945f, 0.25f);
    glVertex2f(-0.938f, 0.2f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.955f, 0.26f);
    glVertex2f(-0.958f, 0.2f);

    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-0.945f, 0.2f);
    glVertex2f(-0.935f, 0.26f);
    glVertex2f(-0.938f, 0.2f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
// glTranslatef(boat_position,0,0);
//        glPushMatrix();
    glTranslatef(1.5f, 0.04f, 0.0f);
    glScalef(0.9, 0.7, 0);
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.64f, 0.2f);
    glVertex2f(-0.64f, 0.3f);
    glVertex2f(-0.65f, 0.3f);
    glVertex2f(-0.65f, 0.2f);
    glEnd();


    GLfloat xt28=-0.645f; //upper circle
    GLfloat yt28=0.3f;
    GLfloat radiust28 =0.035f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt28, yt28);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt28 + (radiust28 * cos(i *  twicePi / triangleAmount)),
                    yt28 + (radiust28 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();


    GLfloat xt30=-0.645f; //middle circle
    GLfloat yt30=0.33f;
    GLfloat radiust30 =0.034f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt30, yt30);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt30 + (radiust30 * cos(i *  twicePi / triangleAmount)),
                    yt30 + (radiust30 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    GLfloat xt29=-0.645f;
    GLfloat yt29=0.36f;
    GLfloat radiust29 =0.027f;
    glColor3f(0.0f,0.2f,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xt29, yt29);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xt29 + (radiust29 * cos(i *  twicePi / triangleAmount)),
                    yt29 + (radiust29 * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glPopMatrix();

}

void downLamp()
{

// lamp part02<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    glPushMatrix();
    glTranslatef(-0.1f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.85f, 0.12f);


        glEnd();
    }
    glPopMatrix();


    //..

    glPushMatrix();
    glTranslatef(0.1f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.85f, 0.12f);


        glEnd();
    }
    glPopMatrix();

    //..

    glPushMatrix();
    glTranslatef(0.3f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.85f, 0.12f);


        glEnd();
    }
    glPopMatrix();

    //..

    glPushMatrix();
    glTranslatef(0.5f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.85f, 0.12f);


        glEnd();
    }
    glPopMatrix();

    //..

    glPushMatrix();
    glTranslatef(0.7f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.85f, 0.12f);


        glEnd();
    }
    glPopMatrix();


    //..

    glPushMatrix();
    glTranslatef(0.9f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.85f, 0.12f);


        glEnd();
    }
    glPopMatrix();


//..

    glPushMatrix();
    glTranslatef(1.1f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.85f, 0.12f);


        glEnd();
    }
    glPopMatrix();


    //..

    glPushMatrix();
    glTranslatef(1.3f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.85f, 0.12f);


        glEnd();
    }
    glPopMatrix();


    //..

    glPushMatrix();
    glTranslatef(1.5f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.85f, 0.12f);


        glEnd();
    }
    glPopMatrix();


    //..

    glPushMatrix();
    glTranslatef(1.7f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.2f,0.2f,0.2f);
        glVertex2f(-0.85f, 0.12f);

        glEnd();
    }
    glPopMatrix();



    glPushMatrix();
    glTranslatef(1.9f,-0.22f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);

    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    glPopMatrix();
}


////////////////////////labiba//////////////////

void house1()
{

    //house1
    glBegin(GL_POLYGON);
    glColor3ub(238,118,0);  //house main box
    glVertex2f(-0.9f, 0.2f);
    glVertex2f(-0.9f, 0.5f);
    glVertex2f(-0.7f, 0.5f);
    glVertex2f(-0.7f, 0.2f);
    glEnd();


    glLineWidth(12);//upper house line
    glBegin(GL_LINES);
    glColor3f(0.2, 0.0, 0.0);
    glVertex2f(-0.9,0.5);
    glVertex2f(-0.699,0.5);
    glEnd();

    if (winter)
    {
        glLineWidth(12);//upper house line
        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(-0.9,0.5);
        glVertex2f(-0.699,0.5);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(255,255,255);
        glVertex2f(-0.9,0.51);
        glVertex2f(-0.699,0.52);
        glVertex2f(-0.72f, 0.53f);
        glVertex2f(-0.8f, 0.511f);
        glVertex2f(-0.9,0.53);
        glEnd();

    }


//windos...................................................................................................
    glBegin(GL_QUADS);//upper small window middle
    glColor3f(1.0f,1.0f,1.0f);

    glVertex2f(-0.808f, 0.43f);
    glVertex2f(-0.792f, 0.43f);
    glVertex2f(-0.792f, 0.46f);
    glVertex2f(-0.808f, 0.46f);

    glColor3f(0.6f,0.8f,1.0f);
    glVertex2f(-0.805f, 0.435f);
    glVertex2f(-0.795f, 0.435f);
    glVertex2f(-0.795f, 0.455f);
    glVertex2f(-0.805f, 0.455f);

    glEnd();

    glPushMatrix(); //first window translate
    glTranslatef(-0.06f, 0.0f, 0.0f);

    glBegin(GL_QUADS);//upper small window first
    glColor3f(1.0f,1.0f,1.0f);

    glVertex2f(-0.808f, 0.43f);
    glVertex2f(-0.792f, 0.43f);
    glVertex2f(-0.792f, 0.46f);
    glVertex2f(-0.808f, 0.46f);

    glColor3f(0.6f,0.8f,1.0f);
    glVertex2f(-0.805f, 0.435f);
    glVertex2f(-0.795f, 0.435f);
    glVertex2f(-0.795f, 0.455f);
    glVertex2f(-0.805f, 0.455f);

    glEnd();
    glPopMatrix();

    glPushMatrix(); //first window translate
    glTranslatef(0.06f, 0.0f, 0.0f);

    glBegin(GL_QUADS);//upper small window 3rd
    glColor3f(1.0f,1.0f,1.0f);

    glVertex2f(-0.808f, 0.43f);
    glVertex2f(-0.792f, 0.43f);
    glVertex2f(-0.792f, 0.46f);
    glVertex2f(-0.808f, 0.46f);

    glColor3f(0.6f,0.8f,1.0f);
    glVertex2f(-0.805f, 0.435f);
    glVertex2f(-0.795f, 0.435f);
    glVertex2f(-0.795f, 0.455f);
    glVertex2f(-0.805f, 0.455f);

    glEnd();
    glPopMatrix();


    glBegin(GL_QUADS);

    glColor3f(1.0f,1.0f,1.0f);//2nd window background

    glVertex2f(-0.78f, 0.32f);
    glVertex2f(-0.82f, 0.32f);
    glVertex2f(-0.82f, 0.38f);
    glVertex2f(-0.78f, 0.38f);

    glColor3f(0.2f,0.0f,0.0f);//2nd window upper line

    glVertex2f(-0.775f, 0.39f);
    glVertex2f(-0.825f, 0.39f);
    glVertex2f(-0.825f, 0.38f);
    glVertex2f(-0.775f, 0.38f);


    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }

    glVertex2f(-0.785f, 0.325f); //2nd windoe small box 4
    glVertex2f(-0.795f, 0.325f);
    glVertex2f(-0.795f, 0.345f);
    glVertex2f(-0.785f, 0.345f);

    glVertex2f(-0.785f, 0.35f);//2nd windoe small box 2
    glVertex2f(-0.795f, 0.35f);
    glVertex2f(-0.795f, 0.37f);
    glVertex2f(-0.785f, 0.37f);

    glVertex2f(-0.815f, 0.325f);//2nd windoe small box 3
    glVertex2f(-0.805f, 0.325f);
    glVertex2f(-0.805f, 0.345f);
    glVertex2f(-0.815f, 0.345f);

    glVertex2f(-0.815f, 0.35f);//2nd windoe small box 1
    glVertex2f(-0.805f, 0.35f);
    glVertex2f(-0.805f, 0.37f);
    glVertex2f(-0.815f, 0.37f);
    glEnd();

    glLineWidth(1); //2nd window middle line
    glBegin(GL_LINES);
    glVertex2f(-0.80f, 0.32f);
    glVertex2f(-0.80f, 0.38f);
    glEnd();


    glPushMatrix(); //first window translate
    glTranslatef(-0.06f, 0.0f, 0.0f);

    glBegin(GL_QUADS);

    glColor3f(1.0f,1.0f,1.0f);//1st window background

    glVertex2f(-0.78f, 0.32f);
    glVertex2f(-0.82f, 0.32f);
    glVertex2f(-0.82f, 0.38f);
    glVertex2f(-0.78f, 0.38f);

    glColor3f(0.2f,0.0f,0.0f);//1st window upper line

    glVertex2f(-0.775f, 0.39f);
    glVertex2f(-0.825f, 0.39f);
    glVertex2f(-0.825f, 0.38f);
    glVertex2f(-0.775f, 0.38f);


    glColor3f(0.6f,0.8f,1.0f);

    glVertex2f(-0.785f, 0.325f);//1st windoe small box 4
    glVertex2f(-0.795f, 0.325f);
    glVertex2f(-0.795f, 0.345f);
    glVertex2f(-0.785f, 0.345f);

    glVertex2f(-0.785f, 0.35f);//1st windoe small box 2
    glVertex2f(-0.795f, 0.35f);
    glVertex2f(-0.795f, 0.37f);
    glVertex2f(-0.785f, 0.37f);

    glVertex2f(-0.815f, 0.325f);//1st windoe small box 3
    glVertex2f(-0.805f, 0.325f);
    glVertex2f(-0.805f, 0.345f);
    glVertex2f(-0.815f, 0.345f);

    glVertex2f(-0.815f, 0.35f);//1st windoe small box 1
    glVertex2f(-0.805f, 0.35f);
    glVertex2f(-0.805f, 0.37f);
    glVertex2f(-0.815f, 0.37f);


    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(-0.80f, 0.32f);
    glVertex2f(-0.80f, 0.38f);
    glEnd();

    glPopMatrix();

    glPushMatrix(); //3rd window translate
    glTranslatef(0.06f, 0.0f, 0.0f);

    glBegin(GL_QUADS);

    glColor3f(1.0f,1.0f,1.0f);

    glVertex2f(-0.78f, 0.32f);
    glVertex2f(-0.82f, 0.32f);
    glVertex2f(-0.82f, 0.38f);
    glVertex2f(-0.78f, 0.38f);

    glColor3f(0.2f,0.0f,0.0f);

    glVertex2f(-0.775f, 0.39f);
    glVertex2f(-0.825f, 0.39f);
    glVertex2f(-0.825f, 0.38f);
    glVertex2f(-0.775f, 0.38f);


    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }

    glVertex2f(-0.785f, 0.325f);
    glVertex2f(-0.795f, 0.325f);
    glVertex2f(-0.795f, 0.345f);
    glVertex2f(-0.785f, 0.345f);

    glVertex2f(-0.785f, 0.35f);
    glVertex2f(-0.795f, 0.35f);
    glVertex2f(-0.795f, 0.37f);
    glVertex2f(-0.785f, 0.37f);

    glVertex2f(-0.815f, 0.325f);
    glVertex2f(-0.805f, 0.325f);
    glVertex2f(-0.805f, 0.345f);
    glVertex2f(-0.815f, 0.345f);

    glVertex2f(-0.815f, 0.35f);
    glVertex2f(-0.805f, 0.35f);
    glVertex2f(-0.805f, 0.37f);
    glVertex2f(-0.815f, 0.37f);


    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(-0.80f, 0.32f);
    glVertex2f(-0.80f, 0.38f);
    glEnd();

    glPopMatrix();

    glPushMatrix(); //5th window translate
    glTranslatef(0.0f, -0.1f, 0.0f);

    glBegin(GL_QUADS);

    glColor3f(1.0f,1.0f,1.0f);

    glVertex2f(-0.78f, 0.32f);
    glVertex2f(-0.82f, 0.32f);
    glVertex2f(-0.82f, 0.38f);
    glVertex2f(-0.78f, 0.38f);

    glColor3f(0.2f,0.0f,0.0f);

    glVertex2f(-0.775f, 0.39f);
    glVertex2f(-0.825f, 0.39f);
    glVertex2f(-0.825f, 0.38f);
    glVertex2f(-0.775f, 0.38f);


    glColor3f(0.6f,0.8f,1.0f);

    glVertex2f(-0.785f, 0.325f);
    glVertex2f(-0.795f, 0.325f);
    glVertex2f(-0.795f, 0.345f);
    glVertex2f(-0.785f, 0.345f);

    glVertex2f(-0.785f, 0.35f);
    glVertex2f(-0.795f, 0.35f);
    glVertex2f(-0.795f, 0.37f);
    glVertex2f(-0.785f, 0.37f);

    glVertex2f(-0.815f, 0.325f);
    glVertex2f(-0.805f, 0.325f);
    glVertex2f(-0.805f, 0.345f);
    glVertex2f(-0.815f, 0.345f);

    glVertex2f(-0.815f, 0.35f);
    glVertex2f(-0.805f, 0.35f);
    glVertex2f(-0.805f, 0.37f);
    glVertex2f(-0.815f, 0.37f);


    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(-0.80f, 0.32f);
    glVertex2f(-0.80f, 0.38f);
    glEnd();

    glPopMatrix();


    glPushMatrix(); //4th window translate
    glTranslatef(-0.06f, -0.1f, 0.0f);

    glBegin(GL_QUADS);

    glColor3f(1.0f,1.0f,1.0f);

    glVertex2f(-0.78f, 0.32f);
    glVertex2f(-0.82f, 0.32f);
    glVertex2f(-0.82f, 0.38f);
    glVertex2f(-0.78f, 0.38f);

    glColor3f(0.2f,0.0f,0.0f);

    glVertex2f(-0.775f, 0.39f);
    glVertex2f(-0.825f, 0.39f);
    glVertex2f(-0.825f, 0.38f);
    glVertex2f(-0.775f, 0.38f);


    glColor3f(0.6f,0.8f,1.0f);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }

    glVertex2f(-0.785f, 0.325f);
    glVertex2f(-0.795f, 0.325f);
    glVertex2f(-0.795f, 0.345f);
    glVertex2f(-0.785f, 0.345f);

    glVertex2f(-0.785f, 0.35f);
    glVertex2f(-0.795f, 0.35f);
    glVertex2f(-0.795f, 0.37f);
    glVertex2f(-0.785f, 0.37f);

    glVertex2f(-0.815f, 0.325f);
    glVertex2f(-0.805f, 0.325f);
    glVertex2f(-0.805f, 0.345f);
    glVertex2f(-0.815f, 0.345f);

    glVertex2f(-0.815f, 0.35f);
    glVertex2f(-0.805f, 0.35f);
    glVertex2f(-0.805f, 0.37f);
    glVertex2f(-0.815f, 0.37f);


    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(-0.80f, 0.32f);
    glVertex2f(-0.80f, 0.38f);
    glEnd();

    glPopMatrix();


//door

    glBegin(GL_QUADS);

    glColor3f(1.0f,1.0f,1.0f);

    glVertex2f(-0.76f, 0.2f);//door background
    glVertex2f(-0.72f, 0.2f);
    glVertex2f(-0.72f, 0.28f);
    glVertex2f(-0.76f, 0.28f);


    glColor3f(0.6f,0.8f,1.0f);

    glVertex2f(-0.755f, 0.21f);//door left side
    glVertex2f(-0.742f, 0.21f);
    glVertex2f(-0.742f, 0.27f);
    glVertex2f(-0.755f, 0.27f);

    glVertex2f(-0.738f, 0.21f);//door right side
    glVertex2f(-0.725f, 0.21f);
    glVertex2f(-0.725f, 0.27f);
    glVertex2f(-0.738f, 0.27f);


    glEnd();

    glBegin(GL_QUADS);//shiri


    glColor3f(0.8f,0.8f,0.8f);

    glVertex2f(-0.76f, 0.2f);
    glVertex2f(-0.72f, 0.2f);
    glVertex2f(-0.72f, 0.19f);
    glVertex2f(-0.76f, 0.19f);

    glVertex2f(-0.755f, 0.17f);
    glVertex2f(-0.725f, 0.17f);
    glVertex2f(-0.725f, 0.19f);
    glVertex2f(-0.755f, 0.19f);
    glEnd();
}

void house2()
{

//house2
    glPushMatrix();
    glTranslatef(1.01f, 0.0f, 0.0f);


    glBegin(GL_QUADS); // big house box

    glColor3ub(105, 89, 205);
    glVertex2f(-0.47f, 0.6f); //left upper point
    glVertex2f(-0.47f, 0.2f);
    glVertex2f(-0.6f, 0.2f);
    glVertex2f(-0.6f, 0.6f);//right upper point
    glEnd();



    glBegin(GL_QUADS); //side house box
    //glColor3f(0.02, 0.18, 0.4);
    glColor3ub(72, 61, 139);
    glVertex2f(-0.47f, 0.47f);//right upper point
    glVertex2f(-0.4f, 0.35f);
    glVertex2f(-0.4f, 0.2f);
    glVertex2f(-0.47f, 0.2f);//right lower point
    glEnd();

    glLineWidth(8);//side house line
    glBegin(GL_LINES);
    glColor3f(0.04, 0.31, 0.52);
    glVertex2f(-.472,.47);
    glVertex2f(-.39,.34);
    glEnd();

    glLineWidth(5); //big house upper line
    glBegin(GL_LINES);
    glColor3f(0.05, 0.20, 0.34);
    glVertex2f(-.61,.60);
    glVertex2f(-.46,.60);
    glEnd();

    glBegin(GL_QUADS);//window 1 background

    glColor3f(0.95, 0.98, 0.98);
    glVertex2f(-0.53f, 0.56f);
    glVertex2f(-0.53f, 0.5f);
    glVertex2f(-0.57f, 0.5f);
    glVertex2f(-0.57f, 0.56f);
    glEnd();

    glLineWidth(6);//window 1 background line
    glBegin(GL_LINES);
    glColor3f(0.00, 0.20, 0.35);
    glVertex2f(-.521,.57);
    glVertex2f(-.579,.57);
    glEnd();

//
    glBegin(GL_QUADS);


    glColor3f(0.38, 0.68, 0.78);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.532f, 0.557f);//window 1 door right
    glVertex2f(-0.532f, 0.503f);
    glVertex2f(-0.549f, 0.503);
    glVertex2f(-0.549f, 0.557f);

    glVertex2f(-0.552f, 0.557f); //window 1 door left
    glVertex2f(-0.552f, 0.503f);
    glVertex2f(-0.568f, 0.503);
    glVertex2f(-0.568f, 0.557f);
    glEnd();

    glBegin(GL_QUADS); //window 1 lower line
    glColor3f(0.62, 0.67, 0.73);
    glVertex2f(-0.52f, 0.51f);
    glVertex2f(-0.52f, 0.475f);
    glVertex2f(-0.58f, 0.475);
    glVertex2f(-0.58f, 0.51f);
    glEnd();



    glBegin(GL_QUADS); //window 3 background

    glColor3f(0.95, 0.98, 0.98);
    glVertex2f(-0.53f, 0.3f);
    glVertex2f(-0.53f, 0.24f);
    glVertex2f(-0.57f, 0.24f);
    glVertex2f(-0.57f, 0.3f);
    glEnd();

    glLineWidth(6);//window 3 upper line
    glBegin(GL_LINES);
    glColor3f(0.00, 0.20, 0.35);
    glVertex2f(-.521,.31);
    glVertex2f(-.579,.31);
    glEnd();



    glBegin(GL_QUADS);

    glColor3f(0.38, 0.68, 0.78);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.532f, 0.297f);//window 3 right door
    glVertex2f(-0.532f, 0.243f);
    glVertex2f(-0.549f, 0.243);
    glVertex2f(-0.549f, 0.297f);

    glVertex2f(-0.552f, 0.297f); ////window 3 left door
    glVertex2f(-0.552f, 0.243f);
    glVertex2f(-0.568f, 0.243);
    glVertex2f(-0.568f, 0.297f);

    glEnd();

    glBegin(GL_QUADS); //window 3 lower line
    glColor3f(0.62, 0.67, 0.73);
    glVertex2f(-0.52f, 0.25f);
    glVertex2f(-0.52f, 0.215f);
    glVertex2f(-0.58f, 0.215);
    glVertex2f(-0.58f, 0.25f);
    glEnd();


    glBegin(GL_QUADS); //window 2 background white
    glColor3f(0.95, 0.98, 0.98);
    glVertex2f(-0.53f, 0.43f);
    glVertex2f(-0.53f, 0.37f);
    glVertex2f(-0.57f, 0.37f);
    glVertex2f(-0.57f, 0.43f);
    glEnd();

    glLineWidth(6); //window 2 upper line
    glBegin(GL_LINES);
    glColor3f(0.00, 0.20, 0.35);
    glVertex2f(-.521,.44);
    glVertex2f(-.579,.44);
    glEnd();



    glBegin(GL_QUADS);
    glColor3f(0.38, 0.68, 0.78);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }

    glVertex2f(-0.532f, 0.427f); //window 2 right door
    glVertex2f(-0.532f, 0.373f);
    glVertex2f(-0.549f, 0.373);
    glVertex2f(-0.549f, 0.427f);

    glVertex2f(-0.552f, 0.427f); //window 2 left door
    glVertex2f(-0.552f, 0.373f);
    glVertex2f(-0.568f, 0.373);
    glVertex2f(-0.568f, 0.427f);

    glEnd();

    glBegin(GL_QUADS); //window 2 lower line
    glColor3f(0.62, 0.67, 0.73);
    glVertex2f(-0.52f, 0.38f);
    glVertex2f(-0.52f, 0.345f);
    glVertex2f(-0.58f, 0.345);
    glVertex2f(-0.58f, 0.38f);
    glEnd();


    glBegin(GL_QUADS); //side window 1 front glass
    glColor3f(0.95, 0.98, 0.98);
    glVertex2f(-0.428f, 0.37f);
    glVertex2f(-0.428f, 0.32f);
    glVertex2f(-0.453f, 0.32f);
    glVertex2f(-0.453f, 0.37f);
    glEnd();

    glBegin(GL_QUADS);//side window 1 background white
    glColor3f(0.38, 0.68, 0.78);
    glVertex2f(-0.431f, 0.365f);
    glVertex2f(-0.431f, 0.323f);
    glVertex2f(-0.450f, 0.323);
    glVertex2f(-0.450f, 0.365f);
    glEnd();


    glBegin(GL_QUADS); //door background
    glColor3f(0.95, 0.98, 0.98);
    glVertex2f(-0.425f, 0.3);
    glVertex2f(-0.425f, 0.2f);
    glVertex2f(-0.455f, 0.2);
    glVertex2f(-0.455f, 0.3);
    glEnd();

    glLineWidth(4); //door lower box left
    glBegin(GL_LINES);
    glColor3f(0.62, 0.67, 0.73);
    glVertex2f(-.435,.215);
    glVertex2f(-.435,.245);
    glEnd();

    glLineWidth(4);//door lower box right
    glBegin(GL_LINES);
    glColor3f(0.62, 0.67, 0.73);
    glVertex2f(-.445,.215);
    glVertex2f(-.445,.245);
    glEnd();


    glLineWidth(4);//door lower upper right box
    glBegin(GL_LINES);
    glColor3f(0.62, 0.67, 0.73);
    glVertex2f(-.435,.255);
    glVertex2f(-.435,.285);
    glEnd();

    glLineWidth(4);//door lower upper left box
    glBegin(GL_LINES);
    glColor3f(0.62, 0.67, 0.73);
    glVertex2f(-.445,.255);
    glVertex2f(-.445,.285);
    glEnd();

    glLineWidth(7); //side house lower door line
    glBegin(GL_LINES);
    glColor3f(0.80, 0.80, 0.80);
    glVertex2f(-.421,.2);
    glVertex2f(-.458,.2);
    glEnd();

    if(winter)
    {
        glBegin(GL_POLYGON);
        glColor3ub(255,255,255);

        glVertex2f(-0.55f, 0.60f); //left upper point
        glVertex2f(-0.49f, 0.60f);
        glVertex2f(-0.5f, 0.62f);
        glVertex2f(-0.50f, 0.62f);//right upper point

        glEnd();

        glLineWidth(5); //big house upper line
        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(-.61,.60);
        glVertex2f(-.46,.60);
        glEnd();

    }

    glPopMatrix();


}



void renderBitmapString(float x, float y, float z, void *font, char *string)
{
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void house3()
{
    //hospital<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, 0.0f);



    glBegin(GL_QUADS);// hos big box right
    glColor3ub(209, 238, 238);
    glVertex2f(0.7f, 0.6f);
    glVertex2f(0.7f, 0.17f);
    glVertex2f(0.48f, 0.17f);
    glVertex2f(0.48f, 0.6f);
    glEnd();


    glLineWidth(6); //hos upper line
    glBegin(GL_LINES);
    glColor3f(0.23, 0.71, 0.78);
    glVertex2f(0.45f, 0.6f);
    glVertex2f(0.715f, 0.6f);
    glEnd();

    if(winter)

    {

        glLineWidth(6); //hos upper line
        glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex2f(0.45f, 0.6f);
        glVertex2f(0.715f, 0.6f);
        glEnd();

        glBegin(GL_POLYGON);//snow
        glColor3ub(255,255,255);
        glVertex2f(0.45f, 0.6f);
        glVertex2f(0.55f, 0.62f);
        glVertex2f(0.62f, 0.63f);
        glVertex2f(0.71f, 0.6f);
        glEnd();

    }

    glBegin(GL_QUADS);//hos right window background
    glColor3f(0.45, 0.79, 0.89);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.58f, 0.52f);
    glVertex2f(0.58f, 0.18f);
    glVertex2f(0.7f, 0.18f);
    glVertex2f(0.7f, 0.52f);
    glEnd();

    glBegin(GL_QUADS); //hospital left window background
    glColor3f(0.45, 0.79, 0.89);
    glVertex2f(0.535f, 0.52f);
    glVertex2f(0.535f, 0.18f);
    glVertex2f(0.48f, 0.18f);
    glVertex2f(0.48f, 0.52f);
    glEnd();

    glLineWidth(2.4);
    glBegin(GL_LINES);
    glColor3f(1.00, 1.00, 1.00);
    glVertex2f(0.62f, 0.52f);//upper window line1
    glVertex2f(0.62f, 0.18f);

    glVertex2f(0.66f, 0.52f);//upper win line2
    glVertex2f(0.66f, 0.18f);

    glVertex2f(0.58f, 0.248f);//lower window parallel line 4
    glVertex2f(0.7f, 0.248);

    glVertex2f(0.58f, 0.316f);//par3
    glVertex2f(0.7f, 0.316);

    glVertex2f(0.58f, 0.384f);//par2
    glVertex2f(0.7f, 0.384);

    glVertex2f(0.58f, 0.452f); //upper par line 1
    glVertex2f(0.7f, 0.452);
    glEnd();

    glLineWidth(6); //big hos side window line
    glBegin(GL_LINES);
    //glColor3f(0.17, 0.53, 0.55);
    glVertex2f(0.535f, 0.248f);//left side window line 4
    glVertex2f(0.48f, 0.248);

    glVertex2f(0.535f, 0.316f);//left side window line 3
    glVertex2f(0.48f, 0.316);

    glVertex2f(0.535f, 0.384f);//left side window line 2
    glVertex2f(0.48f, 0.384);

    glVertex2f(0.535f, 0.452f);//left side window line 4
    glVertex2f(0.48f, 0.452);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.28, 0.68, 0.81);
    if (night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(0.67f, 0.255f);//hos door
    glVertex2f(0.67f, 0.17f);
    glVertex2f(0.61f, 0.17f);
    glVertex2f(0.61f, 0.255f);
    glEnd();

    glLineWidth(2);//hos door middle line
    glBegin(GL_LINES);
    glColor3f(0.17, 0.53, 0.55);
    glVertex2f(.64,.17);
    glVertex2f(.64,.25);
    glEnd();


    glLineWidth(6);
    glBegin(GL_LINES);
    glColor3f(0.73, 0.89, 0.87);
    glVertex2f(0.67f, 0.255f);//door right side line
    glVertex2f(0.67f, 0.17);

    glVertex2f(0.61f, 0.255f);//door right side line
    glVertex2f(0.61f, 0.17);
    glEnd();


    glLineWidth(5);//door upper line
    glBegin(GL_LINES);
    glColor3f(0.17, 0.53, 0.55);
    glVertex2f(0.6f, 0.255f);
    glVertex2f(0.68f, 0.255);
    glEnd();


    glColor3f(0.0,0.0,0.0);
    renderBitmapString(0.54f, 0.56f, 0.0f, GLUT_BITMAP_9_BY_15, "Hospital");
    glPopMatrix();
}


void upperLamp()
{

//lamp 1
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);//stand
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);//parallel stand
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);//lamp1 point

    glVertex2f(-0.885f, 0.213f);


    glEnd();

    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);//left night light
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f); //right night lamp light
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.85f, 0.12f);

        glEnd();
    }

    ////lamp 2

    glPushMatrix();
    glTranslatef(0.2f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);//stand
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);//par stand
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);//point

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);
        glVertex2f(-0.915f, 0.213f);//left light
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);//right light
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.85f, 0.12f);

        glEnd();
    }
    glPopMatrix();


    ////lamp3

    glPushMatrix();
    glTranslatef(0.4f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);//stand
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);//par stand
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);//point

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);//left light
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);//right light
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.85f, 0.12f);
        glEnd();
    }
    glPopMatrix();

    ////lamp4

    glPushMatrix();
    glTranslatef(0.6f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);//stand
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);//par stand
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);//point

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);//left light
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);//right light
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.85f, 0.12f);

        glEnd();
    }
    glPopMatrix();


    ////lamp5

    glPushMatrix();
    glTranslatef(0.8f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);//stand
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);//par stand
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);//point

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);//left light
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);//right light
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.85f, 0.12f);
        glEnd();
    }
    glPopMatrix();


    ////lamp6

    glPushMatrix();
    glTranslatef(1.0f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);//stand
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);//par stand
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);//left light
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);//right light
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.85f, 0.12f);
        glEnd();
    }
    glPopMatrix();


    ////lamp7

    glPushMatrix();
    glTranslatef(1.2f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);//stand
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);//par stand
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);//point

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);//left light
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);// right light
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.85f, 0.12f);

        glEnd();
    }
    glPopMatrix();


    ////lamp8

    glPushMatrix();
    glTranslatef(1.4f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);//stand
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);//par stand
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);//left
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);//right
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.85f, 0.12f);

        glEnd();
    }
    glPopMatrix();

    ////lamp9

    glPushMatrix();
    glTranslatef(1.6f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);//stand
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);//par stand
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);//left
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);//right
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.85f, 0.12f);

        glEnd();
    }
    glPopMatrix();


    ////lamp10

    glPushMatrix();
    glTranslatef(1.8f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glColor3f(0.8f,0.9f,1.0f);//stand
    glVertex2f(-0.9025f, 0.21f);
    glVertex2f(-0.8975f, 0.21f);
    glVertex2f(-0.8975f, 0.11f);
    glVertex2f(-0.9025f, 0.11f);

    glColor3f(0.8f,0.9f,1.0f);//par stand
    glVertex2f(-0.915f, 0.21f);
    glVertex2f(-0.885f, 0.21f);
    glVertex2f(-0.885f, 0.216f);
    glVertex2f(-0.915f, 0.216f);

    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    if(night)
    {
        glColor3f(0.9f,0.9f,0.0f);
    }
    glVertex2f(-0.915f, 0.213f);//point

    glVertex2f(-0.885f, 0.213f);
    glEnd();
    if(night)
    {
        //night light
        glBegin(GL_TRIANGLES);
        glColor3f(0.9f,0.9f,0.0f);//left
        glVertex2f(-0.915f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.905f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.95f, 0.12f);

        glColor3f(0.9f,0.9f,0.0f);//right
        glVertex2f(-0.885f, 0.213f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.895f, 0.12f);
        glColor3f(0.8f,0.8f,0.8f);
        glVertex2f(-0.85f, 0.12f);
        glEnd();
    }
    glPopMatrix();


}


void police()
{

// police head
    glPushMatrix();
    glTranslatef(0.15f,0.0f,0.0f);
    GLfloat xxp=0.4f;
    GLfloat xyp=0.195f;
    GLfloat radiusp =0.008f;

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xxp, xyp); // center of circle
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( xxp + (radiusp * cos(i *  twicePi / triangleAmount)),
                    xyp+ (radiusp * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glBegin(GL_QUADS);//police body
    glColor3f(0.8f,0.8f,0.0f);//body background
    glVertex2f(0.394f, 0.185f);
    glVertex2f(0.407f, 0.185f);
    glVertex2f(0.407f, 0.155f);
    glVertex2f(0.394f, 0.155f);


    glEnd();

    glBegin(GL_QUADS);
//right hand
    glColor3f(0.0f,0.0f,1.0f); //hand upper side
    glVertex2f(0.411f, 0.185f);
    glVertex2f(0.407f, 0.185f);
    glVertex2f(0.407f, 0.145f);
    glVertex2f(0.411f, 0.145f);

    glColor3f(1.0f,1.0f,1.0f); //hand gloves
    glVertex2f(0.411f, 0.155f);
    glVertex2f(0.407f, 0.155f);
    glVertex2f(0.407f, 0.145f);
    glVertex2f(0.411f, 0.145f);
//left hand
    if(!handup)
    {
        glColor3f(0.0f,0.0f,1.0f);//upper left hand
        glVertex2f(0.394f, 0.185f);
        glVertex2f(0.39f, 0.185f);
        glVertex2f(0.39f, 0.145f);
        glVertex2f(0.394f, 0.145f);

        glColor3f(1.0f,1.0f,1.0f);//gloves
        glVertex2f(0.394f, 0.155f);
        glVertex2f(0.39f, 0.155f);
        glVertex2f(0.39f, 0.145f);
        glVertex2f(0.394f, 0.145f);
    }

    //left hand up
    if(handup)
    {
        glColor3f(0.0f,0.0f,1.0f);//up hand left
        glVertex2f(0.394f, 0.175f);
        glVertex2f(0.39f, 0.175f);
        glVertex2f(0.39f, 0.215f);
        glVertex2f(0.394f, 0.215f);

        glColor3f(1.0f,1.0f,1.0f);//gloves
        glVertex2f(0.394f, 0.205f);
        glVertex2f(0.39f, 0.205f);
        glVertex2f(0.39f, 0.215f);
        glVertex2f(0.394f, 0.215f);


    }
// left lag

    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(0.406f, 0.12f);
    glVertex2f(0.401f, 0.12f);
    glVertex2f(0.401f, 0.155f);
    glVertex2f(0.406f, 0.155f);

// right lag

    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(0.395f, 0.12f);
    glVertex2f(0.4f, 0.12f);
    glVertex2f(0.4f, 0.155f);
    glVertex2f(0.395f, 0.155f);

    //table
    glColor3f(0.0f,0.0f,0.0f);//black
    glVertex2f(0.415f, 0.12f);
    glVertex2f(0.47f, 0.12f);
    glVertex2f(0.46f, 0.158f);
    glVertex2f(0.42f, 0.158f);

    glColor3f(0.9f,0.9f,0.0f);//yellow
    glVertex2f(0.414f, 0.12f);
    glVertex2f(0.455f, 0.12f);
    glVertex2f(0.46f, 0.158f);
    glVertex2f(0.42f, 0.158f);

    glEnd();
    glPopMatrix();

}

void first_blade()
{

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.78f,0.3f,0.0f);
    glRotatef(spin, 0.0f, 0.0f,1.0f);
    glTranslatef(-0.78f,-0.3f,0.0f);

//Blade_One  left

    glLineWidth(10);
    glBegin(GL_LINES);
    glColor3ub(200, 255, 255);
    glVertex2f(.77,.3);
    glVertex2f(.66,.17);
    glEnd();


    glPopMatrix();
}


void second_blade()
{

//glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.78f,0.3f,0.0f);
    glRotatef(spin, 0.0f, 0.0f,1.0f);
    glTranslatef(-0.78f,-0.3f,0.0f);

//
//    Blade_two top

    glLineWidth(10);
    glBegin(GL_LINES);
    glColor3ub(200, 255, 255);
    glVertex2f(.78,.3);
    glVertex2f(.78,.5);
    glEnd();



    glPopMatrix();
}

void third_blade()
{

//blade////
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.78f,0.3f,0.0f);
    glRotatef(spin, 0.0f, 0.0f,1.0f);
    glTranslatef(-0.78f,-0.3f,0.0f);

    glLineWidth(10);
    glBegin(GL_LINES);
    glColor3ub(200, 255, 255);
    glVertex2f(.78,.3);
    glVertex2f(.9,.17);
    glEnd();

    glPopMatrix();
}

//windmill
void windmill_stand()  //id26
{


////windmill 1st stand
    glColor3ub(176, 196, 222);
    glBegin(GL_POLYGON);
    glVertex2f(0.76, -0.299);
    glVertex2f(0.775, 0.3);
    glVertex2f(0.79, 0.31);
    glVertex2f(0.81, -0.299);
    glEnd();

}

void windmill_motor()
{

    //circle 1st windmill
    int xy;
    GLfloat p93=0.78f;
    GLfloat q93= 0.3f;
    GLfloat r93 = 0.03f;
    int tringle94=40;
    GLfloat tp94 =2.0f * PI  ;


    glBegin (GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 255);
    glVertex2f (p93,q93);
    for(int xy= 0; xy<=tringle94; xy++)
    {
        glVertex2f (
            p93+(r93*cos(xy*tp94/tringle94)),
            q93+(r93*sin(xy*tp94/tringle94))
        );
    }
    glEnd ();
}


void myDisplay(void)
{
    clearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Background();
    Sky();
    Clouds();
    Sun();
    Moon();
    Mountains();
    MountainHighlights();
    Stars();

    helicopter();

    seaside();
    sea();
    railLine();
    rail();
    wave();
    boat1();
    boat2();
    boat3();
    ship();
    bench2();
    bench1();
    road();
    bridge1();
    tree();
    tree1();

    house1();
    house2();
    house3();
    downLamp();
    upperLamp();

    police();
    car();
    bus();

    bridge2();

    windmill_stand();
    first_blade();
    second_blade();
    third_blade();
    windmill_motor();

    rainyday();

    glFlush ();

}


void myInit(void)
{
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}


void update(int value)
{
    if(rain)
    {
        _rain1y -= .05;
        _rain2y -= .05;
        _rain3y -= .05;
        _rain4y -= .05;
        _rain5y -= .05;
        _rain6y -= .05;
        _rain7y -= .05;
        _rain8y -= .05;
        _rain9y -= .05;
        _rain10y -= .05;
        i += 1;
        _rain1x -= .0055;
        _rain2x -= .0055;
        _rain3x -= .0055;
        _rain4x -= .0055;
        _rain5x -= .0055;
        _rain6x -= .0055;
        _rain7x -= .0055;
        _rain8x -= .0055;
        _rain9x -= .0055;
        _rain10x -= .0055;
    }

    if(_rain1y < -1.9)
    {
        _rain1y = .1;
        _rain1x = 0;
    }
    if(_rain2y < -1.7)
    {
        _rain2y = .3;
        _rain2x = 0;
    }
    if(_rain3y < -1.5)
    {
        _rain3y = .5;
        _rain3x = 0;
    }
    if(_rain4y < -1.3)
    {
        _rain4y = .7;
        _rain4x = 0;
    }
    if(_rain5y < -1.1)
    {
        _rain5y = 0.9;
        _rain5x = 0;
    }
    if(_rain6y < -.9)
    {
        _rain6y = 1.1;
        _rain6x = 0;
    }
    if(_rain7y < -.7)
    {
        _rain7y = 1.3;
        _rain7x = 0;
    }
    if(_rain8y < -.5)
    {
        _rain8y = 1.5;
        _rain8x = 0;
    }
    if(_rain9y < -.3)
    {
        _rain9y = 1.7;
        _rain9x = 0;
    }
    if(_rain10y < -.1)
    {
        _rain10y = 1.9;
        _rain10x = 0;
    }
    if(i == 120)
    {
        resetRain();
    }
    if(Bus_Stop)
    {
        bus_speed -= bus_speed;
    }
    glutPostRedisplay();
    glutTimerFunc(40, update, 0);
}

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(bus_speed >= 0)
        {
            Bus_Stop = false;
        }
        bus_speed = bus_speed+ 0.001;
        break;

    case GLUT_KEY_DOWN:
        if(bus_speed > 0)
        {
            bus_speed = bus_speed - 0.001;
        }
        if(bus_speed <= 0)
        {
            bool Bus_stop = true;
        }
        break;
    }
    glutPostRedisplay();
}

void Input(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'n':
//        if(night)
//        {
//            night = false;
//        }
//        else
//        {
//            night = true;
//        }
        night = true;
        sndPlaySound("H:\AIUB\9th sem\01054 - COMPUTER GRAPHICS [M]\CGPROJECT\music\night.wav",SND_ASYNC);
        break;

    case 'd':
        night = false;
        break;

    case 'h':
        if(handup)
        {
            handup = false;
        }
        else
        {
            handup = true;
        }
        break;


    case 'r':
        if(rain)
        {
            rain = false;
        }
        else
        {
            rain = true;
        }


        break;

    case 'w':
        if(winter)
        {
            winter = false;
        }
        else
        {
            winter = true;
        }
        break;

    case '1':
        helicopter_speed += 0.01f;
        break;

    case '2':
        helicopter_speed -= 0.01f;
        break;

    case '3':
        helicopter_speed = 0.0f;
        break;


    case '9':
        speedCloud += 0.01f;
        break;

    case '0':
        speedCloud = 0.0f;
        break;

    case 'a':
        glutIdleFunc(spinDisplay);
        break;

    case 's':
        glutIdleFunc(NULL);
        break;

    case 'c':
        glutIdleFunc(spinDisplayReverse);
        break;


        glutPostRedisplay();
    };
}

void GlutTimerFunctions()  // All Timer Functions combined
{
    glutTimerFunc(25, updateCloud, 0);
    glutTimerFunc(25, updateSun, 0);
    glutTimerFunc(100, updateShip, 0);
    glutTimerFunc(200, update_wave, 0);
    glutTimerFunc(150, updateRail, 0);
    glutTimerFunc(100, updateBus, 0);
    glutTimerFunc(100, updateBoat, 0);
    glutTimerFunc(100, updateCar, 0);
    glutTimerFunc(25, update, 0);
    glutTimerFunc(100, updateHelicopter, 0);
}

int main(int argc, char** argv)
{

    cout << " \n\t\t ** Welcome to Urban Majestic City **  " << endl;

    cout << " \t\t To control the project conditions please press the following assigned keys  " << endl;
    cout << " \n\t\t Press R -> To start/stop rain " << endl;
    cout << " \t\t Press W -> To start/stop winter " << endl;
    cout << " \t\t Press D -> To shift to day " << endl;
    cout << " \t\t Press N -> To shift to night " << endl;
    cout << " \t\t Press A -> To start the Windmill(anticlockwise) " << endl;
    cout << " \t\t Press C -> To spin the Windmill(clockwise) " << endl;
    cout << " \t\t Press S -> To stop the Windmill " << endl;
    cout << " \t\t Press 9 -> To increase the speed of the Clouds " << endl;
    cout << " \t\t Press 0 -> To stop the Clouds " << endl;
    cout << " \n\t\t Up Arrow -> To increase the speed of the Buses " << endl;
    cout << " \t\t Down Arrow -> To decrease the speed of the Buses " << endl;
    cout << " \n\t\t Left Click -> To increase the speed of the Ship " << endl;
    cout << " \t\t Up Arrow -> To stop the Ship " << endl;

    cout << " \n\t\t ** Hope you like it **  " << endl;


    glutInit(&argc, argv);

    glutInitWindowSize (1200, 720);
    glutInitWindowPosition (60, 80);

    glutCreateWindow ("Urban Majestic City");
    glutDisplayFunc(myDisplay);

    glutMouseFunc(handleMouse);
    glutKeyboardFunc(Input);
    glutSpecialFunc(SpecialInput);

    GlutTimerFunctions();

    myInit ();
    glutMainLoop();

}

