#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535
#define NUMBER_OF_DOTS 10

/* Primitiva koju trenutno korisstimo za iscrtavanje */
static int display_primitive;

/* Funkcija initalize() vrsi OpenGL inicijalizaciju. */
static void initialize(void);

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se funkcije za obradu dogadjaja. */
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    initialize();

    /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void initialize(void)
{
    /* Postavlja se boja pozadine. */
    glClearColor(0.75, 0.75, 0.75, 0);

    /* Podesava se velicina tacaka. */
    glPointSize(6);

    /* Podesava se debljina linija. */
    glLineWidth(12.7);

    /* Podrazumevana primitiva */
    display_primitive = GL_POINTS;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    /* Postavljamo primitivu u zavisnosti od pritisnutog
       tastera */
    case '1':
        display_primitive = GL_POINTS;
        printf("Activated GL_POINTS\n");
        break;
    case '2':
        display_primitive = GL_LINES;
        printf("Activated GL_LINES\n");
        break;
    case '3':
        display_primitive = GL_LINE_STRIP;
        printf("Activated GL_LINE_STRIP\n");
        break;
    case '4':
        display_primitive = GL_LINE_LOOP;
        printf("Activated GL_LINE_LOOP\n");
        break;
    case '5':
        display_primitive = GL_TRIANGLES;
        printf("Activated GL_TRIANGLES\n");
        break;
    case '6':
        display_primitive = GL_TRIANGLE_STRIP;
        printf("Activated GL_TRIANGLE_STRIP\n");
        break;
    case '7':
        display_primitive = GL_TRIANGLE_FAN;
        printf("Activated GL_TRIANGLE_FAN\n");
        break;
    case '8':
        display_primitive = GL_QUADS;
        printf("Activated GL_QUADS\n");
        break;
    case '9':
        display_primitive = GL_QUAD_STRIP;
        printf("Activated GL_QUAD_STRIP\n");
        break;
    case '0':
        display_primitive = GL_POLYGON;
        printf("Activated GL_POLYGON\n");
        break;

    case 'b':
        /* Postavljamo da se prikazuje samo zadnje lice poligona */
        glCullFace(GL_FRONT);
        glEnable(GL_CULL_FACE);
        printf("Activated culling of GL_FRONT\n");
        break;
    case 'f':
        /* Postavljamo da se prikazuje samo prednje lice poligona */
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
        printf("Activated culling of GL_BACK\n");
        break;
    case 'a':
        /* Postavljamo da se prikazuju oba lica poligona */
        glDisable(GL_CULL_FACE);
        printf("Deactivated culling\n");
        break;
    }

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();
}

static void on_display(void)
{
    int i;

    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Iscrtavamo tacke - jednu u koordinatnom pocetku,
       a ostale kao temena 10-ougla cije je teziste
       u koordinatnom pocetku. */
    glBegin(GL_POINTS);

    glColor3f(1, 0, 0);
    glVertex2f(0, 0);

    for (i = 0; i < NUMBER_OF_DOTS; i++) {
        glVertex2f(
                cos(2 * i * PI / NUMBER_OF_DOTS)*0.5 ,
                sin(2 * i * PI / NUMBER_OF_DOTS) *0.5);
    }

    glEnd();

    /* Crta se primitiva cija su temena - jedno u koordinatnom
       pocetku, a ostala kao temena 10-ougla cije je teziste
       u koordinatnom pocetku. */
    glColor3f(0, 0, 1);

    glBegin(display_primitive);

    glVertex2f(0, 0);

    for (i = 0; i < NUMBER_OF_DOTS; i++) {
        glColor3f(0, 0, 0.1 * i);
        glVertex2f(
                cos(2 * i * PI / NUMBER_OF_DOTS) * 0.5,
                sin(2 * i * PI / NUMBER_OF_DOTS) * 0.5);
    }

    glEnd();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
