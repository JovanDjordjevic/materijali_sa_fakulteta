#include <GL/glut.h>

/*
u ovom objasnjenju nesto ne valja, kad se u initdisplaymode ubaci DEPTH ne menja se nista, ali brisanje one linije glEnable(GL_DEPTH_TEST); daje rezultate
*/



/**
 * Program demonstrira razliku u iscrtavanju kad se iskljuci
 * GLUT_DEPTH flag:
 * - kad je flag ukljucen, plavi kvadrat koji je "blize" posmatracu
 *   prekriva crveni kvadrat (prirodno ponasanje)
 * - kad je iskljucen, crveni kvadrat prekriva plavi jer je kasnije
 *   nacrtan (i pored cinjenice da se nalazi "ispod")
 *
 * Da biste iskljucili GLUT_DEPTH flag, izbrisite ga iz linije 23
 * koja poziva funkciju glutInitDisplayMode()
 */

/* Deklaracije callback funkcija. */
static void on_display(void);

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);   //linija 23

    /* Kreira se prozor. */
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_display(void)
{
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Kreira se kvadrat u ravni z=0. */
    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5, -0.5, 0);
        glVertex3f(-0.5, 0.5, 0);
        glVertex3f(0.5, 0.5, 0);
        glVertex3f(0.5, -0.5, 0);
    glEnd();

    /* Kreira se kvadrat u ravni koja se nalazi
     * "ispod" ravni z=0 */
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.5 + 0.5, -0.5, .1);
        glVertex3f(-0.5 + 0.5, 0.5, .1);
        glVertex3f(0.5 + 0.5, 0.5, .1);
        glVertex3f(0.5 + 0.5, -0.5, .1);
    glEnd();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
