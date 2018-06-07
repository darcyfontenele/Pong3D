#include <GL/glut.h>
#include <cmath>

//##################//
//FUNCAO MODELA CUBO//
//##################//
void cubo(int x, int y, int z, int dimensao){
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3i(x, y, z);
    glVertex3i(x+dimensao, y, z);
    glVertex3i(x+dimensao, y+dimensao, z);
    glVertex3i(x, y+dimensao, z);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3i(x, y, z);
    glVertex3i(x, y, z+dimensao);
    glVertex3i(x, y+dimensao, z+dimensao);
    glVertex3i(x, y+dimensao, z);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3i(x+dimensao, y, z);
    glVertex3i(x+dimensao, y, z+dimensao);
    glVertex3i(x+dimensao, y+dimensao, z+dimensao);
    glVertex3i(x+dimensao, y+dimensao, z);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3i(x+dimensao, y, z+dimensao);
    glVertex3i(x, y, z+dimensao);
    glVertex3i(x, y+dimensao, z+dimensao);
    glVertex3i(x+dimensao, y+dimensao, z+dimensao);
    glEnd();
}

//############################//
//FUNCAO MODELA PARALELEPIPEDO//
//############################//
void paralelepipedo(int x, int y, int z, int largura, int altura, int comprimento){
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glVertex3f(x, y, z);
    glVertex3f(x+largura, y, z);
    glVertex3f(x+largura, y+altura, z);
    glVertex3f(x, y+altura, z);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z+comprimento);
    glVertex3f(x, y+altura, z+comprimento);
    glVertex3f(x, y+altura, z);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glVertex3f(x+largura, y, z);
    glVertex3f(x+largura, y, z+comprimento);
    glVertex3f(x+largura, y+altura, z+comprimento);
    glVertex3f(x+largura, y+altura, z);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glVertex3f(x, y, z+comprimento);
    glVertex3f(x+largura, y, z+comprimento);
    glVertex3f(x+largura, y+altura, z+comprimento);
    glVertex3f(x, y+altura, z+comprimento);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glVertex3f(x, y, z);
    glVertex3f(x+largura, y, z);
    glVertex3f(x+largura, y, z+comprimento);
    glVertex3f(x, y, z+comprimento);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glVertex3f(x, y+altura, z);
    glVertex3f(x+largura, y+altura, z);
    glVertex3f(x+largura, y+altura, z+comprimento);
    glVertex3f(x, y+altura, z+comprimento);
    glEnd();
}

//##################//
//FUNCAO MODELA PISO//
//##################//
void piso(int x, int y, int z, int largura, int comprimento){
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
    glVertex3i(x, y, z);
    glVertex3i(x+largura, y, z);
    glVertex3i(x+largura, y, z+comprimento);
    glVertex3i(x, y, z+comprimento);
    glEnd();
}

//#######################//
//FUNCAO MODELA OBSTACULO//
//#######################//
void obstaculo(int x, int y, int z, GLfloat radio){
    glTranslatef(x, y, z);
    glutSolidSphere(radio, 20, 20);
}

//############################//
//FUNCAO MODELA CIRCUNFERENCIA//
//############################//
void circunferencia(int raio, int fatias, int stacks){
    glutSolidSphere(raio, fatias, stacks);
}