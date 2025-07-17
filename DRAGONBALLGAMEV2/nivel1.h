#ifndef NIVEL1_H
#define NIVEL1_H

#include <QGraphicsScene>
#include "goku.h"
#include "enemigo.h"

class Nivel1 : public QGraphicsScene
{
    Q_OBJECT
public:
    Nivel1(int width, int height, QObject* parent = nullptr);

signals:
    void enemigoEliminado();

private:
    void configurarEscena(int width, int height);

    goku* m_goku;
    Enemigo* m_enemigo;
    QTimer* m_colisionTimer;

    const int m_distanciaDano = 50;
};

#endif // NIVEL1_H
