#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/* Fleg koji odredjuje polozaj svetla. */
static int headlight = 0;

/* Konstanta pi. */
const static float pi = 3.141592653589793;

/* Uglovi u sfernom koordinatnom sistemu koji
   odredjuju polozaj vidne tacke. */
static float phi, theta;

/* Inkrementi gornjih uglova. */
static float delta_phi, delta_theta;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char **argv)
{
    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.3, 0.7, 0.3, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.2, 1, 0.2, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 30;

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

    /* Incijalizuju se globalne promjenljive. */
    phi = 0;
    theta = pi / 4;
    delta_phi = delta_theta = pi / 90;

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

    /* Postavljaju se svojstva prvog svetla */
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Postavljaju se svojstva materijala */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

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

    case 'h':
    case 'H':
        /* Invertuje se fleg koji odredjuje pozicioniranje svetla. */
        headlight = !headlight;
        glutPostRedisplay();
        break;

    case 'p':
        /* Dekrementira se ugao phi i ponovo iscrtava scena. */
        phi -= delta_phi;
        if (phi > 2 * pi) {
            phi -= 2 * pi;
        } else if (phi < 0) {
            phi += 2 * pi;
        }
        glutPostRedisplay();
        break;

    case 'P':
        /* Inkrementira se ugao phi i ponovo iscrtava scena. */
        phi += delta_phi;
        if (phi > 2 * pi) {
            phi -= 2 * pi;
        } else if (phi < 0) {
            phi += 2 * pi;
        }
        glutPostRedisplay();
        break;

    case 'r':
    case 'R':
        /* Resetuju se uglovi phi i theta na pocetne vrednosti. */
        phi = theta = 0;
        glutPostRedisplay();
        break;

    case 't':
        /*
         * Dekrementira se ugao theta i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [-89,89] stepeni.
         */
        theta -= delta_theta;
        if (theta < -(pi / 2 - pi / 180)) {
            theta = -(pi / 2 - pi / 180);
        }
        glutPostRedisplay();
        break;

    case 'T':
        /*
         * Inkrementira se ugao theta i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [-89,89] stepeni.
         */
        theta += delta_theta;
        if (theta > pi / 2 - pi / 180) {
            theta = pi / 2 - pi / 180;
        }
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
    /* Pozicija svetla (u pitanju je tackasto svetlo). */
    GLfloat light_position[] = { 0, 0, 0, 1 };

    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Inicijalizuje se matrica transformacije. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*
     * Ako se svetlo postavlja zajedno sa vidnom tackom, pozicija
     * svetla se zadaje na ovom mjestu.
     */
    if (headlight) {
        light_position[0] = 0;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    }

    /* Postavljaju se vidni parametri. */
    gluLookAt(5 * cos(theta) * cos(phi), 5 * cos(theta) * sin(phi),
              5 * sin(theta), 0, 0, 0, 0, 0, 1);

    /*
     * Ako se svetlo ne postavlja zajedno sa vidnom tackom, pozicija
     * svetla se zadaje na ovom mestu.
     */
    if (!headlight) {
        light_position[0] = 5;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    }

    /* Kreira se objekat. */
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0.8, 0);
    glutSolidTeapot(1);

    glScalef(1, -1, 1);
    glTranslatef(0, 1.6, 0);
    glutSolidTeapot(1);

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
