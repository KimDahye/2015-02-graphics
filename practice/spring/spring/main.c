//
//  main.c
//  spring
//
//  Created by 김다혜 on 2015. 8. 31..
//  Copyright (c) 2015년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
void SetupRC()
{
    
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    glColor3f(0.0f,1.0f,0.0f);
    
}
void RenderScene(void)
{
    
    GLfloat x,y,z,angle, radius, step;
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glRotatef(xRot,1.0f,0.0f,0.0f); //(angle)
    glRotatef(yRot,0.0f,1.0f,0.0f);
    glBegin(GL_LINE_STRIP);
    z=-50.0f;
    radius =60.0f;
    step = (10.0f)/(GL_PI/0.1);
    
    for(angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle +=0.1f)// 3.14/0.1 개의 포인트를 뿌린다 총 3바퀴
    {
        x = radius*sin(angle);
        y = radius*cos(angle);
        glVertex3f(x,y,z);
        z +=0.5f;
        radius -= step;
    }
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
    glViewport(0, 0, w ,h );
    
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
