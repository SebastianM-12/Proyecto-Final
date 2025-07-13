#ifndef NIVEL1_H
#define NIVEL1_H

#include <QGraphicsScene>

class Nivel1 : public QGraphicsScene
{
    Q_OBJECT
public:
    Nivel1(int width, int height, QObject* parent = nullptr);
};

#endif // NIVEL1_H
