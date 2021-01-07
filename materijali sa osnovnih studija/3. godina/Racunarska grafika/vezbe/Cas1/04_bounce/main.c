#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 20

const static float size = 0.1;  /* Velicina kvadrata. */
static float x_curr, y_curr;    /* Tekuce koordinate centra kvadrata. */
static float v_x, v_y;          /* Komponente vektora brzine kretanja
                                 * kvadrata. */
static int animation_ongoing;   /* Fleg koji odredjuje da li je
                                 * animacija u toku. */

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);
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

    /* Registruju se funkcije za obradu dogadjaja. */
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);

    /* Inicijalizuje se seed za random brojeve */
    srand(time(NULL));

    /* Inicijalizuju se globalne promjenljive. Nasumicno postavljamo
     * pocetnu poziciju i pocenu brzinu */

//on ovde radi ovo ali posto nam treba broj izmedju 0 i 1 mogli
//smo samo rand/RAND_MAX, on ovde komplikuje jer hoce nesto sto je
//u pola slucajeva manje od 0 a u pola slucajeva vece od nule
    x_curr = -(1 - size / 2) + (2 - size) * rand() / (float) RAND_MAX;
    y_curr = -(1 - size / 2) + (2 - size) * rand() / (float) RAND_MAX;

    v_x = -size / 2 + size * rand() / (float) RAND_MAX;
    v_y = -size / 2 + size * rand() / (float) RAND_MAX;

    /* Na pocetku je animacija neaktivna */
    animation_ongoing = 0;

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);

    /* Ulazi se u glavnu petlju. */
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
    }
}

static void on_timer(int value)
{
    /*
     * Proverava se da li callback dolazi od odgovarajuceg tajmera.
     */
    if (value != TIMER_ID)
        return;

    /* Azuriraju se koordinate centra kvadrata. */
    x_curr += v_x;
    if (x_curr <= -(1 - size / 2) || x_curr >= 1 - size / 2) {
        v_x *= -1;
    }

    y_curr += v_y;
    if (y_curr <= -(1 - size / 2) || y_curr >= 1 - size / 2) {
        v_y *= -1;
    }

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}

static void on_display(void)
{
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Crta se kvadrat na odgovarajucoj poziciji. */
    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex3f(x_curr - size / 2, y_curr - size / 2, 0);
        glVertex3f(x_curr + size / 2, y_curr - size / 2, 0);
        glVertex3f(x_curr + size / 2, y_curr + size / 2, 0);
        glVertex3f(x_curr - size / 2, y_curr + size / 2, 0);
    glEnd();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
