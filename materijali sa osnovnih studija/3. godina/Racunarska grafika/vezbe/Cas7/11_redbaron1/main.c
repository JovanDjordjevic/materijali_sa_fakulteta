#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/* Vreme proteklo od pocetka simulacije. */
static float animation_parameter;

/* Fleg koji odredjuje stanje tajmera. */
static int animation_active;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);
static void on_display(void);

static void draw_baron(void);

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se funkcije za obradu dogadjaja. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Inicijalizuju se globalne promenljive. */
    animation_parameter = 0;
    animation_active = 0;

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);

    /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case 'g':
    case 'G':
        /* Pokrece se simulacija. */
        if (!animation_active) {
            glutTimerFunc(10, on_timer, 0);
            animation_active = 1;
        }
        break;

    case 's':
    case 'S':
        /* Zaustavlja se simulacija. */
        animation_active = 0;
        break;
    }
}

static void on_timer(int value)
{
    /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value != 0)
        return;

    /* Azurira se vreme simulacije. */
    animation_parameter++;

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    if (animation_active)
        glutTimerFunc(10, on_timer, 0);
}

static void on_reshape(int width, int height)
{
    /* Postavlja se viewport. */
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1500);
}

static void on_display(void)
{
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Postavlja se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 5, 10, 0, 0, 0, 0, 1, 0);

    /* Transliramo i rotiramo tako da kretanja ne budu u fazi */

    glTranslatef(
            sin(animation_parameter / 50.0f),
            0,
            0
        );

    glRotatef(
            /* ugao */
            sin(animation_parameter / 50.0f) * 30.0f,
            /* vektor rotacije */
            0, 0, 1
        );

    draw_baron();

    /* Postavlja se nova slika u prozor. */
    glutSwapBuffers();
}

static void draw_baron(void)
{
#define glutCube glutWireCube
    glPushMatrix();

    glColor3f(1, 1, 1);

    /* Crtamo donje krilo */
    /* glColor3f(.7, 0, 0); */
    glScalef(5, .1, 1);
    glutCube(1);

    /* Crtamo gornje krilo */
    /* glColor3f(1, .5, .5); */
    glTranslatef(0, 5, 0);
    glScalef(1.2, 1, 1);
    glutCube(1);

    glTranslatef(0, - 5, 0);

    /* Crtamo repno krilo */
    /* glColor3f(.7, 0, 0); */
    glTranslatef(0, 2, 2);
    glScalef(0.2, 1, 1);
    glutCube(1);

    /* Crtamo trup */
    /* glColor3f(.5, 0, 0); */
    glTranslatef(0, 0, -1);
    glScalef(0.3, 5, 3);
    glutCube(1);

    glPopMatrix();
#undef glutCube
}
