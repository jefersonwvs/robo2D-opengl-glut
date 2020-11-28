#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

/* Estrutura de dados para armazenar um ponto. */
typedef struct point* Point;
struct point {
    GLfloat u;
    GLfloat v;
};

void init();
void reshape(int, int);
void display();
void mouseClick(int, int, int, int);
void keyboard(unsigned char, int, int);
void specialKeyboard(int, int, int);

void displayControlPoints();
void displayBezierCurves();
void bezierCurve1(int);
void bezierCurve2(int);
void bezierCurve3(int);
void setPoint(int, int);
double transformX(int);
double transformY(int);
void drawFoot(double, double);
void drawQuad();
void drawArm(double, double);
void drawTriangle();
void drawCircle();
void drawAxis(double);
void drawAxis2();
void drawLabel(double, double, double, double, double);
void drawObjs(double, double, double, double);
int movementLimitation(double, double, double);

#define SIZE 1000               // quantidade máxima de pontos que serão usados
Point P[SIZE];                  // vetor de pontos
int n;                          // índice do vetor de pontos
char mouseLocation[10] = "";    // vetor que guarda as coordenadas do cursor


int width = 700;
int height = 700;
int win;


#endif // HEADER_H_INCLUDED
