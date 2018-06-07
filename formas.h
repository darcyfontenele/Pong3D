#ifndef PINBALL_FORMAS_H
#define PINBALL_FORMAS_H
#include <GL/glut.h>

void cubo(int x, int y, int z, int dimensao);
void paralelepipedo(int x, int y, int z, int largura, int altura, int comprimento);
void piso(int x, int y, int z, int largura, int comprimento);
void obstaculo(int x, int y, int z, GLfloat radio);
void circunferencia(int raio, int fatias, int stack);
#endif //PINBALL_FORMAS_H