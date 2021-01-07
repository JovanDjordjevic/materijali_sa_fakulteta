#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/* teksture */
GLubyte chimney_texture[3 * 4 * 4] = {
    0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,
    0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,
    0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,
    0xc8, 0x88, 0x88,   0xc8, 0x88, 0x88,   0xc8, 0x88, 0x88,   0xc8, 0x88, 0x88
};

/* Identifikatori tekstura. */
static GLuint names[1];

/* Konstanta pi. */
const static float pi = 3.141592653589793;

/* Dimenzije prozora */
static int window_width, window_height;

/* Funkcija initalize() vrsi OpenGL inicijalizaciju. */
static void initialize(void);

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
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    initialize();

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void initialize(void)
{
    /* Pozicija i boja svetla */
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Postavlja se boja pozadine. */
    glClearColor(0, 0, 0, 0);

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    /* Ukljucujemo koriscenje glColor definisanih boja za materijale */
    glEnable(GL_COLOR_MATERIAL);

    /*
     * Podesava se rezim iscrtavanja tekstura tako da boje na teksturi
     * se mnoze izracunatom bojom objekta.
     */
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
              GL_MODULATE);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(1, names);

    /* Kreira se prva tekstura. */
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, chimney_texture);

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Oslobadjaju se korisceni resursi i zavrsava se program. */
        glDeleteTextures(1, names);
        exit(0);
        break;
    }
}

static void on_reshape(int width, int height)
{
    /* Pamte se sirina i visina prozora. */
    window_width = width;
    window_height = height;

    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) width / height, 1, 25);
}

void draw_pipe_base()
{
    /* crtamo osnovu dimnjaka */
    glColor3f(0.6, 0.6, 0.55);
    glutSolidCube(1);
}

void draw_pipe(float height, float radius_top, float radius_bottom)
{
    /* crtamo dimnjak */
#define SEGMENTS 16

    /* postavljamo osnovnu boju objekta na belu */
    glColor3f(0.7, 0.7, 0.7);

    /* biramo teksturu sa kojom zelimo da radimo, i aktiviramo
     * iscrtavanje tekstura */
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glEnable(GL_TEXTURE_2D);

    int u = 0;
    float angle = 0;

    /* crtamo zarubljenu kupu */
    glBegin(GL_TRIANGLE_STRIP);
        for (u = 0; u <= SEGMENTS; u++) {
            angle = u * (2 * pi / SEGMENTS);

            /* definisemo normalu povrsi */
            glNormal3f(cos(angle), 0, sin(angle));

            /* definisemo koordinate tacaka - u prostoru i teksturi */
            glTexCoord2f(u / (float) SEGMENTS, 0);
            glVertex3f(radius_bottom * cos(angle), 0, radius_bottom * sin(angle));

            glTexCoord2f(u / (float) SEGMENTS, 1);
            glVertex3f(radius_top * cos(angle), height, radius_top * sin(angle));
        }
    glEnd();

    /* Iskljucujemo crtanje tekstura */
    glDisable(GL_TEXTURE_2D);

    draw_pipe_base();

#undef SEGMENTS
}

void draw_baloon()
{
    glColor3f(0.9, 0.5, 0.5);

    glPushMatrix();
       glTranslatef(1.5, 4, 0);
       glutSolidSphere(0.2, 10, 10);
       glTranslatef(0.1, 0, 0);
       glutSolidSphere(0.16, 10, 10);
    glPopMatrix();
}

static void on_display(void)
{
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Inicijalizuje se matrica transformacije. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6, 0, 7, 0, 0, 0, 0, 1, 0);

    GLfloat light_position[] = { 10, 1, 1, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    /* Primjenjuje se translacija koja ce centrirati scenu. */
    glTranslatef(-3, -2.5, 0);

    /* Crtaju se cevi. */
    glPushMatrix();
        glTranslatef(0, 1, 0);

        glPushMatrix();
            glTranslatef(3, 0, 0);
            draw_pipe(4, 0.2, 0.3);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(3, 0, -6);
            draw_pipe(4, 0.2, 0.3);
        glPopMatrix();

        draw_pipe(4, 0.2, 0.3);

        glPushMatrix();
            glTranslatef(0, 0, -6);
            draw_pipe(4, 0.2, 0.3);
        glPopMatrix();
    glPopMatrix();

    /* crtamo fabriku */
    glColor3f(0.5, 0.5, 0.5);

    glPushMatrix();
       glTranslatef(1.5, 0, -3);
       glScalef(3, 1, 4);
       glutSolidCube(2);
    glPopMatrix();

    /* crtamo balon */
    draw_baloon();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
