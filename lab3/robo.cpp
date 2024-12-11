#include "robo.h"
#include <math.h>
#include <iostream>
using namespace std;

void Robo::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glVertex2f(-width/2, 0);
    glVertex2f(width/2, 0);
    glVertex2f(width/2, height);
    glVertex2f(-width/2, height);
    glEnd();
}

void Robo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    // desenhar só os pontos
    glColor3f(R, G, B);
    glBegin(GL_POINTS);
    for (int i = 0; i < 360; i+=10)
    {
        float theta = i * 3.1415926 / 180;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}

void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(thetaWheel, 0, 0, 1);
    DesenhaCirc(radiusWheel, R, G, B);
    glPopMatrix();
}

void Robo::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(theta1, 0, 0, 1);
    DesenhaRect(paddleHeight, paddleWidth, 0.0, 0.0, 1.0);

    glTranslatef(0, paddleHeight, 0);
    glRotatef(theta2, 0, 0, 1);
    DesenhaRect(paddleHeight, paddleWidth, 1.0, 1.0, 0.0);

    glTranslatef(0, paddleHeight, 0);
    glRotatef(theta3, 0, 0, 1);
    DesenhaRect(paddleHeight, paddleWidth, 0.0, 1.0, 0.0);

    glPopMatrix();
}

void Robo::DesenhaRobo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    DesenhaRect(baseHeight, baseWidth, 1.0, 0.0, 0.0);

    DesenhaBraco(0, baseHeight, theta1, theta2, theta3);

    DesenhaRoda(-baseWidth/2, 0, thetaWheel, 1.0, 1.0, 1.0);

    DesenhaRoda(baseWidth/2, 0, thetaWheel, 1.0, 1.0, 1.0);

    glPopMatrix();
}

void Robo::RodaBraco1(GLfloat inc)
{
    gTheta1 += inc;
}

void Robo::RodaBraco2(GLfloat inc)
{
    gTheta2 += inc;
}

void Robo::RodaBraco3(GLfloat inc)
{
    gTheta3 += inc;
}

void Robo::MoveEmX(GLfloat dx)
{
    gX += dx;
    gThetaWheel -= (dx / radiusWheel) * 360.0f;
}

//Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){
    // Converte o ângulo para radianos
    GLfloat angleRad = angle * 3.1415926 / 180;

    // Aplica a rotação
    xOut = x * cos(angleRad) - y * sin(angleRad);
    yOut = x * sin(angleRad) + y * cos(angleRad);
}

Tiro* Robo::Atira()
{
    GLfloat xBase = gX;
    GLfloat yBase = gY + baseHeight;

    // Variáveis para acumular a posição atual
    GLfloat xCurrent = xBase;
    GLfloat yCurrent = yBase;

    // Variáveis temporárias para a rotação
    GLfloat xRotated, yRotated;

    // Transformação do primeiro segmento
    RotatePoint(0, paddleHeight, gTheta1, xRotated, yRotated);
    xCurrent += xRotated;
    yCurrent += yRotated;

    // Transformação do segundo segmento
    RotatePoint(0, paddleHeight, gTheta1 + gTheta2, xRotated, yRotated);
    xCurrent += xRotated;
    yCurrent += yRotated;

    // Transformação do terceiro segmento (ponta da haste)
    RotatePoint(0, paddleHeight, gTheta1 + gTheta2 + gTheta3, xRotated, yRotated);
    xCurrent += xRotated;
    yCurrent += yRotated;

    // Ângulo do tiro
    GLfloat angle = gTheta1 + gTheta2 + gTheta3;

    // Cria o tiro
    Tiro* tiro = new Tiro(xCurrent, yCurrent, angle * 3.1415926 / 180);
    return tiro;
}

