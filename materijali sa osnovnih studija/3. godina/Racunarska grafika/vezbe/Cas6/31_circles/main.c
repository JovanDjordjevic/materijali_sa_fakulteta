#include <GL/glut.h>
#include <math.h>

#define CIRCLE_SEGMENTS 12
#define PI 3.1415926535

GLuint listName;

static void init(void)
{
    int i;
    float angle;

    /* Registrujemo jednu listu */
    listName = glGenLists(1);

    /* Pravimo listu */
    glNewList(listName, GL_COMPILE);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_LOOP);
            for (i = 0; i < CIRCLE_SEGMENTS; i++) {
                angle = i * 2 * PI / CIRCLE_SEGMENTS;
                glVertex2f(0.5 * cos(angle), 0.5 * sin(angle));
            }
        glEnd();
        glTranslatef(1.5, 0.0, 0.0);
    glEndList();

    /* Inicijalizujemo model iscrtavanja */
    glShadeModel(GL_FLAT);
}

void on_display(void)
{
    GLuint i;

    /* Brisemo prethodni sadrzaj */
    glClear(GL_COLOR_BUFFER_BIT);

    for (i = 0; i < 10; i++) {
        glCallList(listName);
    }

    glutSwapBuffers();
}

void on_reshape(int w, int h)
{
    /* Podesavamo pogled */
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) {
        gluOrtho2D(0.0, 2.0, -0.5 * (GLfloat) h / (GLfloat) w,
                   1.5 * (GLfloat) h / (GLfloat) w);
    } else {
        gluOrtho2D(0.0, 2.0 * (GLfloat) w / (GLfloat) h, -0.5, 1.5);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Izlazimo pri pritisku tastera Esc */
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    /* Inicijalizujemo glut i pravimo prozor */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(650, 50);
    glutCreateWindow(argv[0]);

    init();

    /* registrujemo callback funkcije */
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);

    /* Ulazimo u glavnu petlju */
    glutMainLoop();
    return 0;
}
