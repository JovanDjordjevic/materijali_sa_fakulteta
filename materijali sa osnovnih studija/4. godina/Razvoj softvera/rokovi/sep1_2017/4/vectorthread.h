#ifndef VECTORTHREAD_H
#define VECTORTHREAD_H

#include <QThread>

class VectorThread : public QThread
{
    Q_OBJECT
public:
    VectorThread(QObject *parent, QString &filepath);

signals:
    void calculationFinished(double);

    // QThread interface
protected:
    void run() override;

private:
    QString m_filepath;

};

#endif // VECTORTHREAD_H
