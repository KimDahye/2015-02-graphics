//
//  main.c
//  graphics_prob1
//
//  Created by 김다혜 on 2015. 8. 31..
//  Copyright (c) 2015년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
void setStepSize2(GLfloat* num, GLfloat* step, GLfloat length);
void adjustRectangle(GLfloat* a, GLfloat length);

GLsizei rsize = 50.0f;
GLfloat a[] = {0.0f, 50.0f, -50.0f, -80.0f};
GLfloat b[] = {0.0f, 30.0f, -50.0f, -40.0f};
GLfloat xstep[] = {1.0f, -1.0f, 1.0f, -1.0f};
GLfloat ystep[] = {1.0f, 1.0f, -1.0f, -1.0f};
int arraySize = 4;

GLfloat window_width;
GLfloat window_height;

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    glRectf(a[0],b[0],a[0]+rsize,b[0]+rsize);
    
    glColor3f(1.0f,1.0f,0.0f);
    glRectf(a[1],b[1],a[1]+rsize,b[1]+rsize);
    
    glColor3f(0.5f,1.0f,0.5f);
    glRectf(a[2],b[2],a[2]+rsize,b[2]+rsize);
    
    glColor3f(0.0f,1.0f,1.0f);
    glRectf(a[3],b[3],a[3]+rsize,b[3]+rsize);
    glutSwapBuffers();
}

void TimerFunction(int value)
{
    
    for(int i = 0; i < arraySize; i++) {
        setStepSize2(&a[i], &xstep[i], window_width);
        setStepSize2(&b[i], &ystep[i], window_height);
        adjustRectangle(&a[i], window_width);
        adjustRectangle(&b[i], window_height);
        
        a[i] +=xstep[i];
        b[i] +=ystep[i];
    }
    
    glutPostRedisplay();
    glutTimerFunc(33,TimerFunction,1);
}

void setStepSize2(GLfloat* num, GLfloat* step, GLfloat length) {
    GLfloat numVal = *num;
    GLfloat stepVal = *step;
    if(numVal > length -rsize || numVal < -length)
        *step = -(stepVal);
}

void adjustRectangle(GLfloat* a, GLfloat length) {
    if(*a > length)
        *a = length-rsize-1;
}

int adjustRectangleWithHeight(int b) {
    if(b > window_height-rsize)
        b = window_height-rsize-1;
    return b;
}

void SetupRC(void)
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
    {
        window_width = 100.0f; //
        window_height = 100.0f*h/w; //
        glOrtho (-100.0f, 100.0f, -window_height, window_height, 1.0, -1.0);
    }
    else
    {
        window_width = 100.0f*w/h; //
        window_height = 100.0f; //
        glOrtho (-window_width, window_width, -100.0f, 100.0f, 1.0, -1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("BounceRectangle");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize); 
    glutTimerFunc(1000,TimerFunction,1);
    SetupRC();
    glutMainLoop();
    return 0;
}
