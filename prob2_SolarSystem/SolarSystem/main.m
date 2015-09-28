//
//  main.m
//  Solar System
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
float fElect2 = 0.0f;

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glColor3f(0.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    
    GLfloat amb[] = {0.5f,0.5f,0.5f};
    GLfloat diff[] = { 0.7f,0.7f,0.7f};
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    
    /*light add*/
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void TimerFunc(value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat lightPos0[] = {0.0f, 0.0f, -100.0f, 1.0f }; //add
    GLfloat lightPos1[] = {10.0f, 0.0f, -80.0f, 1.0f }; //add

    
    GLfloat nRange = 100.0f;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h){
        glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w, -nRange*2.0f, nRange*2.0f);
    }
    else{
        glOrtho(-nRange*w/h,nRange*w/h,-nRange,nRange, -nRange*2.0f,nRange*2.0f);
    }
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos0); //add
    glLightfv(GL_LIGHT1,GL_POSITION,lightPos1); //add

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void RenderScene()
{
    static GLfloatfElect1=0.0f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -100.0f);
    glColor3ub(255, 230, 80);
    glutSolidSphere(10.0f,15,15);
    glPushMatrix();
    
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(90.0f,0.0f,0.0f);
    glColor3ub(65, 149, 192);
    glutSolidSphere(6.0f,15,15);
    glPushMatrix();
    
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(10.0f,0.0f,0.0f);
    glColor3ub(232,160,26);
    glutSolidSphere(2.0f,15,15);
    
    fElect1 += 5.0f;
    fElect2 += 60.0f;
    
    if(fElect1 > 360.0f)
        fElect1 = 0.0f;
   
    if(fElect2 > 360.0f)
        fElect2 = 0.0f;
    
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
    glutCreateWindow("Solar System");
    
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33,TimerFunc,1);
    glutSpecialFunc(KeyControl);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}
