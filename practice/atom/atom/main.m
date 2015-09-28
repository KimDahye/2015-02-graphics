//
//  main.m
//  atom
//
//  Created by 김다혜 on 2015. 9. 07..
//  Copyright (c) 2015년 김다혜. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
float fElect1 = 0.0f;

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glColor3f(0.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat fAspect;
    glViewport(0,0,w,h);
    fAspect = (GLfloat)w/(GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,fAspect,1.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f, -200.0f); //add

}

void RenderScene()
{
    static GLfloatfElect1=0.0f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -100.0f);
    glColor3ub(255, 0,0);
    glutSolidSphere(10.0f,15,15);
    
    glPushMatrix();
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(90.0f,0.0f,0.0f);
    glColor3ub(150,150,0);
    glutSolidSphere(6.0f,15,15);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(45.0f, 0.0f,0.0f, 1.0f);
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(-70.0f, 0.0f,0.0f);
    glColor3ub(150,0,150);
    glutSolidSphere(6.0f,15,15);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90.0f,0.0f, 0.0f, 1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 60.0f);
    glColor3ub(0,150,150);
    glutSolidSphere(6.0f, 15, 15);
    glPopMatrix();
    
    fElect1 += 10.0f;
    if(fElect1 > 360.0f)
        fElect1 = 0.0f;
    
    glutSwapBuffers();
}

void KeyControl(int key, int x, int y) {
    if(key == GLUT_KEY_UP)
        xRot -=5.0f;
    
    if(key == GLUT_KEY_DOWN)
        xRot +=5.0f;
    
    if(key == GLUT_KEY_LEFT)
        yRot -=5.0f;
    
    if(key == GLUT_KEY_RIGHT)
        yRot +=5.0f;
    
    glutPostRedisplay();
}

int main(int argc, const char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0); // add
    glutInitWindowSize(512,512); // add
    glutCreateWindow("Atom");
    
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33,TimerFunc,1);
    glutSpecialFunc(KeyControl);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}
