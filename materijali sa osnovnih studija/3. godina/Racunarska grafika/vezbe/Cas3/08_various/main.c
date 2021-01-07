#include <stdlib.h>
#include <GL/glut.h>

/* Dimenzije prozora */
static int window_width, window_height;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
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

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);

    /* Program ulazi u glavnu petlju. */
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
    }
}

static void on_reshape(int width, int height)
{
    /* Pamte se sirina i visina prozora. */
    window_width = width;
    window_height = height;
}

static void on_display(void)
{
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se viewport. */
    glViewport(0, 0, window_width, window_height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

    /* Skaliramo sve za koeficijent 2, po svim osama */
    glScalef(2, 2, 2);

    /* Crtamo zicanu sferu */
    glColor3f(0, 0, 1);
    glutWireSphere(0.5, 10, 10);

    /* Crtamo rotiranu i transliranu kupu */
    glTranslatef(1, 0, 0);       /* definisemo transformaciju */
    glRotatef(280, 1, 0, 0);
        glColor3f(0, 1, 1);
        glutWireCone(0.2, 0.3, 10, 1);
    glRotatef(-280, 1, 0, 0);    /* ponistavamo transformaciju */
    glTranslatef(-1, 0, 0);

    /* Crtamo cajnik */
    glTranslatef(-2, 0, 0);
        glColor3f(1, 0, 1);
        glutWireTeapot(0.5);
    glTranslatef(2, 0, 0);

    /* Crtamo dodekaedar */
    glTranslatef(0, 0, -2);
    glScalef(0.5, 0.5, 0.5);
        glColor3f(1, 1, 1);
        glutWireDodecahedron();
    glScalef(2, 2, 2);
    glTranslatef(0, 0, 2);

    /* Crtamo ikosaedar */
    glTranslatef(0, 0, 1);
    glScalef(0.3, 0.3, 0.3);
        glColor3f(0, 0, 0);
        glutWireIcosahedron();
    /* ne moramo da ponistavamo matrice transformacije
     * za ikosaedar jer ne crtamo nista posle njih */

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
