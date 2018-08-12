//Shorook Mohamed Saleh
//ID U14120929
//Submitted 27/10/2016

#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>


#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif


using namespace std;

const int screenWidth = 800;
const int screenHeight = 600;
float factorX = 0, factorY = 0;
float stepSize= 0.001, cstep= 0.02;
float R = 0.5;
bool key = false, keyC = false;
float cy , cx, cs =0;

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>

void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
    
}



void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);       // set white background color
    glColor3f(0.0f, 0.0f, 0.0f);          // set the drawing color
    glPointSize(4.0);       // a ëdotí is 4 by 4 pixels
    setWindow(-20, 20, -20, 20);
    
}



//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>

void creatCircle( int x, int y)
{
    
    glBegin(GL_POLYGON);
    
    for ( float tc = 0; tc <= 2*M_PI; tc+=stepSize )
        
    {
        glColor3f(0.5, 0.5, 0.5);
        float x=R*cos(tc)+cx;
        float y = R * sin(tc) + cy;
        
        glVertex2d(x, y);
    }
    
    glEnd();
    
}


void myDisplay(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
 
    
    glViewport(80 + factorX , 60 + factorY , 640, 480);
    

  
    
    if( key == true)
        
        glBegin(GL_POLYGON);
    else
        glBegin(GL_LINE_STRIP);
    
    
    for ( float t = 0; t <= 2*M_PI; t+=stepSize )
    {
        
        float x = 16 * pow(sin(t),3);
        float y =13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t);
        
        if( x < 0 && key != true)
            glColor3f(0, 1, 0);
        else
            glColor3f(1, 0, 0);
        
        glVertex2d(x, y);
        
    }
    
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    
    glColor3f(1, 0, 0);
    
    glVertex2d(-19.9, -19.9);
    glVertex2d(-19.9, 20);
    glVertex2d(20, 20);
    glVertex2d(20, -19.9);
    
    glEnd();
    
    if ( keyC == true)
        creatCircle(cx, cy);
    
    
    glFlush();                 // send all output to display
    
}


void myKeyboard( unsigned char theyKey, int mouseX, int mouseY)
{
    
    if ( theyKey == 'f' && key == false)
        key = true;
    else if ( theyKey == 'f' && key != false)
        key = false;
    
    
    if ( theyKey == 'w')
        factorY+= 5;
    else if( theyKey == 's')
        factorY-=5;
    else if(theyKey == 'a')
        factorX -=5;
    else if (theyKey == 'd')
        factorX +=5;
    
    
    if ( theyKey == 'c' && keyC == false)
        keyC = true;
    else  if ( theyKey == 'c' && keyC != false)
        keyC = false;
    
    
    glutPostRedisplay();
    
}



void myIdel ()
{
    if ( keyC == true)
    {
        cs+= cstep;
        
        cx = 16 * pow(sin(cs),3);
        cy = 13 *cos(cs)-5*cos(2*cs)-2*cos(3*cs)-cos(4*cs);
    }
    if ( cs >= 2*M_PI || keyC == false)
        cs =0;
    glutPostRedisplay();
    
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>

int main(int argc, char** argv)
{
    
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight);     // set window size
    glutInitWindowPosition(100, 100); // set window position on screen
    glutCreateWindow("My Graphics App"); // open the screen window
    glutDisplayFunc(myDisplay);     // register redraw function
    glutKeyboardFunc(myKeyboard);
    glutIdleFunc(myIdel);
    
    
    
    myInit();
    
    glutMainLoop();      // go into a perpetual loop
    
}

