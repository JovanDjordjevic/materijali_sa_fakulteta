#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/* Definisemo granice parametara povrsi */
#define U_FROM -50
#define V_FROM -50
#define U_TO 50
#define V_TO 50

/* Definisemo osobine tajmera */
#define TIMER_INTERVAL 10
#define TIMER_ID 0

/* Definisemo makro koji vraca maksimalnu vrednost */
#define max(A, B) (((A) > (B)) ? (A) : (B))

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int);

static float t;                 /* Proteklo vreme */
static int animation_ongoing;   /* Fleg koji odredjuje da li je
                                 * animacija u toku. */
static int active_function;     /* identifikator aktuelne funkcije */

int main(int argc, char **argv)
{
    /* Inicijalizacija promenljivih */
    t = 0;
    animation_ongoing = 0;
    active_function = 0;

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

    case 'g':
    case 'G':
        /* Pokrece se animacija. */
        if (!animation_ongoing) {
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            animation_ongoing = 1;
        }
        break;

    case 's':
    case 'S':
        /* Zaustavlja se animacija. */
        animation_ongoing = 0;
        break;

    case 'r':
    case 'R':
        /* Resetuje se proteklo vreme */
        t = 0;
        glutPostRedisplay();
        break;

    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        /* Aktivira se jedna od funkcija u zavisnosti od
         * pritisnutog tastera */
        active_function = key - '0';
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

static void on_timer(int value)
{
    /*
     * Proverava se da li callback dolazi od odgovarajuceg tajmera.
     */
    if (value != TIMER_ID) return;

    t += 10;

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}

/* Izracunava vrednost funkcije za parametre u i v */
float function(float u, float v)
{
    switch (active_function) {
    case 1:
        return 5 * sin((t + u * v) / 150);

    case 2:
        return 5 * sin((- t + u*u + v*v) / 150);

    case 3:
        {
            float parameter = (u*u + v*v + t) / 150 ;
            return 5 * sin(parameter) * exp(2 - parameter / 10);
        }

    case 4:
        return 5 * sin((t + u*u + v*v) / 20);

    case 5:
        return abs(u + v) / 10.0 * sin(t / 50);

    default:
        return 0;

    }
}

/* Postavlja normalu i kordinate verteksa za tacku sa pparametrima
 * u i v */
void set_vertex_and_normal(float u, float v)
{
    float diff_u, diff_v;

    /* Racunamo priblizne vrednosti izvoda funkcije u tacki u, v */
    diff_u = (function(u + 1, v) - function(u - 1, v)) / 2.0;
    diff_v = (function(u, v + 1) - function(u, v - 1)) / 2.0;

    /* Postavljamo normalu - vektor normalan na tangentnu ravan */
    /* Racuna se priblizan vektor normale: */
    glNormal3f(-diff_u, 1, -diff_v);

    /* Racuna se priblizan vektor normale.
     * Primenom sinusa se postize efekat presijavanja
     */
    glNormal3f(sin(-diff_u), 1, sin(-diff_v));

    /* Postavljamo verteks */
    glVertex3f(u, 0, v);
}

/* Crtamo funkciju */
void plot_function()
{
    float scale;
    int u, v;

    glPushMatrix();

    /* Racunamo faktor skaliranja tako da cela funkcija bude prikazana */
    scale = 2.0 / max( U_TO - U_FROM, V_TO - V_FROM );
    glScalef(scale, scale, scale);

    /* Crtamo funkciju strip po strip */
    for (u = U_FROM; u < U_TO; u++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (v = V_FROM; v <= V_TO; v++) {
            set_vertex_and_normal(u, v);
            set_vertex_and_normal(u + 1, v);
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
    GLfloat diffuse_coeffs[] = { 0.2, 0.2, 1, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 0, 0, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 30;

    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 2, 2, 0, 0, 0, 0, 1, 0);

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
    plot_function();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

