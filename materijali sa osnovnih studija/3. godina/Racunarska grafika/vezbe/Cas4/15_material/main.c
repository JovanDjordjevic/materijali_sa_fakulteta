#include <stdlib.h>
#include <GL/glut.h>

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char **argv)
{
    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0, 0, 0, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 1, 1, 1, 1 };

    /* Ambijentalno osvetljenje scene. */
    GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };

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
    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

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
    gluPerspective(30, (float) width / height, 1, 100);
}

static void on_display(void)
{
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 1, 1, 1, 0 };

    /* Nulti koeficijenti refleksije materijala. */
    GLfloat no_material[] = { 0, 0, 0, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat material_ambient[] = { 0.7, 0.7, 0.7, 1 };

    /* Koeficijenti ambijentalne refleksije materijala za slucaj
       nehomogene ambijentalne refleksije. */
    GLfloat material_ambient_heterogeneous[] = { 0.8, 0.8, 0.2, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat material_diffuse[] = { 0.1, 0.5, 0.8, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat material_specular[] = { 1, 1, 1, 1 };

    /* Koeficijent spekularne refleksije za slucaj kada nema spekularne refleksije. */
    GLfloat no_shininess[] = { 0 };

    /* Koeficijent spekularne refleksije za slucaj male vrednosti koeficijenta. */
    GLfloat low_shininess[] = { 5 };

    /* Koeficijent spekularne refleksije za slucaj velike vrednosti koeficijenta. */
    GLfloat high_shininess[] = { 100 };

    /* Emisiona boja materijala. */
    GLfloat material_emission[] = { 0.3, 0.2, 0.2, 0 };

    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);

    /* Pozicionira se svijetlo. */
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    /*
     * Kreira se sfera u prvoj koloni prvog reda samo sa difuznom
     * refleksijom. bez ambijentalne ili spekularne refleksije.
     */
    glPushMatrix();
        glTranslatef(-3.75, 3, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_material);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_material);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u drugoj koloni prvog reda sa difuznom i
     * spekularnom refleksijom i malim koeficijentom spekularne
     * refleksije, bez ambijentalne refleksije.
     */
    glPushMatrix();
        glTranslatef(-1.25, 3, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_material);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u trecoj koloni prvog reda sa difuznom i
     * spekularnom refleksijom i visokim koeficijentom spekularne
     * refleksije, bez ambijentalne refleksije.
     */
    glPushMatrix();
        glTranslatef(1.25, 3, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_material);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u cetvrtoj koloni prvog reda sa difuznom
     * refleksijom i emisionom bojom, bez ambijentalne ili spekularne
     * refleksije.
     */
    glPushMatrix();
        glTranslatef(3.75, 3, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_material);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_material);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u prvoj koloni drugog reda sa ambijentalnom i
     * difuznom refleksijom, bez spekularne refleksije.
     */
    glPushMatrix();
        glTranslatef(-3.75, 0, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_material);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u drugoj koloni drugog reda sa ambijentalnom,
     * difuznom i spekularnom refleksijom i malim koeficijentom
     * spekularne refleksije.
     */
    glPushMatrix();
        glTranslatef(-1.25, 0, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u trecoj koloni drugog reda sa ambijentalnom,
     * difuznom i spekularnom refleksijom i visokim koeficijentom
     * spekularne refleksije.
     */
    glPushMatrix();
        glTranslatef(1.25, 0, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u cetvrtoj koloni drugog reda sa ambijentalnom i
     * difuznom refleksijom i emisionom bojom, bez spekularne refleksije.
     */
    glPushMatrix();
        glTranslatef(3.75, 0, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_material);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u prvoj koloni treceg reda sa nehomogenom
     * ambijentalnom i difuznom refleksijom, bez spekularne refleksije.
     */
    glPushMatrix();
        glTranslatef(-3.75, -3, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_heterogeneous);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_material);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u drugoj koloni treceg reda sa nehomogenom
     * ambijentalnom, difuznom i spekularnom refleksijom i malim
     * koeficijentom spekularne refleksije.
     */
    glPushMatrix();
        glTranslatef(-1.25, -3, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_heterogeneous);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u trecoj koloni treceg reda sa nehomogenom
     * ambijentalnom, difuznom i spekularnom refleksijom i visokim
     * koeficijentom spekularne refleksije.
     */
    glPushMatrix();
        glTranslatef(1.25, -3, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_heterogeneous);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /*
     * Kreira se sfera u cetvrtoj koloni treceg reda sa nehomogenom
     * ambijentalnom i difuznom refleksijom i emisionom bojom, bez
     * spekularne refleksije.
     */
    glPushMatrix();
        glTranslatef(3.75, -3, 0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_heterogeneous);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_material);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
