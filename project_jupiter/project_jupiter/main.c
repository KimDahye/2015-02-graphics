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
float fElect1 = 0.0f;
float fElect2 = 0.0f;
GLUquadricObj *pSphere = NULL;

GLuint sunTex;
GLuint spaceTex;
GLuint jupiterTex;

GLfloat windowWidth = 800;
GLfloat windowHeight = 800;
int w1 = 0;
int h1 = 0;

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

void initTex()
{
    sunTex = loadTex("resources/sun.bmp");
    spaceTex = loadTex("resources/space.bmp");
    jupiterTex = loadTex("resources/jpiter.bmp");
}

void TimerFunc(value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void reshape(int w, int h)
{
    w1 = w;
    h1 = h;
    glViewport(0, 0, w, h);
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

void orthogonalStart()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-w1/2, w1/2, -h1/2, h1/2);
    glMatrixMode(GL_MODELVIEW);
}

void orthogonalEnd()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


GLuint texture = 0;

void background()
{
    glBindTexture( GL_TEXTURE_2D, texture );
    orthogonalStart();
    
    // texture width/height
    const int iw = windowWidth;
    const int ih = windowHeight;
    
    glPushMatrix();
    glTranslatef( -iw/2, -ih/2, 0 );
    glBegin(GL_QUADS);
    glTexCoord2i(0,0); glVertex2i(0, 0);
    glTexCoord2i(1,0); glVertex2i(iw, 0);
    glTexCoord2i(1,1); glVertex2i(iw, ih);
    glTexCoord2i(0,1); glVertex2i(0, ih);
    glEnd();
    glPopMatrix();
    
    orthogonalEnd();
}

void drawSolarSystem() {
    
    static GLfloat fElect1=0.0f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, 0.0f);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    
    glBindTexture(GL_TEXTURE_2D, sunTex);
    glColor3ub(255, 230, 80);
    gluSphere(pSphere, 20.0f, 18, 18);
    glPushMatrix();
    
    glBindTexture(GL_TEXTURE_2D, sunTex);
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(90.0f,0.0f,0.0f);
    glColor3ub(65, 149, 192);
    gluSphere(pSphere, 6.0f, 18, 18);
    glPushMatrix();
    
    glBindTexture(GL_TEXTURE_2D, sunTex);
    glRotatef(fElect2, 0.0f,1.0f,0.0f);
    glTranslatef(10.0f,0.0f,0.0f);
    glColor3ub(232,160,26);
    gluSphere(pSphere, 2.0f, 18, 18);
    
    fElect1 += 5.0f;
    fElect2 += 60.0f;
    
    if(fElect1 > 360.0f)
        fElect1 = 0.0f;
    
    if(fElect2 > 360.0f)
        fElect2 = 0.0f;
    
    glPopMatrix();
}

void SetupRC() {
    /*기본 셋팅*/
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
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
    
    /*light add*/
    GLfloat amb[] = {0.1f,0.1f,0.1f};
    GLfloat diff[] = { 1.0f,1.0f,1.0f};
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void RenderScene()
{
    glClearColor (1.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable( GL_TEXTURE_2D );
    background();
    drawSolarSystem();
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("solar system with background");
    
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(reshape);
    //glutSpecialFunc(KeyControl);
    texture = loadTex("resources/galaxy.png");
    //이동하는 것을 보려면 glutTimerFunc에 걸린 주석을 풀면 된다. 화살표 키로도 움직이는 것을 볼 수있다.
    //glutTimerFunc(33,TimerFunc,1);
    SetupRC();
    glutMainLoop();
    return 0;
}