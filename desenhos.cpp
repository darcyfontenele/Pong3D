#include <GL/glut.h>
#include "formas.h"

//#######################################//
//FUNCAO PARA DESENHAR UM PONTO NA ORIGEM//
//#######################################//
void desenhaOrigem(){
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3i(0, 0, 0);
    glEnd();
}

//#########################################//
//FUNCAO PARA DESENHAR OS EIXOS COORDENADOS//
//#########################################//
void desenhaEixosCoordenados(){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 9999, 0);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(9999, 0, 0);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 9999);
    glEnd();
}

//###########################//
//FUNCAO PARA DESENHAR O PISO//
//###########################//
void desenhaPiso(int x, int y, int z, int largura, int comprimento){
    glColor3f(0.871, 0.722, 0.529);
    piso(x, y, z, largura, comprimento);
}

//##################################//
//FUNCAO PARA DESENHAR OS OBSTACULOS//
//##################################//
void desenhaObstaculo(int x, int y, int z){
    glColor3f(0.545, 0, 0);
    glPushMatrix();
    obstaculo(x, y, z, 30);
    glPopMatrix();
}

//##############################//
//FUNCAO PARA DESENHAR UM PLAYER//
//##############################//
void desenhaJogador(int x, int y, int z, int t){
    glColor3f(0.545, 0, 0);
    glTranslated(t, 0, 0);
    paralelepipedo(x, y, z, 100, 20, 30);
}

//############################//
//FUNCAO PARA DESENHAR PAREDES//
//############################//
void desenhaParedes(int largura, int altura, int comprimento){
    glColor3f(0.545, 0.271, 0.075);
    paralelepipedo(0, 0, 0, 20, altura, comprimento); //ESQUERDA
    paralelepipedo(largura-20, 0, 0, 20, altura, comprimento); //DIREITA
    paralelepipedo(0, 0, 0, largura, altura, 20);
    paralelepipedo(0, 0, comprimento-20, largura, altura, 20);
}

//###########################//
//FUNCAO PARA DESENHAR A BOLA//
//###########################//
void desenhaBola(int x, int z, int raio){
    glColor3f(0, 0, 0.502);
    glPushMatrix();
    glTranslated(x, 15, z);
    circunferencia(raio, 20, 10);
    glPopMatrix();
}