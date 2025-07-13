#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class enemigos : public QObject
{
    Q_OBJECT
public:
    explicit enemigos(QObject *parent = nullptr);

signals:
};

#endif // ENEMIGOS_H
