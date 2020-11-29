#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

/* Estrutura de dados para armazenar um ponto. */
typedef struct point* Point;
struct point {
    GLfloat u;
    GLfloat v;
};

/* Função de inicialização */
void init(void);

/* Funções Callback */
void reshape(int, int);
void display(void);
void mouseClick(int, int, int, int);
void keyboard(unsigned char, int, int);
void specialKeyboard(int, int, int);

/* Funções de desenho */
void drawRobot(void);
void drawFoot(double, double);
void drawArm(double, double);
void drawAxis(double);
void drawLabel(double, double, double);
void drawObjs(double, double, double);

/* Funções de primitivas */
void quad(void);
void triangle(void);
void circle(void);

/* Demais funções: utilitárias */
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

#define SIZE 1000	// quantidade máxima de pontos que serão usados
Point P[SIZE];      // vetor de pontos
int n;              // índice do vetor de pontos

int width = 745;	// largura inicial da tela
int height = 745;	// largura inicial da altura
int win;			// limites dos eixos da projeção ortográfica

/* Posições iniciais das partes do robô */
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

int go = 0;			// variável que funciona como "botão" para movimentar o robô na trajetória

#endif
