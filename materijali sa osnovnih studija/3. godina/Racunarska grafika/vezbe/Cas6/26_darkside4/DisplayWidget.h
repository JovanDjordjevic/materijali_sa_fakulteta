
#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QGLWidget>
#include <QList>
#include <QTimer>

#include "Model.h"

class DisplayWidget : public QGLWidget
{
    Q_OBJECT

public:
    DisplayWidget(QWidget * parent = nullptr);
    ~DisplayWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void addModel(char * filename, int mode);

public slots:
    void setAnimationParameter(int value);
    void setRotationParameter(int value);
    void startAnimation();
    void stopAnimation();
    void timeout();

signals:
    void animationParameterChanged(int value);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    int animationParameter;
    int rotationParameter;

    Model * prism;
    Model * prism_wire;

    QList < Model * > rays;
    QTimer timer;

};

#endif
