//
//  main.c
//  colorCube
//
//  Created by 김다혜 on 2015. 9. 28..
//  Copyright © 2015년 김다혜. All rights reserved.
//
#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static GLfloat v1[] = {0.0f, 0.0f, 0.0f};
static GLfloat v2[] = {40.0f, 0.0f, 0.0f};
static GLfloat v3[] = {40.0f, 40.0f, 0.0f};
static GLfloat v4[] = {0.0f, 40.0f, 0.0f};
static GLfloat v5[] = {0.0f, 0.0f, 40.0f};
static GLfloat v6[] = {40.0f, 0.0f, 40.0f};
static GLfloat v7[] = {40.0f, 40.0f, 40.0f};
static GLfloat v8[] = {0.0f, 40.0f, 40.0f};

static GLfloat c1[] = {0.0f, 0.0f, 0.0f};
static GLfloat c2[] = {0.0f, 0.0f, 1.0f};
static GLfloat c3[] = {1.0f, 0.0f, 1.0f};
static GLfloat c4[] = {1.0f, 0.0f, 0.0f};
static GLfloat c5[] = {0.0f, 1.0f, 0.0f};
static GLfloat c6[] = {0.0f, 1.0f, 1.0f};
static GLfloat c7[] = {1.0f, 1.0f, 1.0f};
static GLfloat c8[] = {1.0f, 1.0f, 0.0f};

void SetupRC()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);

}
void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //depth쓰려면 DEPTH_BUFFER_BIT붙여줘야 함.
    
    glPushMatrix();
    glRotatef(xRot,1.0f,0.0f,0.0f);
    glRotatef(yRot,0.0f,1.0f,0.0f);
    
    glBegin(GL_QUAD_STRIP);
    glColor3f(c1[0], c1[1], c1[2]);
    glVertex3d(v1[0], v1[1], v1[2]);
    glColor3f(c2[0], c2[1], c2[2]);
    glVertex3d(v2[0], v2[1], v2[2]);
    glColor3f(c4[0], c4[1], c4[2]);
    glVertex3d(v4[0], v4[1], v4[2]);
    glColor3f(c3[0], c3[1], c3[2]);
    glVertex3d(v3[0], v3[1], v3[2]);
    glColor3f(c8[0], c8[1], c8[2]);
    glVertex3d(v8[0], v8[1], v8[2]);
    glColor3f(c7[0], c7[1], c7[2]);
    glVertex3d(v7[0], v7[1], v7[2]);
    glColor3f(c5[0], c5[1], c5[2]);
    glVertex3d(v5[0], v5[1], v5[2]);
    glColor3f(c6[0], c6[1], c6[2]);
    glVertex3d(v6[0], v6[1], v6[2]);
    glColor3f(c1[0], c1[1], c1[2]);
    glVertex3d(v1[0], v1[1], v1[2]);
    glColor3f(c2[0], c2[1], c2[2]);
    glVertex3d(v2[0], v2[1], v2[2]);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(c2[0], c2[1], c2[2]);
    glVertex3d(v2[0], v2[1], v2[2]);
    glColor3f(c3[0], c3[1], c3[2]);
    glVertex3d(v3[0], v3[1], v3[2]);
    glColor3f(c7[0], c7[1], c7[2]);
    glVertex3d(v7[0], v7[1], v7[2]);
    glColor3f(c6[0], c6[1], c6[2]);
    glVertex3d(v6[0], v6[1], v6[2]);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(c1[0], c1[1], c1[2]);
    glVertex3d(v1[0], v1[1], v1[2]);
    glColor3f(c4[0], c4[1], c4[2]);
    glVertex3d(v4[0], v4[1], v4[2]);
    glColor3f(c8[0], c8[1], c8[2]);
    glVertex3d(v8[0], v8[1], v8[2]);
    glColor3f(c5[0], c5[1], c5[2]);
    glVertex3d(v5[0], v5[1], v5[2]);
    glEnd();
    
    glPopMatrix();
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

void ChangeSize(int w, int h)
{
    
    GLfloat nRange = 100.0f;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    
    if(w<=h)
        glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w,-nRange, nRange);
    
    else
        glOrtho(-nRange*w/h,nRange*w/h,-nRange,nRange,-nRange, nRange);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0); // add
    glutInitWindowSize(512,512); // add
    glutCreateWindow("SpringVertex");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(KeyControl); // add
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}
