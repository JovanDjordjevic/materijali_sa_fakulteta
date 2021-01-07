#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

/* Funkcija initalize() vrsi OpenGL inicijalizaciju. */
static void initialize(void);

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);

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
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    initialize();

    /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void initialize(void)
{
    /* Velicina tacaka. */
    GLfloat point_size;

    /* Minimalna i maksimalna dozvoljena velicina tacaka */
    GLfloat point_size_range[2];

    /* Debljina linija. */
    GLfloat line_width;

    /* Minimalna i maksimalna dozvoljena debljina linija */
    GLfloat line_width_range[2];

    /* Postavlja se boja pozadine. */
    glClearColor(0.75, 0.75, 0.75, 0);

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    /* Podesava se velicina tacaka. */
    glPointSize(6); /*///// point size*/

    /* Ocitava se i ispisuje tekuca velicina tacaka. */
    glGetFloatv(GL_POINT_SIZE, &point_size);
    printf("current point size: %g\n", point_size);

    /*
     * Ocitavaju se i ispisuju minimalna i maksimalna dozvoljena velicina
     * tacaka.
     */
    glGetFloatv(GL_POINT_SIZE_RANGE, point_size_range);
    printf("minimal point size: %g\n", point_size_range[0]);
    printf("maximal point size: %g\n", point_size_range[1]);

    /* Podesava se debljina linija. */
    glLineWidth(12.7); /*///////////////////////////////////////////////////////////////////// line size*/

    /* Ocitava se i ispisuje tekuca debljina linija. */
    glGetFloatv(GL_LINE_WIDTH, &line_width);
    printf("current line width: %g\n", line_width);

    /*
     * Ocitavaju se i ispisuju minimalna i maksimalna dozvoljena debljina
     * linija.
     */
    printf("Sranje: %d\n", GL_LINE_STIPPLE);
    glGetFloatv(GL_LINE_WIDTH_RANGE, line_width_range);
    printf("minimal line width: %g\n", line_width_range[0]);
    printf("maximal line width: %g\n", line_width_range[1]);

    /* Podesava se pattern kojim ce biti iscrtavane linije. */
    glEnable(GL_LINE_STIPPLE); /*///////////////////////////////////////////////////////////////////// lineStipple*/
    glLineStipple(2, 0xf0f0); /*/////////////////////////////////////////////////////////////////////   */
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;
    }
}

static void on_display(void)
{
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Crtaju se tacke. */
    glColor3f(0, 0, 1);
        glBegin(GL_POINTS);
        glVertex3f(0, 0, 0);
        glVertex3f(0.75, 0, 0);
        glVertex3f(0.75, 0.75, 0);
        glVertex3f(0, 0.75, 0);
    glEnd();

    /* Crtaju se linije. */
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.75, -0.75, 0);
        glVertex3f(-0.25, -0.75, 0);
        glVertex3f(-0.25, -0.25, 0);
        glVertex3f(-0.75, -0.25, 0);
    glEnd();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
