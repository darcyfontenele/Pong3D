#ifndef PINBALL_DESENHOS_H
#define PINBALL_DESENHOS_H

void desenhaOrigem();
void desenhaEixosCoordenados();
void desenhaPiso(int x, int y, int z, int largura, int comprimento);
void desenhaObstaculo(int x, int y, int z);
void desenhaParedes(int largura, int altura, int comprimento);
void desenhaBola(int x, int y, int raio);
void desenhaJogador(int x, int y, int z, int t);

#endif //PINBALL_DESENHOS_H