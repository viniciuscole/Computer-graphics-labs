#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define TAMANHO_JANELA 500

float gx = 0.0;
float gy = 0.0;
int keyStatus[256];
int mouseStatus[3];

void initKeyStatus(){
   for(int i = 0; i < 256; i++){
      keyStatus[i] = 0;
   }
}

void mouse(int button, int state, int x, int y){
   y = TAMANHO_JANELA - y;
   if (button == GLUT_LEFT_BUTTON) {
      if (state == GLUT_DOWN) {
         mouseStatus[0] = 1;
         gx = (float)x / TAMANHO_JANELA - 0.5;
         gy = (float)y / TAMANHO_JANELA - 0.5;
      } else if (state == GLUT_UP) {
         mouseStatus[0] = 0;
      }
   }
}

void mouseMotion(int x, int y){
   y = TAMANHO_JANELA - y;
   if(mouseStatus[0]){
      gx = (float)x / TAMANHO_JANELA - 0.5;
      gy = (float)y / TAMANHO_JANELA - 0.5;
   }
   glutPostRedisplay();
}

void idle(){
   if(keyStatus['w']){
      gy += 0.01;
   }
   if(keyStatus['s']){
      gy -= 0.01;
   }
   if(keyStatus['a']){
      gx -= 0.01;
   }
   if(keyStatus['d']){
      gx += 0.01;
   }
   glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y){
   switch(key){
      case 'w':
         keyStatus['w'] = 0;
         break;
      case 's':
         keyStatus['s'] = 0;
         break;
      case 'a':
         keyStatus['a'] = 0;
         break;
      case 'd':
         keyStatus['d'] = 0;
         break;
   }
   glutPostRedisplay();
}

void keyPress(unsigned char key, int x, int y){
   switch(key){
      case 'w':
         keyStatus['w'] = 1;
         break;
      case 's':
         keyStatus['s'] = 1;
         break;
      case 'a':
         keyStatus['a'] = 1;
         break;
      case 'd':
         keyStatus['d'] = 1;
         break;
   }
   glutPostRedisplay();
}

void display(void)
{
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   glColor3f (1.0, 0.4, 0.7);
   /* Desenhar um polígono branco (retângulo) */
   glBegin(GL_POLYGON);
      glVertex3f (0.25 + gx, 0.25 + gy, 0.0);
      glVertex3f (0.75 + gx, 0.25 + gy, 0.0);
      glVertex3f (0.75 + gx, 0.75 + gy, 0.0);
      glVertex3f (0.25 + gx, 0.75 + gy, 0.0);
   glEnd();

   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void init (void)
{
   /* selecionar cor de fundo (preto) */
   glClearColor (0.0, 0.0, 0.0, 0.0);

   /* inicializar sistema de visualizacao */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

   initKeyStatus();
   glutKeyboardFunc(keyPress);
   glutKeyboardUpFunc(keyUp);
   glutIdleFunc(idle);
   glutMouseFunc(mouse);
   glutMotionFunc(mouseMotion);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello world");
   init ();
   glutDisplayFunc(display);

   glutMainLoop();

   return 0;
}
