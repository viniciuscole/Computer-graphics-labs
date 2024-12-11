#include "alvo.h"
#include <math.h>

#include <iostream>
using namespace std;

void Alvo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    // desenhar o circulo todo
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i+=10)
    {
        float theta = i * 3.1415926 / 180;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}

void Alvo::DesenhaAlvo(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    switch (gColor)
    {
        case 0:
            DesenhaCirc(radiusAlvo, 1.0, 0.0, 0.0);
            break;
        case 1:
            DesenhaCirc(radiusAlvo, 0.0, 1.0, 0.0);
            break;
        case 2:
            DesenhaCirc(radiusAlvo, 0.0, 0.0, 1.0);
            break;
        default:
        break;
    }
    glPopMatrix();
}

void Alvo::Recria(GLfloat x, GLfloat y)
{
    gX = x;
    gY = y;
    gColor = ++gColor % 3;
}

bool Alvo::Atingido(Tiro *tiro)
{
    GLfloat x, y;
    tiro->GetPos(x, y);
    GLfloat dx = x - gX;
    GLfloat dy = y - gY;

    if (sqrt(dx*dx + dy*dy) < radiusAlvo + radiusTiro)
        return true;
    return false;
}
