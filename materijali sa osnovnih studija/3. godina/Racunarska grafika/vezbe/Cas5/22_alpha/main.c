#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

static int leftFirst = GL_TRUE;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

static void init(void)
{
    /* Obavlja se OpenGL inicijalizacija. */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    /* Kreira se prozor. */
    glutInitWindowSize(400, 400);
    glutCreateWindow(argv[0]);

    /* Poziva se funkcija za inicijalizaciju */
    init();

    /* Registruju se callback funkcije. */
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void draw_left_triangle(void)
{
    /* Crtamo levi trougao */
    glBegin(GL_TRIANGLES);
        glColor4f(1.0, 1.0, 0.0, 0.75);
        glVertex3f(0.1, 0.9, 0.0);
        glVertex3f(0.1, 0.1, 0.0);
        glVertex3f(0.7, 0.5, 0.0);
    glEnd();
}

static void draw_right_triangle(void)
{
    /* Crtamo desni trougao */
    glBegin(GL_TRIANGLES);
        glColor4f(0.0, 1.0, 1.0, 0.75);
        glVertex3f(0.9, 0.9, 0.0);
        glVertex3f(0.3, 0.5, 0.0);
        glVertex3f(0.9, 0.1, 0.0);
    glEnd();
}

void on_display(void)
{
    /* Cistimo kolor bafer */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Ako je leftFirst true, prvo crtamo levi trougao,
       ako nije, prvo desni */
    if (leftFirst) {
        draw_left_triangle();
        draw_right_triangle();
    } else {
        draw_right_triangle();
        draw_left_triangle();
    }

    glutSwapBuffers();
}

void on_reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        gluOrtho2D(0.0, 1.0, 0.0, 1.0 * (GLfloat) h / (GLfloat) w);
    } else {
        gluOrtho2D(0.0, 1.0 * (GLfloat) w / (GLfloat) h, 0.0, 1.0);
    }
}

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 't':
        case 'T':
            /* Menjamo redosled iscrtavanja */
            leftFirst = !leftFirst;
            break;

        case 27:
            /* Izlazimo iz programa */
            exit(0);
            break;

        case '1':
            glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
            printf("Activated 1 GL_ZERO\n");
            break;

        case '2':
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            printf("Activated 2 GL_ONE\n");
            break;

        case '3':
            glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
            printf("Activated 3 GL_DST_COLOR\n");
            break;

        case '4':
            glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
            printf("Activated 4 GL_SRC_ALPHA\n");
            break;

        case '5':
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_COLOR);
            printf("Activated 5 GL_ONE_MINUS_DST_COLOR\n");
            break;

        case '6':
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
            printf("Activated 6 GL_ONE_MINUS_SRC_COLOR\n");
            break;

        case '7':
            glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
            printf("Activated 7 GL_SRC_ALPHA\n");
            break;

        case '8':
            glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
            printf("Activated 8 GL_DST_ALPHA\n");
            break;

        case '9':
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
            printf("Activated 9 GL_ONE_MINUS_DST_ALPHA\n");
            break;

        case '0':
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            printf("Activated 0 GL_ONE_MINUS_SRC_ALPHA\n");
            break;

        case '-':
            glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA_SATURATE);
            printf("Activated - GL_SRC_ALPHA_SATURATE\n");
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

