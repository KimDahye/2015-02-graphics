//
//  main.m
//  triangle_example
//
//  Created by 김다혜 on 2015. 8. 31..
//  Copyright (c) 2015년 김다혜. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

GLboolean iCull = GL_FALSE;
GLboolean iOutline = GL_FALSE;
GLboolean iDepth = GL_TRUE;
GLenum mode = GL_CCW;


void ProcessMenu(int value)
{
    switch(value)
    {
        case 1:
            iDepth = !iDepth;
            break;
            
        case 2:
            iCull = !iCull;
            break;
            
        case 3:
            iOutline = !iOutline;
            break;
            
        case 4:
            mode = (mode == GL_CCW) ? GL_CW : GL_CCW;
            break;
            
        default :
            break;
    }
    glutPostRedisplay();
}

void RenderScene()
{
    GLfloat x,y,angle;
    int iPivot =1; // add
    glClear(GL_COLOR_BUFFER_BIT   | GL_DEPTH_BUFFER_BIT );
    
    if(iCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
    
    
    if(iDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    
    
    if(iOutline)
        glPolygonMode(GL_BACK,GL_LINE);
    else
        glPolygonMode(GL_BACK,GL_FILL);
    
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    
    glFrontFace(mode);
    glBegin(GL_TRIANGLE_FAN); // add
    glVertex3f(0.0f, 0.0f, 75.0f); // add - 기준점
    for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f)) {
        x = 50.0f*sin(angle);
        y = 50.0f*cos(angle);
        
        if((iPivot %2) == 0) // add
            glColor3f(0.0f, 1.0f, 0.0f);
        else
            glColor3f(1.0f, 1.0f, 0.0f);
        iPivot++;
        glVertex2f(x, y);
    }
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN); // add
    glVertex2f(0.0f, 0.0f); // add - 기준점
    for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f)) {
        x = 50.0f*sin(angle);
        y = 50.0f*cos(angle);
        if((iPivot %2) == 0) // add
            glColor3f(0.0f, 1.0f, 0.0f);
        else
            glColor3f(1.0f, 1.0f, 0.0f);
        
        iPivot++;
        glVertex2f(x, y);

    }
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}



void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glColor3f(0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT); // add
    glFrontFace(GL_CW); // add
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0); // add
    glutInitWindowSize(512,512); // add
    glutCreateWindow("Triangle_example");
    
    glutCreateMenu(ProcessMenu); //add - Create the Menu
    glutAddMenuEntry("깊이 테스트",1);
    glutAddMenuEntry("은면 제거",2);
    glutAddMenuEntry("뒷면 라인 그리기",3);
    glutAddMenuEntry("앞 뒷 면 바꾸기", 4);
    glutAttachMenu (GLUT_RIGHT_BUTTON);
    
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(KeyControl); // add
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}
