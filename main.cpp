/*
 * Universidade Federal da Grande Dourados - UFGD
 * Faculdade de Ci�ncias Exatas e Tecnologia - FACET
 * Curso de Bacharelado em Sistemas de Informa��o - BSI
 *
 * Disciplina: LABORAT�RIO DE COMPUTA��O GR�FICA - LCG
 * Prof.: Adailton Jos� Alves da Cruz
 * Per�odo: 2020.05 - M�dulo IV - RAE
 *
 * Atividade 02: desenvolvimento de um rob� capaz de fazer movimentos simples,
 *               tais como: transla��es em linha reta, em curva e rota��es.
 *
 * Desenvolvido por: Jeferson Willian Vieira Silva.
 */

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "header.h"

/*
 * Fun��o principal: ponto de partida do programa.
 * Par�metros:
 *  - argc: n�mero de argumentos
 *  - argv: matriz de caracteres (vetor de strings) contendo argumentos
 * Retorno:
 *  - 0: programa finalizado com sucesso
 *  - demais valores: programa finalizado com algum erro
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(621, 0);
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


/*
 * Procedimento para fazer as inicializa��es pertinentes. Faz parte das boas pr�ticas de programa��o.
 * Atrav�s dele vari�veis s�o inicializadas, aloca��es de mem�ria s�o feitas etc..
 */
void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < SIZE; i++) {
        /* iniciliza��o do vetor de pontos de controle para a trajet�ria */
        P[i] = NULL;
	}
	n = 0;

	P[n] = (Point) malloc(sizeof(Point));
	if (P[n] == NULL) {
        printf("Problema de aloca��o de mem�ria!");
	} else {
	    /* estabelecendo o ponto de origem do rob� para qualquer movimenta��o */
        x_foot = P[n]->u = 0.0;
        y_foot = P[n]->v = 0.0;
        n++;
	}

	win = 100;

    /* posi��es iniciais dos elementos do rob� */
	y_arm2 = 60.0;
	y_arm3 = 36.0;
    angle_arm1 = 0.0;
    angle_arm2 = -100.0;
    angle_arm3 = 45.0;
    angle_obj4 = 135.0;
    angle_arm5 = -30.0;
    angle_obj6 = 45.0;
    angle_arm7 = 30.0;
}


/*
 * Procedimento que redimensiona a Viewport e a Proje��o Ortogr�fica, para dispor os desenhos.
 * Par�metros:
 *  - width1: nova largura da window
 *  - height1: nova altura da window
 */
void reshape(int width1, int height1)
{
    /* guardando nas vari�veis globais, para fazer a transformada de viewport */
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


/*
 * Procedimento que atualiza continuamente os desenhos na Proje��o Ortogr�fica.
 */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    //displayInfo(); // mostra informa��es de como usar algumas funcionalidades
	displayControlPoints(); // mostra pontos de controle que ser�o usados para criar a trajet�ria
	drawRobot(); // desenha o rob�

    walkInTheTrajectory(); // realiza a trajet�ria se houver uma definida

	glFlush();
}


/*
 * Procedimento que apresenta algumas op��es de controle do rob�.
 */
void displayInfo()
{
    glColor3f(0.0, 1.0, 0.0);
    char text1[60] = "MOUSE (LEFT BUTTON) - Insere um ponto de controle";
    char text2[60] = "MOUSE (RIGHT BUTTON) - Caminha na trajet�ria";
    char text3[20] = "ESC - Limpa a tela";
    displayText(-95, 95, text1);
    displayText(-95, 90, text2);
    displayText(-95, 85, text3);
}


/*
 * Procedimento que apresenta uma informa��o textual na tela.
 * Par�metros:
 *  - x: posi��o do texto em rela��o ao eixo x
 *  - y: posi��o do texto em rela��o ao eixo y
 *  - text: texto que ser� escrito
 */
void displayText(GLsizei x, GLsizei y, char* text)
{
    glPushMatrix();
        glRasterPos2f(x, y);
        int length = strlen(text);
        for (int i = 0; i < length; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
        }
	glPopMatrix();
}


/*
 * Procedimento que desenha o rob�.
 */
void drawRobot()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    displayControlPoints();

    /* vari�veis para dimensionar adequadamente os elementos do rob� */
    double p = 6.0;
	double k = 1.5;
	double d = 2.5;
    double b = 2.5;
    double h = 6.0;
    double c = 0.625;

    /* Estabelece o centro da base do rob� como centro da proje��o.
    Usando para movimentar o rob� na tela, de todas as formas, e em todas as dire��es. */
    glTranslated(x_foot, y_foot, 0.0);
	drawFoot(p, k);                         // p�/base (ret�ngulo)

	/* Translaciona o centro para desenhar o bra�o 1 exatamente sobre o p�. */
	glTranslated(0.0, 7.5, 0.0);
	glRotated(angle_arm1, 0.0, 0.0, 1.0);   // define a rota��o do bra�o 1
    drawArm(b, h);                          // bra�o 1 (tri�ngulo)
    drawAxis(d);                            // eixo 1 (semic�rculo)
    drawLabel(0.0, 0.20*p, 0.25*k);         // r�tulo 1 ('�')

    /* Translaciona pela segunda vez para desenhar o bra�o 2 a partir
    da ponta do bra�o 1. */
    glTranslated(0.0, y_arm2, 0.0);
    glRotated(angle_arm2, 0.0, 0.0, 1.0);   // define a rota��o do bra�o 2
    drawArm(0.7*b, 0.6*h);                  // bra�o 2 (tri�ngulo)
    drawAxis(0.7*d);                        // eixo 2 (c�rculo)
    /* Desenho do r�tulo 2 atrav�s de 2 ret�ngulas ortogonais entre si */
    drawLabel(0.0, c, c/3);                 // 1.a parte: '�'
    drawLabel(90.0, c, c/3);                // 2.a parte: ' | '

    /* Translaciona pela terceira vez para desenhar o bra�o 3 a partir
    da ponta do bra�o 2. */
    glTranslated(0.0, y_arm3, 0.0);
    glRotated(angle_arm3, 0.0, 0.0, 1.0);
    drawArm(0.5*b, 0.4*h);
    drawAxis(0.5*d);
    /* Desenho do r�tulo 3 atrav�s de 2 ret�ngulas ortogonais entre si */
    drawLabel(0.0, 0.7*c, 0.7*(c/3));       // 1.a parte: '�'
    drawLabel(90.0, 0.7*c, 0.7*(c/3));      // 2.a parte: ' | '

    /* Translaciona pela quarta vez para desenhar a m�o a partir
    da ponta do bra�o 3. */
    glTranslated(0.0, 24.0, 0.0);

    /* Desenho da parte superior da m�o.*/
    glPushMatrix();
        glRotated(angle_obj4, 0.0, 0.0, 1.0);
        drawObjs(7.5, 0.2*p, 0.3*k);
        glTranslated(12.0, 0.0, 0.0);
        glRotated(-angle_obj4, 0.0, 0.0, 1.0);
        glRotated(angle_arm5, 0.0, 0.0, 1.0);
        drawArm(0.2*b, 0.2*h);
        drawAxis(0.2*d);
    glPopMatrix();

    /* Desenho da parte inferior da m�o. */
    glPushMatrix();
        glRotated(angle_obj6, 0.0, 0.0, 1.0);
        drawObjs(7.5, 0.2*p, 0.3*k);
        glTranslated(12.0, 0.0, 0.0);
        glRotated(-angle_obj6, 0.0, 0.0, 1.0);
        glRotated(angle_arm7, 0.0, 0.0, 1.0);
        drawArm(0.2*b, 0.2*h);
        drawAxis(0.2*d);
    glPopMatrix();

    drawAxis(0.3*d);                        // eixo 3

    //displayInfo();

    glFlush();
}


/*
 * Procedimento que desenha o ret�ngulo do p�/base do rob�, com dimens�es modificadas atrav�s da escala aplicada.
 * Agumentos:
 *  - p: escala aplicada na largura
 *  - k: escala aplicada na altura
 */
void drawFoot(double p, double k)
{
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
        glScaled(p, k, 0.0);
        quad();
    glPopMatrix();
}


/*
 * Procedimento que desenha a primitiva quadril�tero.
 */
void quad()
{
    glRectf(-5.0, -5.0, 5.0, 5.0);
}


/*
 * Procedimento que desenha os tri�ngulos dos bra�os.
 * Par�metros:
 *  - b: escala aplicada na base do tri�ngulo
 *  - h: escala aplicada na altura do tri�ngulo
 */
void drawArm(double b, double h)
{
    glColor3f(1.0, 0.5, 1.0);
    glPushMatrix();
        glScaled(b, h, 0.0);
        triangle();
    glPopMatrix();
}


/*
 * Procedimento que desenha a primitiva tri�ngulo.
 */
void triangle()
{
    glBegin(GL_TRIANGLES);
        glVertex2f(-5.0, 0.0);
        glVertex2f(5.0, 0.0);
        glVertex2f(0.0, 10.0);
    glEnd();
}


/*
 * Procedimento que desenha os c�rculos dos eixos.
 * Par�metro:
 *  - d: escala aplicada no di�metro do c�rculo
 */
void drawAxis(double d)
{
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
        glScaled(d, d, 0.0);
        circle();
    glPopMatrix();
}


/*
 * Procedimento que desenha a primitiva c�rculo.
 */
void circle()
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

/*
 * Procedimento que desenha as etiquetas que indicam as movimenta��es.
 * Par�metros:
 *  - angle: �ngulo de rota��o tempor�ria
 *  - p: escala aplicada na largura
 *  - k: escala aplicada na altura
 */
void drawLabel(double angle, double p, double k)
{
    glColor3d(0.0, 0.0, 1.0);
    glPushMatrix();
        glRotated(angle, 0.0, 0.0, 1.0);
        glScaled(p, k, 0.0);
        quad();
    glPopMatrix();
}


/*
 * Procedimemto que desenha as partes retangulares das m�os do rob�.
 * Par�metros:
 *  - x: valor de transla��o tempor�ria
 *  - p: escala aplicada na largura
 *  - k: escala aplicada na altura
 */
void drawObjs(double x, double p, double k)
{
    glColor3f(1.0, 0.5, 1.0);
    glPushMatrix();
        glTranslated(x, 0.0, 0.0);
        glScaled(p, k, 0.0);
        quad();
    glPopMatrix();
}


/*
 * Procedimento que trata os eventos das teclas gen�ricas (letras, n�meros etc) do teclado.
 * Par�metros:
 *  - key: valor ASC da tecla pressionada
 *  - x: posi��o do cursor em rela��o ao eixo x no momento do disparo do evento
 *  - y: posi��o do cursor em rela��o ao eixo y no momento do disparo do evento
 */
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27: // ESC
            clearTrajectory();
            break;
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
            y_arm2 = (movementLimitation(30, 60, y_arm2) ? y_arm2 : 30);
            printf("%f\n", y_arm2);
            break;
        case 'W':
            y_arm2++;
            y_arm2 = (movementLimitation(30, 60, y_arm2) ? y_arm2 : 60);
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

        case 'p':
            P[0]->u = ++x_foot;
            P[0]->v = ++y_foot;
            break;
        case 'P':
            P[0]->u = --x_foot;
            P[0]->v = --y_foot;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


/*
 * Fun��o que avalia a possibilidade de movimenta��o (transla��o e rota��o) de um parte do rob�.
 * Par�metros:
 *  - min: menor valor em que uma dada movimenta��o pode acontecer
 *  - max: maior valor em que uma dada movimenta��o pode acontecer
 *  - value: valor da movimenta��o
 * Retorno:
 *  - 0: movimento n�o est� dentro dos limites
 *  - 1: movimento est� dentro dos limites
 */
int movementLimitation(double min, double max, double value)
{
    return (min <= value && value <= max);
}


/*
 * Procedimento que trata os eventos das teclas especiais (setas, F1, F2 etc) do teclado.
 * Par�metros:
 *  - key: valor ASC da tecla pressionada
 *  - x: posi��o do cursor em rela��o ao eixo x no momento do disparo do evento
 *  - y: posi��o do cursor em rela��o ao eixo y no momento do disparo do evento
 */
void specialKeyboard(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_DOWN:
            y_foot--;
            P[0]->v = y_foot;
            break;
        case GLUT_KEY_UP:
            y_foot++;
            P[0]->v = y_foot;
            break;
        case GLUT_KEY_LEFT:
            x_foot--;
            P[0]->u = x_foot;
            break;
        case GLUT_KEY_RIGHT:
            x_foot++;
            P[0]->u = x_foot;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


/*
 * Procedimento que trata os eventos de mouse.
 * Par�metro:
 *  - button: bot�o pressionado
 *  - state: estado que dispara o evento
 *  - x: posi��o do cursor em rela��o ao eixo x no momento do disparo do evento
 *  - y: posi��o do cursor em rela��o ao eixo y no momento do disparo do evento
 */
void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        setPoint(x, y);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        go = 1;
    }
    glutPostRedisplay();
}

/*
 * Procedimento que insere um ponto na coordenada de viewport (x,y).
 * Par�metros:
 *  - x: posi��o do cursor em rela��o ao eixo x no momento do disparo do evento
 *  - y: posi��o do cursor em rela��o ao eixo y no momento do disparo do evento
 */
void setPoint(int x, int y)
{
    if (n < SIZE) {
        /* Condi��o para guardar apenas a quantidade de pontos suportada pelo vetor */
        P[n] = (Point) malloc(sizeof(Point));
        if (P[n] != NULL) {
            P[n]->u = transformX(x);
            P[n]->v = transformY(y);
            //printf("P%02d = (%f, %f)\n", n, P[n]->u, P[n]->v);
            n++;
        } else {
            printf("Problema de mem�ria!");
            system("pause");
            exit(1);
        }
    } else {
        printf("A aplica��o s� suporta %d pontos.\n", SIZE);
    }
}

/*
 * Fun��o que transforma a coordenada x.
 * Par�metro:
 *  - x: coordenada de viewport
 * Retorno:
 *  - u: coordenada de proje��o ortogr�fica
 */
double transformX(int x)
{
    double u1 = -win;
    double u2 = win;
    double x1 = 0.0;
    double x2 = width;

    double u = (((u2-u1) * (x-x1)) / (x2-x1)) + u1;

    return u;
}


/*
 * Fun��o que transforma a coordenada y.
 * Par�metro:
 *  - y: coordenada de viewport
 * Retorno:
 *  - v: coordenada de proje��o ortogr�fica
 */
double transformY(int y)
{
    double v1 = -win;
    double v2 = win;
    double y1 = 0.0;
    double y2 = width;

    double v = (((v2-v1) * (y-y1)) / (y2-y1)) + v1;

    return -v;
}


/*
 * Procedimento que mostra todos os pontos de controle na tela.
 */
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

/*
 * Procedimento que mostra as Curvas de B�zier na tela.
 */
void displayBezierCurves()
{

    int i;      // �ndice dos pontos desenhados na tela
    int n2;     // pontos que ainda n�o foram usados para construir uma curva
    int curve;  // tipo de curva de acordo com quantidade de pontos usados para constru�-la

    i = 0;
    n2 = n;

    while (i < n) {

        /* Caso forem dados mais do que 4 pontos, a curva ser� constru�da atrav�s das demais. */
        curve = (n2 > 4) ? 4 : n2;

        switch (curve) {
            case 2:                 /* Curva do tipo 1 - com base em dois pontos de controle. Neste caso, � uma reta. */
                bezierCurve1(i);    /* Procedimento que desenha uma reta com origem no ponto P[i]. */
                n2 -= 1;            // Descarte do ponto de controle que n�o ser� mais usado.
                i++;                // Itera para o pr�ximo ponto de controle que ainda pode ser usado.
                break;
            case 3:                 /* Curva do tipo 2 - com base em tr�s pontos de controle. */
                bezierCurve2(i);    /* Procedimento que desenha uma curva do tipo 2 com origem no ponto P[i]. */
                n2 -= 2;            // Descarte dos dois pontos de controle que n�o ser�o mais usados.
                i += 2;             // Itera para o pr�ximo ponto de controle que ainda pode ser usado.
                break;
            case 4:                 /* Curva do tipo 3 - com base em quatro pontos de controle. */
                bezierCurve3(i);    /* Procedimento que desenha uma curva do tipo 3 com origem no ponto P[i]. */
                n2 -= 3;            // Descarte dos tr�s pontos de controle que n�o ser�o mais usados.
                i += 3;             // Itera para o pr�ximo ponto de controle que ainda pode ser usado.
                break;
            default:                /* Um �nico ponto. */
                i++;
                break;
        }
    }
}

/*
 * Procedimento que desenha uma curva do tipo 1 (cor branca), isto �, uma reta.
 * Par�metros:
 *  - i: �ndice do ponto de origem da curva.
 */
void bezierCurve1(int i)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(1.5f);

    for (float t = 0.0; t <= 1.0; t += 0.0005) {
        /* C�lculo da curva C(t) */
        GLfloat x = (1-t)*(P[i]->u)  +  t*P[i+1]->u;
        GLfloat y = (1-t)*(P[i]->v)  +  t*P[i+1]->v;

        P[0]->u = x_foot = x;
        P[0]->v = y_foot = y;
        drawRobot();
    }
}

/*
 * Procedimento que desenha uma curva do tipo 2 (cor vermelha), curva com tr�s pontos de controle.
 * Par�metro:
 *  - i: �ndice do ponto de origem da curva
 */
void bezierCurve2(int i)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(1.5f);

    for (float t = 0.0; t <= 1.0; t += 0.0005) {
        /* C�lculo da curva C(t) */
        GLfloat x = pow(1-t, 2)*(P[i]->u)  +  2*t*(1-t)*P[i+1]->u  +  pow(t, 2)*P[i+2]->u;
        GLfloat y = pow(1-t, 2)*(P[i]->v)  +  2*t*(1-t)*P[i+1]->v  +  pow(t, 2)*P[i+2]->v;

        x_foot = x;
        y_foot = y;
        drawRobot();
    }
}

/*
 * Procedimento que desenha uma curva do tipo 3 (cor azul), curva com quatro pontos de controle.
 * Par�metro:
 *  - i: �ndice do ponto de origem da curva
 */
void bezierCurve3(int i)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 1.0f);
    glPointSize(1.5f);

    for (float t = 0.0; t <= 1.0; t += 0.0005) {
        /* C�lculo da curva C(t)*/
        GLfloat x = pow(1-t, 3)*(P[i]->u)  +  3*t*pow(1-t, 2)*P[i+1]->u  +  3*pow(t, 2)*(1-t)*P[i+2]->u  +  pow(t, 3)*P[i+3]->u;
        GLfloat y = pow(1-t, 3)*(P[i]->v)  +  3*t*pow(1-t, 2)*P[i+1]->v  +  3*pow(t, 2)*(1-t)*P[i+2]->v  +  pow(t, 3)*P[i+3]->v;

        x_foot = x;
        y_foot = y;
        drawRobot();
    }
}

/*
 * Procedimento que faz o rob� caminhar na trajet�ria configurada.
 */
void walkInTheTrajectory()
{
    if (go) { // se o "bot�o" go estiver ligado
        displayBezierCurves();
        clearTrajectory();  // limpa a trajet�ria velha
        go = 0; // ...desligando
    }
}

/*
 * Procedimento que limpa uma trajet�ria depois de percorrida.
 */
void clearTrajectory()
{
    for (int i = 1; i < n; i++) {
        free(P[i]);
        P[i] = NULL;
    }
    P[0]->u = x_foot;
    P[0]->v = y_foot;
    n = 1;
}
