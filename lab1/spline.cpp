#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#define TAMANHO_JANELA 500
#define MAX_POINTS 100

float size = 5.0;
int nPoint = 4;

//Pontos de controle da Spline
GLfloat ctrlpoints[MAX_POINTS][3] = {
        { -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0},
        {2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}};

int ctrlpointStatus[MAX_POINTS];

float size_to_window(float size){
   return (size + 5) * 50;
}

float window_to_size(float window){
   return window / 50 - 5;
}

void initControlPoints(){
   for(int i = 0; i < MAX_POINTS; i++){
      ctrlpointStatus[i] = 0;
   }
}

void keyPress(unsigned char key, int x, int y){
   switch(key){
      case '+':
         if (nPoint < MAX_POINTS)
            nPoint++;
            ctrlpoints[nPoint - 1][0] = 0.0;
            ctrlpoints[nPoint - 1][1] = 0.0;
            ctrlpoints[nPoint - 1][2] = 0.0;
            glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, nPoint, &ctrlpoints[0][0]);
         break;
      case '-':
         if (nPoint > 2)
            nPoint--;
            glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, nPoint, &ctrlpoints[0][0]);
         break;
   }
   glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y){
    y = TAMANHO_JANELA - y;
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            for(int i = 0; i < nPoint; i++){
                if(abs(x - size_to_window(ctrlpoints[i][0])) < 30 && abs(y - size_to_window(ctrlpoints[i][1])) < 30){
                    ctrlpointStatus[i] = 1;
                    return;
                }
            }
        } else if (state == GLUT_UP) {
            for(int i = 0; i < nPoint; i++){
                ctrlpointStatus[i] = 0;
            }
        }
    }
}

void mouseMotion(int x, int y){
   y = TAMANHO_JANELA - y;
   for(int i = 0; i < nPoint; i++){
      if(ctrlpointStatus[i]){
         ctrlpoints[i][0] = window_to_size(x);
         ctrlpoints[i][1] = window_to_size(y);
      }
   }
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, nPoint, &ctrlpoints[0][0]);
   glutPostRedisplay();
}

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_MAP1_VERTEX_3);

   //Definicao do polinomio com os pontos de controle
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, nPoint, &ctrlpoints[0][0]);

   //Muda para a matriz de projecao (aulas futuras)
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //Define a area/volume de visualizacao. Os objetos desenhados devem estar dentro desta area
   glOrtho(-size, size, -size, size, -size, size);

   initControlPoints();
   glutMouseFunc(mouseClick);
   glutMotionFunc(mouseMotion);
   glutKeyboardFunc(keyPress);
}

void display(void)
{
   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   /* Desenha a curva aproximada por n+1 pontos. */
   int n = 30;
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINE_STRIP);
      for (i = 0; i <= n; i++){
        //Avaliacao do polinomio, retorna um vertice (equivalente a um glVertex3fv)
        glEvalCoord1f((GLfloat) i/(GLfloat)n);
      }
   glEnd();

   /* Desenha os pontos de controle. */
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < nPoint; i++)
         glVertex3fv(&ctrlpoints[i][0]);
   glEnd();

   glutSwapBuffers();
}

void reshape(int w, int h)
{
   //Define a porcao visivel da janela
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);

   //Muda para a matriz de projecao (aulas futuras)
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   //Controla o redimensionamento da janela mantendo o aspect ration do objeto
   if (w <= h)
      glOrtho(-size, size, -size*(GLfloat)h/(GLfloat)w,
               size*(GLfloat)h/(GLfloat)w, -size, size);
   else
      glOrtho(-size*(GLfloat)w/(GLfloat)h,
               size*(GLfloat)w/(GLfloat)h, -size, size, -size, size);

   //Muda para a matriz de trasformacoes (aulas futuras)
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
