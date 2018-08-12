//Shorook Mohamed Saleh
//ID U14120929
//Submitted 24/12/2016

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
#include "vector.h"
#define M_PI 3.141592653589793238462643


using namespace std;

const int screenWidth = 800;
const int screenHeight = 600;
int clicks = 0, position=0;
Point positions[3], S, mouseTrack;
bool drawPerp = false, drawIntersec = false, drawCircle = false, isSelected = false;
float stepSize= 0.001;
int mx , my;
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>

void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
    
}

void setViewport(GLint left, GLint right, GLint bottom, GLint top)
{
    glViewport(left, bottom, right - left, top - bottom);
}

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);       // set white background color
    glColor3f(0.0f, 0.0f, 0.0f);          // set the drawing color
    glPointSize(8.0);       // a ëdotí is 4 by 4 pixels
    glEnable(GL_POINT_SMOOTH);

}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>

void myDisplay(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
    setWindow(0, screenWidth, 0, screenHeight);
    setViewport(0 ,screenWidth , 0, screenHeight);

    // After three clicks, draw the triangle segment
    if (clicks == 3)
    {
        
        // Draw the triangle
        glColor3f(0.0, 1.0, 0.0);
        
        glBegin(GL_LINE_LOOP);
        glVertex2d(positions[0].x, positions[0].y);
        glVertex2d(positions[1].x, positions[1].y);
        glVertex2d(positions[2].x, positions[2].y);

        glEnd();
        
        // Calculate the vectors
        Vector vLineAB = positions[1] - positions[0];
        Vector vLineBC = positions[2] - positions[1];
        Vector vLineCA = positions[0] - positions[2];
        
        // Calculate the perpendicular vectors
        Vector vPerpAB = perp(vLineAB);
        Vector vPerpBC = perp(vLineBC);
        Vector vPerpCA = perp(vLineCA);
        
        // Calculate the mid points
        Point midPointAB = positions[0] + vLineAB / 2;
        Point midPointBC = positions[1] + vLineBC / 2;
        Point midPointCA = positions[2] + vLineCA / 2;
        
        // Calculate the start and end points of the perpendicular vectors
        Point perpStartAB = midPointAB + 10 * vPerpAB;
        Point perpEndAB = midPointAB - 10 * vPerpAB;
        
        Point perpStartBC = midPointBC + 10 * vPerpBC;
        Point perpEndBC = midPointBC - 10 * vPerpBC;
        
        Point perpStartCA = midPointCA + 10 * vPerpCA;
        Point perpEndCA = midPointCA - 10 * vPerpCA;
       
        
        // Draw the perpendicular line segments
        if (drawPerp)
        {
            glColor3f(1, 0, 1);
            glBegin(GL_LINES);
            glVertex2d(perpStartAB.x, perpStartAB.y);
            glVertex2d(perpEndAB.x, perpEndAB.y);
            
            glVertex2d(perpStartBC.x, perpStartBC.y);
            glVertex2d(perpEndBC.x, perpEndBC.y);
            
            glVertex2d(perpStartCA.x, perpStartCA.y);
            glVertex2d(perpEndCA.x, perpEndCA.y);
            glEnd();
        }

        // Draw the mid points
        glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_POINTS);
        glVertex2d(midPointAB.x, midPointAB.y);
        glVertex2d(midPointBC.x, midPointBC.y);
        glVertex2d(midPointCA.x, midPointCA.y);
        glEnd();
        
        
        // Draw intersection
        S = positions[0] + 0.5*(vLineAB+ vPerpAB*((vLineCA.x*vLineBC.x+vLineCA.y*vLineBC.y+vLineCA.z*vLineBC.z)/
                                                  ( vPerpAB.x*vLineCA.x+ vPerpAB.y*vLineCA.y+ vPerpAB.z*vLineCA.z)));
        if (drawIntersec)
        {
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_POINTS);
            glVertex2d(S.x, S.y);
            glEnd();
        }
        // Draw circle
        Vector R = S - positions[0];
        int r = sqrt(pow(R.x,2)+pow(R.y,2));
        if (drawCircle)
        {
            glBegin(GL_LINE_LOOP);
            
            for ( float tc = 0; tc <= 2*M_PI; tc+=stepSize )
            {
                glColor3f(0.5, 0.5, 0.5);
                float x = r * cos(tc) + S.x;
                float y = r * sin(tc) + S.y;
                
                glVertex2d(x, y);
            }
            
            glEnd();

        }
        
        
    }
    
    // Draw the end points of the line segment
    for (int i = 0; i < clicks; i++)
    {
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2d(positions[i].x, positions[i].y);
        glEnd();
    }
    
    if(isSelected)
    {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POINTS);
        glVertex2d(positions[position].x, positions[position].y);
        glEnd();

    }
    
    glFlush();                 // send all output to display
    glutSwapBuffers();

}


double Distance(const Point& p1, const Point& p2)
{
    Vector v = p2 - p1;
    return v.norm();
}

void myKeyboard( unsigned char theyKey, int mouseX, int mouseY)
{
    if (theyKey == 'b'||theyKey == 'B')
        drawPerp = !drawPerp;
    if (theyKey == 'i'||theyKey == 'I')
        drawIntersec = !drawIntersec;
    if (theyKey == 'c'||theyKey == 'C')
        drawCircle= !drawCircle;

    
    glutPostRedisplay();
    
}

void myMouse(int button, int state, int x, int y)
{
    mx = x; my = screenHeight - y;
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if (clicks == 3)
            clicks = 0;
        positions[clicks] = Point(x, screenHeight - y);
        clicks++;
    }
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseTrack.x = mx;
        mouseTrack.y = my;
        isSelected = true;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        isSelected = false;
        cout<< isSelected << endl;
        
        
    }
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        clicks = 0;
    
    glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
    // Update the location of the current point as the mouse moves with button pressed.
    mx = x; my = screenHeight - y;
    mouseTrack.x = mx;
    mouseTrack.y = my;
    


        if (Distance(mouseTrack, positions[0]) <= 8) {
            cout<< "Point A" <<endl;
            cout << mouseTrack << isSelected <<endl;
            positions[0].x = mouseTrack.x;
            positions[0].y = mouseTrack.y;
            position = 0;
        }
        else if (Distance(mouseTrack, positions[1]) <= 8) {
            cout<< "Point B" << endl;
            positions[1].x = mouseTrack.x;
            positions[1].y = mouseTrack.y;
            position = 1;

        }
        else if (Distance(mouseTrack, positions[2]) <= 8) {
            cout<< "Point C"<< endl;
            positions[2].x = mouseTrack.x;
            positions[2].y = mouseTrack.y;
            position = 2;

        }
    else
    {
        isSelected = 0;
    }
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
    glutMouseFunc(myMouse);
    glutMotionFunc(mouseMotion);

    
    
    myInit();
    
    glutMainLoop();      // go into a perpetual loop
    
}

