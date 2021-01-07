#include <math.h>
#include <GL/glut.h>

/* Deklaracije callback funkcija. */
static void onDisplay(void);
static void onKeyboard(unsigned char key, int x, int y);
static void onTimer(int id);

/* Deklaracija funkcija za crtanje */
static void drawInRay();
static void drawOutRay();
static void drawTriangleBackground();
static void drawTriangleLight();
static void drawTriangleLine();

/* Fleg koji odredjuje da li je animacija pokrenuta */
static int animationOngoing = 0;

/* Parametar animacije */
static float animationParameter = -1.0;

/* definisemo ivicu i visinu trougla */
static float side;
static float height;

#define TIMER_INTERVAL 10
#define TIMER_ID 1

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se funkcije za obradu dogadjaja. */
    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(onKeyboard);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);

    /* Inicijalizaicja promenljivih */
    side = 0.7;
    height = side * sqrt(3) / 2.0;

    /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void onDisplay(void)
{
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Definisemo dodatnu ravan odsecanja */
    double clipPlane[] = { -1, 0, 0, animationParameter };
    glClipPlane(GL_CLIP_PLANE0, clipPlane);

    /* Crtamo delove scene */
    glEnable(GL_CLIP_PLANE0);
    drawInRay();
    drawOutRay();
    glDisable(GL_CLIP_PLANE0);

    drawTriangleBackground();

    glEnable(GL_CLIP_PLANE0);
    drawTriangleLight();
    glDisable(GL_CLIP_PLANE0);

    drawTriangleLine();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

static void onKeyboard(unsigned char key, int x, int y)
{
    switch (key) {
        /* Izlazimo iz programa (Esc) */
        case 27:
            exit(0);
            break;

        /* pokrecemo animaciju */
        case 'g':
            animationOngoing = 1;
            glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
            break;

        /* resetujemo animaciju */
        case 'r':
            animationParameter = -1;
            glutPostRedisplay();
            // break;

        /* zaustavljamo animaciju */
        case 's':
            animationOngoing = 0;
            break;

    }
}

static void onTimer(int id)
{
    if (id != TIMER_ID) {
        return;
    }

    animationParameter += 0.01;

    glutPostRedisplay();

    if (animationOngoing) {
        glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
    }
}

static void drawInRay()
{
    glColor3f(1, 1, 1);
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2f( 0, 0.05);
        glVertex2f(-1, -0.2);
    glEnd();
}

/* Crta izlazne zrake, prelomljene kroz prizmu */

static void drawOutRay()
{
    int i = 0;

    /* Ukljucujemo iscrtavanje poligona sa popunom */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);
        /* Crtamo sest razlicitih nijansi */
        for (i = 0; i < 6; i++) {

            /* Podesavamo boju popune na osnovu rednog broja zraka */
            switch (i) {
                case 0:
                    glColor3f(.9, 0, 0);
                    break;
                case 1:
                    glColor3f(.7, .5, 0);
                    break;
                case 2:
                    glColor3f(.7, .7, 0);
                    break;
                case 3:
                    glColor3f(.3, .7, 0);
                    break;
                case 4:
                    glColor3f(0, .6, .6);
                    break;
                case 5:
                    glColor3f(.5, 0, .4);
                    break;
            }

            /* crtamo trougao koji predstavlja izlazni zrak */
            glVertex2f(0, 0.05);
            glVertex2f(1, -0.2 - 0.05 * i);
            glVertex2f(1, -0.2 - 0.05 * 6);
        }
    glEnd();
}

static void drawTriangleBackground()
{
    /* ukljucujemo iscrtavanje sa popunom */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);
        /* iscrtavamo skoro crnu popunu glavnog trougla
         * preko prethodno nacrtanih zraka */
        glColor3f(0.2, 0.2, 0.2);

        glVertex2f(0, 1.0 / 2.0 * height);
        glVertex2f(side / 2.0, - 1.0 / 2.0 * height);
        glVertex2f(-side / 2.0, - 1.0 / 2.0 * height);
    glEnd();
}

static void drawTriangleLight()
{
    glBegin(GL_TRIANGLES);
        /* iscrtavamo trougao koji predstavlja prelomljenu
         * svetlost unutar prizme */
        glColor3f(0.9, 0.9, 0.9);
        glVertex2f(- side / 4.0, 0);

        glColor3f(0.2, 0.2, 0.2);
        glVertex2f(side / 4.0, 0);
        glVertex2f(side * 0.32, -0.07);
    glEnd();
}

static void drawTriangleLine()
{
    /* Ukljucujemo iscrtavanje linija poligona umesto popune */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_TRIANGLES);
        /* crtamo skoro beli trougao koji predstavlja prizmu */
        glColor3f(0.9, 0.9, 0.9);

        glVertex2f(0, 1.0 / 2.0 * height);
        glVertex2f(side / 2.0, - 1.0 / 2.0 * height);
        glVertex2f(-side / 2.0, - 1.0 / 2.0 * height);

    glEnd();
}

