#include <GL/glut.h>

//#############################################//
//FUNCAO INICIALIZA OS PARAMETROS DE ILUMINACAO//
//#############################################//
void parametrosIluminacao(float x, float y, float z){

    GLfloat posicaoLuz[] = {x, y, z, 1.0};
    GLfloat luzAmbiente[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat luzDifusa[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat luzEspecular[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    GLfloat ka[]={0.50, 0.50, 0.50, 1.0};
    GLfloat kd[]={0.43, 0.47, 0.54, 1.0};
    GLfloat ks[]={1.0, 1.0, 1.0, 1.0};
    GLfloat shininess = 60.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

}

