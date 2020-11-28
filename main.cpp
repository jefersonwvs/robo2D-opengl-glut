#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "header.h"

int x_foot;
int y_foot;
float y_arm2;
float y_arm3;

double p;
double k;
double d;
double b;
double h;
double c;

float angle_arm1;
float angle_arm2;
float angle_arm3;
float angle_obj4;
float angle_arm5;
float angle_obj6;
float angle_arm7;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("LCG - Atividade 02 - Robo");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);

	init();
	glutMainLoop();

	return 0;
}

void init() {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	win = 100;

	for (int i = 0; i < SIZE; i++) {
        P[i] = NULL;
	}
	n = 0;

	x_foot = 0;
	y_foot = 0;
	y_arm2 = 60.0;
	y_arm3 = 36.0;

	p = 6.0;
	k = 1.5;
	d = 2.5;
    b = 2.5;
    h = 6.0;
    c = 0.625;

    angle_arm1 = 0.0;
    angle_arm2 = -100.0;
    angle_arm3 = 45.0;
    angle_obj4 = 135.0;
    angle_arm5 = -30.0;
    angle_obj6 = 45.0;
    angle_arm7 = 30.0;
}

void reshape(int width1, int height1)
{
    width = width1;
    height = height1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (height == 0) {
		height = 1;
	}
	if (width <= height) {
		gluOrtho2D(-win, win, -win * height/width, win * height/width);
	} else {
        gluOrtho2D(-win * width/height, win * width/height, -win, win);
	}

}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glTranslated(x_foot, y_foot, 0.0);
	drawFoot(p, k);

	glTranslated(0.0, 7.5, 0.0);
	glRotated(angle_arm1, 0.0, 0.0, 1.0);
    drawArm(b, h);  // braço 1

    drawAxis(d);

    drawLabel(0.0, 0.0, 0.0, 0.20*p, 0.25*k);

    glTranslated(0.0, y_arm2, 0.0);
    glRotated(angle_arm2, 0.0, 0.0, 1.0);
    drawArm(0.7*b, 0.6*h);

    drawAxis(0.7*d);

    drawLabel(0.0, 0.0, 0.0, c, c/3);
    drawLabel(90.0, 0.0, 0.0, c, c/3);

    glTranslated(0.0, y_arm3, 0.0);
    glRotated(angle_arm3, 0.0, 0.0, 1.0);
    drawArm(0.5*b, 0.4*h);

    drawAxis(0.5*d);

    drawLabel(0.0, 0.0, 0.0, 0.7*c, 0.7*(c/3));
    drawLabel(90.0, 0.0, 0.0, 0.7*c, 0.7*(c/3));

    glTranslated(0.0, 24.0, 0.0);
    glPushMatrix();
        glRotated(angle_obj4, 0.0, 0.0, 1.0);
        drawObjs(7.5, 0.0, 0.2*p, 0.3*k);
        glTranslated(12.0, 0.0, 0.0);
        glRotated(-angle_obj4, 0.0, 0.0, 1.0); // !!!
        glRotated(angle_arm5, 0.0, 0.0, 1.0);
        drawArm(0.2*b, 0.2*h);
        drawAxis(0.2*d);
    glPopMatrix();

    glPushMatrix();
        glRotated(angle_obj6, 0.0, 0.0, 1.0);
        drawObjs(7.5, 0.0, 0.2*p, 0.3*k);
        glTranslated(12.0, 0.0, 0.0);
        glRotated(-angle_obj6, 0.0, 0.0, 1.0); // !!!
        glRotated(angle_arm7, 0.0, 0.0, 1.0);
        drawArm(0.2*b, 0.2*h);
        drawAxis(0.2*d);
    glPopMatrix();

    drawAxis(0.3*d);

    /*glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2d(0.0, 0.0);
        glVertex2d(0.0, 20.0);
        glVertex2d(0.0, 0.0);
        glVertex2d(10.0, 0.0);
    glEnd();*/

	glFlush();
}




/* Desenho do retângulo do pé */
void drawFoot(double p, double k)
{
    glPushMatrix();
        glColor3f(1.0, 0.5, 0.0);
        glScaled(p, k, 0.0);
        drawQuad();
    glPopMatrix();
}

void drawQuad()
{
    glRectf(-5.0, -5.0, 5.0, 5.0);
}


void drawArm(double b, double h)
{
    glPushMatrix();
        glColor3f(1.0, 0.5, 1.0);
        glScaled(b, h, 0.0);
        drawTriangle();
    glPopMatrix();
}


void drawTriangle()
{
    glBegin(GL_TRIANGLES);
        glVertex2f(-5.0, 0.0);
        glVertex2f(5.0, 0.0);
        glVertex2f(0.0, 10.0);
    glEnd();
}


void drawAxis(double d)
{
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
        glScaled(d, d, 0.0);
        drawCircle();
    glPopMatrix();
}


void drawCircle()
{
    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            double theta = i*3.142/180;
            double x = 5.0 * cos(theta);
            double y = 5.0 * sin(theta);
            glVertex2d(x, y);
        }
    glEnd();
}


void drawLabel(double angle, double x, double y, double p, double k)
{
    /* Desenha o sinal de translação ( – )*/
    glColor3d(0.0, 0.0, 1.0);
    glPushMatrix();
    glRotated(angle, 0.0, 0.0, 1.0);
        glTranslated(x, y, 0.0);
        glScaled(p, k, 0.0);
        drawQuad();
    glPopMatrix();
}

void drawObjs(double x, double y, double p, double k)
{
    glColor3f(1.0, 0.5, 1.0);
    glPushMatrix();
        glTranslated(x, y, 0.0);
        glScaled(p, k, 0.0);
        drawQuad();
    glPopMatrix();
}

void keyboard(unsigned char key, int x, int y)
{
    int mod = 0;
    switch (key) {

        case 'a':
            angle_arm1--;
            angle_arm1 = (movementLimitation(-30, 30, angle_arm1) ? angle_arm1 : -30);
            printf("%f\n", angle_arm1);
            break;
        case 'A':
            angle_arm1++;
            angle_arm1 = (movementLimitation(-30, 30, angle_arm1) ? angle_arm1 : 30);
            printf("%f\n", angle_arm1);
            break;

        case 's':
            angle_arm2--;
            angle_arm2 = (movementLimitation(-120, -80, angle_arm2) ? angle_arm2 : -120);
            printf("%f\n", angle_arm2);
            break;
        case 'S':
            angle_arm2++;
            angle_arm2 = (movementLimitation(-120, -80, angle_arm2) ? angle_arm2 : -80);
            printf("%f\n", angle_arm2);
            break;

        case 'w':
            y_arm2--;
            y_arm2 = (movementLimitation(40, 60, y_arm2) ? y_arm2 : 40);
            printf("%f\n", y_arm2);
            break;
        case 'W':
            y_arm2++;
            y_arm2 = (movementLimitation(40, 60, y_arm2) ? y_arm2 : 60);
            printf("%f\n", y_arm2);
            break;

        case 'd':
            angle_arm3--;
            angle_arm3 = (movementLimitation(-70, 70, angle_arm3) ? angle_arm3 : -70);
            printf("%f\n", angle_arm3);
            break;
        case 'D':
            angle_arm3++;
            angle_arm3 = (movementLimitation(-70, 70, angle_arm3) ? angle_arm3 : 70);
            printf("%f\n", angle_arm3);
            break;

        case 'e':
            y_arm3--;
            y_arm3 = (movementLimitation(20, 36, y_arm3) ? y_arm3 : 20);
            printf("%f\n", y_arm3);
            break;
        case 'E':
            y_arm3++;
            y_arm3 = (movementLimitation(20, 36, y_arm3) ? y_arm3 : 36);
            printf("%f\n", y_arm3);
            break;

        case 'f':
            angle_obj4--;
            angle_obj4 = (movementLimitation(120, 135, angle_obj4) ? angle_obj4 : 120);
            printf("%f\n", angle_obj4);
            break;
        case 'F':
            angle_obj4++;
            angle_obj4 = (movementLimitation(120, 135, angle_obj4) ? angle_obj4 : 135);
            printf("%f\n", angle_obj4);
            break;

        case 'g':
            angle_arm5--;
            angle_arm5 = (movementLimitation(-30, -10, angle_arm5) ? angle_arm5 : -30);
            printf("%f\n", angle_arm5);
            break;
        case 'G':
            angle_arm5++;
            angle_arm5 = (movementLimitation(-30, -10, angle_arm5) ? angle_arm5 : -10);
            printf("%f\n", angle_arm5);
            break;

        case 'h':
            angle_obj6++;
            angle_obj6 = (movementLimitation(45, 60, angle_obj6) ? angle_obj6 : 60);
            printf("%f\n", angle_obj6);
            break;
        case 'H':
            angle_obj6--;
            angle_obj6 = (movementLimitation(45, 60, angle_obj6) ? angle_obj6 : 45);
            printf("%f\n", angle_obj6);
            break;

        case 'j':
            angle_arm7++;
            angle_arm7 = (movementLimitation(10, 30, angle_arm7) ? angle_arm7 : 30);
            printf("%f\n", angle_arm7);
            break;
        case 'J':
            angle_arm7--;
            angle_arm7 = (movementLimitation(10, 30, angle_arm7) ? angle_arm7 : 10);
            printf("%f\n", angle_arm7);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int movementLimitation(double min, double max, double value)
{
    if (min <= value && value <= max)
        return 1;
    return 0;
}


void specialKeyboard(int key, int x, int y)
{
    int mod;
    switch (key) {
        case GLUT_KEY_DOWN:
            y_foot--;
            break;
        case GLUT_KEY_UP:
            y_foot++;
            break;
        case GLUT_KEY_LEFT:
            x_foot--;
            break;
        case GLUT_KEY_RIGHT:
            x_foot++;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


/*
* Procedimento que trata os eventos de mouse.
*/
void mouseClick(int button, int state, int x, int y)
{
    /*if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        setPoint(x, y);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        glTranslated(x_robot, x_robot, 0.0);
        drawFoot();
    }*/
    glutPostRedisplay();
}

/*
* Procedimento que insere um ponto na coordenada (x,y).
*/
void setPoint(int x, int y)
{
    if (n < SIZE) {
    /* Condição para guardar apenas a quantidade de pontos suportada pelo vetor*/
        P[n] = (Point) malloc(sizeof(Point));
        if (P[n] != NULL) {
            P[n]->u = transformX(x);
            P[n]->v = transformY(y);    // transformando da coordenada de viewport para a coordenada da projeção ortográfica
            printf("P%02d = (%f, %f)\n", n, P[n]->u, P[n]->v);
            n++;
        } else {
            printf("Problema de memória!");
            system("pause");
            exit(1);
        }
    } else {
        printf("A aplicação só suporta %d pontos.\n", SIZE);
    }
}


double transformX(int x)
{
    double u1 = -win;
    double u2 = win;
    double x1 = 0.0;
    double x2 = width;

    double u = (((u2-u1) * (x-x1)) / (x2-x1)) + u1;

    return u;
}


double transformY(int y)
{
    double v1 = -win;
    double v2 = win;
    double y1 = 0.0;
    double y2 = width;

    double v = (((v2-v1) * (y-y1)) / (y2-y1)) + v1;

    return -v;
}


void displayControlPoints()
{
    glPointSize(7.5f);
    glColor3f(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < n; i++) {
    /* Desenho e rotulagem dos n pontos de controle */
        glBegin(GL_POINTS);
            glVertex2f(P[i]->u, P[i]->v);
        glEnd();
    }
}


void displayBezierCurves(void)
{
    int i;      // índice dos pontos desenhados na tela
    int n2;     // pontos que ainda não foram usados para construir uma curva
    int curve;  // tipo de curva de acordo com quantidade de pontos usados para construí-la

    i = 0;
    n2 = n;

    while (i < n) {

        /* Caso forem dados mais do que 4 pontos, a curva será construída através das demais. */
        curve = (n2 > 4) ? 4 : n2;

        switch (curve) {
            case 2:                 /* Curva do tipo 1 - com base em dois pontos de controle. Neste caso, é uma reta. */
                bezierCurve1(i);    /* Procedimento que desenha uma reta com origem no ponto P[i]. */
                n2 -= 1;            // Descarte do ponto de controle que não será mais usado.
                i++;                // Itera para o próximo ponto de controle que ainda pode ser usado.
                break;
            case 3:                 /* Curva do tipo 2 - com base em três pontos de controle. */
                bezierCurve2(i);    /* Procedimento que desenha uma curva do tipo 2 com origem no ponto P[i]. */
                n2 -= 2;            // Descarte dos dois pontos de controle que não serão mais usados.
                i += 2;             // Itera para o próximo ponto de controle que ainda pode ser usado.
                break;
            case 4:                 /* Curva do tipo 3 - com base em quatro pontos de controle. */
                bezierCurve3(i);    /* Procedimento que desenha uma curva do tipo 3 com origem no ponto P[i]. */
                n2 -= 3;            // Descarte dos três pontos de controle que não serão mais usados.
                i += 3;             // Itera para o próximo ponto de controle que ainda pode ser usado.
                break;
            default:                /* Um único ponto. */
                i++;
                break;
        }
    }

}

/*
* Procedimento que desenha uma curva do tipo 1 (cor branca), isto é, uma reta.
* P[i]: ponto de origem da reta.
*/
void bezierCurve1(int i)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 1.0f);
    glPointSize(1.5f);

    for (float t = 0.0; t <= 1.0; t += 0.001) {
        /* Cálculo da curva C(t) */
        GLfloat x = (1-t)*(P[i]->u)  +  t*P[i+1]->v;
        GLfloat y = (1-t)*(P[i]->u)  +  t*P[i+1]->v;

        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }
    //glFlush();
}

/*
* Procedimento que desenha uma curva do tipo 2 (cor vermelha), curva com três pontos de controle.
* P[i]: ponto de origem da curva.
*/
void bezierCurve2(int i)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(1.5f);

    for (float t = 0.0; t <= 1.0; t += 0.001) {
        /* Cálculo da curva C(t) */
        GLfloat x = pow(1-t, 2)*(P[i]->u)  +  2*t*(1-t)*P[i+1]->u  +  pow(t, 2)*P[i+2]->u;
        GLfloat y = pow(1-t, 2)*(P[i]->v)  +  2*t*(1-t)*P[i+1]->v  +  pow(t, 2)*P[i+2]->v;

        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }
    //glFlush();
}

/*
* Procedimento que desenha uma curva do tipo 3 (cor azul), curva com quatro pontos de controle.
* P[i]: ponto de origem da curva.
*/
void bezierCurve3(int i)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 1.0f);
    glPointSize(1.5f);

    for (float t = 0.0; t <= 1.0; t += 0.001) {
        /* Cálculo da curva C(t)*/
        GLfloat x = pow(1-t, 3)*(P[i]->u)  +  3*t*pow(1-t, 2)*P[i+1]->u  +  3*pow(t, 2)*(1-t)*P[i+2]->u  +  pow(t, 3)*P[i+3]->u;
        GLfloat y = pow(1-t, 3)*(P[i]->v)  +  3*t*pow(1-t, 2)*P[i+1]->v  +  3*pow(t, 2)*(1-t)*P[i+2]->v  +  pow(t, 3)*P[i+3]->v;

        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }
}
