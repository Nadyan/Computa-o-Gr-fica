/*
 *  CGR0001 - UDESC
 *  Nadyan Suriel Pscheidt
 *  Adapted from the code written by Richard S. Wright Jr.  
 *
 *  Quadric Snowman in OpenGL using the GLUT library
 *  gcc CGR_quadric_Castle.c -lglut -lGL -lGLU -lm -o castle
 */

#include <GL/glut.h>  // Header File For The GLUT Library 
#include <GL/gl.h>    // Header File For The OpenGL32 Library
#include <GL/glu.h>   // Header File For The GLu32 Library
#include <math.h>
#include <unistd.h>

// Rotações
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static GLfloat rotX = 0.0f;
static GLfloat rotY = 0.0f;
static GLfloat rotZ = 0.0f;

// Arrumar imagem quando a janela é redimensionada
void ChangeSize(int w, int h){  
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(h == 0)
        h = 1;
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);
  
    fAspect = (GLfloat)w/(GLfloat)h;
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  
    // Produce the perspective projection
    gluPerspective(35.0f, fAspect, 1.0, 40.0);
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}  

// Função para mover o objeto com as setas do teclado 
void SpecialKeys(int key, int x, int y){  
    if(key == GLUT_KEY_UP)  
        xRot -= 5.0f;  
  
    if(key == GLUT_KEY_DOWN)  
        xRot += 5.0f;  
  
    if(key == GLUT_KEY_LEFT)  
        yRot -= 5.0f;  
  
    if(key == GLUT_KEY_RIGHT)  
        yRot += 5.0f;  
                  
        xRot = (GLfloat)((const int)xRot % 360);  
        yRot = (GLfloat)((const int)yRot % 360);  
  
    // Refresh the Window  
    glutPostRedisplay();  
}  
  
// Inicialização do render e iluminação
void SetupRC(){  
    // Valores e coordenadas da luz
    GLfloat  whiteLight[] = {0.05f, 0.05f, 0.05f, 1.0f};  
    GLfloat  sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};  
    GLfloat  lightPos[] = {-10.f, 5.0f, 10.0f, 1.0f};  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Habilita iluminação 
    glEnable(GL_LIGHTING);  
  	
    // Setup da iluminação  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  

    glEnable(GL_COLOR_MATERIAL);
       
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Background
    glClearColor(0.3f, 0.8f, 0.8f, 0.0f);
}  
  
// Called to draw scene  
void RenderScene(void){  
    GLUquadricObj *pObj;   // Quádrica  
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();    
		
        glTranslatef(0.0f, -1.0f, -5.0f);  
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);  
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

        pObj = gluNewQuadric(); // objeto 
        gluQuadricNormals(pObj, GLU_SMOOTH);  
           
        glPushMatrix();  
            // Torre meio frente
            glColor3f(1.0f, 0.5f, 0.0f);
            glTranslatef(0.0f, 0.5f, 0.0f);
            glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.4f, 0.0f, 0.7f, 80, 13); //0.0f no terceiro parametro para ser um cone

            glColor3f(0.45f, 0.45f, 0.45f);
            glTranslatef(0.0f, 0.0f, -0.8f);
            gluCylinder(pObj, 0.4f, 0.4f, 0.8f, 80, 13);
        glPopMatrix();

        glPushMatrix();
            // Torre esquerda frente
            glColor3f(1.0f, 0.5f, 0.0f);  
            glTranslatef(-1.2f, 0.49f, 0.0f);
            glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.4f, 0.0f, 0.7f, 80, 13); //0.0f no terceiro parametro para ser um cone

            glColor3f(0.45f, 0.45f, 0.45f);
            glTranslatef(0.0f, 0.0f, -0.8f);
            gluCylinder(pObj, 0.4f, 0.4f, 0.8f, 80, 13);
        glPopMatrix();

        glPushMatrix();
            // Torre direita frente
            glColor3f(1.0f, 0.5f, 0.0f);  
            glTranslatef(1.2f, 0.49f, 0.0f);
            glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.4f, 0.0f, 0.7f, 80, 13); //0.0f no terceiro parametro para ser um cone

            glColor3f(0.45f, 0.45f, 0.45f);
            glTranslatef(0.0f, 0.0f, -0.8f);
            gluCylinder(pObj, 0.4f, 0.4f, 0.8f, 80, 13);
        glPopMatrix();

        glPushMatrix();  
            // Torre meio fundos
            glColor3f(1.0f, 0.5f, 0.0f);
            glTranslatef(0.0f, 0.5f, -2.0f);
            glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.4f, 0.0f, 0.7f, 80, 13); //0.0f no terceiro parametro para ser um cone

            glColor3f(0.45f, 0.45f, 0.45f);
            glTranslatef(0.0f, 0.0f, -0.8f);
            gluCylinder(pObj, 0.4f, 0.4f, 0.8f, 80, 13);
        glPopMatrix();

        glPushMatrix();
            // Torre esquerda fundos
            glColor3f(1.0f, 0.5f, 0.0f);  
            glTranslatef(-1.2f, 0.49f, -2.0f);
            glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.4f, 0.0f, 0.7f, 80, 13); //0.0f no terceiro parametro para ser um cone

            glColor3f(0.45f, 0.45f, 0.45f);
            glTranslatef(0.0f, 0.0f, -0.8f);
            gluCylinder(pObj, 0.4f, 0.4f, 0.8f, 80, 13);
        glPopMatrix();

        glPushMatrix();
            // Torre direita fundos
            glColor3f(1.0f, 0.5f, 0.0f);  
            glTranslatef(1.2f, 0.49f, -2.0f);
            glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.4f, 0.0f, 0.7f, 80, 13); //0.0f no terceiro parametro para ser um cone

            glColor3f(0.45f, 0.45f, 0.45f);
            glTranslatef(0.0f, 0.0f, -0.8f);
            gluCylinder(pObj, 0.4f, 0.4f, 0.8f, 80, 13);
        glPopMatrix();

    glPopMatrix();  

    // Muro frente
    // ...

    // Muro direita
    // ...

    // Muro esquerda
    // ...

    // Muro fundos
    // ...

    glutSwapBuffers();  
}
  
  
  
int main(int argc, char *argv[]){  
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(1000, 800);  
    glutCreateWindow("CGR0001 - Castelo com quadricas");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0;  
 }
