//
//  main.c
//  texture
//
//  Created by 김다혜 on 2015. 9. 29..
//  Copyright © 2015년 김다혜. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include "SOIL.h"

#define GL_PI 3.14159f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;

GLfloat amb [] = { 0.3f, 0.3f, 0.3f, 1.0f};
GLfloat dif [] = { 0.8f, 0.8f, 0.8f, 1.0f};
GLfloat	lightPos[] = { -50.0f, 50.0f, 100.0f, 1.0f};

GLuint tex;

void SetupRC()
{
    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f,0.0f, zDistance);
    
    //int width, height;
    //unsigned char* image = SOIL_load_image("/Users/JoJo/texture.bmp", &width, &height, 0, SOIL_LOAD_RGB);
    
    tex = SOIL_load_OGL_texture("resources/earth.jpg", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    if(tex==0)
        printf("load image failed");
    
    //glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT0,GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, dif);
    glLightfv(GL_LIGHT0,GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);
    
    glColor3f(1.0f,1.0f,1.0f);
    glutSolidTeapot(10.0f);
    glPopMatrix();
    
    glutSwapBuffers();
}

void KeyControl(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
        xRot-= 5.0f;
    
    if(key == GLUT_KEY_DOWN)
        xRot += 5.0f;
    
    if(key == GLUT_KEY_LEFT)
        yRot -= 5.0f;
    
    if(key == GLUT_KEY_RIGHT)
        yRot += 5.0f;
    
    if(key == GLUT_KEY_HOME)
        zDistance += 5.0f;
    
    if(key == GLUT_KEY_END)
        zDistance -= 5.0f;
    
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    GLfloat fAspect;
    
    glViewport(0,0,w,h);
    fAspect = (GLfloat)w/(GLfloat)h; // Window¿« ¡æ»æ∫Ò ∞ËªÍ
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0f,fAspect,1.0f,500.0f); //(FOV,¡æ»æ∫Ò,near,far)
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-50.0f);
    
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("2D texture");
    glutSpecialFunc(KeyControl);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    
    SetupRC();
    glutMainLoop();
    
}