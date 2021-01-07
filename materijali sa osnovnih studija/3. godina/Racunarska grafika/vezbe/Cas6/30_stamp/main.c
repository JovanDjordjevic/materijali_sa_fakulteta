#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define checkImageWidth 64
#define checkImageHeight 64

/* Bajtovi pixmape */
GLubyte checkImage[checkImageHeight][checkImageWidth][3];

static GLdouble zoomFactor = 1.5;
static GLint height;

void makeCheckImage(void)
{
    int i, j, c;

    for (i = 0; i < checkImageHeight; i++) {
        for (j = 0; j < checkImageWidth; j++) {
            c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0)))
                * 255;
            checkImage[i][j][0] = (GLubyte) c;
            checkImage[i][j][1] = (GLubyte) c;
            checkImage[i][j][2] = (GLubyte) c;
        }
    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void on_display(void)
{
    /* Cistimo prethodni sadrzaj */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Postavljamo raster poziciju na 0, 0 */
    glRasterPos2i(0, 0);

    /* Crtamo sliku */
    glDrawPixels(checkImageWidth, checkImageHeight, GL_RGB,
                 GL_UNSIGNED_BYTE, checkImage);

    /* Posto ne koristimo double bafer, forsiramo openGL
     * da izvrsi sve do sada zadate komande */
    glFlush();
}

void on_reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    height = (GLint) h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void on_motion(int x, int y)
{
    static GLint screeny;

    screeny = height - (GLint) y;

    glRasterPos2i(x, screeny);
    glPixelZoom(zoomFactor, zoomFactor);
    glCopyPixels(0, 0, checkImageWidth, checkImageHeight, GL_COLOR);
    glPixelZoom(1.0, 1.0);

    glFlush();
}

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'r':
    case 'R':
        /* Postavljamo zoom faktor na 1 */
        zoomFactor = 1.0;
        glutPostRedisplay();

        break;
    case 'z':
        /* Povecavamo zoom faktor */
        zoomFactor += 0.5;
        if (zoomFactor >= 3.0) {
            zoomFactor = 3.0;
        }

        break;
    case 'Z':
        /* Smanjujemo zoom faktor */
        zoomFactor -= 0.5;
        if (zoomFactor <= 0.5) {
            zoomFactor = 0.5;
        }

        break;
    case 27:
        /* Izlazimo iz programa */
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    /* Inicijalizujemo glut i pravimo prozor */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();

    /* registrujemo callback funkcije */
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutMotionFunc(on_motion);

    /* ulazimo u glavnu petlju */
    glutMainLoop();

    return 0;
}
