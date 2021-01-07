#include <stdlib.h>
#include <GL/glut.h>

static int face;

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
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    face = GL_FRONT;

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

    case 'l':
        /* Ukljucuje se ravno sencenje i ponovo iscrtava scena. */
        glShadeModel(GL_FLAT);
        glutPostRedisplay();
        break;

    case 's':
        /* Ukljucuje se glatko sencenje i ponovo iscrtava scena. */
        glShadeModel(GL_SMOOTH);
        glutPostRedisplay();
        break;

    case 'f':
        /* Iscrtava se lice. */
        face = GL_FRONT;
        glutPostRedisplay();
        break;

    case 'b':
        /* Iscrtava se nalicje. */
        face = GL_BACK;
        glutPostRedisplay();
        break;

    case 't':
        /* Ukljucujemo sencenje nalicja poligona */
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
        glutPostRedisplay();
        break;

    case 'T':
        /* Iskljucujemo sencenje nalicja poligona - sencenje se
         * vrsi po istoj formuli kao i za lica
         */
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
        glutPostRedisplay();
        break;

    }
}

static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 10);
}

static void on_display(void)
{
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 1, 1, 1, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.3, 0.6, 0.9, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.2, 0.2, 1, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 30;

    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(face, GL_AMBIENT,   ambient_coeffs);
    glMaterialfv(face, GL_DIFFUSE,   diffuse_coeffs);
    glMaterialfv(face, GL_SPECULAR,  specular_coeffs);
    glMaterialf(face,  GL_SHININESS, shininess);

    /* Iskljucuje se prikaz lica, odnosno nalicja
       u zavisnosti od promenljive face */
    glCullFace(
            (face == GL_FRONT) ? GL_BACK : GL_FRONT
        );

    /* Kreira se objekat. */
    glutSolidSphere(1, 16, 16);

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
