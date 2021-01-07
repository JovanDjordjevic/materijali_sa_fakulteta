#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QMainWindow>
#include <QSlider>
#include <QToolButton>
#include <QVBoxLayout>

#include "DisplayWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFrame * window = new QFrame();

    QVBoxLayout * mainLayout  = new QVBoxLayout(window);
    QHBoxLayout * panelLayout = new QHBoxLayout(window);

    QSlider     * sliderAnimation = new QSlider(Qt::Horizontal, window);
    QSlider     * sliderRotation  = new QSlider(Qt::Horizontal, window);

    QToolButton * buttonPlay  = new QToolButton(window);
    QToolButton * buttonStop  = new QToolButton(window);
    QLabel      * title       = new QLabel(window);
    QLabel      * labelRotate = new QLabel(window);

    DisplayWidget * display  = new DisplayWidget(window);

    display->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    panelLayout->addWidget(buttonPlay);
    panelLayout->addWidget(buttonStop);
    panelLayout->addWidget(sliderAnimation);
    panelLayout->addWidget(labelRotate);
    panelLayout->addWidget(sliderRotation);

    mainLayout->addWidget(title);
    mainLayout->addWidget(display);
    mainLayout->addLayout(panelLayout);
    window->setLayout(mainLayout);

    sliderAnimation->setRange(0, 100);
    sliderAnimation->setSingleStep(5);

    sliderRotation->setRange(0, 100);
    sliderRotation->setValue(50);
    sliderRotation->setSingleStep(5);

    buttonPlay->setIcon(QIcon::fromTheme("media-playback-start"));
    buttonStop->setIcon(QIcon::fromTheme("media-playback-stop"));
    title->setText("Pink Floyd - Dark Side of the Moon");
    labelRotate->setText("rotation:");

    QObject::connect(
            sliderRotation, SIGNAL(valueChanged(int)),
            display, SLOT(setRotationParameter(int))
            );
    QObject::connect(
            sliderAnimation, SIGNAL(valueChanged(int)),
            display, SLOT(setAnimationParameter(int))
            );
    QObject::connect(
            display, SIGNAL(animationParameterChanged(int)),
            sliderAnimation, SLOT(setValue(int))
            );

    QObject::connect(
            buttonPlay, SIGNAL(clicked()),
            display, SLOT(startAnimation())
            );
    QObject::connect(
            buttonStop, SIGNAL(clicked()),
            display, SLOT(stopAnimation())
            );

    window->setStyleSheet("                \
            .QToolButton { border: none; } \
            .QFrame { background: black; } \
            .QLabel { color: white; }      \
            ");

    window->show();

    return app.exec();
}
