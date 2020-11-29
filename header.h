#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

/* Estrutura de dados para armazenar um ponto. */
typedef struct point* Point;
struct point {
    GLfloat u;
    GLfloat v;
};

/* Fun��o de inicializa��o */
void init(void);

/* Fun��es Callback */
void reshape(int, int);
void display(void);
void mouseClick(int, int, int, int);
void keyboard(unsigned char, int, int);
void specialKeyboard(int, int, int);

/* Fun��es de desenho */
void drawRobot(void);
void drawFoot(double, double);
void drawArm(double, double);
void drawAxis(double);
void drawLabel(double, double, double);
void drawObjs(double, double, double);

/* Fun��es de primitivas */
void quad(void);
void triangle(void);
void circle(void);

/* Demais fun��es: utilit�rias */
void displayInfo(void);
void displayText(int, int, char*);
void displayControlPoints(void);
void displayBezierCurves(void);
void bezierCurve1(int);
void bezierCurve2(int);
void bezierCurve3(int);
void setPoint(int, int);
double transformX(int);
double transformY(int);
int movementLimitation(double, double, double);
void walkInTheTrajectory();
void clearTrajectory();

#define SIZE 1000	// quantidade m�xima de pontos que ser�o usados
Point P[SIZE];      // vetor de pontos
int n;              // �ndice do vetor de pontos

int width = 745;	// largura inicial da tela
int height = 745;	// largura inicial da altura
int win;			// limites dos eixos da proje��o ortogr�fica

/* Posi��es iniciais das partes do rob� */
int x_foot;
int y_foot;
float y_arm2;
float y_arm3;
float angle_arm1;
float angle_arm2;
float angle_arm3;
float angle_obj4;
float angle_arm5;
float angle_obj6;
float angle_arm7;

int go = 0;			// vari�vel que funciona como "bot�o" para movimentar o rob� na trajet�ria

#endif
