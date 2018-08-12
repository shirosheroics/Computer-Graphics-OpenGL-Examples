//Shorook Mohamed Saleh
//ID U14120929
//Submitted 2/10/2016

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

const int screenWidth = 640;
const int screenHeight = 480;
char keypress;
float stepsize = 0.001;

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);       // set white background color
    glColor3f(0.0f, 0.0f, 0.0f);          // set the drawing color
    glPointSize(4.0);       // a ëdotí is 4 by 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
    
    if (keypress == 'p')
    {
        for (float x = 0; x <= 3.454; x += stepsize)
        {
            float y = sin(x)*cos(201*x);
            
            float sx = x * screenWidth / 3.454;
            float sy = (y+0.846623) * screenHeight / 1.839823;
            
            cout << sx << " " << sy << endl;
            if(sy<screenHeight/2)
                glColor3f(1, 0, 0);
            else
                glColor3f(0, 1, 0);
            glBegin(GL_POINTS);
            glVertex2f(sx, sy);
            glEnd();
        }
    }
    else
    {
        glBegin(GL_LINE_STRIP);
        
        for (float x = 0; x <= 3.454; x += stepsize)
        {
            float y = sin(x)*cos(201*x);
            
            float sx = x * screenWidth / 3.454;
            float sy = (y+0.846623) * screenHeight / 1.839823;
        
            cout << sx << " " << sy << endl;
            if(sy<screenHeight/2)
                glColor3f(1, 0, 0);
            else
                glColor3f(0, 1, 0);
        
            glVertex2f(sx, sy);
       
        }
        glEnd();
    }
  
    
    
    glFlush();                 // send all output to display
}

void myKeyboard(unsigned char key, int x, int y)
{
    if (key == '1')
        stepsize = 1.0;
        else if( key == '2')
            stepsize = 0.1;
            else if( key == '3')
                stepsize = 0.01;
                else if( key == '4')
                    stepsize = 0.001;
                    else if( key == '5')
                        stepsize = 0.0001;

    keypress = key;
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
    myInit();
    glutMainLoop();      // go into a perpetual loop
}
