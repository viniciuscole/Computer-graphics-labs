#include "tiro.h"
#include <math.h>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
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

void Tiro::DesenhaTiro(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    DesenhaCirc(radiusTiro, 1.0, 1.0, 1.0);
    glPopMatrix();
}

void Tiro::Move(GLdouble dt)
{

    gX -= gVel * sin(gDirectionAng)*dt;
    gY += gVel * cos(gDirectionAng)*dt;
}

bool Tiro::Valido(GLdouble dt)
{
    if (sqrt((gX - gXInit)*(gX - gXInit) + (gY - gYInit)*(gY - gYInit)) > DISTANCIA_MAX)
        return false;
    return true;
}
