
#include <QtGui>
#include <QtOpenGL>

#include <GL/glu.h>

#include "DisplayWidget.h"

DisplayWidget::DisplayWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
      animationParameter(0), rotationParameter(50)
{
    rays << new Model("models/in_ray.model", GL_FILL)
         << new Model("models/mid_ray.model", GL_FILL)
         << new Model("models/out_ray_1.model", GL_FILL)
         << new Model("models/out_ray_2.model", GL_FILL)
         << new Model("models/out_ray_3.model", GL_FILL)
         << new Model("models/out_ray_4.model", GL_FILL)
         << new Model("models/out_ray_5.model", GL_FILL)
         << new Model("models/out_ray_6.model", GL_FILL);

    prism = new Model("models/prism.model", GL_FILL);
    prism_wire = new Model("models/prism_wire.model", GL_LINE);
}

DisplayWidget::~DisplayWidget()
{
    // delete ...
}

QSize DisplayWidget::minimumSizeHint() const
{
    return QSize(500, 500);
}

QSize DisplayWidget::sizeHint() const
{
    return QSize(400, 400);
}

void DisplayWidget::setRotationParameter(int value)
{
    if (value >= 100) {
        value = 100;
    }

    if (rotationParameter == value)
        return;

    rotationParameter = value;
    updateGL();
}

void DisplayWidget::setAnimationParameter(int value)
{
    if (value >= 100) {
        timer.stop();
        value = 100;
    }

    if (animationParameter == value)
        return;

    animationParameter = value;
    updateGL();

    emit animationParameterChanged(value);
}

void DisplayWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(3);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    connect(&timer, SIGNAL(timeout()),
            this, SLOT(timeout()));
}

void DisplayWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(2, 2, 5, 0, 0, 0, 0, 1, 0);

    glRotatef(rotationParameter / 2.0 - 45, 0, 1, 0);

    GLdouble location = (animationParameter * 1.6 / 50.0) - 1.6;

    GLdouble clip_plane[] = { -1, 0, 0, location };

    prism_wire->draw();

    glEnable(GL_CLIP_PLANE0);
    glClipPlane(GL_CLIP_PLANE0, clip_plane);

    foreach (Model * model, rays) {
        model->draw();
    }

    glDisable(GL_CLIP_PLANE0);

    prism->draw();
    prism_wire->draw();

}

void DisplayWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, width / (float) height, 1, 100);

}

void DisplayWidget::startAnimation()
{
    timer.start(20);
}

void DisplayWidget::stopAnimation()
{
    timer.stop();
}

void DisplayWidget::timeout()
{
    setAnimationParameter(animationParameter + 1);
}
