#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/* Deklaracije callback funkcija. */
static void on_display(void);

/* Deklaracija funkcija za crtanje */
static void drawInRay();
static void drawOutRay();
static void drawTriangle();

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
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);

    /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_display(void)
{
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Crtamo delove scene */
    drawInRay();
    drawOutRay();
    drawTriangle();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

/* Crta ulazni beli zrak */

static void drawInRay()
{
    glColor3f(1, 1, 1);
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2f(0, 0.05);
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

static void drawTriangle()
{
    /* definisemo ivicu i visinu trougla */
    float side = 0.7;
    float height = side * sqrt(3) / 2.0;  //a koren iz tri sa dva

    /* ukljucujemo iscrtavanje sa popunom */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);
        /* iscrtavamo skoro crnu popunu glavnog trougla
         * preko prethodno nacrtanih zraka */
        glColor3f(0.1, 0.1, 0.1);

        glVertex2f(0, 1.0 / 2.0 * height);   //sbugde gde je 1/2h izgleda da je moglo i samo h/2 dobije se ista slika (?)
        glVertex2f(side / 2.0, - 1.0 / 2.0 * height);
        glVertex2f(-side / 2.0, - 1.0 / 2.0 * height);

        /* iscrtavamo trougao koji predstavlja prelomljenu
         * svetlost unutar prizme */
        glColor3f(0.9, 0.9, 0.9);
        glVertex2f(- side / 4.0, 0);   //generalno ne kapiram odakle mu ovi brojevi svi, kako se do njih doslo

        glColor3f(0.2, 0.2, 0.2);
        glVertex2f(side / 4.0, 0);
        glVertex2f(side * 0.32, -0.07);

    glEnd();

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

