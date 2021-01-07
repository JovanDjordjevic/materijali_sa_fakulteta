#include <GL/glut.h>
#include <stdlib.h>

/* Bitmapa */
GLubyte rasters[5 * 24] = {
    0b11000000, 0b00001100,
    0b11000000, 0b00001100,
    0b11000000, 0b00001100,
    0b11000000, 0b00001100,
    0b11000011, 0b00001100,
    0b11000111, 0b10001100,
    0b11001100, 0b11001100,
    0b11011000, 0b01101100,
    0b11110000, 0b00111100,
    0b11100000, 0b00011100,
    0b11000000, 0b00001100,
    0b11000000, 0b00001100,

    0b11000000, 0b00001100,
    0b11000000, 0b00001100,
    0b11000000, 0b00001100,
    0b11000000, 0b00001100,
    0b11111111, 0b11111100,
    0b11111111, 0b11111100,
    0b11000000, 0b00001100,
    0b11000000, 0b00001100,
    0b11000000, 0b00001100,
    0b11100000, 0b00011100,
    0b01111111, 0b11111000,
    0b00111111, 0b11110000,

    0b00000011, 0b00000000,
    0b00000011, 0b00000000,
    0b00000011, 0b00000000,
    0b00000011, 0b00000000,
    0b00000011, 0b00000000,
    0b00000011, 0b00000000,
    0b00000011, 0b00000000,
    0b00000011, 0b00000000,
    0b00000011, 0b00000000,
    0b00000011, 0b00000000,
    0b11111111, 0b11111100,
    0b11111111, 0b11111100,

    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b11111111, 0b11110000,
    0b11111111, 0b11110000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b11111111, 0b11111100,
    0b11111111, 0b11111100,

    0b11110000, 0b00000000,
    0b11110000, 0b00000000,
    0b11110000, 0b00000000,
    0b11110000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000
};

void init(void)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void on_display(void)
{
    int i;

    /* Cistimo prethodni sadrzaj */
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    /* Definisemo pocetnu poziciju */
    glRasterPos2i(20, 20);

    /* Crtamo bitmapu nekoliko puta */
    for (i = 0; i < 4; i++) {
        glBitmap(
                16, 12,
                0.0, 0.0,
                16.0, 0.0,
                rasters + 24 * i
                );
    }

    glutSwapBuffers();
}

void on_reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Izlazimo iz programa */
        exit(0);
    }
}

int main(int argc, char **argv)
{
    /* Inicijalizuje se glut i pravi se prozor */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(100, 100);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();

    /* Registruju se callback f-je */
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);

    /* Ulazimo u glavnu petlju */
    glutMainLoop();

    return 0;
}
