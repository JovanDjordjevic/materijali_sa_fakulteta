#include <stdlib.h>
#include <GL/glut.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 20

float animation_parameter;
int animation_ongoing;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int id);

static void init_lights();

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

    /* Ukjucujemo blending */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Inicijalizujemo promenljive */
    animation_parameter = -1.5;
    animation_ongoing = 0;

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_timer(int id)
{
    if (TIMER_ID != id)
        return;

    animation_parameter += 0.01;

    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
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
        /* Pokrecemo animaciju */
        if (!animation_ongoing) {
            animation_ongoing = 1;
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
        }
        break;

    case 's':
    case 'S':
        animation_ongoing = 0;
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
    gluPerspective(30, (float) width / height, 1, 10);
}

static void init_lights()
{
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 1, 15, 5, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

static void set_material(int id)
{
    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.3, 0.3, 0.3, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 30;

    switch (id) {
        case 0:
            /* Difuzna komponenta se postavlja na crvenu */
            diffuse_coeffs[0] = 1.0;
            diffuse_coeffs[3] = 0.7;
            break;
        case 1:
            /* Difuzna komponenta se postavlja na zelenu */
            diffuse_coeffs[1] = 1.0;
            break;
        case 2:
            /* Difuzna komponenta se postavlja na plavu */
            diffuse_coeffs[2] = 1.0;
            break;
    }

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

}

static void on_display(void)
{
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(2, 5, 5, 0, 0, 0, 0, 1, 0);

    init_lights();

    /* Kreiraju se kocke */
    glPushMatrix();
        set_material(1);
        glTranslatef(- 0.5, 0, 0);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        set_material(2);
        glTranslatef(0.5, 0, 0);
        glutSolidCube(1);
    glPopMatrix();

    /* Kreira se sfera. */
    set_material(0);

    double clip_plane[] = {-1, 0, 0, animation_parameter};

    glClipPlane(GL_CLIP_PLANE0, clip_plane);
    glEnable(GL_CLIP_PLANE0);

    /* Da bismo garantovali korektno iscrtavanje
     * providne sfere, prvo iscrtavamo zadnji deo
     * (nalicja poligona) */

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glutSolidSphere(1.5, 64, 64);

    glCullFace(GL_BACK);
    glutSolidSphere(1.5, 64, 64);

    glDisable(GL_CULL_FACE);

    glDisable(GL_CLIP_PLANE0);

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
