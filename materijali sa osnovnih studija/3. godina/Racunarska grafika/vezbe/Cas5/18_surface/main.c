#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535
#define EPSILON 0.01

/* #define DRAW_CONE */
#define DRAW_SPHERE 
/* #define DRAW_CYLINDER */
//#define DRAW_CYLINDER

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
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    /* Ukljucujemo normalizaciju vektora normala */
    glEnable(GL_NORMALIZE);

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
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 10);
}

#ifdef DRAW_SPHERE
/*
 * Postavlja koordinate i normale temena sfere,
 * u zavisnosti od parametara u i v
 */
void set_normal_and_vertex(float u, float v)
{
    glNormal3f(
            sin(u) * sin(v),
            cos(u),
            sin(u) * cos(v)
            );
    glVertex3f(
            sin(u) * sin(v),
            cos(u),
            sin(u) * cos(v)
            );
}
#endif // DRAW_SPHERE

#ifdef DRAW_CYLINDER
/*
 * Postavlja koordinate i normale temena cilindra,
 * u zavisnosti od parametara u i v
 */
void set_normal_and_vertex(float u, float v)
{
    // pravilno bi bilo y = 0 za normalu,
    // ovako je render lepsi
    glNormal3f(
            sin(v),
            0,
            cos(v)
            );
    glVertex3f(
            sin(v),
            u,
            cos(v)
            );
}
#endif

#ifdef DRAW_CONE
/*
 * Postavlja koordinate i normale temena kupe,
 * u zavisnosti od parametara u i v
 */
void set_normal_and_vertex(float u, float v)
{
    // pravilno bi bilo racunati nagib kupe
    // i postaviti y konstantno
    glNormal3f(
            u * sin(v),
            u,
            u * cos(v)
            );
    glVertex3f(
            u / 10 * sin(v),
            u,
            u / 10 * cos(v)
            );
}
#endif

/* Crtamo objekat */
void draw_object()
{
    float u, v;

    glPushMatrix();

    /* Crtamo objekat strip po strip */
    // TODO: Ovako je ispravno :)
    for (u = 0; u < PI; u += PI / 20) {
        glBegin(GL_TRIANGLE_STRIP);
        for (v = 0; v <= PI*2 + EPSILON; v += PI / 20) {
            set_normal_and_vertex(u, v);
            set_normal_and_vertex(u + PI / 20, v);
        }
        glEnd();
    }

    glPopMatrix();
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
    GLfloat ambient_coeffs[] = { 0.3, 0.3, 0.7, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 1, 1, 0, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 30;

    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 5, 5, 0, 0, 0, 0, 1, 0);

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glShadeModel(GL_SMOOTH);

    /* Kreira se objekat. */
    draw_object();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

