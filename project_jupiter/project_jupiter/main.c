//
//  main.c
//  project_jupiter
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

float sunRotate = 0.0f;
float fElect1 = 0.0f;
float fElect2 = 0.0f;
GLUquadricObj *pSphere = NULL;

GLuint earthTex;
GLuint sunTex;
GLuint moonTex;
GLuint jupiterTex;

GLuint loadTex(const char* filename)
{
    GLuint tex_ID = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,(SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT));
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, tex_ID );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    return tex_ID;
}

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glColor3f(0.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    
    /* for lighting on texture mapping
     * http://stackoverflow.com/questions/27712437/opengl-how-do-i-affect-the-lighting-on-a-textured-plane 참고.
     */
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
    
    
    /* for texture mapping
     * http://stackoverflow.com/questions/25592313/opengl-texturing-sphere-using-soil 참고.
     */
    pSphere = gluNewQuadric();
    gluQuadricDrawStyle(pSphere, GLU_FILL);
    gluQuadricNormals(pSphere, GLU_SMOOTH);
    gluQuadricTexture(pSphere, GLU_TRUE);
}

void initTex()
{
    sunTex = loadTex("resources/sun.bmp");
    earthTex = loadTex("resources/earth.bmp");
    moonTex = loadTex("resources/moon.bmp");
    jupiterTex = loadTex("resources/jupiter.bmp");
}

void TimerFunc(value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void lightSetting (GLfloat * amb, GLfloat * diff) {
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void RenderScene()
{
    // TODO. 카메라 위치 바꾸기...
    
    //multi light이 잘 안되서, 태양의 amb light값만 높임.
    GLfloat amb[] = {0.001f, 0.001f,0.001f};
    GLfloat diff[] = { 1.0f,1.0f,1.0f};
    lightSetting(amb, diff);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST); // TODO. 왜 SetupRC에도 있는데.. RenderScene에도 있어야 할까?
    glBindTexture(GL_TEXTURE_2D, jupiterTex);
    glRotatef(sunRotate, 0.0f, 1.0f, 0.0f);// 목성 자전
    glColor3ub(255, 255, 255);
    gluSphere(pSphere, 50.0f, 25, 25); //glutSolidSphere로 그리면 texture mapping이 안된다!
    
//    GLfloat amb2[] = {1.0f,1.01f,1.01f};
//    lightSetting(amb2, diff);
//    glBindTexture(GL_TEXTURE_2D, sunTex);
//    glPopMatrix();
//    glRotatef(fElect1, 0.0f,1.0f,0.0f);
//    glTranslatef(100.0f,0.0f,0.0f);
//    glColor3ub(255, 255, 255);
//    gluSphere(pSphere, 6.0f, 18, 18);
//    glPushMatrix();
    
    sunRotate += 5.0f;
    fElect1 += 5.0f;
    fElect2 += 5.0f;
    
    if(sunRotate > 360.0f)
        sunRotate = 0.0f;
    
    if(fElect1 > 360.0f)
        fElect1 = 0.0f;
    
    if(fElect2 > 360.0f)
        fElect2 = 0.0f;
    
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
    GLfloat lightPos0[] = {60.0f, 60.0f, 100.0f, 1.0f };
    //    GLfloat lightPos1[] = {-20.0f, 0.0f, -100.0f, 1.0f };
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
    glLightfv(GL_LIGHT0, GL_POSITION,lightPos0);
    //    glLightfv(GL_LIGHT1, GL_POSITION,lightPos1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Solar system with texture");
    glutSpecialFunc(KeyControl);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    initTex();
    glutTimerFunc(33,TimerFunc,1);
    SetupRC();
    glutMainLoop();
    return 0;
}
