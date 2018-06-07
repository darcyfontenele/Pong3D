#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include "desenhos.h"
#include "iluminacao.h"

#define LARGURA 800
#define ALTURA 800

//################################//
//      TRABALHO FINAL - PONG     //
// Disciplina: Computacao Grafica //
// Semestre: 2017.2               //
// Alunos: Darcy Fontenele        //
//         Levy Gurgel            //
//         Aurelio Araripe        //
//################################//

using namespace std;

//###################//
//VARIAVEIS DA CAMERA//
//###################//
double cRotationX = 0.0;
double cRotationY = 15.0;
int lastPressX = 0;
int lastPressY = 0;
double zoom = 60.0;
double xCamera = 250.0;
double zCamera = 1800.0;
double yCamera = 600.0;

//#######################//
//VARIAVEIS DE ILUMINACAO//
//#######################//
int lightX = 250.0;
int lightY = 100.0;
int lightZ = 400.0;
bool isLight = false;

//#####################//
//VARIAVEIS DO PLAYER 1//
//#####################//
int accumulated1 = 0;
int x1 = 200;
int z1 = 80;
int p1 = 0;

//#####################//
//VARIAVEIS DO PLAYER 2//
//#####################//
int accumulated2 = 0;
int x2 = 200;
int z2 = 1010;
int p2 = 0;

//#################//
//VARIAVEIS DA BOLA//
//#################//
double bPosX = 250;
double bPosY = 550;
int radio = 15;

//#################################//
//VARIAVEIS DE MOVIMENTACAO DA BOLA//
//#################################//
int keyPressed = 0;
double stepX = 2; //FIXO
double stepY = 5; //FIXO
bool crashedObs[] = {false, false};
bool crashedPlayer[] = {false, false};
int numRandX = 0;
int numRandY = 0;
bool jogoInicio = true;

//########################//
//VARIAVEIS DO OBSTACULO 1//
//########################//
int obs1X = 150;
int obs1Y = 550;

//########################//
//VARIAVEIS DO OBSTACULO 2//
//########################//
int obs2X = 350;
int obs2Y = 550;

//#############################//
//FUNCAO PARA DESENHO DE TEXTOS//
//#############################//
void drawText(string text, float x, float y, float z, int size) {
    glTranslated(x, y, z);
    glScaled(size, size, size);

    for(int i=0;i<text.length();i++){
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, int(text[i]));
    }
}

string IntToString (int a) {
    ostringstream temp;
    temp<<a;
    return temp.str();
}

//######################//
//FUNCAO DE RENDERIZACAO//
//######################//
void render(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xCamera, yCamera, zCamera,
              xCamera, 0.0, 200.0,
              0.0, 1.0, 0.0);
    glRotatef(cRotationY, 1.0, 0.0, 0.0);
    glRotatef(cRotationX, 0.0, 1.0, 0.0);
    parametrosIluminacao(lightX, lightY, lightZ);

    //CAMPO DE JOGO
    desenhaPiso(0, 0, 0, 500, 1100);
    desenhaParedes(500, 20, 1100);
    desenhaObstaculo(obs1X, 0, obs1Y);
    desenhaObstaculo(obs2X, 0, obs2Y);

    //PLAYER 1
    glPushMatrix();
    desenhaJogador(x1, 0, z1, accumulated1);
    glPopMatrix();

    //PLAYER 2
    glPushMatrix();
    desenhaJogador(x2, 0, z2, accumulated2);
    glPopMatrix();

    //BOLA
    glPushMatrix();
    desenhaBola(bPosX, bPosY, radio);
    glPopMatrix();

    //TEXTO
    glPointSize(1);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    drawText(IntToString(p2), -350, 100, 0, 3);
    glPopMatrix();
    glPushMatrix();
    drawText(IntToString(p1), 500, 100, 0, 3);
    glPopMatrix();

    glFlush();
}

//#########################//
//FUNCAO MOVIMENTO DO MOUSE//
//#########################//
void mouseMotion(int x, int y){
    cRotationX += (double)(x - lastPressX);
    lastPressX = x;
//    cRotationY += (double)(y - lastPressY);
//    lastPressY = y;
    glutPostRedisplay();
}

//###################//
//FUNCAO CLIQUE NO MOUSE//
//###################//
void mousePress(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        lastPressX = x;
        lastPressY = y;
    }
}

double distance(double x1, double y1, double x2, double y2){
    double x = fabs(x1 - x2);
    double y = fabs(y1 - y2);
    return (x*x) + (y*y);
}

//#######################//
//FUNCAO ANIMACAO DA BOLA//
//#######################//
void ballAnim(int value){
        if(keyPressed == 1){
	    if(jogoInicio){
		srand(time(0));
		numRandX = (rand()-rand())%10;
		numRandY = (rand()-rand())%10;
		bPosY += numRandY;
		bPosX += numRandX;
		if(numRandX < 0){stepX = -stepX;}
		if (numRandY < 0){stepY = -stepY;}

		jogoInicio = false;
	    }
	    else{
            bPosY += stepY;
            bPosX += stepX;
            if (bPosX <= 42){ //COLISAO PAREDE LATERAL ESQUERDA
                cout << "bateu Parede Lateral" << endl;
                stepX = (-1)*stepX;
                crashedObs[1] = false;
                crashedObs[2] = false;
                crashedPlayer[1] = false;
                crashedPlayer[2] = false;
            }
            if (bPosX > 450){ //COLISAO PAREDE LATERAL DIREITA
                cout << "bateu Parede Lateral" << endl;
                stepX = (-1)*stepX;
                crashedObs[1] = false;
                crashedObs[2] = false;
                crashedPlayer[1] = false;
                crashedPlayer[2] = false;
            }
            if (bPosY >= 1060){ //COLISAO CHAO
                cout << "bateu Chao" << endl;
                stepY = (-1)*stepY;
                p1 += 1;
                bPosX = 250;
                bPosY = 550;
                stepX = 2;
                stepY = 5;
                crashedObs[1] = false;
                crashedObs[2] = false;
                crashedPlayer[1] = false;
                crashedPlayer[2] = false;
		jogoInicio = true;
            }
            if (bPosY <= 50){ //COLISAO TETO
                cout << "bateu Teto" << endl;
                stepY = (-1)*stepY;
                p2 += 1;
                bPosX = 250;
                bPosY = 550;
                stepX = 2;
                stepY = 5;
                crashedObs[1] = false;
                crashedObs[2] = false;
                crashedPlayer[1] = false;
                crashedPlayer[2] = false;
		jogoInicio = true;
            }
            if(bPosX >= x1+accumulated1 && bPosX <= x1+accumulated1+100 && bPosY+radio <= 150) { //COLISAO PLAYER 1
                if(!crashedPlayer[1]){
                    crashedObs[1] = false;
                    crashedObs[2] = false;
                    crashedPlayer[1] = true;
                    crashedPlayer[2] = false;
                    stepY = (-1)*stepY;
                }
            }
            if(bPosX >= x2+accumulated2 && bPosX <= x2+accumulated2+100 && bPosY+radio >= 1010) { //COLISAO PLAYER 2
                if(!crashedPlayer[2]){
                    crashedObs[1] = false;
                    crashedObs[2] = false;
                    crashedPlayer[1] = false;
                    crashedPlayer[2] = true;
                    stepY = (-1)*stepY;
                }
            }
            if(distance(bPosX, bPosY, obs1X, obs1Y) <= ((15+30)*(15+30))){ //COLISAO OBSCTACULO 1
                if(!crashedObs[1]){
                    std::cout << "bateuOBS1" << std::endl;
                    crashedObs[1] = true;
                    stepY = (-1)*stepY;
                    crashedObs[2] = false;
                    crashedPlayer[1] = false;
                    crashedPlayer[2] = false;
                }
            }
            if(distance(bPosX, bPosY, obs2X, obs2Y) <= ((15+30)*(15+30))){ //COLISAO OBSTACULO 2
                if(!crashedObs[1]){
                    std::cout << "bateuOBS2" << std::endl;
                    crashedObs[2] = true;
                    stepY = (-1)*stepY;
                    crashedObs[1] = false;
                    crashedPlayer[1] = false;
                    crashedPlayer[2] = false;
                }
            }
        }
        if(stepY <= 0){
            stepY -= 0.01;
        } else{
            stepY += 0.01;
        }

	}
        glutPostRedisplay();
        glutTimerFunc(20, ballAnim, 1);
}

//###########################//
//FUNCAO ANIMACAO DO PLAYER 1//
//###########################//
void player1Anim(char key){
    if(key == 'z'){
        if(x1+accumulated1 > 20){
            accumulated1 -= 15;
        }
    } else{
        if(x1+accumulated1 < 380){
            accumulated1 += 15;
        }
    }
    glutPostRedisplay();
}

//###########################//
//FUNCAO ANIMACAO DO PLAYER 2//
//###########################//
void player2Anim(char key){
    if(key == 'l'){
        if(x2+accumulated2 > 20){
            accumulated2 -= 15;
        }
    } else{
        if(x2+accumulated2 < 380){
            accumulated2 += 15;
        }
    }
    glutPostRedisplay();
}

//###############################//
//FUNCAO PRESSIONA TECLA ESPECIAL//
//###############################//
void keyboardSpecialPress(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            player2Anim('l');
            break;
        case GLUT_KEY_RIGHT:
            player2Anim('r');
            break;
    }
}

//##############################//
//FUNCAO PRESSIONA TECLA TECLADO//
//##############################//
void keyboardPress(unsigned char key, int x, int y){
    switch(key){
        case 'W':
        case 'w':
            zCamera -= 10;
            break;
        case 'S':
        case 's':
            zCamera += 10;
            break;
        case 'A':
        case 'a':
            yCamera -= 10;
            break;
        case 'D':
        case 'd':
            yCamera += 10;
            break;
        case 'P':
	    case 'p':
            keyPressed = 1;
            break;
        case 'L':
        case 'l':
            if(isLight){
                glDisable(GL_LIGHT0);
                isLight = false;
            } else{
                glEnable(GL_LIGHT0);
                isLight = true;
            }
            break;
        case 'R':
        case 'r':
            keyPressed = 0;
            bPosX = 250;
            bPosY = 550;
            p1 = 0;
            p2 = 0;
            crashedObs[1] = false;
            crashedObs[2] = false;
            crashedPlayer[1] = false;
            crashedPlayer[2] = false;
            break;
        case 'Z':
        case 'z':
            player1Anim('z');
            break;
        case 'C':
        case 'c':
            player1Anim('c');
            break;
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

//##################//
//FUNCAO MENU CAMERA//
//##################//
void menuCamera(int op){
    switch(op){
        case 1:
            keyboardPress('w', 1, 1);
            break;
        case 2:
            keyboardPress('s', 1, 1);
            break;
        case 3:
            keyboardPress('a', 1, 1);
            break;
        case 4:
            keyboardPress('d', 1, 1);
            break;
    }
}

//######################//
//FUNCAO MENU ILUMINACAO//
//######################//
void menuIluminacao(int op) {
    switch(op){
        case 1:
            keyboardPress('l', 1, 1);
            break;
    }
}

//#####################//
//FUNCAO MENU PRINCIPAL//
//#####################//
void menuPrincipal(int op) {
    switch(op){
        case 1:
            keyboardPress(27, 1, 1);
            break;
    }
}

//################//
//FUNCAO CRIA MENU//
//################//
void createMenu(){
    int subMenu1 = glutCreateMenu(menuCamera);
    glutAddMenuEntry("Zoom in (w)", 1);
    glutAddMenuEntry("Zoom out (s)", 2);
    glutAddMenuEntry("Incline (a)", 3);
    glutAddMenuEntry("Decline (d)", 4);
    int subMenu2 = glutCreateMenu(menuIluminacao);
    glutAddMenuEntry("Light on/off (l)", 1);
    int menu = glutCreateMenu(menuPrincipal);
    glutAddSubMenu("Camera", subMenu1);
    glutAddSubMenu("Iluminacao", subMenu2);
    glutAddMenuEntry("Exit (ESC)", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//##########################//
//FUNCAO INICIALIZA MATRIZES//
//##########################//
void start(void) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0f, 1.0f, -1.5f, 0.5f, 2.0, 3000.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_LIGHT0);
    isLight = true;
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

//################//
//FUNCAO PRINCIPAL//
//################//
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(LARGURA, ALTURA);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Pong 3D");
    glutDisplayFunc(render);
    createMenu();
    glutKeyboardFunc(keyboardPress);
    glutSpecialFunc(keyboardSpecialPress);
    glutMouseFunc(mousePress);
    glutMotionFunc(mouseMotion);
    start();
    glutTimerFunc(100, ballAnim, 1);
    glutMainLoop();
}
