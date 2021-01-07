#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define GLubyte_SIZE (sizeof(GLubyte))
#define GLubyte_SIZE_IN_BITS (sizeof(GLubyte) * 8)

/* Bitmapa */
GLubyte * rasters;

/* Broj znakova */
static int char_count;

/* Sirina i visina jednog znaka */
static int char_width, char_height;

void init(void)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

/*
 * Funkcija cita niz bitmapa sa standardnog ulaza u sledecem formatu:
 * 1. Meta-podaci
 * broj bitmapa, sirina svake bitmape, visina svake bitmape
 * (bitmape moraju biti isth dimenzija)
 * 2. Podaci
 * Ucitava se bit po bit, '#' i '1' predstavljaju jedinicu, dok
 * '.' i '0' predstavljaju nulu. Ostali znaci se ignorisu.
 */
void read_data()
{
    int array_size;

    /* Ucitavamo broj znakova, sirinu i visinu svakog znaka */
    scanf("%d %d %d", &char_count, &char_width, &char_height);

    /* Pravimo niz bajtova u koji smestamo bitmapu */
    array_size = char_count * char_width * char_height / GLubyte_SIZE_IN_BITS;
    rasters = (GLubyte *) malloc ( array_size * GLubyte_SIZE );

    /* U byte promenljivoj gradimo bajt bitmape koji trenutno citamo */
    GLubyte byte = 0;

    /* Redni broj bita u aktuelnom bajtu koji citamo */
    short reading_bit = 0;

    /* Redni broj bajta koji citamo */
    short reading_byte = 0;

    /* Znak koji je procitan sa standardnog ulaza */
    int read_char;

    /* Pocinjemo sa citanjem fajla */
    while((read_char = getchar()) != EOF) {
        switch (read_char) {
            case '#':
            case '1':
                /* Ukoliko smo procitali '#' ili '1',
                 * siftujemo byte za jedno mesto u levo
                 * i poslednnji bit postavljamo na jedan
                 */
                byte <<= 1;
                byte |= 1;
                reading_bit++;
                break;
            case '.':
            case '0':
                /* Ukoliko smo procitali '.' ili '0',
                 * siftujemo byte za jedno mesto u levo
                 * i poslednnji bit ostavljamo na nuli
                 */
                byte <<= 1;
                reading_bit++;
                break;
        }

        /* Ako smo vec procitali ceo bajt bitmape, pamtimo ga u niz,
         * povecavamo indeks bajta koji citamo za jedan, i
         * resetujemo ostale promenljive */
        if (reading_bit == GLubyte_SIZE_IN_BITS) {
            printf("Citamo bajt: %d vrednost: %d\n", reading_byte, byte);
            rasters[reading_byte++] = byte;
            reading_bit = 0;
            byte = 0;
        }
    }
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
        glBitmap(16, 12, 0.0, 0.0, 16.0, 0.0, rasters + 24 * i /* + 12 */);
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
    read_data();

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
